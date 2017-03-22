#include <avr/io.h>
#include <avr/interrupt.h>
#include "functions.h"
float targetCoord = 0;
float coord = 0;
float speed = 0;
float period = 1000;
float minPeriod = 1000;
// TCCR0B=0x03: 16 - 2040 us
// TCCR0B=0x04: 64 - 8200 us
// TCCR0B=0x05: 256 - 32600 us
void checkPeriod(){
	if(period < minPeriod) period = minPeriod;
}
int32_t c=0;
void readUartDec(){
	static bool minus;
	if(uart_available()){
		
		int8_t u = uart_getchar();
		if(u=='\n'){
			if(minus)
				targetCoord = -c;
			else
				targetCoord = c;
				
			
			//drive(0, targetCoord);
			uart_dec(targetCoord);
			uart_putchar('\n');
			c = 0;
			minus = false;
		}else if(u=='-'){
			c = 0;
			minus = true;
		}else{
			if(c==0){
				c = u-48;
			}else{
				c *= 10;
				c += u-48;
			}
		}
		
	}
}
int main(void)
{
	gpio_init();
	interrupt_init();
	uart_init();
	asm("sei");
    while (1) 
    {
		readUartDec();
    }
}

ISR(TIMER0_COMPA_vect){
	if(PIND & 0b01000000){
		speed = targetCoord-coord;
		period = 20000./speed;
		if(period<0) period = -period;
		checkPeriod();
		drive(0, period);
	}else{
		if(speed > 0){
			coord++;
		}else return;
		uart_dec(speed);
		uart_putchar('\t');
		uart_dec(period);
		uart_putchar('\t');
		uart_dec(coord);
		uart_putchar('\n');
	}
}
ISR(TIMER1_COMPA_vect){
	
}
ISR(TIMER2_COMPA_vect){
	
}
