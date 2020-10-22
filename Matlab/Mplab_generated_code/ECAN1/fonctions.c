
#include <xc.h>
#include <stdio.h>

#include "can_types.h"
#include "ecan1.h"
#include "can1.h"
#include "dma.h"

void ECAN1_Simulink_Init(void)
{

    //    DMA0I: DMA Channel 0
    //    Priority: 1
        IPC1bits.DMA0IP = 1;
    //    CI: ECAN1 Event
    //    Priority: 1
        IPC8bits.C1IP = 1;
		
	CAN1_Initialize();
    DMA_Initialize();
		
	/* Set the PPS */
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

   // RPINR26bits.C1RXR = 0x002E;    //RB14->ECAN1:C1RX
   // RPOR0bits.RP20R = 0x000E;    //RA4->ECAN1:C1TX
    
    RPINR26bits.C1RXR = 0x0014;   
   //RPINR26bits.C1RXR = 0x0028; //RP40 
    
    RPOR1bits.RP36R = 0X000E;   
   //RPOR3bits.RP41R = 0x000E;
    
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS

    ECAN1_TransmitEnable();
    ECAN1_ReceiveEnable();

	__builtin_enable_interrupts();

}

void ECAN1_Simulink_Transmit(unsigned int Valid, unsigned int Id, unsigned char Dlc, unsigned char* Data)
{
	uCAN_MSG MESCAN_T ;
	if (Valid>0)
	{
		MESCAN_T.frame.id = Id;
		MESCAN_T.frame.idType = CAN_FRAME_STD;
		MESCAN_T.frame.msgtype = CAN_MSG_DATA;
		MESCAN_T.frame.dlc = Dlc;
		
		MESCAN_T.frame.data0 = Data[0];
		MESCAN_T.frame.data1 = Data[1];
		MESCAN_T.frame.data2 = Data[2];
		MESCAN_T.frame.data3 = Data[3];
		MESCAN_T.frame.data4 = Data[4];
		MESCAN_T.frame.data5 = Data[5];
		MESCAN_T.frame.data6 = Data[6];
		MESCAN_T.frame.data7 = Data[7];
	
		while(!ECAN1_transmit(1,&MESCAN_T));
		//ECAN1_transmit(1,&MESCAN_T);
	}
}

unsigned int ECAN1_Simulink_Receive(unsigned int* Id,unsigned char* Data,unsigned char* Dlc)
{
	unsigned int messagesInBuffer = 0;
	uCAN_MSG MESCAN ;
	
    messagesInBuffer = CAN1_messagesInBuffer();
    if (messagesInBuffer>0)
    {
        
		ECAN1_receive(&MESCAN);
				
		Id[0] =  MESCAN.frame.id;
		Dlc[0] = MESCAN.frame.dlc;

		Data[0] = MESCAN.frame.data0;
		Data[1] = MESCAN.frame.data1;
		Data[2] = MESCAN.frame.data2;
		Data[3] = MESCAN.frame.data3;
		Data[4] = MESCAN.frame.data4;
		Data[5] = MESCAN.frame.data5;
		Data[6] = MESCAN.frame.data6;
		Data[7] = MESCAN.frame.data7;
						
			/*
			uCAN_MSG MESCAN2 ;
			MESCAN2.frame.id = 0x20;
			MESCAN2.frame.idType = CAN_FRAME_STD;
			MESCAN2.frame.msgtype = CAN_MSG_DATA;
			MESCAN2.frame.dlc = MESCAN.frame.dlc;
			MESCAN2.frame.data0 = Data[0];
			MESCAN2.frame.data1 = Data[1];
			MESCAN2.frame.data2 = Data[2];
			MESCAN2.frame.data3 = Data[3];
			MESCAN2.frame.data4 = Data[4];
			MESCAN2.frame.data5 = Data[5];
			MESCAN2.frame.data6 = Data[6];
			MESCAN2.frame.data7 = Data[7];
			while(!ECAN1_transmit(1,&MESCAN2));*/
		
    }   
	  
	return messagesInBuffer;
	
	
}

/*
Header file
#include "can1.h";
#include "ecan1.h";
#include "dma.h";
#include "can_types.h";

Source files
fonctions.c
can1.c
ecan1.c
dma.c
*/