#include <avr/io.h>
#include <util/delay.h>

#include "tinySPI.h"
#define SS_PIN PB2 //or LATCH_PIN or select slave
int main()
{
    SPI.begin();
    DDRB |= (1 << SS_PIN);
    PORTB |= (1 << SS_PIN); //set latch pin low when transferring data
    
    while (1)
    {
        PORTB &= ~(1 << SS_PIN);
        //trasfer 1 byte
        SPI.transfer(0b00010111);
        PORTB |= (1 << SS_PIN);

        _delay_ms(100);
    }
    return 0;
}
