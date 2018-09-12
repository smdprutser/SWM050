#ifndef __SWM500_TMRSE_H__
#define __SWM500_TMRSE_H__

typedef struct {
	uint32_t mode; //0 Timer 1 Counter 2 PWM 3 Pulse Width Measurement 4 Duty Cycle Measurement
	uint32_t period; //Set timer/counter cycle in timer, counter, pulse width measurement, duty cycle measurement mode
	//Note: This value does not need to be set in PWM mode. The high and low levels in PWM mode are set by pwm_h and pwm_l respectively.
	uint32_t output_act; //Output pin action 00 No output 01 Invert 10 Set high 11 Set low
	// is used to set the timer/counter to the period value or pulse width measurement detects the second edge, and the duty cycle measures the output pin action when the third edge is detected
	//Note: This value does not need to be set in PWM mode because forced pin inversion in PWM mode
	uint32_t out_initLvl; //Output pin initial level status 0 Low level 1 High level
	//Note: The output pin start level can be set in all 5 modes
	uint32_t count_edge; //Which edge is counted up in counter mode 0 Rising edge 1 Falling edge
	uint32_t pwm_clksrc; //clock source selection in PWM mode 0 internal 1 external
	uint32_t pwm_h,pwm_l; //PWM high/low time, all in units of CPU clock cycles
	uint32_t cap_trigger; //Capture trigger edge 0 Rising edge 1 Falling edge
	uint32_t single_cycle; //1 Single cycle mode 0 Cycle mode
	uint32_t en_int; //Enable interrupt
} TMRSE_InitStructure;


void TMRSE_Init(TMRSE_T * TMRSEx, TMRSE_InitStructure * initStruct); // TMRSE timer initialization, including mode selection (timer, counter, PWM output, pulse width measurement, duty cycle measurement), timing cycle setting, interrupt enable, etc.
void TMRSE_Open(TMRSE_T * TMRSEx); //TMRSE timer enable, enable refers to provide clock to TMRSE module
void TMRSE_Close(TMRSE_T * TMRSEx); //The TMRSE timer is disabled. Disabling means cutting off the clock supply of the TMRSE module, thus reducing power consumption.
void TMRSE_Start(TMRSE_T * TMRSEx); // Start the specified TMRSE and start timing/counting
void TMRSE_Stop(TMRSE_T * TMRSEx); // Disable the specified TMRSE and stop the timer/count

void TMRSE_SetMode(TMRSE_T * TMRSEx, uint32_t mode); //mode: 0 Timer 1 Counter 2 PWM 3 Pulse width measurement 4 Duty cycle measurement
uint32_t TMRSE_GetMode(TMRSE_T * TMRSEx);
void TMRSE_SetLoop(TMRSE_T * TMRSEx, uint32_t single); //Set loop mode 1 Single mode 0 Loop mode
uint32_t TMRSE_GetLoop(TMRSE_T * TMRSEx);
void TMRSE_SetCountEdge(TMRSE_T * TMRSEx, uint32_t edge_f); // Set count-up edge in counter mode 1 Falling edge 0 Rising edge
uint32_t TMRSE_GetCountEdge(TMRSE_T * TMRSEx);
void TMRSE_SetPWMClkSrc(TMRSE_T * TMRSEx, uint32_t ext); // Set PWM mode clock source 0 Internal clock 1 External clock
uint32_t TMRSE_GetPWMClkSrc(TMRSE_T * TMRSEx);
void TMRSE_SetOutputAct(TMRSE_T * TMRSEx, uint32_t act); // Output pin action 00 No output 01 Invert 10 Set high 11 Set low
uint32_t TMRSE_GetOutputAct(TMRSE_T * TMRSEx);
void TMRSE_SetOutputLvl(TMRSE_T * TMRSEx, uint32_t lvl); // Set output pin level 0 Low 1 High
uint32_t TMRSE_GetOutputLvl(TMRSE_T * TMRSEx);
void TMRSE_SetCAPTrigger(TMRSE_T * TMRSEx, uint32_t edge_f); // Set pulse width measurement and duty cycle measurement trigger 1 Falling edge 0 Rising edge
uint32_t TMRSE_GetCAPTrigger(TMRSE_T * TMRSEx);

void TMRSE_SetPeriod(TMRSE_T * TMRSEx, uint32_t period); // Set the number of counts or timing of the specified TMRSE (in CPU clock cycles)
uint32_t TMRSE_GetPeriod(TMRSE_T * TMRSEx); //Get the number of counts or timing of the specified TMRSE (in CPU clock cycles)
uint32_t TMRSE_GetCurrent(TMRSE_T * TMRSEx); // Get the current count value (counter mode) or the current count value (in CPU clock cycles) of the specified TMRSE
void TMRSE_SetPWMLow(TMRSE_T * TMRSEx, uint32_t count); // Set PWM waveform low-level time period in CPU clock cycles
uint32_t TMRSE_GetPWMLow(TMRSE_T * TMRSEx);
void TMRSE_SetPWMHigh(TMRSE_T * TMRSEx, uint32_t count); // Set the PWM waveform high time period in CPU clock cycles
uint32_t TMRSE_GetPWMHigh(TMRSE_T * TMRSEx);
void TMRSE_SetPWMLowHig (TMRSE_T * TMRSEx, uint32_t low, uint32_t high); // Set the length of the low and high periods of the PWM waveform in units of CPU clock cycles.
uint32_t TMRSE_GetCAPPulse(TMRSE_T * TMRSEx); // In pulse width measurement mode, the captured pulse width is returned (in CPU clock cycles)
// Return to the captured waveform cycle (in CPU clock cycles) in duty cycle measurement mode
uint32_t TMRSE_GetCAPPulseFP(TMRSE_T * TMRSEx); //FP means Front Part, the pulse width of the first half of the captured waveform in the duty cycle measurement mode (in CPU clock cycles)
uint32_t TMRSE_GetCurrentPos (TMRSE_T * TMRSEx); // Current position status, used in PWM mode and duty cycle mode to determine whether it is in the first half cycle or the second half cycle
//0 is currently in the first half of the cycle 1 is currently in the second half of the cycle

void TMRSE_INTEn(TMRSE_T * TMRSEx); //Enable the interrupt specified TMRSE
void TMRSE_INTDis(TMRSE_T * TMRSEx); // disable interrupts that specify TMRSE
void TMRSE_INTClr(TMRSE_T * TMRSEx); // Clear the interrupt flag for the specified TMRSE
uint32_t TMRSE_INTStat(TMRSE_T * TMRSEx); // Get the interrupt status of the specified TMRSE
uint32_t TMRSE_INTRawStat(TMRSE_T * TMRSEx); // Get the original status of the specified TRMSE
uint32_t TMRSE_INTOVStat(TMRSE_T * TMRSEx); // Get the interrupt status of the specified TMRSE Overflow


#endif //__SWM500_TMRSE_H__