#include "app.h"





CAN_MSG_OBJ message_rec;


APP_DATA appData;

uint8_t cmd_id;

int i;



void APP_Initialize(void){

	//System initialize is defined by MCC when configuring the used modules

	SYSTEM_Initialize();  

	OC1_Start();
	OC2_Start();
	OC1RS = 20000;
	OC2RS=20000;
	

   
    
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
    //TMR2_Start();
    LATAbits.LATA3=0;


   
    //Default values
    appData.reqPos = 0;
    appData.reqVel = 0;
    appData.on = 0;
    appData.sensPos = 17;
    appData.sensVel = 20;
    appData.sensTorque = 25;
    appData.filter =0 ;
    appData.sensLowVelRaw = 0;
    appData.sensLowVel = 0;
    appData.pidOutputVel = 0;

    //     /* Initialize QEI 1 Peripheral */
    QEI1LECH = 0x00;                     /* Lower bound (High)*/
    QEI1LECL = 0x00;                     /* Lower bound (Low)*/
    QEI1GECH = 0x00;                     /* Upper bound (High)*/
    QEI1GECL = 0xFFFF;                   /* Upper bound (Low)*/
    QEI1IOC = 0x7100;

    // DFLT1CONbits.CEID = 1; // Count error interrupts disabled
    // DFLT1CONbits.QEOUT = 1; // Digital filters output enabled for QEn pins
    // DFLT1CONbits.QECK = 5; // 1:64 clock divide for digital filter for QEn
    // DFLTCONbits.INDOUT = 1; // Digital filter output enabled for Index pin
    // DFLTCONbits.INDCK = 5; // 1:64 clock divide for digital filter for Index
    QEI1CON = 0x9800;
    QEI1CONbits.INTDIV = 6; //INTDIV is set to 6 for a 1:256 prescaler 8.5248 uS/ time step

    POS1CNTL=0;

    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1=0;






}


void APP_Tasks(void){

	//State machine

	uint8_t data[8] = {0};
    CAN_MSG_OBJ msg_rec;
    msg_rec.data = data;

	switch(appData.state){

		case APP_STATE_INIT : 
        {
        	appData.state = APP_STATE_UPDATE_SENSORS;
            break;
        }
          

        case APP_STATE_UPDATE_SENSORS :
        {

        
          //appData.sensLowVel = INT1HLDL;
          appData.sensPos = POS1CNTL;
          appData.sensVel = VEL1CNT;
          appData.timerVel = INT1HLDL;

          appData.sensLowVelRaw = (float) 2*4*0.008377/(appData.timerVel*0.0000085248);
          if(appData.filter <8){
            appData.sensFilterVel += appData.sensLowVelRaw;
            appData.filter += 1;
          }
          else{
            appData.filter = 0;

            appData.sensFilteredVel = appData.sensFilterVel/8;
            appData.sensFilterVel = 0;
          }

          
        	appData.state = APP_STATE_UPDATE_RELAY;
        	break;
        }








        case APP_STATE_UPDATE_RELAY :
        {
        	// Relay is controlled by RA1 (jumper)
        	//Should implement a timeout so that turns off automatically
        	//If connection lost
        	LATAbits.LATA3 = 1;

          LATBbits.LATB0 = PORTBbits.RB6;
        	appData.state = APP_STATE_UPDATE_MOTOR;
        	break;
        }









        case APP_STATE_UPDATE_MOTOR :
        {
        	
       		
        	//To be changed by real duty cycle after PID implementation

          appData.reqPWM = (float) (appData.reqVel/1000 + 8.5)/0.46; //Calculated from excel spreadsheet and divided by 1000
          
          setDuty(appData.reqPWM);
        	//setDuty(-40);
          


			   appData.state = APP_STATE_SEND_UART;
        	break;
        }




        case APP_STATE_SEND_UART:
        {
    		//printf("Number of can messages received : %i \r\n",CAN1_ReceivedMessageCountGet());
			//printf("Id of message : %i \r\n",message_receive.msgId);
			// if(CAN1_ReceivedMessageCountGet()>0){
			// 	printf("Received a message\r\n" );
			// 	if(true == CAN1_Receive(&msg_rec)){
			// 		printf("Read message successful\r\n");
			// 		cmd_id= msg_rec.msgId&0b00001111111;
			// 		printf("Command ID : %i \r\n",cmd_id);
			// 	}
			// 	else{
			// 		printf("Read unsuccsessful\r\n");
			// 	}
			// }

            
			//printf("Conversion result : %u \r\n",appData.motorPowerVoltage);

          //printf("Speed raw, pos, Speed Low : %i %i %f\r\n",appData.timerVel, appData.sensPos, appData.sensFilteredVel);

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