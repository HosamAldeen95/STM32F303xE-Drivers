/**
 ******************************************************************************
 * @file           : GPIO.c
 * @author         : Hosam Aldeen
 * @brief          : GPIO Driver Implementation
 ******************************************************************************
 */

#include "GPIO.h"

static void (*_EXTI0_IRQ_Handler)();
static void (*_EXTI1_IRQ_Handler)();
static void (*_EXTI2_IRQ_Handler)();
static void (*_EXTI3_IRQ_Handler)();
static void (*_EXTI4_IRQ_Handler)();
static void (*_EXTI9_5_IRQ_Handler)();
static void (*_EXTI15_10_IRQ_Handler)();

void GPIO_Port_Clock (GPIO_Pin_t Port, uint8_t CK_State) {
	switch (Port) {
		case PORT_A: if (CK_State) set_bit(RCC->AHBENR, 17); else clear_bit(RCC->AHBENR, 17); break;
		case PORT_B: if (CK_State) set_bit(RCC->AHBENR, 18); else clear_bit(RCC->AHBENR, 18); break;
		case PORT_C: if (CK_State) set_bit(RCC->AHBENR, 19); else clear_bit(RCC->AHBENR, 19); break;
		case PORT_D: if (CK_State) set_bit(RCC->AHBENR, 20); else clear_bit(RCC->AHBENR, 20); break;
		case PORT_E: if (CK_State) set_bit(RCC->AHBENR, 21); else clear_bit(RCC->AHBENR, 21); break;
		case PORT_F: if (CK_State) set_bit(RCC->AHBENR, 22); else clear_bit(RCC->AHBENR, 22); break;
		case PORT_G: if (CK_State) set_bit(RCC->AHBENR, 23); else clear_bit(RCC->AHBENR, 23); break;
		case PORT_H: if (CK_State) set_bit(RCC->AHBENR, 16); else clear_bit(RCC->AHBENR, 16); break;
		default: break;
	}
}

void GPIO_Port_Reset (GPIO_Pin_t Port) {
	switch (Port) {
		case PORT_A: set_bit (RCC->AHBRSTR, 17); clear_bit (RCC->AHBRSTR, 17); break;
		case PORT_B: set_bit (RCC->AHBRSTR, 18); clear_bit (RCC->AHBRSTR, 18); break;
		case PORT_C: set_bit (RCC->AHBRSTR, 19); clear_bit (RCC->AHBRSTR, 19); break;
		case PORT_D: set_bit (RCC->AHBRSTR, 20); clear_bit (RCC->AHBRSTR, 20); break;
		case PORT_E: set_bit (RCC->AHBRSTR, 21); clear_bit (RCC->AHBRSTR, 21); break;
		case PORT_F: set_bit (RCC->AHBRSTR, 22); clear_bit (RCC->AHBRSTR, 22); break;
		case PORT_G: set_bit (RCC->AHBRSTR, 23); clear_bit (RCC->AHBRSTR, 23); break;
		default: break;
	}
}

void GPIO_Pin_init (GPIO_Pin_t Pin, uint8_t Mode, uint8_t Speed) {
	GPIO_RegDef_t *Target_Port;
	uint8_t temp = (uint8_t)(Pin / 16);
	uint8_t pin_Num = (uint8_t)(Pin % 16);

	/*
	 * defining target port from the Pin passed as argument.
	 * defining target pin number at the port from the Pin passed as argument.
	 * work on the registers to apply desired configuration, with help of reference manual (Page 237).
	 */

	switch (temp) {
		case 0: Target_Port = GPIOA; break;
		case 1: Target_Port = GPIOB; break;
		case 2: Target_Port = GPIOC; break;
		case 3: Target_Port = GPIOD; break;
		case 4: Target_Port = GPIOE; break;
		case 5: Target_Port = GPIOF; break;
		case 6: Target_Port = GPIOG; break;
		case 7: Target_Port = GPIOH; break;
		default: break;
	}

	switch (Mode) {
		case PIN_OUTPUT_PUSHPULL:
			// Output Mode - MODER Register.
			set_bit  (Target_Port->MODER, (pin_Num * 2));
			clear_bit(Target_Port->MODER, ((pin_Num * 2) + 1));
			// Push-Pull Mode - OTYPER Register.
			clear_bit (Target_Port->OTYPER, pin_Num);
		break;

		case PIN_OUTPUT_OPEN_DRAIN:
			// Output Mode - MODER Register.
			set_bit  (Target_Port->MODER, (pin_Num * 2));
			clear_bit(Target_Port->MODER, ((pin_Num * 2) + 1));
			// Open-Drain Mode - OTYPER Register.
			set_bit (Target_Port->OTYPER, pin_Num);
		break;

		case PIN_INPUT_FLOATING:
			// Input Mode - MODER Register.
			clear_bit(Target_Port->MODER, (pin_Num * 2));
			clear_bit(Target_Port->MODER, ((pin_Num * 2) + 1));
			// Input floating Mode - PUPDR Register.
			clear_bit (Target_Port->PUPDR, (pin_Num * 2));
			clear_bit (Target_Port->PUPDR, ((pin_Num * 2) + 1));
		break;

		case PIN_INPUT_PULL_UP:
			// Input Mode - MODER Register.
			clear_bit(Target_Port->MODER, (pin_Num * 2));
			clear_bit(Target_Port->MODER, ((pin_Num * 2) + 1));
			// Input Pull-Up Mode - PUPDR Register.
			set_bit   (Target_Port->PUPDR, (pin_Num * 2));
			clear_bit (Target_Port->PUPDR, ((pin_Num * 2) + 1));
		break;

		case PIN_INPUT_PULL_DOWN:
			// Input Mode - MODER Register.
			clear_bit(Target_Port->MODER, (pin_Num * 2));
			clear_bit(Target_Port->MODER, ((pin_Num * 2) + 1));
			// Input Pull-Down Mode - PUPDR Register.
			clear_bit (Target_Port->PUPDR, (pin_Num * 2));
			set_bit   (Target_Port->PUPDR, ((pin_Num * 2) + 1));
		break;

		case PIN_ALTERNATE_FCN:
			// AF Mode - MODER Register.
			clear_bit(Target_Port->MODER, (pin_Num * 2));
			set_bit  (Target_Port->MODER, ((pin_Num * 2) + 1));
		break;

		case PIN_ANALOG_MODE:
			// Analog Mode - MODER Register.
			set_bit(Target_Port->MODER, (pin_Num * 2));
			set_bit(Target_Port->MODER, ((pin_Num * 2) + 1));
		break;

		default: break;
	}

	switch (Speed) {
		case PIN_LOW_SPEED:
			// Low Speed Mode - OSPEEDR Register.
			clear_bit(Target_Port->OSPEEDR, (pin_Num * 2));
			clear_bit(Target_Port->OSPEEDR, ((pin_Num * 2) + 1));
		break;

		case PIN_MID_SPEED:
			// Mid Speed Mode - OSPEEDR Register.
			set_bit  (Target_Port->OSPEEDR, (pin_Num * 2));
			clear_bit(Target_Port->OSPEEDR, ((pin_Num * 2) + 1));
		break;

		case PIN_HIGH_SPEED:
			// High Speed Mode - OSPEEDR Register.
			set_bit(Target_Port->OSPEEDR, (pin_Num * 2));
			set_bit(Target_Port->OSPEEDR, ((pin_Num * 2) + 1));
		break;

		default: break;
	}
}

void GPIO_Pin_set_AF (GPIO_Pin_t Pin, uint8_t AF_Val) {
	GPIO_RegDef_t *Target_Port;
	uint8_t temp = (uint8_t)(Pin / 16);
	uint8_t pin_Num = (uint8_t)(Pin % 16);
	/*
	 * defining target port from the Pin passed as argument.
	 * defining target pin number at the port from the Pin passed as argument.
	 * work on the registers to apply desired configuration, with help of reference manual (Page 237).
	 */
	switch (temp) {
		case 0: Target_Port = GPIOA; break;
		case 1: Target_Port = GPIOB; break;
		case 2: Target_Port = GPIOC; break;
		case 3: Target_Port = GPIOD; break;
		case 4: Target_Port = GPIOE; break;
		case 5: Target_Port = GPIOF; break;
		case 6: Target_Port = GPIOG; break;
		case 7: Target_Port = GPIOH; break;
		default: break;
	}

	/*
	 * for the first 8 pins of the port (pin 0 to 7),  will deal with the AFRL.
	 * for the last  8 pins of the port (pin 8 to 15), will deal with the AFRH.
	 */
	if (pin_Num < 8) {
		Target_Port->AFRL |= ((AF_Val & 0x0F) << (pin_Num * 4));
	}
	else {
		Target_Port->AFRH |= ((AF_Val & 0x0F) << ((pin_Num - 8) * 4));
	}
}

void GPIO_Pin_Lock (GPIO_Pin_t Pin) {

}

void GPIO_Pin_set (GPIO_Pin_t Pin, uint8_t Val) {
	GPIO_RegDef_t *Target_Port;
	uint8_t temp = (uint8_t)(Pin / 16);
	uint8_t pin_Num = (uint8_t)(Pin % 16);
	/*
	 * defining target port from the Pin passed as argument.
	 * defining target pin number at the port from the Pin passed as argument.
	 * work on the registers to apply desired configuration, with help of reference manual (Page 237).
	 */
	switch (temp) {
		case 0: Target_Port = GPIOA; break;
		case 1: Target_Port = GPIOB; break;
		case 2: Target_Port = GPIOC; break;
		case 3: Target_Port = GPIOD; break;
		case 4: Target_Port = GPIOE; break;
		case 5: Target_Port = GPIOF; break;
		case 6: Target_Port = GPIOG; break;
		case 7: Target_Port = GPIOH; break;
		default: break;
	}

	/*
	 * if setting,  set BSy (first 16-bit of BSRR Register).
	 * if clearing, set BRy (last  16-bit of BSRR Register).
	 */
	if (Val) set_bit (Target_Port->BSRR, pin_Num);
	else	 set_bit (Target_Port->BSRR, (pin_Num + 16));
}

uint8_t GPIO_Pin_get (GPIO_Pin_t Pin) {
	GPIO_RegDef_t *Target_Port;
	uint8_t temp = (uint8_t)(Pin / 16);
	uint8_t pin_Num = (uint8_t)(Pin % 16);
	/*
	 * defining target port from the Pin passed as argument.
	 * defining target pin number at the port from the Pin passed as argument.
	 * work on the registers to get desired data, with help of reference manual (Page 237).
	 */
	switch (temp) {
		case 0: Target_Port = GPIOA; break;
		case 1: Target_Port = GPIOB; break;
		case 2: Target_Port = GPIOC; break;
		case 3: Target_Port = GPIOD; break;
		case 4: Target_Port = GPIOE; break;
		case 5: Target_Port = GPIOF; break;
		case 6: Target_Port = GPIOG; break;
		case 7: Target_Port = GPIOH; break;
		default: break;
	}

	/*
	 * pin Mode definition is required first from the MODER Register.
	 * if the required pin is input, get its value from IDR Register.
	 * if the required pin is output, get its value from ODR Register.
	 */

	// Input Pin.
	if ((!get_bit(Target_Port->MODER, 2 * pin_Num)) && (!get_bit(Target_Port->MODER, ((2 * pin_Num) + 1))))
		return get_bit (Target_Port->IDR, pin_Num);
	// Output Pin.
	else if ((get_bit(Target_Port->MODER, 2 * pin_Num)) && (!get_bit(Target_Port->MODER, ((2 * pin_Num) + 1))))
		return get_bit (Target_Port->ODR, pin_Num);
	// Other Configuration.
	else return -1;
}

void GPIO_Port_init (GPIO_Pin_t Port, uint8_t Mode, uint8_t Speed) {
	uint8_t i;
	for (i = Port; i < Port + 16; i++)
		GPIO_Pin_init(i, Mode, Speed);
}

void GPIO_Port_set (GPIO_Pin_t Port, uint16_t Val) {
	GPIO_RegDef_t *Target_Port;
	uint8_t temp = (uint8_t)(Port / 16);
	/*
	 * defining target port from the Port passed as argument.
	 * work on the registers to apply desired data, with help of reference manual (Page 237).
	 */
	switch (temp) {
		case 0: Target_Port = GPIOA; break;
		case 1: Target_Port = GPIOB; break;
		case 2: Target_Port = GPIOC; break;
		case 3: Target_Port = GPIOD; break;
		case 4: Target_Port = GPIOE; break;
		case 5: Target_Port = GPIOF; break;
		case 6: Target_Port = GPIOG; break;
		case 7: Target_Port = GPIOH; break;
		default: break;
	}
	Target_Port->ODR = Val;
}

uint16_t GPIO_Port_get (GPIO_Pin_t Port) {
	GPIO_RegDef_t *Target_Port;
	uint8_t temp = (uint8_t)(Port / 16);
	/*
	 * defining target port from the Port passed as argument.
	 * work on the registers to get desired data, with help of reference manual (Page 237).
	 * Port must be an Input Port.
	 */
	switch (temp) {
		case 0: Target_Port = GPIOA; break;
		case 1: Target_Port = GPIOB; break;
		case 2: Target_Port = GPIOC; break;
		case 3: Target_Port = GPIOD; break;
		case 4: Target_Port = GPIOE; break;
		case 5: Target_Port = GPIOF; break;
		case 6: Target_Port = GPIOG; break;
		case 7: Target_Port = GPIOH; break;
		default: break;
	}
	return Target_Port->IDR;
}

void GPIO_Interrupt_Enable (GPIO_Pin_t Pin, uint8_t Edge, uint8_t IT_Priority) {
	// 1- first edit SYSCONF to pass the desired pin to the corresponding EXTI line.
		// A. Define port and pin:
	uint32_t port_no = (uint32_t)(Pin / 16);
	uint8_t pin_no  = (uint8_t)(Pin % 16);
	uint8_t port_no_shift_ammount = (uint8_t) ((pin_no * 4) % 16);
	volatile uint32_t *EXTICR_Edit;
	uint8_t IRQ_NUM_of_EXTI_Line [16] = {6, 7, 8, 9, 10, 23, 23, 23, 23, 23, 40, 40, 40, 40, 40, 40};
		// B. Enable Clock for SYSCONFIG - Hanging on the APB2 bus.
	set_bit (RCC->APB2ENR, 0);

		/*
		 * Now, we have two cases: the value to be placed which is related to the port, and
		 * 							the position at which it will be placed which is related to pin number.
		 * 							the available positions are the SYSCONIG_EXTICR Registers (32-bit X 4 Registers).
		 * 							each registers low 16-bits are divided to 4 positions, the high 16-bits are reserved.
		 * 							each position of these registers controls the pin of which port will be passed to the
		 * 							corresponding EXTI line. refer to data manual page 249.
		 * 							EXTI 0->3: located at first 16-bit of (SYSCFG_EXTICR1)
		 * 							EXTI 4->7: located at first 16-bit of (SYSCFG_EXTICR2)
		 * 							EXTI 8->11: located at first 16-bit of (SYSCFG_EXTICR3)
		 * 							EXTI 12->15: located at first 16-bit of (SYSCFG_EXTICR4)
		 */

		// C. Define which register to edit, based on the pin number:
	if 		((pin_no >= 0) && (pin_no < 4))   EXTICR_Edit = &SYSCFG_COMP_OPAMP->EXTICR1;
	else if ((pin_no >= 4) && (pin_no < 8))   EXTICR_Edit = &SYSCFG_COMP_OPAMP->EXTICR2;
	else if ((pin_no >= 8) && (pin_no < 12))  EXTICR_Edit = &SYSCFG_COMP_OPAMP->EXTICR3;
	else if ((pin_no >= 12) && (pin_no < 16)) EXTICR_Edit = &SYSCFG_COMP_OPAMP->EXTICR4;

		// D. Clear the Corresponding bits, then mask the port value in it with the prober shift amount.
	*EXTICR_Edit &= (~(0xF<<port_no_shift_ammount));
	*EXTICR_Edit |= (port_no << port_no_shift_ammount);

	// 2- depending on the passed Edge, modify EXTI Registers (FTSR, RTSR) - pin_no represent the EXTI Line.
	if (Edge == PIN_IT_FALLING) {
		set_bit   (EXTI->FTSR1, pin_no);
		clear_bit (EXTI->RTSR1, pin_no);
	}
	else if (Edge == PIN_IT_RISING) {
		clear_bit (EXTI->FTSR1, pin_no);
		set_bit   (EXTI->RTSR1, pin_no);
	}
	else if (Edge == PIN_IT_CHANGING) {
		set_bit (EXTI->FTSR1, pin_no);
		set_bit (EXTI->RTSR1, pin_no);
	}

	// 3- Enable the Corresponding EXTI Line - pin_no represent the EXTI Line:
	set_bit (EXTI->IMR1, pin_no);

	// 4- define IRQ Number (from IRQ_NUM_of_EXTI_Line) of the EXTI line (pin_no), Enable it and Update its priority:
		// A. Enable IRQ:
	if (pin_no > 9) set_bit (NVIC_ISER [1], (IRQ_NUM_of_EXTI_Line [pin_no] - 32));
	else 			set_bit (NVIC_ISER [0], IRQ_NUM_of_EXTI_Line [pin_no]);
		// B. Update Priority:
	uint8_t priority_register_index = (uint8_t) (IRQ_NUM_of_EXTI_Line [pin_no] / 4);
	uint8_t priority_register_shift = (uint8_t) (IRQ_NUM_of_EXTI_Line [pin_no] % 4) * 8;
	uint32_t priority_32 = ((uint32_t)IT_Priority) << priority_register_shift;
	NVIC_IPR [priority_register_index] &= (~(0xFF<<priority_register_shift));
	NVIC_IPR [priority_register_index] |= priority_32;
}

void GPIO_Interrupt_Disable (GPIO_Pin_t Pin) {
	uint8_t pin_no  = (uint8_t)(Pin % 16);
	uint8_t IRQ_NUM_of_EXTI_Line [16] = {6, 7, 8, 9, 10, 23, 23, 23, 23, 23, 40, 40, 40, 40, 40, 40};

	// 1- first disable the corresponding EXTI line.
	clear_bit (EXTI->IMR1, pin_no);
	// 2- define IRQ Number of the EXTI line, Disable it.
	if (pin_no > 9) clear_bit (NVIC_ISER [1], (IRQ_NUM_of_EXTI_Line [pin_no] - 32));
	else 			clear_bit (NVIC_ISER [0], IRQ_NUM_of_EXTI_Line [pin_no]);
}

void GPIO_Interrupt_Set_Callback_Function (GPIO_Pin_t Pin, void (*CBK_FCN)()) {
	uint8_t pin_no  = (uint8_t)(Pin % 16);

	// pass the callback to the defined IRQ Handler.
	switch (pin_no) {
		case 0:  _EXTI0_IRQ_Handler     = CBK_FCN; break;
		case 1:  _EXTI0_IRQ_Handler     = CBK_FCN; break;
		case 2:  _EXTI0_IRQ_Handler     = CBK_FCN; break;
		case 3:  _EXTI0_IRQ_Handler     = CBK_FCN; break;
		case 4:  _EXTI0_IRQ_Handler     = CBK_FCN; break;
		case 5:  _EXTI9_5_IRQ_Handler   = CBK_FCN; break;
		case 6:  _EXTI9_5_IRQ_Handler   = CBK_FCN; break;
		case 7:  _EXTI9_5_IRQ_Handler   = CBK_FCN; break;
		case 8:  _EXTI9_5_IRQ_Handler   = CBK_FCN; break;
		case 9:  _EXTI9_5_IRQ_Handler   = CBK_FCN; break;
		case 10: _EXTI15_10_IRQ_Handler = CBK_FCN; break;
		case 11: _EXTI15_10_IRQ_Handler = CBK_FCN; break;
		case 12: _EXTI15_10_IRQ_Handler = CBK_FCN; break;
		case 13: _EXTI15_10_IRQ_Handler = CBK_FCN; break;
		case 14: _EXTI15_10_IRQ_Handler = CBK_FCN; break;
		case 15: _EXTI15_10_IRQ_Handler = CBK_FCN; break;
	}
}

void EXTI0_IRQHandler () {
	_EXTI0_IRQ_Handler ();
}

void EXTI1_IRQHandler () {
	_EXTI1_IRQ_Handler ();
}

void EXTI2_IRQHandler () {
	_EXTI2_IRQ_Handler ();
}

void EXTI3_IRQHandler () {
	_EXTI3_IRQ_Handler ();
}

void EXTI4_IRQHandler () {
	_EXTI4_IRQ_Handler ();
}

void EXTI9_5_IRQHandler () {
	_EXTI9_5_IRQ_Handler ();
}

void EXTI15_10_IRQHandler () {
	_EXTI15_10_IRQ_Handler ();
}
