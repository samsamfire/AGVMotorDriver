/*This file contains the different message ids recognized by the driver*/


#ifndef H_CAN_MESSAGE
#define H_CAN_MESSAGE

#include "mcc_generated_files/can_types.h"
#include "app.h"


#define ADDRESS_REQ_ID (appData.canAddress << 7)|1

#define POS_REQ_ID (appData.canAddress << 7)|10; 
#define VEL_REQ_ID (appData.canAddress << 7)|11;
#define TORQUE_REQ_ID (appData.canAddress << 7)|12;

#define POS_VEL_TORQUE_REQ_ID (appData.canAddress <<7)|13;

#define POS_CMD_ID (appData.canAddress<<7)|20;
#define VEL_CMD_ID (appData.canAddress << 7)|21;
#define TORQUE_CMD_ID (appData.canAddress << 7)|22;

















#endif