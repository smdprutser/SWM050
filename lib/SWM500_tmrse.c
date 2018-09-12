/************************************************* ************************************************** ***************************************
* File name: SWM500_tmrse.c
* Function description: SWM500 multi-function timer TMRSE function driver library
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
#include "SWM500_tmrse.h"

static uint32_t PWMHighFirst0 = 0;			//1 High-level and low-level after PWM square-wave period 0 Low-level after PWM square-wave period
static uint32_t PWMHighFirst1 = 0;			//1 High-level and low-level after PWM square-wave period 0 Low-level after PWM square-wave period

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_Init()
* Function description: TMRSE timer initialization, including mode selection (timer, counter, PWM output, pulse width measurement, duty cycle 
*				measurement), timing cycle setting, interrupt enable, etc.
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* 			TMRSE_InitStructure * initStruct Structure containing TMRSE timer related settings
* Output: 	one
* Note: 	The corresponding pin must be switched to the correct mode (digital peripheral mode) before calling this function
************************************************** ************************************************** **************************************/
void TMRSE_Init(TMRSE_T * TMRSEx,TMRSE_InitStructure * initStruct)
{
	TMRSE_Open(TMRSEx);						// The bus clock can only be provided to the TMRSE module to read and write module registers
	
	TMRSEx->CTRL.ENA = 0;					// Disable TRMSE before configuring TMRSE				
	TMRSEx->CTRL.VALSAVE = 0;				//This feature is not easy to use, and has no uselessness. Discard it under any circumstances
			
	switch((uint32_t)TMRSEx)
	{
	case ((uint32_t)TMRSE0):
		switch(initStruct->mode)
		{
		case 0:								//Timer mode
			TMRSE0->CTRL.WMOD = 0;
			TMRSE0->CTRL.OSCMOD = 0;		//Internal clock
			TMRSE0->CTRL.SINGLE = initStruct->single_cycle;
		
			TMRSE0->TARVAL = initStruct->period;
		
			TMRSE0->CTRL.OUTMOD = initStruct->output_act;
			TMRSE0->OUT_LVL = initStruct->out_initLvl;
			break;
		
		case 1:								//Counter mode
			TMRSE0->CTRL.WMOD = 0;
			TMRSE0->CTRL.OSCMOD = 1;		//External clock
			TMRSE0->CTRL.SINGLE = initStruct->single_cycle;
		
			TMRSE0->CTRL.EDGE_F = initStruct->count_edge;
			TMRSE0->TARVAL = initStruct->period;
		
			TMRSE0->CTRL.OUTMOD = initStruct->output_act;
			TMRSE0->OUT_LVL = initStruct->out_initLvl;
			break;
		
		case 2:								//PWM output mode
			TMRSE0->CTRL.WMOD = 1;
			TMRSE0->CTRL.OSCMOD = initStruct->pwm_clksrc;	
			TMRSE0->CTRL.SINGLE = initStruct->single_cycle;
		
			TMRSE0->CTRL.OUTMOD = 1;		//Output inversion
			TMRSE0->OUT_LVL = (PWMHighFirst0 = initStruct->out_initLvl);
		
			TMRSE0->TARVAL = (PWMHighFirst0==0) ? (initStruct->pwm_l + (initStruct->pwm_h<<16)) :
												  (initStruct->pwm_h + (initStruct->pwm_l<<16));
			break;
		
		case 3:								//Pulse width measurement mode
			TMRSE0->CTRL.WMOD = 2;
			TMRSE0->CTRL.OSCMOD = 0;		//Internal clock
			TMRSE0->CTRL.SINGLE = initStruct->single_cycle;
			
			TMRSE0->CTRL.EDGE_F = initStruct->cap_trigger;
		
			TMRSE0->TARVAL = initStruct->period;
		
			TMRSE0->CTRL.OUTMOD = initStruct->output_act;
			TMRSE0->OUT_LVL = initStruct->out_initLvl;
			break;
		
		case 4:								//Duty cycle measurement mode
			TMRSE0->CTRL.WMOD = 3;
			TMRSE0->CTRL.OSCMOD = 0;		//Internal clock
			TMRSE0->CTRL.SINGLE = initStruct->single_cycle;
		
			TMRSE0->CTRL.EDGE_F = initStruct->cap_trigger;
		
			TMRSE0->TARVAL = initStruct->period;
		
			TMRSE0->CTRL.OUTMOD = initStruct->output_act;
			TMRSE0->OUT_LVL = initStruct->out_initLvl;
			break;
		}

		TMRSE0->INTCTRL.ENA =   1;		//Makes it always possible to query interrupt status via INTSTAT
		TMRSE0->INTCTRL.MASKn = (initStruct->en_int == 1) ? 1 : 0;
		if(initStruct->en_int == 1)
		{
			NVIC_EnableIRQ(TMRSE0_IRQn);
		}
		break;
	
	case ((uint32_t)TMRSE1):
		switch(initStruct->mode)
		{
		case 0:								//Timer mode
			TMRSE1->CTRL.WMOD = 0;
			TMRSE1->CTRL.OSCMOD = 0;		//Internal clock
			TMRSE1->CTRL.SINGLE = initStruct->single_cycle;
		
			TMRSE1->TARVAL = initStruct->period;
		
			TMRSE1->CTRL.OUTMOD = initStruct->output_act;
			TMRSE1->OUT_LVL = initStruct->out_initLvl;
			break;
		
		case 1:								//Counter mode
			TMRSE1->CTRL.WMOD = 0;
			TMRSE1->CTRL.OSCMOD = 1;		//External clock
			TMRSE1->CTRL.SINGLE = initStruct->single_cycle;
		
			TMRSE1->CTRL.EDGE_F = initStruct->count_edge;
			TMRSE1->TARVAL = initStruct->period;
		
			TMRSE1->CTRL.OUTMOD = initStruct->output_act;
			TMRSE1->OUT_LVL = initStruct->out_initLvl;
			break;
		
		case 2:								//PWM output mode
			TMRSE1->CTRL.WMOD = 1;
			TMRSE1->CTRL.OSCMOD = initStruct->pwm_clksrc;	
			TMRSE1->CTRL.SINGLE = initStruct->single_cycle;
		
			TMRSE1->CTRL.OUTMOD = 1;		//Output inversion
			TMRSE1->OUT_LVL = (PWMHighFirst1 = initStruct->out_initLvl);
		
			TMRSE1->TARVAL = (PWMHighFirst1==0) ? (initStruct->pwm_l + (initStruct->pwm_h<<16)) :
												  (initStruct->pwm_h + (initStruct->pwm_l<<16));
			break;
		
		case 3:								//Pulse width measurement mode
			TMRSE1->CTRL.WMOD = 2;
			TMRSE1->CTRL.OSCMOD = 0;		//Internal clock
			TMRSE1->CTRL.SINGLE = initStruct->single_cycle;
			
			TMRSE1->CTRL.EDGE_F = initStruct->cap_trigger;
		
			TMRSE1->TARVAL = initStruct->period;
		
			TMRSE1->CTRL.OUTMOD = initStruct->output_act;
			TMRSE1->OUT_LVL = initStruct->out_initLvl;
			break;
		
		case 4:								//Duty cycle measurement mode
			TMRSE1->CTRL.WMOD = 3;
			TMRSE1->CTRL.OSCMOD = 0;		//Internal clock
			TMRSE1->CTRL.SINGLE = initStruct->single_cycle;
		
			TMRSE1->CTRL.EDGE_F = initStruct->cap_trigger;
		
			TMRSE1->TARVAL = initStruct->period;
		
			TMRSE1->CTRL.OUTMOD = initStruct->output_act;
			TMRSE1->OUT_LVL = initStruct->out_initLvl;
			break;
		}

		TMRSE1->INTCTRL.ENA =   1;		//Makes it always possible to query interrupt status via INTSTAT
		TMRSE1->INTCTRL.MASKn = (initStruct->en_int == 1) ? 1 : 0;
		if(initStruct->en_int == 1)
		{
			NVIC_EnableIRQ(TMRSE1_IRQn);
		}
		break;
	}
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_Open()
* Function description: TMRSE timer enable, enable refers to provide the work clock for TMRSE module
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	None
* Note: 	The module register read/write operation does not work after the module clock is turned off
************************************************** ************************************************** **************************************/
void TMRSE_Open(TMRSE_T * TMRSEx)
{
	switch((uint32_t)TMRSEx)
	{
	case ((uint32_t)TMRSE0):
		SYS->PCLK_EN.TMRSE0_CLK = 1;
		break;
	
	case ((uint32_t)TMRSE1):
		SYS->PCLK_EN.TMRSE1_CLK = 1;
		break;
	}
}


/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_Close()
* Function description: TMRSE timer disable, disable refers to cut off the TMRSE module clock supply, thereby reducing energy consumption
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	None
* Note: 	The module register read/write operation does not work after the module clock is turned off
************************************************** ************************************************** **************************************/
void TMRSE_Close(TMRSE_T * TMRSEx)
{
	switch((uint32_t)TMRSEx)
	{
	case ((uint32_t)TMRSE0):
		SYS->PCLK_EN.TMRSE0_CLK = 0;
		break;
	
	case ((uint32_t)TMRSE1):
		SYS->PCLK_EN.TMRSE1_CLK = 0;
		break;
	}
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_Start()
* Function description: Start the specified TMRSE, start timing/counting
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output:	None
* Note: None
************************************************** ************************************************** **************************************/
void TMRSE_Start(TMRSE_T * TMRSEx)
{
	TMRSEx->CTRL.ENA = 1;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_Stop()
* Function description: Turn off the specified TMRSE and stop the timer/count
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void TMRSE_Stop(TMRSE_T * TMRSEx)
{
	TMRSEx->CTRL.ENA = 0;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_SetMode()
* Function Description: Set TMRSE working mode
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* 			uint32_t mode 0 Timer 1 Counter 2 PWM 3 Pulse Width Measurement 4 Duty Cycle Measurement
* Output: 	None
* Note: 	The working mode can be modified only when TMRSE is stopped
************************************************** ************************************************** **************************************/
void TMRSE_SetMode(TMRSE_T * TMRSEx,uint32_t mode)
{
	TMRSEx->CTRL.WMOD = (mode==0) ? 0 : (mode-1);
	
	switch(mode)
	{
	case 0:
		TMRSEx->CTRL.OSCMOD = 0;	//Internal clock
		break;
	
	case 1:
		TMRSEx->CTRL.OSCMOD = 1;	//External clock
		break;
	
	case 3:
	case 4:
		TMRSEx->CTRL.OSCMOD = 0;	//Internal clock
		break;
	}
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_GetMode()
* Function description: Query TMRSE working mode
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	0 Timer 1 Counter 2 PWM 3 Pulse Width Measurement 4 Duty Cycle Measurement
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t TMRSE_GetMode(TMRSE_T * TMRSEx)
{
	uint32_t mode;
	
	mode = TMRSEx->CTRL.WMOD+1;
	
	if((mode==1) && (TMRSEx->CTRL.OSCMOD==0)) mode = 0;
	
	return mode;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_SetLoop()
* Function Description: Set cycle mode
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* 			uint32_t single 1 single mode 0 circular mode
* Output: 	None
* Note: 	The cycle mode can be modified only when TMRSE is stopped
************************************************** ************************************************** **************************************/
void TMRSE_SetLoop(TMRSE_T * TMRSEx,uint32_t single)
{
	TMRSEx->CTRL.SINGLE = single;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_GetLoop()
* Function description: Query the TMRSE cycle mode
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	1 Single Mode 0 Loop Mode
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t TMRSE_GetLoop(TMRSE_T * TMRSEx)
{
	return TMRSEx->CTRL.SINGLE;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_SetCountEdge()
* Function description: Set count-up edge in counter mode
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* 			uint32_t edge_f 1 falling edge 0 rising edge
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void TMRSE_SetCountEdge(TMRSE_T * TMRSEx,uint32_t edge_f)
{
	TMRSEx->CTRL.EDGE_F = edge_f;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_GetCountEdge()
* Function description: Accumulate count edge in query counter mode
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	1 Falling edge 0 Rising edge
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t TMRSE_GetCountEdge(TMRSE_T * TMRSEx)
{
	return TMRSEx->CTRL.EDGE_F;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_SetPWMClkSrc()
* Function description: Set the PWM mode clock source
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* 			uint32_t ext 0 Internal Clock 1 External Clock
* Output:	None
* Note: 	The clock source can only be modified when TMRSE is stopped.
************************************************** ************************************************** **************************************/
void TMRSE_SetPWMClkSrc(TMRSE_T * TMRSEx,uint32_t ext)
{
	TMRSEx->CTRL.OSCMOD = ext;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_GetPWMClkSrc()
* Function description: Query PWM mode clock source
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	0 Internal clock 1 External clock
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t TMRSE_GetPWMClkSrc(TMRSE_T * TMRSEx)
{
	return TMRSEx->CTRL.OSCMOD;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_SetOutputAct()
* Function description: It is used to set the timer/counter to record the cycle value or pulse width measurement detects the second edge, and 
*				the output pin action is detected when the duty cycle measurement detects the third edge.
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* 			uint32_t act 00 No output 01 Invert 10 Set high 11 Set low
* Output: 	None
* Note: 	The output pin action can be modified only when TMRSE is stopped
* 			This value does not need to be set in PWM mode because forced pin inversion in PWM mode
************************************************** ************************************************** **************************************/
void TMRSE_SetOutputAct(TMRSE_T * TMRSEx,uint32_t act)
{
	TMRSEx->CTRL.OUTMOD = act;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_GetOutputAct()
* Function description: Query output pin action
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	00 No output 01 Inverted 10 Set high 11 Set low
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t TMRSE_GetOutputAct(TMRSE_T * TMRSEx)
{
	return TMRSEx->CTRL.OUTMOD;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_SetOutputLvl()
* Function Description: Set output pin level
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* 			uint32_t lvl 0 low 1 high
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void TMRSE_SetOutputLvl(TMRSE_T * TMRSEx,uint32_t lvl)
{
	TMRSEx->OUT_LVL = lvl;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_GetOutputLvl()
* Function description: Query output pin level
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	0 low 1 high
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t TMRSE_GetOutputLvl(TMRSE_T * TMRSEx)
{
	return TMRSEx->OUT_LVL;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_SetCAPTrigger()
* Function description: Set pulse width measurement and duty cycle measurement trigger edge
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	uint32_t edge_f 1 Falling edge 0 Rising edge
* Note: 	The capture trigger edge can only be modified when TMRSE is stopped
************************************************** ************************************************** **************************************/
void TMRSE_SetCAPTrigger(TMRSE_T * TMRSEx,uint32_t edge_f)
{
	TMRSEx->CTRL.EDGE_F = edge_f;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_GetCAPTrigger()
* Function description: Query pulse width measurement and duty cycle measurement trigger edge
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	1 Falling edge 0 Rising edge
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t TMRSE_GetCAPTrigger(TMRSE_T * TMRSEx)
{
	return TMRSEx->CTRL.EDGE_F;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_SetPeriod()
* Function description: Set the number of counts or timing of the specified TMRSE (in CPU clock cycles)
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* 			uint32_t period The number of TMRSE counts or timing (in CPU clock cycles)
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void TMRSE_SetPeriod(TMRSE_T * TMRSEx,uint32_t period)
{
	TMRSEx->TARVAL = period;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_GetPeriod()
* Function description: Query the number of counts or timing of the specified TMRSE (in CPU clock cycles)
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	Count or count time of TMRSE (in CPU clock cycles)
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t TMRSE_GetPeriod(TMRSE_T * TMRSEx)
{
	return TMRSEx->TARVAL;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_GetCurrent()
* Function description: Query the current count value (counter mode) or the current timing value (in CPU clock cycles) of the specified TMRSE
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	Current count value (counter mode) or current count value (in CPU clock cycles)
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t TMRSE_GetCurrent(TMRSE_T * TMRSEx)
{
	return TMRSEx->CURVAL;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_SetPWMLow()
* Function description: Set the PWM waveform low-level period length in units of CPU clock cycles
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* 			uint32_t count PWM waveform low period duration in CPU clock cycles
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void TMRSE_SetPWMLow(TMRSE_T * TMRSEx,uint32_t count)
{
	switch((uint32_t)TMRSEx)
	{
	case ((uint32_t)TMRSE0):
		TMRSE0->TARVAL = (PWMHighFirst0==0) ? (count + (TMRSE0->TARVAL&(0xFFFFU<<16))) :
											  ((TMRSE0->TARVAL&0xFFFFU) + (count<<16));
		break;
	
	case ((uint32_t)TMRSE1):
		TMRSE1->TARVAL = (PWMHighFirst1==0) ? (count + (TMRSE1->TARVAL&(0xFFFFU<<16))) :
											  ((TMRSE1->TARVAL&0xFFFFU) + (count<<16));
		break;
	}
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_GetPWMLow()
* Function description: Query PWM waveform low-level period length in CPU clock period
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	PWM waveform low-level period length in CPU clock cycles
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t TMRSE_GetPWMLow(TMRSE_T * TMRSEx)
{
	switch((uint32_t)TMRSEx)
	{
	case ((uint32_t)TMRSE0):
		return (PWMHighFirst0==0) ? (TMRSE0->TARVAL&0xFFFF) :
								    ((TMRSE0->TARVAL>>16)&0xFFFF);

	case ((uint32_t)TMRSE1):
		return (PWMHighFirst1==0) ? (TMRSE1->TARVAL&0xFFFF) :
								    ((TMRSE1->TARVAL>>16)&0xFFFF);
	
	default: return 0xFFFFFFFF;
	}
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_SetPWMHigh()
* Function Description: Set the PWM waveform high time duration, in units of CPU clock cycles
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* 			uint32_t count High-level time length of the PWM waveform in CPU clock cycles
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void TMRSE_SetPWMHigh(TMRSE_T * TMRSEx,uint32_t count)
{
	switch((uint32_t)TMRSEx)
	{
	case ((uint32_t)TMRSE0):
		TMRSE0->TARVAL = (PWMHighFirst0==0) ? ((TMRSE0->TARVAL&0xFFFFU) + (count<<16)) :
											  (count + (TMRSE0->TARVAL&(0xFFFFU<<16)));
		break;
	
	case ((uint32_t)TMRSE1):
		TMRSE1->TARVAL = (PWMHighFirst1==0) ? ((TMRSE1->TARVAL&0xFFFFU) + (count<<16)) :
											  (count + (TMRSE1->TARVAL&(0xFFFFU<<16)));
		break;
	}
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_GetPWMHigh()
* Function description: Query PWM waveform high-level period length in CPU clock period
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	Duration of PWM waveform high period in CPU clock cycles
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t TMRSE_GetPWMHigh(TMRSE_T * TMRSEx)
{
	switch((uint32_t)TMRSEx)
	{
	case ((uint32_t)TMRSE0):
		return (PWMHighFirst0==0) ? ((TMRSE0->TARVAL>>16)&0xFFFF) :
								    (TMRSE0->TARVAL&0xFFFF);

	case ((uint32_t)TMRSE1):
		return (PWMHighFirst1==0) ? ((TMRSE1->TARVAL>>16)&0xFFFF) :
								    (TMRSE1->TARVAL&0xFFFF);
	
	default: return 0xFFFFFFFF;
	}
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_SetPWMLowHig()
* Function description: Simultaneously set PWM waveform low-level period and high-level period length in CPU clock period
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* 			uint32_t low PWM waveform low period duration in CPU clock cycles
* 			uint32_t high Duration of PWM waveform high period in CPU clock cycles
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void TMRSE_SetPWMLowHig(TMRSE_T * TMRSEx,uint32_t low,uint32_t high)
{
	switch((uint32_t)TMRSEx)
	{
	case ((uint32_t)TMRSE0):
		TMRSE0->TARVAL = (PWMHighFirst0==0) ? (low + (high<<16)) :
											  (high + (low<<16));

		break;
	
	case ((uint32_t)TMRSE1):
		TMRSE1->TARVAL = (PWMHighFirst1==0) ? (low + (high<<16)) :
											  (high + (low<<16));

		break;
	}
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_GetCAPPulse()
* Function description: In the pulse width measurement mode, the captured pulse width is returned (in CPU clock cycles)
* 				Return to the captured waveform cycle (in CPU clock cycles) in duty cycle measurement mode
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	pulse width
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t TMRSE_GetCAPPulse(TMRSE_T * TMRSEx)
{
	return TMRSEx->CAPVAL;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_GetCAPPulseFP()
* Function description: FP means Front Part, which is the pulse width of the first half of the captured waveform in the duty cycle measurement mode (in CPU clock cycles)
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	1 Falling edge 0 Rising edge
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t TMRSE_GetCAPPulseFP(TMRSE_T * TMRSEx)
{
	return TMRSEx->CAPHALF;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_GetCurrentPos()
* Function description: Current position status, used in PWM mode and duty cycle mode to judge whether the current is in the first half cycle or the latter half cycle
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	0 is currently in the first half cycle 1 is currently in the second half of the cycle
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t TMRSE_GetCurrentPos(TMRSE_T * TMRSEx)
{
	return TMRSEx->STATE_P;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_INTEn()
* Function Description: Enables the specified TMRSE interrupt
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	None
* Note:		None
************************************************** ************************************************** **************************************/
void TMRSE_INTEn(TMRSE_T * TMRSEx)
{
	TMRSEx->INTCTRL.ENA =   1;		//Makes it always possible to query interrupt status via INTSTAT
	TMRSEx->INTCTRL.MASKn = 1;
	
	switch((uint32_t)TMRSEx)
	{
	case ((uint32_t)TMRSE0):
		NVIC_EnableIRQ(TMRSE0_IRQn);
		break;
	
	case ((uint32_t)TMRSE1):
		NVIC_EnableIRQ(TMRSE1_IRQn);
		break;
	}
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_INTDis()
* Function Description: Disables the specified TMRSE interrupt
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void TMRSE_INTDis(TMRSE_T * TMRSEx)
{
	TMRSEx->INTCTRL.MASKn = 0;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_INTClr()
* Function description: Clear the interrupt flag of the specified TMRSE
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	None
* Note: 	None
************************************************** ************************************************** **************************************/
void TMRSE_INTClr(TMRSE_T * TMRSEx)
{
	TMRSE_GetCurrent(TMRSEx);			//Read current value clear interrupt
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_INTStat()
* Function Description: Get the interrupt status of the specified TMRSE
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	1 Interrupt occurred 0 No interrupt occurred
* Note: 	This driver library ensures that TMRSE_INTStat() always returns the same value as TMRSE_INTRawStat(), so TMRSE_INTStat() always returns the correct interrupt status.
************************************************** ************************************************** **************************************/
uint32_t TMRSE_INTStat(TMRSE_T * TMRSEx)
{
	return TMRSEx->INTSTAT;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_INTRawStat()
* Function Description: Get the original status of the specified TMRSE
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	1 Interrupt occurred 0 No interrupt occurred
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t TMRSE_INTRawStat(TMRSE_T * TMRSEx)
{
	return TMRSEx->INTRSTAT;
}

/************************************************* ************************************************** ***************************************
* Function Name: TMRSE_INTOVStat()
* Function Description: Get the interrupt status of the specified TMRSE Overflow
* Input: 	TMRSE_T * TMRSEx specifies the timer to be set. Valid values include TMRSE
* Output: 	1 Interruption occurred Overflow 0 No interruption occurred Overflow
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t TMRSE_INTOVStat(TMRSE_T * TMRSEx)
{
	return TMRSEx->INTOFLAG;
}

