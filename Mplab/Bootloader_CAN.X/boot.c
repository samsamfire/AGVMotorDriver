
#include "boot.h"
#include "mcc_generated_files/memory/flash.h"
#include "boot_can_process.h"
#include "mcc_generated_files/boot/boot_config.h"
#include "mcc_generated_files/can1.h"
#include "mcc_generated_files/boot/com_adaptor.h"


#include <stdbool.h>
#include <stdint.h>


static bool inBootloadMode = false;

static bool EnterBootloadMode(void);

uint8_t canAddress = 0;



void setCanFilter();


void BOOT_CAN_Initialize(){
    
    canAddress = ~(PORTBbits.RB12 + 2*PORTBbits.RB13 + 4*PORTBbits.RB14 + 8*PORTBbits.RB15)&(0x0F);
    //Enable CAN transmit and receive operations
    setCanFilter();
    CAN1_ReceiveEnable();
    CAN1_TransmitEnable();

}


void BOOT_CAN_Tasks(){
    
    if(inBootloadMode == false)
    {
        if( (EnterBootloadMode() == true) || (BOOT_Verify() == false) )
        {
            inBootloadMode = true;
        }
        else
        {
            BOOT_StartApplication();
        }
    }
    
    BOOT_ProcessCommand();
    //BOOT_COM_GetMessagesReady();
    
    
    
}



static bool EnterBootloadMode(void)
{
    #warning "Update this function to return 'true' when you want to stay in the boot loader, and 'false' when you want to allow a release to the application code"
 
    /* NOTE: This might be a a push button status on power up, a command from a peripheral, 
     * or whatever is specific to your boot loader implementation */    

    return false;
}
