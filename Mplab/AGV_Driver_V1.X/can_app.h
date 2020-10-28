#ifndef H_CAN_APP
#define H_CAN_APP

#include "app.h"
#include "can_message.h"





typedef enum
{
	CAN_APP_STATE_INIT=0,
	CAN_APP_STATE_RECEIVE,
	CAN_APP_STATE_TRANSMIT
           

} CAN_APP_STATES;

//This contains the essential data during app operation
typedef struct
{
	APP_STATES state;
	uint8_t canAddress;
	CAN_MSG_OBJ msgRx;
	CAN_MSG_OBJ msgTx;
	uint8_t dataRx[8];
	uint8_t dataTx[8];
	uint8_t cmdId;
	uint8_t sendCanMessages;
	
	
} CAN_APP_DATA;


void CAN_APP_Init();
void CAN_APP_Tasks();



extern CAN_APP_DATA cappData;






























#endif