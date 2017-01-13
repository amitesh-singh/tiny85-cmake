#include <avr/io.h>
#include <util/delay.h>

#include "spiSoft.h"
#define SS_PIN PB4 //or LATCH_PIN or select slave
spiSoft SPI;

int main()
{                                 //dpin lpin
    SPI.begin(&DDRB, &PORTB, &PINB, PB1, PB2);
    DDRB |= (1 << SS_PIN);
    PORTB |= (1 << SS_PIN); //set latch pin low when transferring data
    while (1)
    {
        PORTB &= ~(1 << SS_PIN);
        //trasfer 1 byte
        SPI.shiftOut(0b10010111);
        PORTB |= (1 << SS_PIN);
        //SPI.shiftIn(val);
        _delay_ms(100);
        PORTB &= ~(1 << SS_PIN);
        //trasfer 1 byte
        SPI.shiftOut(0);
        PORTB |= (1 << SS_PIN);
        _delay_ms(100);
    }
    return 0;
}
