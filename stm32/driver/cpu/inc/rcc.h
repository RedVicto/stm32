/*
 * rcc.h
 *
 *  Created on: 2013-5-04
 *      Author: 朱凯
 */

#ifndef RCC_H_
#define RCC_H_

typedef unsigned int uint32_t;

/**
 * 0x4002 1000 - 0x4002 13FF 复位和时钟控制(RCC)
 */

#define RCCBASE 0x40021000


/**
 * bit_word_addr = bit_band_base + (byte_offset×32) + (bit_number×4)
 * Bit Band Ragion 0x4000 0000 - 0x4010 0000 (1M)
 * Bit Band Alias  0x4200 0000 - 0x43ff ffff (32M)
 */
#define RCC_ALIAS_BASE (0x42000000 + (0x21000 * 32))

/**
 * APB2外设复位寄存器 (RCC_APB2RSTR) 偏移地址: 0x0C 复位值: 0x0000 0000 访问：无等待周期, 字, 半字 和字节访问
 * Bit 8 IOPGRST: IO port G reset
 * Set and cleared by software.
 * 0: No effect
 * 1: Reset IO port G
 * Bit 7 IOPFRST: IO port F reset
 * Set and cleared by software.
 * 0: No effect
 * 1: Reset IO port F
 * Bit 6 IOPERST: IO port E reset
 * Set and cleared by software.
 * 0: No effect
 * 1: Reset IO port E
 * Bit 5 IOPDRST: IO port D reset
 * Set and cleared by software.
 * 0: No effect
 * 1: Reset IO port D
 * Bit 4 IOPCRST: IO port C reset
 * Set and cleared by software.
 * 0: No effect
 * 1: Reset IO port C
 * Bit 3 IOPBRST: IO port B reset
 * Set and cleared by software.
 * 0: No effect
 * 1: Reset IO port B
 * Bit 2 IOPARST: IO port A reset
 * Set and cleared by software.
 * 0: No effect
 * 1: Reset IO port A
 * Bit 1 Reserved, must be kept at reset value.
 * Bit 0 AFIORST: Alternate function IO reset
 * Set and cleared by software.
 * 0: No effect
 * 1: Reset Alternate Function
 *
 */

typedef struct{
	uint32_t afio;
	uint32_t reserved;
	uint32_t gpioa;
	uint32_t gpiob;
	uint32_t gpioc;
	uint32_t gpiod;
	uint32_t gpioe;
	uint32_t gpiof;
	uint32_t gpiog;
}rcc_apb2_st;

#define RCC_RESET_APB2  ((rcc_apb2_st *)(RCC_ALIAS_BASE + (0xc *32)))

/**
 * APB2 peripheral clock enable register (RCC_APB2ENR)
 * Address: 0x18
 * Reset value: 0x0000 0000
 * Access: word, half-word and byte access
 * No wait states, except if the access occurs while an access to a peripheral in the APB2
 * domain is on going. In this case, wait states are inserted until the access to APB2
 * peripheralis finished.
 * Note: When the peripheral clock is not active, the peripheral register values may not be
 *  readable by software and the returned value is always 0x0.
 *  Bits 31:22 Reserved, must be kept at reset value.
 *  Bit 21 TIM11EN: TIM11 timer clock enable
 *  Set and cleared by software.
 *  0: TIM11 timer clock disabled
 *  1: TIM11 timer clock enabled
 *  Bit 20 TIM10EN: TIM10 timer clock enable
 *  Set and cleared by software.
 *  0: TIM10 timer clock disabled
 *  1: TIM10 timer clock enabled
 *  Bit 19 TIM9EN: TIM9 timer clock enable
 *  Set and cleared by software.
 *  0: TIM9 timer clock disabled
 *  1: TIM9 timer clock enabled
 *  Bits 18:16 Reserved, always read as 0.
 *  Bit 15 ADC3EN: ADC3 interface clock enable
 *  Set and cleared by software.
 *  0: ADC3 interface clock disabled
 *  1: ADC3 interface clock enabled
 *  Bit 14 USART1EN: USART1 clock enable
 *  Set and cleared by software.
 *  0: USART1 clock disabled
 *  1: USART1 clock enabled
 *  Bit 13 TIM8EN: TIM8 Timer clock enable
 *  Set and cleared by software.
 *  0: TIM8 timer clock disabled
 *  1: TIM8 timer clock enabled
 *  Bit 12 SPI1EN: SPI1 clock enable
 *  Set and cleared by software.
 *  0: SPI1 clock disabled
 *  1: SPI1 clock enabled
 *  Bit 11 TIM1EN: TIM1 timer clock enable
 *  Set and cleared by software.
 *  0: TIM1 timer clock disabled
 *  1: TIM1 timer clock enabled
 *  Bit 10 ADC2EN: ADC 2 interface clock enable
 *  Set and cleared by software.
 *  0: ADC 2 interface clock disabled
 *  1: ADC 2 interface clock enabled
 *  Bit 9 ADC1EN: ADC 1 interface clock enable
 *  Set and cleared by software.
 *  0: ADC 1 interface disabled
 *  1: ADC 1 interface clock enabled
 *  Bit 8 IOPGEN: IO port G clock enable
 *  Set and cleared by software.
 *  0: IO port G clock disabled
 *  1: IO port G clock enabled
 *  Bit 7 IOPFEN: IO port F clock enable
 *  Set and cleared by software.
 *  0: IO port F clock disabled
 *  1: IO port F clock enabled
 *  Bit 6 IOPEEN: IO port E clock enable
 *  Set and cleared by software.
 *  0: IO port E clock disabled
 *  1: IO port E clock enabled
 *  Bit 5 IOPDEN: IO port D clock enable
 *  Set and cleared by software.
 *  0: IO port D clock disabled
 *  1: IO port D clock enabled
 *  Bit 4 IOPCEN: IO port C clock enable
 *  Set and cleared by software.
 *  0: IO port C clock disabled
 *  1: IO port C clock enabled
 *  Bit 3 IOPBEN: IO port B clock enable
 *  Set and cleared by software.
 *  0: IO port B clock disabled
 *  1: IO port B clock enabled
 *  Bit 2 IOPAEN: IO port A clock enable
 *  Set and cleared by software.
 *  0: IO port A clock disabled
 *  1: IO port A clock enabled
 *  Bit 1 Reserved, must be kept at reset value.
 *  Bit 0 AFIOEN: Alternate function IO clock enable
 *  Set and cleared by software.
 *  0: Alternate Function IO clock disabled
 *  1: Alternate Function IO clock enabled
 */
#define RCC_ENABLE_APB2  ((rcc_apb2_st *)(RCC_ALIAS_BASE + (0x18 *32)))

static void rcc_gpioa_enable(){
	RCC_ENABLE_APB2->gpioa = 1;
}

#endif
