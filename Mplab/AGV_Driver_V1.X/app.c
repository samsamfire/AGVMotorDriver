#include "app.h"





CAN_MSG_OBJ message_rec;

APP_DATA appData;

int i;



void APP_Initialize(void){

	//System initialize is defined by MCC when configuring the used modules
	SYSTEM_Initialize();  
   
    
	//Calculate Can bus address given by Hex Switch Wheel
	//CAN address cannot be changed at runtime
    appData.canAddress = ~(PORTBbits.RB12 + 2*PORTBbits.RB13 + 4*PORTBbits.RB14 + 8*PORTBbits.RB15)&(0x0F);
  	//Filter messages so it reads only messages that have its hex address
  	setCanFilter();

  	//Enable CAN transmit and receive operations
    CAN1_ReceiveEnable();
    CAN1_TransmitEnable();
    //Enable analog to digital conversion
    ADC1_Enable();
    IO_RA4_SetHigh();
    
    //Timers initialization
    TMR3_SetInterruptHandler(&Tmr3_interrupt);
    TMR3_Start();




   
    //Testing

    appData.pos = 17;
    appData.vel = 20;
    appData.torque = 25;

    appData.sendCanMessages = 0;



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
        	//appData.sendCanMessages is interrupt driven at a frequency ginven by TMR2

        	if(appData.sendCanMessages == 1)
        	{
        		//Send CAN data
        		sendPosVelTorque(appData.pos, appData.vel, appData.torque);
        		appData.sendCanMessages = 0;
        	}
        	
        	appData.state = APP_STATE_SEND_UART;
        	break;
        }




        case APP_STATE_SEND_UART:
        {
    		//printf("Number of can messages received : %i \r\n",CAN1_ReceivedMessageCountGet());
			//printf("%i\r\n", C1RXF1SID);
			//CAN1_Receive(&message_rec);	

			/*ADC1_SoftwareTriggerEnable();
			for(i=0;i <1000;i++)
	        {
	        }
	        ADC1_SoftwareTriggerDisable();
	        */
        	//while(!ADC1_IsConversionComplete(channel_AN0));

			printf("Conversion result : %u \r\n",appData.motorPowerVoltage);

			appData.state = APP_STATE_READ_BATTERY;
			break;
		}

		case APP_STATE_READ_BATTERY:
		{
			/*Autosampling is activated
			Voltage is 10 bit unsigned decimal
			Measured voltage is 1/10th of real voltage via voltage divider*/
			
			appData.motorPowerVoltage = ADC1_ConversionResultGet(channel_AN0);
			appData.state = APP_STATE_UPDATE_SENSORS;

			break;
		}

        
        case APP_STATE_ERROR:
        {
            break;
        }







		default : 
		{
			break;
		};
	}

}