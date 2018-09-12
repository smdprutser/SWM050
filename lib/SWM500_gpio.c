/************************************************* ************************************************** ***************************************
* File Name: SWM500_gpio.c
* Function description: Universal input and output function driver library of SWM500
* Technical support: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* Precautions:
* Version date: V1.0.0 June 30, 2013
* Upgrade record:
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION 
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE 
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT 
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology 
*******************************************************************************************************************************************/
#include "SWM500.h"
#include "SWM500_gpio.h"


/************************************************* ************************************************** ***************************************
* Function Name: GPIO_Init()
* Function description: Pin initialization, switching specified pin function, including GPIO function, digital peripheral function, analog 
				peripheral function
* Input: 	GPIO_T * GPIOx indicates GPIO port, valid values include GPIOA
* 			uint32_t n indicates the GPIO pin. Valid values include PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* 			GPIO_InitStructure * initStruct Structure pointer containing GPIO pin related setpoints
* Output: 	None
* Note: 	All member variables of the initStruct structure must be given the correct value
************************************************** ************************************************** **************************************/
void GPIO_Init(GPIO_T * GPIOx,uint32_t n,GPIO_InitStructure * initStruct)
{
	switch((uint32_t)GPIOx)
	{
	case ((uint32_t)GPIOA):
		PORT->u32PORTA_SEL &= ~(0x03 << (2*n));
		PORT->u32PORTA_SEL |= (initStruct->func << (2*n));

		if(initStruct->pull_up == 0)
		{
			PORT->u32PORTA_PULLU &= ~(0x01 << n);
		}
		else
		{
			PORT->u32PORTA_PULLU |= (0x01 << n);
		}
		
// 		if(initStruct->pull_down == 0)
// 		{
// 			PORT->u32PORTA_PULLD &= ~(0x01 << n);
// 		}
// 		else
// 		{
// 			PORT->u32PORTA_PULLD |= (0x01 << n);
// 		}

// 		if(initStruct->open_drain == 0)
// 		{
// 			PORT->u32PORTA_OPEND &= ~(0x01 << n);
// 		}
// 		else
// 		{
// 			PORT->u32PORTA_OPEND |= (0x01 << n);
// 		}

		if(((GPIOA->u32DIR >> n)&0x01) != initStruct->dir)
		{
			if(((GPIOA->u32DIR >> n)&0x01) ==0)
			{
			 	GPIOA->u32DIR |= 1 << n;
			}
			else
			{
				GPIOA->u32DIR &= ~(1 << n);
			}
		}
		break;
	}
}

/************************************************* ************************************************** ***************************************
* Function Name: GPIO_SetBit()
* Function Description: Set the pin level specified by parameter
* Input: 	GPIO_T * GPIOx indicates the GPIO port, which can include GPIOA
* 			uint32_t n indicates the GPIO pin. Possible values include PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void GPIO_SetBit(GPIO_T * GPIOx,uint32_t n)
{
	GPIOx->u32DAT |= (0x01 << n);
}

/************************************************* ************************************************** ***************************************
* Function Name: GPIO_ClrBit()
* Function description: Deassert the pin level specified by the parameter
* Input: 	GPIO_T * GPIOx indicates the GPIO port, which can include GPIOA
* 			uint32_t n indicates the GPIO pin. Possible values include PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void GPIO_ClrBit(GPIO_T * GPIOx,uint32_t n)
{
	GPIOx->u32DAT &= ~(0x01 << n);
}

/************************************************* ************************************************** ***************************************
* Function Name: GPIO_InvBit()
* Function Description: Invert the pin level specified by the parameter
* Input: 	GPIO_T * GPIOx indicates the GPIO port, which can include GPIOA
* 			uint32_t n indicates the GPIO pin. Possible values include PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void GPIO_InvBit(GPIO_T * GPIOx,uint32_t n)
{
	if(((GPIOx->u32DAT >> n) & 0x01) == 0)
	{
		GPIOx->u32DAT |= (0x01 << n);
	}
	else
	{
		GPIOx->u32DAT &= ~(0x01 << n);
	}
}

/************************************************* ************************************************** ***************************************
* Function Name: GPIO_GetBit()
* Function Description: Reads the level state of the pin specified by the parameter
* Input: 	GPIO_T * GPIOx indicates the GPIO port, which can include GPIOA
* 			uint32_t n indicates the GPIO pin. Possible values include PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* Output: 	Level status of pin specified by parameter 0 Low level 1 High level
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t GPIO_GetBit(GPIO_T * GPIOx,uint32_t n)
{
	uint32_t v;

	switch((uint32_t)GPIOx)
	{
	case ((uint32_t)GPIOA):
		v = (GPIO_EXTA->u32EXT >> n) & 0x01;	break;
	default:
		v = 0xFFFFFFFF;							break;
	}

	return v;
}

/************************************************* ************************************************** ***************************************
* Function Name: GPIO_SetBits()
* Function description: Sets the level of the continuous pin of w bit specified by the parameter from n
* Input:	GPIO_T * GPIOx indicates the GPIO port, which can include GPIOA
* 			uint32_t n indicates the GPIO pin. Possible values include PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* 			uint32_t w specifies the number of pins to set the pin high
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void GPIO_SetBits(GPIO_T * GPIOx,uint32_t n,uint32_t w)
{
	uint32_t bits;

	bits = 0xFFF>>(12-w);
	GPIOx->u32DAT |= (bits << n);
}

/************************************************* ************************************************** ***************************************
* Function Name: GPIO_ClrBits()
* Function description: Deassert the level of w-bit continuous pin from n specified by the parameter
* Input:	GPIO_T * GPIOx indicates the GPIO port, which can include GPIOA
* 			uint32_t n indicates the GPIO pin. Possible values include PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* 			uint32_t w Specifies the number of pins to be deasserted
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void GPIO_ClrBits(GPIO_T * GPIOx,uint32_t n,uint32_t w)
{
	uint32_t bits;

	bits = 0xFFF>>(12-w);
	GPIOx->u32DAT &= ~(bits << n);
}

/************************************************* ************************************************** ***************************************
* Function Name: GPIO_InvBits()
* Function Description: Inverts the level of the w-bit continuous pin from n specified by the parameter
* Input: 	GPIO_T * GPIOx indicates the GPIO port, which can include GPIOA
* 			uint32_t n indicates the GPIO pin. Possible values include PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* 			uint32_t w Specifies the number of pins to be level inverted
* Output: 	None
* Note: 	none
************************************************** ************************************************** **************************************/
void GPIO_InvBits(GPIO_T * GPIOx,uint32_t n,uint32_t w)
{
	uint32_t bits;
	uint32_t dat1,dat2;	

	bits = 0xFFF>>(12-w);
   	dat1 = GPIOx->u32DAT;
	dat2 = dat1&(~(bits<<n));
	dat1 = (~dat1)&(bits<<n);

	GPIOx->u32DAT =dat2|dat1;
}

/************************************************* ************************************************** ***************************************
* Function Name: GPIO_GetBits()
* Function description: Reads the level state of the w-bit continuous pin from n specified by the parameter
* Input: 	GPIO_T * GPIOx indicates the GPIO port, which can include GPIOA
* 			int32_t n indicates the GPIO pin. Possible values include PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* 			uint32_t w specifies the number of pins to set the pin high
* Output: 	Parameter specifies the state of the continuous state of the w-bit pin starting at n 0 Low 1 High
* The 0th bit of the return value indicates the level state of the pin n, the first bit of the return value indicates the level state of the 
* pin n+1... The wth bit of the return value indicates the pin n+w Level status
* Note: None
************************************************** ************************************************** **************************************/
uint32_t GPIO_GetBits(GPIO_T * GPIOx,uint32_t n,uint32_t w)
{
	uint32_t bits;
	uint32_t vals;

   	bits = 0xFFF>>(12-w);

	switch((uint32_t)GPIOx)
	{
	case ((uint32_t)GPIOA):
		vals = (GPIO_EXTA->u32EXT >> n) & bits;	break;
	default:
		vals = 0xFFFFFFFF;						break;
	}

	return vals;
}
