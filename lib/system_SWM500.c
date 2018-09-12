/****************************************************************************************************************************************** 
* 文件名称:	system_SWM1000.c
* 功能说明:	SWM1200单片机的时钟设置
* 技术支持:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.0.0		2012年10月30日
* 升级记录: 
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
#include <stdint.h>
#include "SWM500.h"


uint32_t SystemCoreClock  = __HSI;   				//System Clock Frequency (Core Clock)
uint32_t CyclesPerUs      = (__HSI / 1000000); 		//Cycles per micro second



/****************************************************************************************************************************************** 
* 函数名称: 
* 功能说明: This function is used to update the variable SystemCoreClock and must be called whenever the core clock is changed
* 输    入: 
* 输    出: 
* 注意事项: 
******************************************************************************************************************************************/
void SystemCoreClockUpdate(void)    
{
	uint16_t clk_div;

	if(SYS->CLK_CFG.CORE_CLK_DIV == 0)			//时钟分频为 0
	{
		clk_div = 2;
	}
	else if(SYS->CLK_CFG.CORE_CLK_DIV%2 == 1)	//时钟分频为奇数
	{
		clk_div = 1;
	}
	else										//时钟分频为偶数
	{
		clk_div = SYS->CLK_CFG.CORE_CLK_DIV;
	}

	if(SYS->DBL_IRC.DBL_IRC == 1)
		SystemCoreClock  = __HSI*2/clk_div;
	else
		SystemCoreClock  = __HSI/clk_div;
}

/****************************************************************************************************************************************** 
* 函数名称: 
* 功能说明: The necessary initializaiton of systerm
* 输    入: 
* 输    出: 
* 注意事项: 
******************************************************************************************************************************************/
void SystemInit(void)
{
	uint32_t i;
		
	SYS->CLK_CFG.CORE_CLK_DIV = 1;	//奇数：不分频   偶数：对应分频值（0为2分频）
	SYS->DBL_IRC.DBL_IRC = 0;		//0：内部时钟22M  1：内部时钟44M
	for(i = 0;i <10000;i++);		//等待时钟稳定。。。
	
	SystemCoreClockUpdate();
}
