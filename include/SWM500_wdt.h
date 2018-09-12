#ifndef __SWM500_WDT_H__
#define __SWM500_WDT_H__

typedef struct {
	uint32_t mode; //0 Watchdog resets the chip immediately after countdown from time1 to 0
	//1 The watchdog countdown from time1 to 0 does not reset the chip but instead generates an interrupt and starts counting down from time2 at the same time, resetting the chip if the interrupt flag is not cleared by zero.
	uint32_t time1; // see the explanation of mode; the value range is 0-15, which means the length of time is 2**(16+time1) CPU cycles
	uint32_t time2; // see the explanation of mode; the value range is 0-15, indicating the length of time is 2** (16+time2) CPU cycles
} WDT_InitStructure;

void WDT_Init(WDT_T * WDTx,WDT_InitStructure * initStruct); //WDT watchdog initialization
void WDT_Open(WDT_T * WDTx); //WDT watchdog enable, enable means provide the WDT module with an operating clock
void WDT_Close(WDT_T * WDTx); //WDT watchdog disable, disable refers to cut off the clock supply to the WDT module, thus reducing power consumption
void WDT_Start(WDT_T * WDTx); //Start the specified WDT and start counting down
void WDT_Stop(WDT_T * WDTx); //Close specified WDT, stop countdown
void WDT_Feed(WDT_T * WDTx); // Feed the dog and start the countdown from the load value again
void WDT_INTClr(WDT_T * WDTx); //Watchdog timer timeout interrupt flag clear
int32_t WDT_GetValue(WDT_T * WDTx); //Get the current countdown value of the specified watchdog timer
 
#endif //__SWM500_WDT_H__
