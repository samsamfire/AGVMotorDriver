#include "can_message.h"
#include "app.h"




CAN_TX_MSG_REQUEST_STATUS sendPosVelTorque(uint16_t pos, int16_t vel, uint16_t torque){
	
	//Create CAN message
	CAN_MSG_OBJ canMessage;
	int16_t data[3];

	data[0] = pos;
	data[1] = vel;
	data[2] = torque;

	canMessage.field.frameType = CAN_FRAME_DATA;
	canMessage.field.idType = CAN_FRAME_STD;
	canMessage.field.dlc = CAN_DLC_6;
	canMessage.msgId = POS_VEL_TORQUE_REQ_ID;

	canMessage.data = (uint8_t *)&data[0];

	return CAN1_Transmit(CAN_PRIORITY_HIGH, &canMessage);


}

void setCanFilter(){

	//This is so the PIC only responds to certain type of messages
    

    /* Filter configuration */
    /* enable window to access the filter configuration registers */
    /* use filter window*/
    C1CTRL1bits.WIN=1;     
	    /* select acceptance masks for filters */
    C1FMSKSEL1bits.F0MSK = 0x0; //Select Mask 0 for Filter 0

    /* Configure the masks */
    C1RXM0SIDbits.SID = 0x780; //This means that only 4 upper bits count in filter

   
     /* Configure the filters */


    C1RXF1SIDbits.SID = (appData.canAddress) << 7; 
    
    C1RXF1SIDbits.EID = 0x0; 
    
    C1RXF1EID = 0x00; 
    
    C1RXF1SIDbits.EXIDE = 0x0; 
    
    /* FIFO Mode */
    C1BUFPNT1bits.F1BP = 0xf; //Filter 1 uses FIFO
    
    /* clear window bit to access CAN1 control registers */
    C1CTRL1bits.WIN=0;    



}