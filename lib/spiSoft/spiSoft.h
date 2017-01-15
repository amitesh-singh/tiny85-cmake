/*
 *  spiSoft library
 *
 *  (C) Amitesh Singh <singh.amitesh@gmail.com>, 2017
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SPI_SOFT_H
#define __SPI_SOFT_H
#include <stdint.h>
#include <avr/io.h>

class spiSoft
{
    volatile uint8_t *_dirReg;
    volatile uint8_t *_portReg;
    volatile uint8_t *_pinReg;

    uint8_t  _dataPin, _clockPin; // _latchpin
    //uint8_t _dataInPin;
    public:
    void                begin(volatile uint8_t *dirReg, volatile uint8_t *portReg, volatile uint8_t *pinReg, uint8_t dpin, uint8_t cpin);
    void                shiftOut(uint8_t data, uint8_t bitorder = 0); // 0 - lsb, 1 - msb
    void                shiftIn(uint8_t &data, uint8_t bitorder = 0); // 0 - lsb, 1 - msb
    uint8_t             shiftInOut(uint8_t data, uint8_t dataInPin);
    void                end(); 
};
#endif