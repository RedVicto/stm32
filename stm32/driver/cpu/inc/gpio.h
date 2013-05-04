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

typedef struct{
	gpio_cr_st cr[16];
	/**
	 * Port input data register (GPIOx_IDR) (x=A..G)
	 * Address offset: 0x08h
	 * Reset value: 0x0000 XXXX
	 * Bits 15:0 IDRy[15:0]: Port input data (y= 0 .. 15)
	 * These bits are read only and can be accessed in Word mode only.
	 * They contain the input value of the corresponding I/O port.
	 *
	 */
	uint32_t idr[32];
	/**
	 * Port output data register (GPIOx_ODR) (x=A..G)
	 * Address offset: 0x0Ch
	 * Reset value: 0x0000 0000
	 * ODRy[15:0]: Port output data (y= 0 .. 15)
	 * These bits can be read and written by software and can be accessed in Word mode only.
	 * Note: For atomic bit set/reset, the ODR bits can be individually set and cleared
	 * by writing to the GPIOx_BSRR register (x = A .. G).
	 */
	uint32_t odr[32];
	/**
	 * Port bit set/reset register (GPIOx_BSRR) (x=A..G)
	 * Address offset: 0x10
	 * Reset value: 0x0000 0000
	 * Bits 31:16 BRy: Port x Reset bit y (y= 0 .. 15)
	 * These bits are write-only and can be accessed in Word mode only.
	 * 0: No action on the corresponding ODRx bit
	 * 1: Reset the corresponding ODRx bit
	 * Note: If both BSx and BRx are set, BSx has priority.
	 * Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
	 * These bits are write-only and can be accessed in Word mode only.
	 * 0: No action on the corresponding ODRx bit
	 * 1: Set the corresponding ODRx bit
	 */
	uint32_t bs[16];
	uint32_t br[16];
	/**
	 * Port bit reset register (GPIOx_BRR) (x=A..G)
	 * Address offset: 0x14
	 * Reset value: 0x0000 0000
	 * Bits 31:16 Reserved
	 * Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
	 * These bits are write-only and can be accessed in Word mode only.
	 * 0: No action on the corresponding ODRx bit
	 * 1: Reset the corresponding ODRx bit
	 */
	uint32_t brr[32];
	/**
	 * Port configuration lock register (GPIOx_LCKR) (x=A..G)
	 * This register is used to lock the configuration of the port bits when
	 * a correct write sequence is applied to bit 16 (LCKK). The value of bits [15:0] is
	 *  used to lock the configuration of the GPIO. During the write sequence,
	 *  the value of LCKR[15:0] must not change. When the LOCK sequence has been applied
	 *  on a port bit it is no longer possible to modify the value of the port bit until
	 *  the next reset. Each lock bit freezes the corresponding 4 bits of the control
	 *   register (CRL, CRH).
	 *   Address offset: 0x18
	 *   Reset value: 0x0000 0000
	 *   Bit 16 LCKK[16]: Lock key
	 *   This bit can be read anytime. It can only be modified using the Lock Key
	 *   Writing Sequence.
	 *   0: Port configuration lock key not active
	 *   1: Port configuration lock key active. GPIOx_LCKR register is locked
	 *   until an MCU reset occurs.
	 *   LOCK key writing sequence:
	 *   Write 1
	 *   Write 0
	 *   Write 1
	 *   Read 0
	 *   Read 1 (this read is optional but confirms that the lock is active)
	 *   Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	 *   Any error in the lock sequence will abort the lock.
	 *   Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	 *   These bits are read write but can only be written when the LCKK bit is 0.
	 *   0: Port configuration not locked
	 *   1: Port configuration locked.
	 */
	uint32_t lck[16];
	uint32_t lckk;

}gpio_st;

#define GPIO_ALIAS_A ((gpio_st *)GPIO_ALIAS_BASE)
#define GPIO_ALIAS_B ((gpio_st *)(GPIO_ALIAS_A + GPIO_ALIAS_STEP))
#define GPIO_ALIAS_C ((gpio_st *)(GPIO_ALIAS_B + GPIO_ALIAS_STEP))
#define GPIO_ALIAS_D ((gpio_st *)(GPIO_ALIAS_C + GPIO_ALIAS_STEP))
#define GPIO_ALIAS_E ((gpio_st *)(GPIO_ALIAS_D + GPIO_ALIAS_STEP))
#define GPIO_ALIAS_F ((gpio_st *)(GPIO_ALIAS_E + GPIO_ALIAS_STEP))
#define GPIO_ALIAS_G ((gpio_st *)(GPIO_ALIAS_F + GPIO_ALIAS_STEP))

static void set_gpioa(uint32_t port){
	if(port > 15){
		return;
	}
	GPIO_ALIAS_A->bs[port] = 1;
}

static void reset_gpioa(uint32_t port){
	if(port > 15){
		return;
	}
	GPIO_ALIAS_A->br[port] = 1;
}

static void set_output_gpioa(uint32_t port){
	if(port > 15){
		return;
	}
	GPIO_ALIAS_A->cr[port].cnf.cnf0 = 0;
	GPIO_ALIAS_A->cr[port].cnf.cnf1 = 0;
	GPIO_ALIAS_A->cr[port].mode.mode0 = 1;
	GPIO_ALIAS_A->cr[port].mode.mode1 = 1;
}

#endif /* GPIO_H_ */
