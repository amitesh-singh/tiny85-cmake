#include <avr/io.h>

int main()
{
	DDRB |= (1 << PB3);
	PORTB |= (1 << PB3);

	while (1)	
	{
	}
	return 0;
}
