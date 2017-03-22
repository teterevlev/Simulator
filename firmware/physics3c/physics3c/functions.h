/*
 * functions.h
 *
 * Created: 21.03.2017 21:03:02
 *  Author: odama
 */ 


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

template<typename T> inline const T abs(T const & x)
{
	return ( x<0 ) ? -x : x;
}
void uart_init();
void gpio_init();
void interrupt_init();
void uart_putchar(uint8_t c);
uint8_t uart_getchar();
bool uart_available();
void uart_dec(int32_t);
void drive(uint8_t id, float period);
void timer(uint8_t id, uint8_t prescale, uint8_t ocr);

#endif /* FUNCTIONS_H_ */