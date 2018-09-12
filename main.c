

#include <SWM500.h>


void main(void)
{
	PORT->PORTA_SEL.PA05=0;			// normal operation
	PORT->PORTA_PULLU.PA05=0;		// no pullup
	PORT->PORTA_INDIS.PA05=1;		// port enabled(?)
	GPIOA->DIR.DIR_5=1;			// output


	while(1)
	{
		GPIOA->DAT.DAT_5=1;

		GPIOA->DAT.DAT_5=0;
	}
}


