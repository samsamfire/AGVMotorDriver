#include "interrupts.h"
#include "can_app.h"
#include "app.h"
#include "mcc_generated_files/system.h"
#include <stdio.h>
#include <stdlib.h>




void Tmr3_interrupt(void)
{
	cappData.sendCanMessages = 1; //Around 10 ms
}


void Tmr2_interrupt(void) //5ms
{
	//Update PIDs
	appData.updateMotor = 1; 

}


void Tmr4_interrupt(void)
{
	appData.updateQEI=1; //500us

}

















