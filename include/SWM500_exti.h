#ifndef __SWM500_EXTI_H__
#define __SWM500_EXTI_H__

void EXTI_Init(EXTI_T * EXTIx, uint32_t n, uint32_t mode, uint32_t level); //Specify pin external interrupt initialization, including level trigger, edge trigger selection, low level (falling edge) trigger, high level (rising edge ) Trigger selection
void EXTI_Open(EXTI_T * EXTIx, uint32_t n); //Specify pin external interrupt to open (even if it can)
void EXTI_Close(EXTI_T * EXTIx, uint32_t n); // Specifies pin external interrupt off (ie disable)
void EXTI_Clear(EXTI_T * EXTIx, uint32_t n); //Specify pin external interrupt clear (ie clear interrupt flag to avoid re-entering this interrupt)

uint32_t EXTI_State(EXTI_T * EXTIx, uint32_t n);



void EXTI_SetMode (EXTI_T * EXTIx, uint32_t n, uint32_t mode); // set the pin external interrupt mode, including level trigger, edge trigger
uint32_t EXTI_GetMode (EXTI_T * EXTIx, uint32_t n); // Get the mode of the external interrupt specified pin
void EXTI_SetLevel (EXTI_T * EXTIx, uint32_t n, uint32_t level); // Set the external interrupt level of the specified pin, including low (falling) trigger, high (rising) trigger
uint32_t EXTI_GetLevel(EXTI_T * EXTIx, uint32_t n); //Get the external interrupt level of the specified pin

#endif //__SWM500_EXTI_H__
