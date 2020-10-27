#include "interrupts.h"
#include "app.h"
#include "mcc_generated_files/system.h"
#include <stdio.h>
#include <stdlib.h>






void Tmr3_interrupt(void)
{
	appData.sendCanMessages = 1;
}





















