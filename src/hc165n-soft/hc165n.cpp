#include <avr/io.h>
#include <util/delay.h>

//This is a test done on 74HC595N spi

//NOTE:
//MOSI and MISO for uploading the code via programmer is PB0 and PB1
// But for USI based SPI communication, Dataout or D0 is PB1 and Datain or DI is PB0. This is opposite to above case. so remember this.
// connection
// DO(PB1) - serial data pin 74HC595
// PB2  --- shift clock
// PB4  --- latch clock
// OE - GND  (must)
// RST - Vcc (must)

#include "spiSoft.h"
#define LATCH PB4 //or LATCH_PIN or select slave
int main()
{
    spiSoft SPI;

    //uint8_t buttonVal = 0;

    SPI.begin(&DDRB, &PORTB, &PINB, PB0, PB2);
    DDRB |= (1 << LATCH);
    DDRB |= (1 << PB3);
    PORTB &= ~(1 << PB3);
    PORTB &= ~(1 << LATCH); 
    
    PORTB |= (1 << PB3);
    // The transfer order is LSB Q0 -- Q7
    _delay_ms(1000);
    PORTB  &= ~(1 << PB3);
    _delay_ms(1000);
    uint8_t data;
    while (1)
    {
        PORTB &= ~(1 << LATCH);
        _delay_us(5);
        PORTB |= (1 << LATCH); //set latch pin HIGH when transferring data
        //trasfer 1 byte
        SPI.shiftIn(data, 1);
        
        //if (data == 0b10000000) => use this when SPI.shiftIn(data, 0)
        if (data == 0b00000001)
            PORTB &= ~(1 << PB3);
        else
            PORTB |= (1 << PB3);

        _delay_ms(10);
    }
    return 0;
}
