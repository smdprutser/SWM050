/************************************************* ************************************************** ***************************************
* File Name: SWM500_wdt.c
* Function description: WDT watchdog function driver library for SWM500
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
#include "SWM500_wdt.h"


/************************************************* ************************************************** ***************************************
* Function Name: WDT_Init()
* Function description: WDT watchdog initialization
* Input: 	WDT_T * WDTx Specifies the watchdog to be set. Valid values include WDT.
* 			WDT_InitStructure * initStruct Structure containing watchdog related setpoints
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void WDT_Init(WDT_T * WDTx,WDT_InitStructure * initStruct)
{
	WDT_Open(WDTx);		//必须先给WDT模块提供总线时钟，才能对WDT模块寄存器进行读写操作
	
	WDTx->CR.RMOD = initStruct->mode;
	WDTx->TORR.TOP_INIT = initStruct->time1;
	WDTx->TORR.TOP = initStruct->time2;
	
	if(initStruct->mode == 1)
	{
		NVIC_EnableIRQ(WDT_IRQn);
	}

	WDT_Feed(WDTx);		//使能之前先喂一次狗	
}

/************************************************* ************************************************** ***************************************
* Function Name: WDT_Open()
* Function description: WDT watchdog enable, enable refers to provide WDT module with operating clock
* Input: 	WDT_T * WDTx Specifies the watchdog to be set. Valid values include WDT.
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void WDT_Open(WDT_T * WDTx)
{
	SYS->PCLK_EN.WDT_CLK = 1;	
}

/************************************************* ************************************************** ***************************************
* Function Name: WDT_Close()
* Function description: WDT watchdog disable, disable means to cut off the clock supply of the WDT module, thereby reducing energy consumption
* Input: 	WDT_T * WDTx Specifies the watchdog to be set. Valid values include WDT.
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void WDT_Close(WDT_T * WDTx)
{
	SYS->PCLK_EN.WDT_CLK = 0;	
}

/************************************************* ************************************************** ***************************************
* Function Name: WDT_Start()
* Function description: Start the specified WDT and start counting down
* Input: 	WDT_T * WDTx Specifies the watchdog to be set. Valid values include WDT.
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void WDT_Start(WDT_T * WDTx)
{
	WDTx->CR.EN = 1;
}

/************************************************* ************************************************** ***************************************
* Function Name: WDT_Stop()
* Function description: Close specified WDT, stop countdown
* Input: 	WDT_T * WDTx Specifies the watchdog to be set. Valid values include WDT.
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void WDT_Stop(WDT_T * WDTx)
{
	WDTx->CR.EN = 0;
}

/************************************************* ************************************************** ***************************************
* Function Name: WDT_Feed()
* Function description: Feed the dog and start the countdown from the loading value again
* Input: 	WDT_T * WDTx Specifies the watchdog to be set. Valid values include WDT.
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void WDT_Feed(WDT_T * WDTx)
{
	WDTx->CRR = 0x76;	
}

/************************************************* ************************************************** ***************************************
* Function Name: WDT_INTClr()
* Function description: Watchdog timer timeout interrupt flag clear
* Input: 	WDT_T * WDTx Specifies the watchdog to be set. Valid values include WDT.
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void WDT_INTClr(WDT_T * WDTx)
{
	uint32_t tmp;

	tmp = WDTx->ICLR;
	tmp = tmp;	
}

/************************************************* ************************************************** ***************************************
* Function name: WDT_GetValue()
* Function description: Get the current countdown value of the specified watchdog timer
* Input: 	DT_T * WDTx Specifies the watchdog to be set. Valid values include WDT.
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
int32_t WDT_GetValue(WDT_T * WDTx)
{
	return WDTx->CCVR;
}


