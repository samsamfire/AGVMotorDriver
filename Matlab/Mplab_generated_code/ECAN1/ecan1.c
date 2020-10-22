/**
  ECAN1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    ecan1.c

  @Summary
    This is the generated driver implementation file for the ECAN1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for ECAN1.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  dsPIC33EP512MC502
        Driver Version    :  1.00
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB 	          :  MPLAB X v5.10
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include <xc.h>
#include "ecan1.h"
#include "can1.h"
#include "dma.h"
#include "can_types.h"

/* Null weak implementations of callback functions. */
void __attribute__((weak, deprecate("\nThis will be removed in future MCC releases. \nUse CAN1_CallbackBusOff instead. "))) ECAN1_CallbackBusOff(void){}
void __attribute__((weak, deprecate("\nThis will be removed in future MCC releases. \nUse CAN1_CallbackTxErrorPassive instead. "))) ECAN1_CallbackTxErrorPassive(void){}
void __attribute__((weak, deprecate("\nThis will be removed in future MCC releases. \nUse CAN1_CallbackRxErrorPassive instead. "))) ECAN1_CallbackRxErrorPassive(void){}
void __attribute__((weak, deprecate("\nThis will be removed in future MCC releases. \nUse CAN1_CallbackMessageReceived instead. "))) ECAN1_CallbackMessageReceived(void){}
void __attribute__((weak, deprecate("\nThis will be removed in future MCC releases. \nUse CAN1_CallbackRxBufferOverflow instead. "))) ECAN1_CallbackRxBufferOverflow(){}

/**
  Section: ECAN1 APIs
*****************************************************************************************/

void ECAN1_Initialize(void)
{
    CAN1_Initialize();
}

/******************************************************************************
*                                                                             
*    Function:		ECAN1_TransmitEnable
*    Description:       Setup the DMA for Transmit from the CAN module.  The 
*                       relevant DMA module APIs are grouped in this function 
*                       and this API needs to be called after DMA_Initialize 
*                       and CAN_Initialize
*                                                                                                                                                       
******************************************************************************/

void ECAN1_TransmitEnable()
{
    CAN1_TransmitEnable();
}

/******************************************************************************
*                                                                             
*    Function:		ECAN1_ReceiveEnable
*    Description:       Setup the DMA for Receive on the CAN module.  The 
*                       relevant DMA module APIs are grouped in this function 
*                       and this API needs to be called after DMA_Initialize 
*                       and CAN_Initialize
*                                                                                                                                                       
******************************************************************************/

void ECAN1_ReceiveEnable()
{
    CAN1_ReceiveEnable();
}

/******************************************************************************
*                                                                             
*    Function:		ECAN1_transmit
*    Description:       Transmits the message from user buffer to CAN buffer
*                       as per the buffer number allocated.
*                       Allocation of the buffer number is done by user 
*                                                                             
*    Arguments:		priority : priority of the message to be transmitted
*                       sendCanMsg: pointer to the message object
*                                             
*    Return Value:      true - Transmit successful
*                       false - Transmit failure                                                                              
******************************************************************************/

bool ECAN1_transmit(ECAN1_TX_PRIOIRTY priority, uCAN1_MSG *sendCanMsg) 
{
    return CAN1_transmit((CAN_TX_PRIOIRTY) priority, (uCAN_MSG *)sendCanMsg);
}

/******************************************************************************
*                                                                             
*    Function:		ECAN1_receive
*    Description:       Receives the message from CAN buffer to user buffer 
*                                                                             
*    Arguments:		recCanMsg: pointer to the message object
*                                             
*    Return Value:      true - Receive successful
*                       false - Receive failure                                                                              
******************************************************************************/

bool ECAN1_receive(uCAN1_MSG *recCanMsg) 
{          
    return CAN1_receive((uCAN_MSG *)recCanMsg); 
}

/******************************************************************************
*                                                                             
*    Function:		ECAN1_isBusOff
*    Description:       Checks whether the transmitter in Bus off state
*                                                                             
                                             
*    Return Value:      true - Transmitter in Bus Off state
*                       false - Transmitter not in Bus Off state                                                                              
******************************************************************************/

bool ECAN1_isBusOff() 
{
    return CAN1_isBusOff();	
}

/******************************************************************************
*                                                                             
*    Function:		ECAN1_isRXErrorPassive
*    Description:       Checks whether the receive in error passive state
*                                             
*    Return Value:      true - Receiver in Error Passive state
*                       false - Receiver not in Error Passive state                                                                              
******************************************************************************/

bool ECAN1_isRXErrorPassive()
{
    return CAN1_isRXErrorPassive();   
}

/******************************************************************************
*                                                                             
*    Function:		ECAN1_isTXErrorPassive
*    Description:       Checks whether the transmitter in error passive state                                                                          
*                                             
*    Return Value:      true - Transmitter in Error Passive state
*                       false - Transmitter not in Error Passive state                                                                              
******************************************************************************/

bool ECAN1_isTXErrorPassive()
{
    return CAN1_isTXErrorPassive();
}

/******************************************************************************
*                                                                             
*    Function:		ECAN1_messagesInBuffer
*    Description:       returns the number of messages that are received                                                                           
*                                             
*    Return Value:      Number of message received
******************************************************************************/

uint8_t ECAN1_messagesInBuffer() 
{           
    return CAN1_messagesInBuffer();
}

/******************************************************************************
*                                                                             
*    Function:		ECAN1_sleep
*    Description:       Puts ECAN1 module in disable mode.
*                                                                       
******************************************************************************/

void ECAN1_sleep(void) 
{
    CAN1_sleep();
}

/**
 End of File
*/