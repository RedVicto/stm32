/*
 * test.c
 *
 *  Created on: 2013-5-4
 *      Author: Öì¿­
 */
#include "gpio.h"
#include "rcc.h"

int main(void){
	rcc_gpioa_enable();
	set_output_gpioa(1);
	set_output_gpioa(2);
	set_gpioa(1);
	reset_gpioa(2);
}

int SystemInit(){
	return 0;
}


