/*This file contains the different message ids recognized by the driver*/


#ifndef H_CAN_MESSAGE
#define H_CAN_MESSAGE

#include "mcc_generated_files/can_types.h"
#include "mcc_generated_files/system.h"
#include "app.h"



#define ADDRESS_REQ_ID (appData.canAddress << 7)|1

#define POS_REQ_ID (appData.canAddress << 7)|10; 
#define VEL_REQ_ID (appData.canAddress << 7)|11;
#define TORQUE_REQ_ID (appData.canAddress << 7)|12;


#define POS_VEL_TORQUE_REQ_ID (appData.canAddress <<7)|13;

#define POS_CMD_ID (appData.canAddress<<7)|20;
#define VEL_CMD_ID (appData.canAddress << 7)|21;
#define TORQUE_CMD_ID (appData.canAddress << 7)|22;




CAN_TX_MSG_REQUEST_STATUS sendPosVelTorque(uint16_t pos, int16_t vel, uint16_t torque);


/*This function is used in order to create a filter for the pic on the
CAN bus. The PIC will only receive the messages if the 4 upper bits of SID
correspond to the hex address given by the address switch*/

void setCanFilter();










#endif