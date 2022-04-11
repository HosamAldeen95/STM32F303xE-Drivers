/*
 * STM32F303x_INT.h
 *
 *  Created on: Apr 4, 2022
 *      Author: Hosam Aldeen
 */

#ifndef STM32F303X_INT_H_
#define STM32F303X_INT_H_

/* Interrupts Registers Definition */

/* Extended interrupts and events controller Registers (EXTI) */
#define EXTI_BASE_ADDRESS		0x40010400U

typedef struct {
	volatile uint32_t IMR1;
	volatile uint32_t EMR1;
	volatile uint32_t RTSR1;
	volatile uint32_t FTSR1;
	volatile uint32_t SWIER1;
	volatile uint32_t PR1;
	volatile uint32_t IMR2;
	volatile uint32_t EMR2;
	volatile uint32_t RTSR2;
	volatile uint32_t FTSR2;
	volatile uint32_t SWIER2;
	volatile uint32_t PR2;
}EXTI_RegDef_t;

#define EXTI ((EXTI_RegDef_t *)EXTI_BASE_ADDRESS)
/* =============================================================== */

/* Nested Vectored Interrupt Controller Registers */

// 1- Interrupt Set-enable Registers:
#define NVIC_ISER ((volatile uint32_t *)0xE000E100U)

// 2- Interrupt Clear-enable Registers:
#define NVIC_ICER ((volatile uint32_t *)0xE000E180U)

// 3- Interrupt Set-pending Registers:
#define NVIC_ISPR ((volatile uint32_t *)0xE000E200U)

// 4-Interrupt Clear-pending Registers:
#define NVIC_ICPR ((volatile uint32_t *)0xE000E280U)

// 5- Interrupt Active Bit Registers:
#define NVIC_IABR ((volatile uint32_t *)0xE000E300U)

// 6- Interrupt Priority Registers:
#define NVIC_IPR ((volatile uint32_t *)0xE000E400U)

// 7- Software Trigger Interrupt Register:
#define NVIC_STIR ((volatile uint32_t *)0xE000EF00U)


#endif /* STM32F303X_INT_H_ */
