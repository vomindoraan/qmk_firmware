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
#pragma once

#include "quantum.h"

// readability
#define XXX KC_NO

// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array

#define LAYOUT_104( \
	k05,      k44, k42, k32, k02, k21, k0a, k3e, k4e, k4d, k2d, k0d, k7d,   k23, k53, k51,                       \
	k45, k25, k24, k22, k20, k40, k48, k28, k2a, k2e, k2f, k4f, k4a, k3d,   k47, k4c, k46,   k69, k67, k66, k76, \
	k35, k55, k54, k52, k50, k30, k38, k58, k5a, k5e, k5f, k3f, k3a, k1d,   k49, k2c, k26,   k59, k57, k56, k5c, \
	k34, k15, k14, k12, k10, k00, k08, k18, k1a, k1e, k1f, k0f,      k6d,                    k39, k37, k36,      \
	k3b, k04, k65, k64, k62, k60, k70, k78, k68, k6a, k6e, k7f,      k1b,        k0c,        k19, k17, k16, k1c, \
	k41, k31, k03,                k09,                k73, k11, k33, k61,   k7c, k79, k77,   k07,      k06       \
) \
{ \
	{k00, XXX, k02, k03, k04, k05, k06, k07, k08, k09, k0a, XXX, k0c, k0d, XXX, k0f}, \
	{k10, k11, k12, XXX, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f}, \
	{k20, k21, k22, k23, k24, k25, k26, XXX, k28, XXX, k2a, XXX, k2c, k2d, k2e, k2f}, \
	{k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3d, k3e, k3f}, \
	{k40, k41, k42, XXX, k44, k45, k46, k47, k48, k49, k4a, XXX, k4c, k4d, k4e, k4f}, \
	{k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5a, XXX, k5c, XXX, k5e, k5f}, \
	{k60, k61, k62, XXX, k64, k65, k66, k67, k68, k69, k6a, XXX, XXX, k6d, k6e, XXX}, \
	{k70, XXX, XXX, k73, XXX, XXX, k76, k77, k78, k79, XXX, XXX, k7c, k7d, XXX, k7f}  \
}

#define LAYOUT_TKL( \
	k05,      k44, k42, k32, k02, k21, k0a, k3e, k4e, k4d, k2d, k0d, k7d,   k23, k53, k51, \
	k45, k25, k24, k22, k20, k40, k48, k28, k2a, k2e, k2f, k4f, k4a, k3d,   k47, k4c, k46, \
	k35, k55, k54, k52, k50, k30, k38, k58, k5a, k5e, k5f, k3f, k3a, k1d,   k49, k2c, k26, \
	k34, k15, k14, k12, k10, k00, k08, k18, k1a, k1e, k1f, k0f,      k6d,                  \
	k3b, k04, k65, k64, k62, k60, k70, k78, k68, k6a, k6e, k7f,      k1b,        k0c,      \
	k41, k31, k03,                k09,                k73, k11, k33, k61,   k7c, k79, k77  \
) \
{ \
	{k00, XXX, k02, k03, k04, k05, XXX, XXX, k08, k09, k0a, XXX, k0c, k0d, XXX, k0f}, \
	{k10, k11, k12, XXX, k14, k15, XXX, XXX, k18, XXX, k1a, k1b, XXX, k1d, k1e, k1f}, \
	{k20, k21, k22, k23, k24, k25, k26, XXX, k28, XXX, k2a, XXX, k2c, k2d, k2e, k2f}, \
	{k30, k31, k32, k33, k34, k35, XXX, XXX, k38, XXX, k3a, k3b, XXX, k3d, k3e, k3f}, \
	{k40, k41, k42, XXX, k44, k45, k46, k47, k48, k49, k4a, XXX, k4c, k4d, k4e, k4f}, \
	{k50, k51, k52, k53, k54, k55, XXX, XXX, k58, XXX, k5a, XXX, XXX, XXX, k5e, k5f}, \
	{k60, k61, k62, XXX, k64, k65, XXX, XXX, k68, XXX, k6a, XXX, XXX, k6d, k6e, XXX}, \
	{k70, XXX, XXX, k73, XXX, XXX, XXX, k77, k78, k79, XXX, XXX, k7c, k7d, XXX, k7f}  \
}

void matrix_init_user(void);
void matrix_scan_user(void);