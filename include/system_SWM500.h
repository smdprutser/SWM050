#ifndef __SYSTEM_M051Series_H__
#define __SYSTEM_M051Series_H__

#ifdef __cplusplus
 extern "C" {
#endif 


#define __HSI		(18000000UL)		//高速内部时钟

extern uint32_t SystemCoreClock;		// System Clock Frequency (Core Clock)
extern uint32_t CyclesPerUs;			// Cycles per micro second


/* Setup the microcontroller system Initialise GPIO directions and values */
extern void SystemInit(void);


/* Updates the SystemCoreClock with current core Clock retrieved from cpu registers */
extern void SystemCoreClockUpdate (void);

#ifdef __cplusplus
}
#endif

#endif //__SYSTEM_M051Series_H__
