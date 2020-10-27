#ifndef H_APP
#define H_APP

/*All includes necessary for application*/

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/can1.h"
#include "mcc_generated_files/can_types.h"
#include "motor_driver.h"
#include "can_message.h"
#include <stdlib.h>
#include <stdio.h>
#include "interrupts.h"
#include "mcc_generated_files/tmr3.h"
#include "mcc_generated_files/adc1.h"



//This is an enumeration of all the different possible states of the state machine

typedef enum
{
	APP_STATE_INIT = 0,
	APP_STATE_UPDATE_SENSORS,
	APP_STATE_UPDATE_MOTOR,
	APP_STATE_TRANSMIT_CAN,
	APP_STATE_SEND_UART,
	APP_STATE_ERROR,
	APP_STATE_READ_BATTERY
           

} APP_STATES;

//This contains the essential data during app operation
typedef struct
{
	APP_STATES state;
	uint8_t canAddress;
	uint8_t sendCanMessages;
	uint16_t motorPowerVoltage;
	int16_t vel_sensor;
	int16_t pos_sensor;
	int16_t torque;
	float reqvel;
	float reqpos;
	float reqtorque;
	CAN_MSG_OBJ canMsg;
	
} APP_DATA;



//This is called once at app initialization
void APP_Initialize(void);



//This is called in the main loop
void APP_Tasks(void);




extern APP_DATA appData;














#endif