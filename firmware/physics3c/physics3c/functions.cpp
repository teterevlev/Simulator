#include <avr/io.h>
#define F_CPU 16000000UL
#define BAUD 115200
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
bool uart_available(){
	if ( !(UCSR0A & (1<<RXC0)) ) return false;
	return true;
}
uint8_t uart_getchar(){
	return UDR0;
}
void uart_dec(int32_t d){
	if(d<0){
		uart_putchar('-');
		d = -d;
	}
	if(d>=10000) uart_putchar((d/10000)+48);
	if(d>=1000) uart_putchar(((d/1000)%10)+48);
	if(d>=100) uart_putchar(((d/100)%10)+48);
	if(d>=10) uart_putchar(((d/10)%10)+48);
	uart_putchar((d%10)+48);
}
void timer(uint8_t id, uint8_t prescale, uint8_t ocr){
	if(id==0){
		TCCR0B=prescale;
		OCR0A = ocr;
	}else if(id==1){
		TCCR1B=prescale;
		OCR1A = ocr;
	}else if(id==3){
		TCCR2B=prescale;
		OCR2A = ocr;
	}
}
void drive(uint8_t id, float period){
	if(period<2048){
		timer(id, 0x03, period*256/2048);
	}else if(period<8192){
		timer(id, 0x04, period*256/8192);
	}else if(period<32768){
		timer(id, 0x05, period*256/32768);
	}
}
void gpio_init(){
	TCCR0A=0x42;
	TCCR0B=0x05;
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
