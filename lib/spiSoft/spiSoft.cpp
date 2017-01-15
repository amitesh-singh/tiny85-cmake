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

#include "spiSoft.h"
#include <util/delay.h>

void spiSoft::begin(volatile uint8_t *dirReg, volatile uint8_t *portReg, volatile uint8_t *pinReg,
 uint8_t dpin, uint8_t cpin)
{
    _dirReg = dirReg;
    _portReg = portReg;
    _pinReg = pinReg;
    //_latchpin = lpin;
    _dataPin = dpin;
    _clockPin = cpin;

    //set dpin and cpin as OUTPUT
    *_dirReg |= (1 << dpin) | (1 << cpin); //| (1 << lpin);

    //*_portReg |= (1 << lpin);
}

void spiSoft::shiftOut(uint8_t data, uint8_t bitorder)
{
    uint8_t i = 0;

    *_portReg &= ~(1 << _clockPin);
    //make latch pin go low
    // don't handle latchpin at library side. it gives flexibility at userside.
    //*_portReg &= ~(1 << _latchPin);

    for (; i < 8; ++i)
    {
        // LSB
        if (bitorder == 0)
        {
            if (data & 0x01)
                *_portReg |= (1 << _dataPin);
            else
                *_portReg &= ~(1 << _dataPin);
            data >>= 1;
        }
        else if (bitorder == 1)
        {
            if (data & 0b10000000)
                *_portReg |= (1 << _dataPin);
            else
                *_portReg &= ~(1 << _dataPin);
            data <<= 1;
        }
        //pulse clock pin 
       *_portReg |= (1 << _clockPin);
       *_portReg &= ~(1 << _clockPin);
    }
    //*_portReg |= (1 << _latchPin);
}

void spiSoft::shiftIn(uint8_t &data, uint8_t bitorder)
{
    *_portReg &= ~(1 << _clockPin); // make latch pin go low;
    uint8_t i = 0;
    uint8_t currentByte = 0;

    for (; i < 8; ++i)
    {
        *_portReg |= (1 << _clockPin);
        // LSB
        if (bitorder == 0)
        {
            currentByte |= ((*_pinReg) & (1 << _dataPin)) << i;
        }
        else if (bitorder == 1)
        {
            currentByte |= ((*_pinReg) & (1 << _dataPin)) << (7 - i);
        }
        *_portReg &= ~(1 << _clockPin);
    }
    data = currentByte;
}

uint8_t spiSoft::shiftInOut(uint8_t byteout, uint8_t dataInPin)
{
    uint8_t bytein = 0;
    uint8_t bit;

   for (bit = 0; bit < 8; ++bit)
   {
       if (byteout & 0x01)
       {
           *_portReg |= (1 << _dataPin);  
       }
       else
           *_portReg &= ~(1 << _dataPin);

       _delay_ms(1);
       byteout >>= 1;
          //pulse clock pin 
       *_portReg |= (1 << _clockPin);
       if (*_pinReg & (1 << dataInPin))
         bytein |= 0x01 << bit;
       //bytein <<= 1;
       _delay_ms(1);

       *_portReg &= ~(1 << _clockPin);

   }
       return bytein;

}
void spiSoft::end()
{
    *_portReg &= ~((1 << _dataPin) | (1 << _clockPin));
}