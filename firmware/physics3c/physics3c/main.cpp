#include <avr/io.h>
#include <avr/interrupt.h>
#include "functions.h"
float targetCoord = 0;
float coord = 0;
float speed = 0;
float period = 1000;
float acceleration = 0;
float maxSpeed = 20;
float maxAcceleration = 1;
float requestFrequency = .01;

void checkSpeed(){
	if(speed > maxSpeed) speed = maxSpeed;
}
int32_t c=0;
void setCoord(){
	float newSpeed = requestFrequency*(targetCoord-coord);
	acceleration = newSpeed-speed;
	if(acceleration>maxAcceleration) acceleration = maxAcceleration;
	
}
void readUartDec(){
	static bool minus;
	if(uart_available()){
		
		int8_t u = uart_getchar();
		if(u=='\n'){
			if(minus)
				targetCoord = -c;
			else
				targetCoord = c;
				
			setCoord();
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
		speed += acceleration;
		checkSpeed();
		period = 20000./speed;
		if(period<0) period = -period;
		drive(0, period);
	}else{
		if(speed > 0){
			coord++;
			if(coord > targetCoord){
				acceleration = -maxAcceleration/4;
			}
		}else return;
		uart_dec(speed);
		uart_putchar('\t');
		uart_dec(period);
		//uart_putchar('\t');
		//uart_dec(acceleration);
		uart_putchar('\t');
		uart_dec(coord);
		uart_putchar('\n');
	}
}
ISR(TIMER1_COMPA_vect){
	
}
ISR(TIMER2_COMPA_vect){
	
}
