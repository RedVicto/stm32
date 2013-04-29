/*
 * gpio.h
 *
 *  Created on: 2013-4-30
 *      Author: 朱凯
 */

#ifndef GPIO_H_
#define GPIO_H_

typedef unsigned int uint32_t;

/**
 * 0x4001 2000 - 0x4001 23FF GPIO端口G
 * 0x4001 1c00 - 0x4001 1fFF GPIO端口F
 * 0x4001 1800 - 0x4001 1BFF GPIO端口E
 * 0x4001 1400 - 0x4001 17FF GPIO端口D
 * 0x4001 1000 - 0x4001 13FF GPIO端口C
 * 0X4001 0C00 - 0x4001 0FFF GPIO端口B
 * 0x4001 0800 - 0x4001 0BFF GPIO端口A
 */

#define GPIOBASE 0x40010800
#define GPIOSTEP 0x400
#define GPIOA    0x40010800
#define GPIOB    0x40010C00
#define GPIOC    0x40011000
#define GPIOD    0x40011400
#define GPIOE    0x40011800
#define GPIOF    0x40011c00
#define GPIOG    0x40012000

/**
 * bit_word_addr = bit_band_base + (byte_offset×32) + (bit_number×4)
 * Bit Band Ragion 0x4000 0000 - 0x4010 0000 (1M)
 * Bit Band Alias  0x4200 0000 - 0x43ff ffff (32M)
 */
#define GPIO_ALIAS_BASE (0x42000000 + (0x10800 * 32))
#define GPIO_ALIAS_STEP (GPIOSTEP * 32)
#define GPIO_ALIAS_A GPIO_ALIAS_BASE
#define GPIO_ALIAS_B (GPIO_ALIAS_A + GPIO_ALIAS_STEP)
#define GPIO_ALIAS_C (GPIO_ALIAS_B + GPIO_ALIAS_STEP)
#define GPIO_ALIAS_D (GPIO_ALIAS_C + GPIO_ALIAS_STEP)
#define GPIO_ALIAS_E (GPIO_ALIAS_D + GPIO_ALIAS_STEP)
#define GPIO_ALIAS_F (GPIO_ALIAS_E + GPIO_ALIAS_STEP)
#define GPIO_ALIAS_G (GPIO_ALIAS_F + GPIO_ALIAS_STEP)

/**
 * Port configuration register low (GPIOx_CRL) (x=A..G)
 * Address offset: 0x00
 * Reset value: 0x4444 4444
 * Bits 31:30, 27:26, 23:22, 19:18, 15:14, 11:10, 7:6, 3:2
 *
 * CNFy[1:0]: Port x configuration bits (y= 0 .. 7)
 * These bits are written by software to configure the corresponding I/O port.
 * In input mode (MODE[1:0]=00):
 * 00: Analog mode
 * 01: Floating input (reset state)
 * 10: Input with pull-up / pull-down
 * 11: Reserved
 * In output mode (MODE[1:0] > 00):
 * 00: General purpose output push-pull
 * 01: General purpose output Open-drain
 * 10: Alternate function output Push-pull
 * 11: Alternate function output Open-drain
 * Bits 29:28, 25:24, 21:20, 17:16, 13:12, 9:8, 5:4, 1:0
 *
 * MODEy[1:0]: Port x mode bits (y= 0 .. 7)
 * These bits are written by software to configure the corresponding I/O port.
 * 00: Input mode (reset state)
 * 01: Output mode, max speed 10 MHz.
 * 10: Output mode, max speed 2 MHz.
 * 11: Output mode, max speed 50 MHz.
 *
 *
 * Port configuration register high (GPIOx_CRH) (x=A..G)
 * Address offset: 0x04
 * Reset value: 0x4444 4444
 *
 * Bits 31:30, 27:26, 23:22, 19:18, 15:14, 11:10, 7:6, 3:2
 * CNFy[1:0]: Port x configuration bits (y= 8 .. 15)
 *
 *Bits 29:28, 25:24, 21:20, 17:16, 13:12, 9:8, 5:4, 1:0
 *Bits MODEy[1:0]: Port x mode bits (y= 8 .. 15)
 *
 */
typedef struct{
	uint32_t cnf0;
	uint32_t cnf1;
}gpio_cnf_st;

typedef struct{
	uint32_t mode0;
	uint32_t mode1;
}gpio_mode_st;

typedef struct{
	gpio_mode_st mode;
	gpio_cnf_st cnf;
}gpio_cr_st;

#endif /* GPIO_H_ */
