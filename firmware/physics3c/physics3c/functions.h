/*
 * functions.h
 *
 * Created: 21.03.2017 21:03:02
 *  Author: odama
 */ 


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

void uart_init();
void gpio_init();
void interrupt_init();
void uart_putchar(uint8_t c);
uint8_t uart_getchar();


#endif /* FUNCTIONS_H_ */