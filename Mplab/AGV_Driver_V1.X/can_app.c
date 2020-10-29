#include "can_app.h"



CAN_APP_DATA cappData;

void CAN_APP_Init(){
	int i;
	 for (i = 0; i < 8; ++i)
	 {
	 	cappData.dataRx[i] = 0;
	 	cappData.dataTx[i] = 0;
	 }

	

	//CAN initialization stuff
	cappData.canAddress = ~(PORTBbits.RB12 + 2*PORTBbits.RB13 + 4*PORTBbits.RB14 + 8*PORTBbits.RB15)&(0x0F);
}





void CAN_APP_Tasks(){
	//CAN processing

	
	cappData.msgRx.data = &cappData.dataRx[0];
	cappData.msgTx.data = &cappData.dataTx[0];

	switch(cappData.state){

		case CAN_APP_STATE_INIT :
		{
			cappData.state = CAN_APP_STATE_RECEIVE;
			break;
		}

		case CAN_APP_STATE_RECEIVE :
		{
			if(CAN1_ReceivedMessageCountGet()>0){
				if(true == CAN1_Receive(&cappData.msgRx)){
					cappData.cmdId = getCmdId(&cappData.msgRx);

					switch(cappData.cmdId){
					
						case START_ID :
						{
							appData.on = 1;
							break;
						}

						case STOP_ID :
						{
							appData.on = 0;
							break;
						}

						case SET_VEL_ID :
						{
							appData.reqVel = (cappData.dataRx[0]) + (cappData.dataRx[1]<<8);
						}

						case SET_POS_ID :
						{
							appData.reqPos = (cappData.dataRx[0]) + (cappData.dataRx[1]<<8);
						}

						case SET_MODE_ID :
						{
							appData.mode = cappData.msgRx.data[0];
						}

						default :
						{
							//Add an error mechanism
							break;
						}
					}
				}

			}


			cappData.state = CAN_APP_STATE_TRANSMIT;
			break;
		}

		case CAN_APP_STATE_TRANSMIT :
		{
			//Check whether it's time to send
			if (cappData.sendCanMessages == 1)
			{
				
				sendPosVelTorque(200,-50,88,&cappData.msgTx);
				cappData.sendCanMessages = 0;

			}

			cappData.state = CAN_APP_STATE_RECEIVE;
			break;
		}

		default:
		{
			break;
		}


	}
}