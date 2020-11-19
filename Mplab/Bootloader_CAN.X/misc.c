/*
 * File:   misc.c
 * Author: samfi
 *
 * Created on 18 novembre 2020, 20:08
 */


#include "xc.h"
#include "boot.h"
#include "mcc_generated_files/can1.h"

void setCanFilter(){

	//This is so the PIC only responds to certain type of messages
    

        /* Filter configuration */
    /* enable window to access the filter configuration registers */
    /* use filter window*/
    C1CTRL1bits.WIN=1;	   
    
    /* select acceptance masks for filters */
    C1FMSKSEL1bits.F0MSK = 0x0; //Select Mask 0 for Filter 0
    
    /* Configure the masks */
    C1RXM0SIDbits.SID = 0x780; 
    C1RXM1SIDbits.SID = 0x0; 
    C1RXM2SIDbits.SID = 0x0; 
    
    C1RXM0SIDbits.EID = 0x0; 
    C1RXM1SIDbits.EID = 0x0; 
    C1RXM2SIDbits.EID = 0x0; 
    
    C1RXM0EID = 0x00;     	
    C1RXM1EID = 0x00;     	
    C1RXM2EID = 0x00;     	
    
    C1RXM0SIDbits.MIDE = 0x0; 
    C1RXM1SIDbits.MIDE = 0x0; 
    C1RXM2SIDbits.MIDE = 0x0; 
    
    /* Configure the filters */
    C1RXF0SIDbits.SID = canAddress << 7; 
    
    C1RXF0SIDbits.EID = 0x0; 
    
    C1RXF0EID = 0x00; 
    
    C1RXF0SIDbits.EXIDE = 0x0; 
    
    /* FIFO Mode */
    C1BUFPNT1bits.F0BP = 0xf; //Filter 0 uses FIFO
    
    /* clear window bit to access CAN1 control registers */
    C1CTRL1bits.WIN=0;    

    /*configure CAN1 Transmit/Receive buffer settings*/
    C1TR01CONbits.TXEN0 = 0x1; // Buffer 0 is a Transmit Buffer 
    C1TR01CONbits.TXEN1 = 0x1; // Buffer 1 is a Transmit Buffer 
    C1TR23CONbits.TXEN2 = 0x1; // Buffer 2 is a Transmit Buffer 
    C1TR23CONbits.TXEN3 = 0x1; // Buffer 3 is a Transmit Buffer 
    C1TR45CONbits.TXEN4 = 0x0; // Buffer 4 is a Receive Buffer 
    C1TR45CONbits.TXEN5 = 0x0; // Buffer 5 is a Receive Buffer 
    C1TR67CONbits.TXEN6 = 0x0; // Buffer 6 is a Receive Buffer 
    C1TR67CONbits.TXEN7 = 0x0; // Buffer 7 is a Receive Buffer 

    C1TR01CONbits.TX0PRI = 0x0; // Message Buffer 0 Priority Level
    C1TR01CONbits.TX1PRI = 0x0; // Message Buffer 1 Priority Level
    C1TR23CONbits.TX2PRI = 0x0; // Message Buffer 2 Priority Level
    C1TR23CONbits.TX3PRI = 0x0; // Message Buffer 3 Priority Level
    C1TR45CONbits.TX4PRI = 0x0; // Message Buffer 4 Priority Level
    C1TR45CONbits.TX5PRI = 0x0; // Message Buffer 5 Priority Level
    C1TR67CONbits.TX6PRI = 0x0; // Message Buffer 6 Priority Level
    C1TR67CONbits.TX7PRI = 0x0; // Message Buffer 7 Priority Level

    /* clear the buffer and overflow flags */   
    C1RXFUL1 = 0x0000;
    C1RXFUL2 = 0x0000;
    C1RXOVF1 = 0x0000;
    C1RXOVF2 = 0x0000;	

    /* configure the device to interrupt on the receive buffer full flag */
    /* clear the buffer full flags */ 	
    C1INTFbits.RBIF = 0;  

    /* put the module in normal mode */
    C1CTRL1bits.REQOP = CAN_NORMAL_OPERATION_MODE;
    while(C1CTRL1bits.OPMODE != CAN_NORMAL_OPERATION_MODE);	

    /* Initialize Interrupt Handler*/
    CAN1_SetBusWakeUpActivityInterruptHandler(&CAN1_DefaultBusWakeUpActivityHandler);

    /* Enable CAN1 Interrupt */
    IEC2bits.C1IE = 1;



}

