#include <avr/io.h>
#include <avr/interrupt.h>
#include "functions.h"

// TCCR0B=0x05: 64 - 8200 us
// TCCR0B=0x05: 256 - 32600 us
ISR(TIMER0_COMPA_vect){
	uart_putchar(48);
}
ISR(TIMER1_COMPA_vect){
	
}
ISR(TIMER2_COMPA_vect){
		PORTB ^= 0b10000;
	
}

int main(void)
{
	gpio_init();
	interrupt_init();
	uart_init();
	asm("sei");
    while (1) 
    {
		
    }
}

