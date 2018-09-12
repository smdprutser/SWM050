#ifndef __SWM500_GPIO_H__
#define __SWM500_GPIO_H__

typedef struct {
	uint16_t func; // Pin function: 0 pin is GPIO function 1 pin is digital peripheral function (including UART, SPI, PWM, etc. What specific pin is for digital peripheral function please see chip manual
	//2 Pins are analog peripheral functions (including ADCs, amplifiers, comparators, etc.) For specific pins, what analog peripheral functions are specified? See the chip manual 3 for functions with the same value as 2
	uint8_t pull_up; // Pin pullup enabled 0 Pullup not enabled 1 Pullup enabled
	uint8_t pull_down; //pin pull down enable 0 don't enable pull down 1 enable pull down
	uint8_t open_drain; // open drain enable 0 pin in push-pull mode 1 open drain mode
	uint8_t dir; // pin direction: 0 pin is input 1 pin is output
} GPIO_InitStructure; // Structures that contain various features of the GPIO pins


void GPIO_Init(GPIO_T * GPIOx, uint32_t n, GPIO_InitStructure * initStruct); // Pin initialization, switching specified pin functions, including GPIO function, digital peripheral function, analog peripheral function
void GPIO_SetBit(GPIO_T * GPIOx, uint32_t n); // Set the pin level specified by the parameter to high
void GPIO_ClrBit(GPIO_T * GPIOx, uint32_t n); // Deassert the pin level specified by the parameter
void GPIO_InvBit(GPIO_T * GPIOx, uint32_t n); //Invert the pin level specified by the parameter
uint32_t GPIO_GetBit(GPIO_T * GPIOx, uint32_t n); //Read the level state of the pin specified by the parameter
void GPIO_SetBits(GPIO_T * GPIOx, uint32_t n, uint32_t w); // Set the level of the w-bit continuous pin from n specified by the parameter to high
void GPIO_ClrBits(GPIO_T * GPIOx, uint32_t n, uint32_t w); // Deassert the level of the w-bit consecutive pin from n specified by the parameter
void GPIO_InvBits(GPIO_T * GPIOx, uint32_t n, uint32_t w); // Invert the level of the w-bit continuation pin from n specified by the argument
uint32_t GPIO_GetBits(GPIO_T * GPIOx, uint32_t n, uint32_t w); // Reads the level state of the w-bit continuation pin specified by n from n


#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7
#define PIN_8 8
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11
#define PIN_12 12
#define PIN_13 13
#define PIN_14 14
#define PIN_15 15
#define PIN_16 16
#define PIN_17 17
#define PIN_18 18
#define PIN_19 19
#define PIN_20 20
#define PIN_21 21
#define PIN_22 22
#define PIN_23 23
#define PIN_24 24
#define PIN_25 25
#define PIN_26 26
#define PIN_27 27
#define PIN_28 28
#define PIN_29 29
#define PIN_30 30
#define PIN_31 31

#endif //__SWM500_GPIO_H__
