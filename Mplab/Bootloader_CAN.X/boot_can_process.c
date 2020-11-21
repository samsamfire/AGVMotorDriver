#include "boot_can_process.h"
#include "boot_can_messages.h"
#include "mcc_generated_files/boot/boot_config.h"
#include "mcc_generated_files/memory/flash.h" 
#include "mcc_generated_files/can_types.h"
#include "boot_can_messages.h"
#include "mcc_generated_files/boot/com_adaptor.h"
#include "boot.h"
#include "mcc_generated_files/can1.h"
#include <math.h>
#include <string.h>




void BOOT_Initialize() 
{
    
}




uint8_t getCmdId(CAN_MSG_OBJ * msgRx){

    return (msgRx->msgId) & 0b00001111111;
}



static enum BOOT_COMMAND_RESULT ReadVersion(void);
static enum BOOT_COMMAND_RESULT ReadFlash(const CAN_MSG_OBJ msg);
static enum BOOT_COMMAND_RESULT WriteFlash(const CAN_MSG_OBJ msg);

static enum BOOT_COMMAND_RESULT CommandError(enum BOOT_COMMAND_RESPONSES errorType)
{
    CAN_MSG_OBJ msgTx;
    
    msgTx.field = NO_DATA_FIELD;
    msgTx.msgId = canAddress <<7 | errorType;
    
    BOOT_COM_Write(&msgTx,1);
    
    return BOOT_COMMAND_ERROR;
}

enum BOOT_COMMAND_RESULT BOOT_ProcessCommand(void)
{    
    uint16_t msgs_ready = BOOT_COM_GetMessagesReady();
    CAN_MSG_OBJ msgRx;
    uint8_t dataRx[8];
    uint8_t msgId = 0;
    msgRx.data = &dataRx[0];

    if (msgs_ready == 0) 
    { 
        return BOOT_COMMAND_NONE; 
    }

    else{
        
        CAN1_Receive(&msgRx);
        
    }
    
    
    msgId = getCmdId(&msgRx);
   
    switch (msgId)
    {
  
        case READ_VERSION:

            return ReadVersion();

        case READ_FLASH:
            
            return ReadFlash(msgRx);
            
        case WRITE_FLASH:
            
            return WriteFlash(msgRx);
    
    default:
        return CommandError(UNSUPPORTED_COMMAND);
        break;
    }
    
    return BOOT_COMMAND_ERROR;
}



void BOOT_StartApplication()
{
    int (*user_application)(void);
    user_application = (int(*)(void))BOOT_CONFIG_APPLICATION_RESET_ADDRESS;
    user_application();       
}  


static enum BOOT_COMMAND_RESULT ReadVersion(void)
{
    uint8_t data[8];
    
    data[0] = 0x11;
    data[1] = 0x22;
    data[2] = 0x33;
    data[3] = 0x44;
    data[4] = 0x55;
    data[5] = 0x66;
    data[6] = 0x77;
    data[7] = 0x88;
    
    CAN_MSG_OBJ msgTx ={
        .msgId = READ_VERSION,
        .field = FULL_DATA_FIELD,
        .data = data
        
    };
    
    //(void)BOOT_COM_Read(commandArray, sizeof(struct CMD_STRUCT_0));
    BOOT_COM_Write(&msgTx, 1);

    return BOOT_COMMAND_SUCCESS;
}

static bool IsLegalAddress(uint32_t addressToCheck)
{
   return ( (addressToCheck >= BOOT_CONFIG_PROGRAMMABLE_ADDRESS_LOW) && (addressToCheck < BOOT_CONFIG_PROGRAMMABLE_ADDRESS_HIGH) );
}


static enum BOOT_COMMAND_RESULT ReadFlash(const CAN_MSG_OBJ msg)
{
    
    uint32_t flashData;
    uint32_t address;
    uint16_t nbBytes;
    uint16_t nbMessages;
    uint16_t count;
    uint8_t data[BOOT_CONFIG_MAX_PACKET_SIZE];
    CAN_MSG_OBJ msgData[BOOT_CONFIG_MAX_PACKET_SIZE/8];
    
    
    address = ((uint32_t)msg.data[0]<<24) | ((uint32_t)msg.data[1]<<16) | ((uint32_t)msg.data[2]<<8) | ((uint32_t)msg.data[3]);
    nbBytes = ((uint16_t)msg.data[4]<<8) | ((uint16_t)msg.data[5]);
    nbMessages = ceil(nbBytes/8);
    
    if(msg.field.dlc != 6){
        
        BOOT_COM_Response(BAD_DLC);
        return BOOT_COMMAND_ERROR;
    }
    
   

    
    
    if ( IsLegalAddress(address) && IsLegalAddress(address+nbBytes-1) && ((nbBytes%4)==0) && nbBytes <= BOOT_CONFIG_MAX_PACKET_SIZE )
    {
        //This is for retreiving the flash data
        for (count = 0; count < nbBytes; count += 4)
        {
            flashData = FLASH_ReadWord24(address+count/2);
            memcpy(&data[count], &flashData, 4);
        }
        //This is for copying the flash data into a can message array;
        
        for(count = 0; count < nbMessages; count+=1){
            
            msgData[count].data = &data[count*8];
            msgData[count].msgId = (canAddress) << 7 | READ_FLASH_RESULT;
            msgData[count].field = FULL_DATA_FIELD;
        }
        
    } 
    else
    {
        BOOT_COM_Response(BAD_ADDRESS);
        
        return BOOT_COMMAND_ERROR;        
    }
    
    if(BOOT_COM_Write(msgData,nbMessages)==CAN_TX_MSG_REQUEST_SUCCESS){
        
        return BOOT_COMMAND_SUCCESS;
    }
    
    else{
        
        return BOOT_COMMAND_ERROR;
    }

    return BOOT_COMMAND_SUCCESS;
}




static enum BOOT_COMMAND_RESULT WriteFlash(const CAN_MSG_OBJ msg)
{
 
    uint32_t unlockKey;
    uint32_t address;
    uint16_t nbBytes;
    uint16_t count;
    uint8_t cmdId;
    
    CAN_MSG_OBJ msgUnlock;
    CAN_MSG_OBJ msgData;

    
    uint8_t dataUnlock[8];
    uint8_t dataData[8];

    
    msgUnlock.data = dataUnlock;
    msgData.data = dataData;
    
    address = ((uint32_t)msg.data[0]<<24) | ((uint32_t)msg.data[1]<<16) | ((uint32_t)msg.data[2]<<8) | ((uint32_t)msg.data[3]);
    nbBytes = ((uint16_t)msg.data[4]<<8) | ((uint16_t)msg.data[5]);
    
    //Add timeout
    while(BOOT_COM_GetMessagesReady()== 0);
    
    
    CAN1_Receive(&msgUnlock);
    cmdId = getCmdId(&msgUnlock);
    
    if(cmdId == UNLOCK_FLASH){
        unlockKey = ((uint32_t)msgUnlock.data[0]<<24) | ((uint32_t)msgUnlock.data[1]<<16) | ((uint32_t)msgUnlock.data[2]<<8) | ((uint32_t)msgUnlock.data[3]);
    }
    else{
        return BOOT_COMMAND_ERROR;
    }
    
            
    if ( IsLegalAddress(address) && IsLegalAddress(address+nbBytes-1) && ((nbBytes%4)==0) && nbBytes <= BOOT_CONFIG_MAX_PACKET_SIZE){
        
        FLASH_Unlock(unlockKey);

        for (count = 0; count < nbBytes; count += 8)
        {
            uint32_t flashData[2];
            
            //Wait for new data
            while(BOOT_COM_GetMessagesReady()== 0);
            CAN1_Receive(&msgData);
            cmdId = getCmdId(&msgData);
            
            if(cmdId == FLASH_DATA){
                memcpy(&flashData[0], msgData.data, 8);
                
            }
            
            else{
                
                BOOT_COM_Response(FLASH_CMD_ERROR); 
                return BOOT_COMMAND_ERROR;
            }

            if (FLASH_WriteDoubleWord24(address+count/2, flashData[0],flashData[1] ) == false)
            {
            }
        }
        
        BOOT_COM_Response(FLASH_WRITE_SUCCESS);

        FLASH_Lock();
        
        return BOOT_COMMAND_SUCCESS;
    }   
    
    else
    {
        
        BOOT_COM_Response(BAD_ADDRESS);
        
        return BOOT_COMMAND_ERROR;
    }
    
}


