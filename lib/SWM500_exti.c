/****************************************************************************************************************************************** 
* File Name: SWM500_exti.c
* Function description: External interrupt function driver library of SWM500
* Technical support: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* Precautions:
* Version date: V1.0.0 June 30, 2013
* Upgrade record:
*
*
********************************************************************************************************************************************
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
#include "SWM500_exti.h"

/************************************************* ************************************************** ***************************************
* Function Name: EXTI_Init()
* Function description: Specify pin external interrupt initialization, including level trigger, edge trigger selection, low level (falling
* 				edge) trigger, high level (rising edge) trigger selection
* Input:	EXTI_T * EXTIx Specifies the port on which the external interrupt pin is located. Valid values include EXXI, which is the EXTI
*				external interrupt on the GPIOA port.
* 			uint32_t n Specifies the pins that generate pin external interrupts, including PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* 			uint32_t mode 0 level-triggered interrupt 1 falling-edge triggered interrupt
* 			uint32_t level 0 Low/Falling edge triggered interrupt 1 High/Rising edge triggered interrupt
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void EXTI_Init(EXTI_T * EXTIx,uint32_t n,uint32_t mode,uint32_t level)
{
	switch((uint32_t)EXTIx)
	{
	case ((uint32_t)EXTIA):
		if(mode == 0)
		{
			EXTIA->u32INTMODE &= ~(0x01 << n); 
		}
		else
		{
			EXTIA->u32INTMODE |= (0x01 << n);
		}

		if(level == 0)
		{
			EXTIA->u32INTLEVEL &= ~(0x01 << n);
		}
		else
		{
			EXTIA->u32INTLEVEL |= (0x01 << n);
		}
		break;
	}
}

/************************************************* ************************************************** ***************************************
* Function Name: EXTI_Open()
* Function Description: Specified pin external interrupt open (even if possible)
* Input:	EXTI_T * EXTIx Specifies the port on which the external interrupt pin is located. Optional values include EXXI, which is the EXTI
*				external interrupt on the GPIOA port.
* 			uint32_t n Specifies the pins that generate pin external interrupts, including PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void EXTI_Open(EXTI_T * EXTIx,uint32_t n)
{
	EXTIx->u32INTEN |= (0x01 << n);
	EXTIx->u32INTMSK &= ~(0x01 << n);
	
	NVIC_EnableIRQ((enum IRQn)(4+n));
}

/************************************************* ************************************************** ***************************************
* Function Name: EXTI_Close()
* Function Description: Specified pin external interrupt off (ie disable)
* Input: 	EXTI_T * EXTIx Specifies the port on which the external interrupt pin is located. Optional values include EXXI, which is the EXTI
*				external interrupt on the GPIOA port.
* 			int32_t n Specifies the pins that generate pin external interrupts, including PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void EXTI_Close(EXTI_T * EXTIx,uint32_t n)
{
	EXTIx->u32INTEN &= ~(0x01 << n);
}

/************************************************* ************************************************** ***************************************
* Function Name: EXTI_Clear()
* Function Description: Specifies pin external interrupt clear (ie clear interrupt flag to avoid re-entering this interrupt)
* Input:	EXTI_T * EXTIx Specifies the port on which the external interrupt pin is located. Optional values include EXXI, which is the EXTI
*				external interrupt on the GPIOA port.
* 			uint32_t n Specifies the pins that generate pin external interrupts, including PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void EXTI_Clear(EXTI_T * EXTIx,uint32_t n)
{
	EXTIx->u32INTCLR |= (0x01 << n);
}

/************************************************* ************************************************** ***************************************
* Function Name: EXTI_State()
* Function description: whether the interrupt has been triggered
* Input: 	EXTI_T * EXTIx Specifies the port on which the external interrupt pin is located. Optional values include EXXI, which is the EXTI
*				external interrupt on the GPIOA port.
* 			uint32_t n Specifies the pins that generate pin external interrupts, including PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* Output: 	uint32_t 0 No interrupt triggered 1 Trigger triggered
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t EXTI_State(EXTI_T * EXTIx, uint32_t n)
{
	return (EXTIx->u32INTSTAT & (0x01 << n)) ? 1 : 0;
}

/************************************************* ************************************************** ***************************************
* Function Name: EXTI_SetMode()
* Function Description: Set the external interrupt mode of the specified pin, including level trigger, edge trigger
* Input:	EXTI_T * EXTIx Specifies the port on which the external interrupt pin is located. Optional values include EXXI, which is the EXTI 
*				external interrupt on the GPIOA port.
* 			uint32_t n Specifies the pins that generate pin external interrupts, including PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* 			uint32_t mode 0 level-triggered interrupt 1 falling-edge triggered interrupt
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void EXTI_SetMode(EXTI_T * EXTIx,uint32_t n,uint32_t mode)
{
	if(mode == 0)
	{
		EXTIx->u32INTMODE &= ~(0x01 << n); 
	}
	else
	{
		EXTIx->u32INTMODE |= (0x01 << n);
	}
}

/************************************************* ************************************************** ***************************************
* Function Name: EXTI_GetMode()
* Function description: Get the external interrupt mode of the specified pin
* Input: 	EXTI_T * EXTIx Specifies the port on which the external interrupt pin is located. Optional values include EXXI, which is the EXTI 
*			external interrupt on the GPIOA port.
* 			uint32_t n Specifies the pins that generate pin external interrupts, including PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* Output: 	0 Level-triggered interrupt 1 Falling-edge triggered interrupt
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t EXTI_GetMode(EXTI_T * EXTIx,uint32_t n)
{
	return (EXTIx->u32INTMODE & (0x01 << n)) ? 1 : 0;
}

/************************************************* ************************************************** ***************************************
* Function Name: EXTI_SetLevel()
* Function description: Set the external interrupt level of the specified pin, including low level (falling edge) triggering and high level 
*				(rising edge) triggering.
* Input: 	EXTI_T * EXTIx Specifies the port on which the external interrupt pin is located. Optional values include EXXI, which is the EXTI 
*				external interrupt on the GPIOA port.
* 			uint32_t n Specifies the pins that generate pin external interrupts, including PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* 			uint32_t level 0 Low/Falling edge triggered interrupt 1 High/Rising edge triggered interrupt
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void EXTI_SetLevel(EXTI_T * EXTIx,uint32_t n,uint32_t level)
{
	if(level == 0)
	{
		EXTIx->u32INTLEVEL &= ~(0x01 << n);
	}
	else
	{
		EXTIx->u32INTLEVEL |= (0x01 << n);
	}
}

/************************************************* ************************************************** ***************************************
* Function Name: EXTI_GetLevel()
* Function Description: Get the external interrupt level of the specified pin
* Input: 	EXTI_T * EXTIx Specifies the port on which the external interrupt pin is located. Optional values include EXXI, which is the EXTI 
				external interrupt on the GPIOA port.
* 			uint32_t n Specifies the pins that generate pin external interrupts, including PIN_0, PIN_1, PIN_2, ... PIN_8, PIN_9
* Output:	0 low/falling edge triggered interrupt 1 high/rising edge triggered interrupt
* Note: N	one
************************************************** ************************************************** **************************************/
uint32_t EXTI_GetLevel(EXTI_T * EXTIx,uint32_t n)
{
	return (EXTIx->u32INTLEVEL & (0x01 << n)) ? 1 : 0;
}
