#include <avr/io.h>
#define F_CPU 16000000UL
#define BAUD 9600
#include <util/setbaud.h>
#include "functions.h"
void uart_init(void) {
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	#if USE_2X
	UCSR0A |= _BV(U2X0);
	#else
	UCSR0A &= ~(_BV(U2X0));
	#endif

	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}
void uart_putchar(uint8_t c) {
	loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
	UDR0 = c;
}
uint8_t uart_getchar(){
	while ( !(UCSR0A & (1<<RXC0)) );
	return UDR0;
}
void gpio_init(){
	TCCR0A=0x42;
	TCCR0B=0x04;
	TCNT0=0x00;
	OCR0A=255;
	OCR0B=0x00;
		
		
	TCCR1A=0x40;
	TCCR1B=0x09;
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x00;
	OCR1AL=110;
	OCR1BH=0x00;
	OCR1BL=0x00;
		
		
	ASSR=0x00;
	TCCR2A=0x42;
	TCCR2B=0x01;
	TCNT2=0x00;
	OCR2A=120;
	OCR2B=0x00;
		
	TIMSK0=0x02;
	TIMSK1=0x02;
	TIMSK2=0x02;
	ACSR=0x80;
}
void interrupt_init(){
	PORTB=0x00;
	DDRB=0b11010;

	PORTC=0x00;
	DDRC=0x00;

	PORTD=0x00;
	DDRD=0x40;
}
