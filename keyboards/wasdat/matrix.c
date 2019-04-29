/*
Copyright 2012-2018 Jun Wako, Jack Humbert, Yiancar

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"

#if (MATRIX_COLS <= 8)
#    define print_matrix_header()  print("\nr/c 01234567\n")
#    define print_matrix_row(row)  print_bin_reverse8(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop(matrix[i])
#    define ROW_SHIFTER ((uint8_t)1)
#elif (MATRIX_COLS <= 16)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse16(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop16(matrix[i])
#    define ROW_SHIFTER ((uint16_t)1)
#elif (MATRIX_COLS <= 32)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse32(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop32(matrix[i])
#    define ROW_SHIFTER  ((uint32_t)1)
#endif

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

/* matrix state(1:on, 0:off) */
static matrix_row_t raw_matrix[MATRIX_ROWS];

static matrix_row_t matrix[MATRIX_ROWS];

static void init_rows(void);
static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col);
static void unselect_cols(void);
static void select_col(uint8_t col);

__attribute__ ((weak))
void matrix_init_quantum(void) {
    matrix_init_kb();
}

__attribute__ ((weak))
void matrix_scan_quantum(void) {
    matrix_scan_kb();
}

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

inline
uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}

void matrix_init(void) {

    // initialize row and col
    unselect_cols();
    init_rows();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i] = 0;
    }
    debounce_init(MATRIX_ROWS);

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
  bool changed = false;
  // Set col, read rows
  for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
    changed |= read_rows_on_col(raw_matrix, current_col);
  }

  debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

  matrix_scan_quantum();
  return 1;
}

bool matrix_is_modified(void)
{
    if (debounce_active()) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print_matrix_header();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        print_matrix_row(row);
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += matrix_bitpop(i);
    }
    return count;
}

static void init_rows(void)
{
    for(uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh(row_pins[x]);
    }
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col)
{
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    wait_us(30);

    // For each row...
    for(uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++)
    {

        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        // Check row pin state
        if (readPin(row_pins[row_index]) == 0)
        {
            // Pin LO, set col bit
            current_matrix[row_index] |= (ROW_SHIFTER << current_col);
        }
        else
        {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~(ROW_SHIFTER << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[row_index]) && !(matrix_changed))
        {
            matrix_changed = true;
        }
    }

    // Unselect col
    unselect_cols();

    return matrix_changed;
}

/* Cols 0 - 15
 * col 0: C7
 * col 1:  B6
 * col 2: C6
 * col 3:  B4
 * col 4:  B5
 * col 5:   D7
 * These columns use a 74HC237D 3 to 8 bit demultiplexer.
 *                A0   A1   A2
 * col / pin:    PD2  PD1  PD0
 * 6:             1    1    1
 * 7:             0    1    1
 * 8:             1    0    1
 * 9:             0    0    1
 * 10:            1    1    0
 * 11:            0    1    0
 * 12:            1    0    0
 * col 13:  D3
 * col 14:  B7
 * col 15:  B3
 */
static void select_col(uint8_t col)
{
    switch (col) {
        case 0:
            PORTC &= ~(1<<7); // LO
            break;
        case 1:
            PORTB &= ~(1<<6); // LO
            break;
        case 2:
            PORTC &= ~(1<<6); // LO
            break;
        case 3:
            PORTB &= ~(1<<4); // LO
            break;
        case 4:
            PORTB &= ~(1<<5); // LO
            break;
        case 5:
            PORTD &= ~(1<<7); // LO
            break;
        case 6:
            PORTD |= (1<<0); // HI
            PORTD |= (1<<1); // HI
            PORTD |= (1<<2); // HI
            break;
        case 7:
            PORTD |= (1<<0); // HI
            PORTD |= (1<<1); // HI
            break;
        case 8:
            PORTD |= (1<<0); // HI
            PORTD |= (1<<2); // HI
            break;
        case 9:
            PORTD |= (1<<0); // HI
            break;
        case 10:
            PORTD |= (1<<1); // HI
            PORTD |= (1<<2); // HI
            break;
        case 11:
            PORTD |= (1<<1); // HI
            break;
        case 12:
            PORTD |= (1<<2); // HI
            break;
        case 13:
            PORTD &= ~(1<<3); // LO
            break;
        case 14:
            PORTB &= ~(1<<7); // LO
            break;
        case 15:
            PORTB &= ~(1<<3); // LO
            break;
    }
}

static void unselect_cols(void)
{
	//Native
    DDRD  |= (1<<7) | (1<<3); // OUT
    PORTD |= ((1<<7) | (1<<3)); // HI
	
    DDRC  |= (1<<7) | (1<<6); // OUT
    PORTC |= ((1<<7) | (1<<6)); // HI
	
    DDRB  |= (1<<6) | (1<<4) | (1<<5) | (1<<7) | (1<<3); // OUT
    PORTB |= ((1<<6) | (1<<4) | (1<<5) | (1<<7) | (1<<3)); // HI
	
	//Demultiplexer
    DDRD  |= (1<<0) | (1<<1) | (1<<2); // OUT
    PORTD &= ~((1<<0) | (1<<1) | (1<<2)); // LO
}