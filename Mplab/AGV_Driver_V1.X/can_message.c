#include "can_message.h"
#include "app.h"
#include "can_app.h"




CAN_TX_MSG_REQUEST_STATUS sendPosVelTorque(uint16_t pos, int16_t vel, uint16_t torque,CAN_MSG_OBJ* msgTx){
	
	
	msgTx->data[0] = pos&0xFF;
    msgTx->data[1] =(uint8_t) (pos >> 8);
    msgTx->data[2] = vel&0xFF;
    msgTx->data[3] =(uint8_t) (vel >> 8);
    msgTx->data[4] = torque&0xFF;
    msgTx->data[5] =(uint8_t) (torque >> 8);
	

	msgTx->field.frameType = CAN_FRAME_DATA;
	msgTx->field.idType = CAN_FRAME_STD;
	msgTx->field.dlc = CAN_DLC_6;
	msgTx->msgId = (cappData.canAddress <<7) | POS_VEL_TORQUE_SENS_ID;


	return CAN1_Transmit(CAN_PRIORITY_HIGH, msgTx);
    
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


uint8_t getCmdId(CAN_MSG_OBJ * msgRx){

    return (msgRx->msgId) & 0b00001111111;
}