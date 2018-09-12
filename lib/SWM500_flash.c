/************************************************* ************************************************** ***************************************
* File Name: SWM500_flash.c
* Function description: SWM500 microcontroller on-chip Flash read and write driver
* Technical support: http://www.synwit.com.cn/e/tool/gbook/?bid=1
* Precautions:
* Version date: V1.0.0 June 13, 2017
* Upgrade record:
*
*
************************************************** ************************************************** ***************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology
************************************************** ************************************************** ***************************************/
#include "SWM500.h"
#include "SWM500_flash.h"

typedef uint32_t (*IAP_Write_Func)(uint32_t, uint32_t*, uint32_t, uint32_t);
typedef uint32_t (*IAP_Erase_Func)(void);

IAP_Write_Func IAP_Write = (IAP_Write_Func)0x1000AB;
IAP_Erase_Func IAP_Erase = (IAP_Erase_Func)0x100127;

/************************************************* ************************************************** ***************************************
* Function Name: FLASH_Erase()
* Function description: Erase 128-word Flash data storage area on-chip
* Input: 	None
* Output: 	Erase Successful 0 Erase Failed
* Note: 	he chip clock cannot exceed 18MHz when erasing
************************************************** ************************************************** **************************************/
uint32_t FLASH_Erase(void)
{
	return IAP_Erase();
}

/************************************************* ************************************************** ***************************************
* Function Name: FLASH_Write()
* Function description: Write data to the specified position in the on-chip flash data memory area
* Input: 	uint32_t addr The position to be written, value 0--127
* 	uint32_t data[] data to write
* 	uint32_t count the number of words to write
* Output: 	 write success 0 write failed
* Note: 	The chip clock cannot exceed 18MHz when writing
************************************************** ************************************************** **************************************/
uint32_t FLASH_Write(uint32_t addr, uint32_t data[], uint32_t count)
{
	return IAP_Write(addr, data, count, 1);
}

/************************************************* ************************************************** ***************************************
* Function Name: FLASH_Read()
* Function description: Read data from the specified position in the on-chip flash data storage area
* Input: 	uint32_t addr The position to read, value 0--127
* 	uint32_t data[] read data storage location
* 	uint32_t count the number of words to read
* Output: 	1 Read succeeded 0 Read failed
* Note: 	None
************************************************** ************************************************** **************************************/
uint32_t FLASH_Read(uint32_t addr, uint32_t data[], uint32_t count)
{
	return IAP_Write(addr, data, count, 0);
}
