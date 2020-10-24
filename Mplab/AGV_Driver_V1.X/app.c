#include "app.h"



APP_DATA appData;

CAN_MSG_OBJ message;

uint8_t hex_wheel = 0;

uint8_t to_send[4] = {178,203,15,18};



void APP_Initialize(void){

	SYSTEM_Initialize();  //System initialize is defined by MCC when configuring the used modules
    CAN1_TransmitEnable(); //Enable CAN transmit and receive operations
    CAN1_ReceiveEnable();
    IO_RA4_SetHigh();


    //Calculate Can bus address given by Hex Switch Wheel
    appData.canAddress = ~(PORTBbits.RB12 + 2*PORTBbits.RB13 + 4*PORTBbits.RB14 + 8*PORTBbits.RB15)&(0x0F);


    //Initial app state
    appData.state = APP_STATE_TRANSMIT_CAN;

    message.field.frameType = CAN_FRAME_DATA; //Data transfer type
	message.field.idType = CAN_FRAME_STD; //Regular id 
	message.field.dlc = CAN_DLC_4; //transfer 4 bytes
	message.msgId = ADDRESS_REQ_ID; //Message id
	message.data = &to_send[0]; //Data to send


}


void APP_Tasks(void){

	//State machine

	switch(appData.state){

		case APP_STATE_INIT : 
        {
        	appData.state = APP_STATE_UPDATE_SENSORS;
            break;
        }
          

        case APP_STATE_UPDATE_SENSORS :
        {
        	appData.state = APP_STATE_UPDATE_MOTOR;
        	break;
        }

        case APP_STATE_UPDATE_MOTOR :
        {
        	LATAbits.LATA3 = PORTAbits.RA1; // Relay is controlled by RA1 (jumper)

        	setDuty(100);

			appData.state = APP_STATE_TRANSMIT_CAN;
        	break;
        }

        case APP_STATE_TRANSMIT_CAN:
        {
        	CAN1_Transmit(CAN_PRIORITY_HIGH,&message);
        	appData.state = APP_STATE_SEND_UART;
        	break;
        }

        case APP_STATE_SEND_UART:
        {
    
			appData.state = APP_STATE_UPDATE_SENSORS;
			break;
		}





		default : 
		{
			break;
		};
	}

}