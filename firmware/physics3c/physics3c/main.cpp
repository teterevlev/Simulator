#include <avr/io.h>
#include <avr/interrupt.h>
#include "functions.h"
float targetCoord = 0;
float coord = 0;
float speed = 0;
float period = 1000;
float acceleration = 0;
float maxSpeed = 20;
float maxAcceleration = 5;
float requestFrequency = .1;
float frict = .1;
bool fizmath = 0;
void checkSpeed(){
	if(speed > maxSpeed){
		speed = maxSpeed;
	}else if(speed < -maxSpeed){
		speed = -maxSpeed;
	}else if(speed<1 && speed>-1){
		speed = 0;
	}
}
int32_t c=0;
void setCoord(){
	float newSpeed = requestFrequency*(targetCoord-coord);
	acceleration = newSpeed-speed;
	if(acceleration>maxAcceleration) acceleration = maxAcceleration;
	physically();
	return;
				uart_dec(targetCoord);
				uart_putchar('\n');

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
void friction(){
	if(speed>0)
		speed-= frict;
	else if(speed<0)
		speed+= frict;
}
void pr(){
	uart_dec(speed);
	uart_putchar('\t');
	uart_dec(period);
	uart_putchar('\t');
	uart_dec(coord);
	//uart_putchar('\t');
	//uart_dec(acceleration);
	uart_putchar('\n');
}
void physically(){
	if(speed>0){
		PORTD |= 0b00100000;
	}else{
		PORTD &= 0b11011111;
	}
	speed += acceleration;
	checkSpeed();
	period = 20000./speed;
	if(period<0) period = -period;
	drive(0, period);
	fizmath = false;
}
void mathematically(){
		if(acceleration==0){
			friction();
		}
		if(speed > 0){
			coord++;
			if(coord > targetCoord){
				acceleration = 0;
			}

		}else if(speed <0){
			coord--;
			if(coord < targetCoord){
				acceleration = 0;
			}
		}else{
			stopTimer(0);
			uart_dec(coord);
			uart_putchar('\n');
		}
		//pr();
		fizmath = true;
};
ISR(TIMER0_COMPA_vect){
	if(fizmath){
		physically();
	}else{
		mathematically();
	}
}
ISR(TIMER1_COMPA_vect){
	
}
ISR(TIMER2_COMPA_vect){
	
}
