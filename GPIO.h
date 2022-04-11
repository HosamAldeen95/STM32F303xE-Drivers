/*
 * GPIO.h
 *
 *  Created on: Mar 10, 2022
 *      Author: Hosam Aldeen
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "STM32F303xE.h"

typedef uint8_t GPIO_Pin_t;

#define PORT_A		0
#define PA_0		0
#define PA_1		1
#define PA_2		2
#define PA_3		3
#define PA_4		4
#define PA_5		5
#define PA_6		6
#define PA_7		7
#define PA_8		8
#define PA_9		9
#define PA_10		10
#define PA_11		11
#define PA_12		12
#define PA_13		13
#define PA_14		14
#define PA_15		15

#define PORT_B		16
#define PB_0		16
#define PB_1		17
#define PB_2		18
#define PB_3		19
#define PB_4		20
#define PB_5		21
#define PB_6		22
#define PB_7		23
#define PB_8		24
#define PB_9		25
#define PB_10		26
#define PB_11		27
#define PB_12		28
#define PB_13		29
#define PB_14		30
#define PB_15		31

#define PORT_C		32
#define PC_0		32
#define PC_1		33
#define PC_2		34
#define PC_3		35
#define PC_4		36
#define PC_5		37
#define PC_6		38
#define PC_7		39
#define PC_8		40
#define PC_9		40
#define PC_10		42
#define PC_11		43
#define PC_12		44
#define PC_13		45
#define PC_14		46
#define PC_15		47

#define PORT_D		48
#define PD_0		48
#define PD_1		49
#define PD_2		50
#define PD_3		51
#define PD_4		52
#define PD_5		53
#define PD_6		54
#define PD_7		55
#define PD_8		56
#define PD_9		57
#define PD_10		58
#define PD_11		59
#define PD_12		60
#define PD_13		61
#define PD_14		62
#define PD_15		63

#define PORT_E		64
#define PE_0		64
#define PE_1		65
#define PE_2		66
#define PE_3		67
#define PE_4		68
#define PE_5		69
#define PE_6		70
#define PE_7		71
#define PE_8		72
#define PE_9		73
#define PE_10		74
#define PE_11		75
#define PE_12		76
#define PE_13		77
#define PE_14		78
#define PE_15		79

#define PORT_F		80
#define PF_0		80
#define PF_1		81
#define PF_2		82
#define PF_3		83
#define PF_4		84
#define PF_5		85
#define PF_6		86
#define PF_7		87
#define PF_8		88
#define PF_9		89
#define PF_10		90
#define PF_11		91
#define PF_12		92
#define PF_13		93
#define PF_14		94
#define PF_15		95

#define PORT_G		96
#define PG_0		96
#define PG_1		97
#define PG_2		98
#define PG_3		99
#define PG_4		100
#define PG_5		101
#define PG_6		102
#define PG_7		103
#define PG_8		104
#define PG_9		105
#define PG_10		106
#define PG_11		107
#define PG_12		108
#define PG_13		109
#define PG_14		110
#define PG_15		111

#define PORT_H		112
#define PH_0		112
#define PH_1		113
#define PH_2		114
#define PH_3		115
#define PH_4		116
#define PH_5		117
#define PH_6		118
#define PH_7		119
#define PH_8		120
#define PH_9		121
#define PH_10		121
#define PH_11		123
#define PH_12		124
#define PH_13		125
#define PH_14		126
#define PH_15		127

/* Clocks Setup */
#define PORT_CLOCK_DISABLE		0
#define PORT_CLOCK_ENABLE		1

/* Pin Modes Setup */
#define PIN_OUTPUT_PUSHPULL		0
#define PIN_OUTPUT_OPEN_DRAIN	1
#define PIN_INPUT_FLOATING		2
#define PIN_INPUT_PULL_UP		3
#define PIN_INPUT_PULL_DOWN		4
#define PIN_ALTERNATE_FCN		5
#define PIN_ANALOG_MODE			6

/* Pin Speed Setup */
#define PIN_LOW_SPEED			0
#define PIN_MID_SPEED			1
#define PIN_HIGH_SPEED			2

/* Port Modes Setup */
#define PORT_OUTPUT_PUSHPULL	0
#define PORT_OUTPUT_OPEN_DRAIN	1
#define PORT_INPUT_FLOATING		2
#define PORT_INPUT_PULL_UP		3
#define PORT_INPUT_PULL_DOWN	4

/* Port Speed Setup */
#define PORT_LOW_SPEED			0
#define PORT_MID_SPEED			1
#define PORT_HIGH_SPEED			2

/* Interrupt Edge Trigger */
#define PIN_IT_FALLING			0
#define PIN_IT_RISING			1
#define PIN_IT_CHANGING			2

void GPIO_Port_Clock (GPIO_Pin_t Port, uint8_t CK_State);
void GPIO_Pin_init (GPIO_Pin_t Pin, uint8_t Mode, uint8_t Speed);
void GPIO_Pin_set_AF (GPIO_Pin_t Pin, uint8_t AF_Val);
void GPIO_Pin_Lock (GPIO_Pin_t Pin);

void GPIO_Pin_set (GPIO_Pin_t Pin, uint8_t Val);
uint8_t GPIO_Pin_get (GPIO_Pin_t Pin);
void GPIO_Port_set (GPIO_Pin_t Port, uint16_t Val);
void GPIO_Port_init (GPIO_Pin_t Port, uint8_t Mode, uint8_t Speed);
uint16_t GPIO_Port_get (GPIO_Pin_t Port);
void GPIO_Port_Reset (GPIO_Pin_t Port);

void GPIO_Interrupt_Enable (GPIO_Pin_t Pin, uint8_t Edge, uint8_t IT_Priority);
void GPIO_Interrupt_Disable (GPIO_Pin_t Pin);
void GPIO_Interrupt_Set_Callback_Function (GPIO_Pin_t Pin, void (*CBK_FCN)());

#define set_bit(PORT, bitNumber) PORT|=(1<<bitNumber)
#define toggle_bit(PORT, bitNumber) PORT^=(1<<bitNumber)
#define clear_bit(PORT, bitNumber) PORT&=~(1<<bitNumber)
#define get_bit(PORT, bitNumber) ((PORT & (1<<bitNumber))?1:0)
#endif		/* GPIO_H_ */
