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

#include "tinySPI.h"
#define SS_PIN PB4 //or LATCH_PIN or select slave
int main()
{
    uint8_t buttonVal = 0;

    SPI.begin();
    DDRB |= (1 << SS_PIN);
    DDRB |= (1 << PB3);
    //PORTB &= ~(1 << PB3);
    PORTB |= (1 << SS_PIN); //set latch pin low when transferring data
    PORTB |= (1 << PB3);
    // The transfer order is LSB Q0 -- Q7
    _delay_ms(1000);
    PORTB  &= ~(1 << PB3);
    _delay_ms(1000);

    while (1)
    {
        PORTB &= ~(1 << SS_PIN);
        PORTB |= (1 << SS_PIN);
        //trasfer 1 byte
        buttonVal = SPI.transfer(0);
               
        //if (buttonVal == 1 || buttonVal == 2 || buttonVal == 4 )
        if (buttonVal == 2 || buttonVal == 4)
            PORTB &= ~(1 << PB3);
        else
            PORTB |= (1 << PB3);

       // _delay_ms(10);
     
    }
    return 0;
}
