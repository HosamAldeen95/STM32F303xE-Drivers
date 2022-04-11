/*
 * STM32F303xE.h
 *
 *  Created on: Mar 10, 2022
 *      Author: Hosam Aldeen
 */

#ifndef STM32F303XE_H_
#define STM32F303XE_H_

#include <stdint.h>
#include "STM32F303x_INT.h"

/* System configuration Registers (SYSCFG) */
#define SYSCFG_COMP_OPAMP_BASE_ADDRESS 		0x40010000U

typedef struct {
	volatile uint32_t CFGR1;
	volatile uint32_t RCR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t CFGR2;
	volatile uint32_t COMP1_CSR;
	volatile uint32_t COMP2_CSR;
	volatile uint32_t COMP3_CSR;
	volatile uint32_t COMP4_CSR;
	volatile uint32_t COMP5_CSR;
	volatile uint32_t COMP6_CSR;
	volatile uint32_t COMP7_CSR;
	volatile uint32_t OPAMP1_CSR;
	volatile uint32_t OPAMP2_CSR;
	volatile uint32_t OPAMP3_CSR;
	volatile uint32_t OPAMP4_CSR;
	volatile uint32_t CFGR4;
	volatile uint32_t CFGR3;
}SYSCONFIG_RegDef_t;

#define SYSCFG_COMP_OPAMP ((SYSCONFIG_RegDef_t *)SYSCFG_COMP_OPAMP_BASE_ADDRESS)
/* =============================================================== */

/* Reset and Clock Control Register Definition */
#define RCC_BASE_ADDRESS		0x40021000U

typedef struct {
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBRSTR;
	volatile uint32_t CFGR2;
	volatile uint32_t CFGR3;
}RCC_RegDef_t;

#define RCC ((RCC_RegDef_t *)RCC_BASE_ADDRESS)
/* ====================================================================== */

/* GPIO Registers Definition */
#define GPIOA_BASE_ADDRESS		0x48000000U
#define GPIOB_BASE_ADDRESS		0x48000400U
#define GPIOC_BASE_ADDRESS		0x48000800U
#define GPIOD_BASE_ADDRESS		0x48000C00U
#define GPIOE_BASE_ADDRESS		0x48001000U
#define GPIOF_BASE_ADDRESS		0x48001400U
#define GPIOG_BASE_ADDRESS		0x48001800U
#define GPIOH_BASE_ADDRESS		0x48001C00U

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
	volatile uint32_t BRR;
}GPIO_RegDef_t;

/* GPIO Registers */
#define GPIOA ((GPIO_RegDef_t *)GPIOA_BASE_ADDRESS)
#define GPIOB ((GPIO_RegDef_t *)GPIOB_BASE_ADDRESS)
#define GPIOC ((GPIO_RegDef_t *)GPIOC_BASE_ADDRESS)
#define GPIOD ((GPIO_RegDef_t *)GPIOD_BASE_ADDRESS)
#define GPIOE ((GPIO_RegDef_t *)GPIOE_BASE_ADDRESS)
#define GPIOF ((GPIO_RegDef_t *)GPIOF_BASE_ADDRESS)
#define GPIOG ((GPIO_RegDef_t *)GPIOG_BASE_ADDRESS)
#define GPIOH ((GPIO_RegDef_t *)GPIOH_BASE_ADDRESS)


#endif		/* STM32F303XE_H_ */
