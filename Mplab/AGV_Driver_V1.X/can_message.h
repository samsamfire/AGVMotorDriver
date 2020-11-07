/*This file contains the different message ids recognized by the driver*/


#ifndef H_CAN_MESSAGE
#define H_CAN_MESSAGE

#include "mcc_generated_files/can_types.h"
#include "mcc_generated_files/system.h"


#define START_ID 33
#define STOP_ID 44

#define SET_MODE_ID 5
#define SET_KP_KI_VEL_ID 7

#define SET_VEL_ID 10
#define GET_VEL_ID 20

#define SET_POS_ID 11
#define GET_POS_ID 21

#define POS_VEL_TORQUE_SENS_ID 30


// #define ADDRESS_REQ_ID (appData.canAddress << 7)|1

// #define START_REQ_ID (appData.canAddress <<7)|33;
// #define STOP_REQ_ID (appData.canAddress <<7)|44;

// #define POS_REQ_ID (appData.canAddress << 7)|10; 
// #define VEL_REQ_ID (appData.canAddress << 7)|11;
// #define TORQUE_REQ_ID (appData.canAddress << 7)|12;


// #define POS_VEL_TORQUE_REQ_ID (appData.canAddress <<7)|13;

// #define POS_CMD_ID (appData.canAddress<<7)|20;
// #define VEL_CMD_ID (appData.canAddress << 7)|21;
// #define TORQUE_CMD_ID (appData.canAddress << 7)|22;



/*This function sends to RPI position, velocity and torque measured values
from sensors*/

CAN_TX_MSG_REQUEST_STATUS sendPosVelTorque(uint16_t pos, int16_t vel, uint16_t torque, CAN_MSG_OBJ *msgTx);


/*This function is used in order to create a filter for the pic on the
CAN bus. The PIC will only receive the messages if the 4 upper bits of SID
correspond to the hex address given by the address switch*/

void setCanFilter();

/*This functions returns the command type of a received message*/

uint8_t getCmdId(CAN_MSG_OBJ * msgRx);










#endif