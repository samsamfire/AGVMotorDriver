/*
 * File:   com_adaptor_can.c
 * Author: samfi
 *
 * Created on November 17, 2020, 1:27 PM
 */


#include "xc.h"
#include <string.h>
#include "mcc_generated_files/can_types.h"
#include "mcc_generated_files/can1.h"
#include "mcc_generated_files/boot/boot_config.h"

#define CAN_BUFFER_MAX_SIZE 16


CAN_MSG_OBJ canMsg;

struct COM_DATA_STRUCT {
    uint8_t pendingCommand[BOOT_CONFIG_MAX_PACKET_SIZE];
    uint16_t pendingCommandLength;
    bool isPendingCommandLoaded;
    uint8_t responseBuffer[BOOT_CONFIG_MAX_PACKET_SIZE];
    uint16_t responseBufferLength;
    bool isResponseLoaded;
};

struct CAN_DATA_STRUCT {
    
    CAN_MSG_OBJ pendingCommand[CAN_BUFFER_MAX_SIZE];
    uint16_t pendingCommandLength;
    bool isPendingCommandLoaded;
    CAN_MSG_OBJ responseBuffer[CAN_BUFFER_MAX_SIZE];
    uint16_t responseBufferLength;
    bool isResponseLoaded;
    
};

struct CAN_DATA_STRUCT canComData;

//Writting to host
CAN_TX_MSG_REQUEST_STATUS BOOT_COM_Write(CAN_MSG_OBJ msgTx[], uint16_t length){
    int i =0;
    CAN_TX_MSG_REQUEST_STATUS transmit_result;
    //Define what do to 
    for(i=0;i<length;i++){
        transmit_result = CAN1_Transmit(CAN_PRIORITY_HIGH,&msgTx[i]);
        if(transmit_result != 0){
            if(transmit_result == CAN_TX_MSG_REQUEST_BUFFER_FULL){
                //If buffer is full keep sending until buffer is not full
                while(CAN1_Transmit(CAN_PRIORITY_HIGH,&msgTx[i]) == CAN_TX_MSG_REQUEST_BUFFER_FULL );
            }
            //return transmit_result;
        }
    }
    return CAN_TX_MSG_REQUEST_SUCCESS;
}

uint16_t BOOT_COM_GetMessagesReady()
{
     static bool initialized=false;
     
    if (!initialized)
    {
        // ======================================================================================================
        // During com_adaptor_initialization the user may want to check the UART for any errors here before 
        // proceeding. Make sure the RX line is either driven high by the transmitter or pulled high via a pullup.
        // Failure to do so could cause the user to encounter frame errors or other line errors which can be 
        // difficult to debug.
        // ======================================================================================================      
        memset(&canComData,0, sizeof(struct CAN_DATA_STRUCT )/sizeof(uint8_t));
        initialized = true;
    }
    
    
    return CAN1_ReceivedMessageCountGet();
}

void BOOT_COM_Read(CAN_MSG_OBJ msgTx[],uint16_t length){

    uint16_t i =0;
    
    if (BOOT_COM_GetMessagesReady() >= length)
    {
        for (i = 0; i < length; i++)
        {
            msgTx[i] = canComData.pendingCommand[i];
        }

        i = length;
        canComData.pendingCommandLength = 0;   
        canComData.isPendingCommandLoaded = false;
    }

    return i;

};


CAN_MSG_OBJ BOOT_COM_Peek(uint16_t location)
{
    return canComData.pendingCommand[location];
}
