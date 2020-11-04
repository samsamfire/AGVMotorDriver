#include "interrupts.h"
#include "can_app.h"
#include "app.h"
#include "mcc_generated_files/system.h"
#include <stdio.h>
#include <stdlib.h>




void Tmr3_interrupt(void)
{
	cappData.sendCanMessages = 1; //Around 50 ms
}


void Tmr2_interrupt(void)
{
	//Update PIDs
	appData.updateMotor = 1;

}


















