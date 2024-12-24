/*
 * This file is part of the Trezor project, https://trezor.io/
 *
 * Copyright (c) SatoshiLabs
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "rand.h"
// 声明 RP2040 的随机数生成函数
extern uint8_t rosc_random_u8(size_t cycles);

uint32_t random32(void) {
    uint32_t r = 0;
    // 使用 4 次 rosc_random_u8 来生成 32 位随机数
    r |= ((uint32_t)rosc_random_u8(8)) << 24;
    r |= ((uint32_t)rosc_random_u8(8)) << 16;
    r |= ((uint32_t)rosc_random_u8(8)) << 8;
    r |= ((uint32_t)rosc_random_u8(8));
    return r;
}
