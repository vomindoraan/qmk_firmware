/*
Copyright 2019 Maarten Dekkers <maartenwut@gmail.com>

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
#include "wasdat.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	matrix_init_user();
	led_init_ports();
};

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)
	matrix_scan_user();
};

void led_init_ports(void) {
    // * Set our LED pins as output
    setPinOutput(B0);
    setPinOutput(B1);
    setPinOutput(B2);
}

void led_set_kb(uint8_t usb_led) {
	if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // Turn capslock led on
        writePinLow(B0);
    } else {
        // Turn capslock led off
        writePinHigh(B0);
    } 
	
	if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        // Turn scrollock led on
        writePinLow(B1);
    } else {
        // Turn scrollock led off
        writePinHigh(B1);
	}
	
	if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        // Turn numlock led on
        writePinLow(B2);
    } else {
        // Turn numlock led off
        writePinHigh(B2);
	}
    led_set_user(usb_led);
}
