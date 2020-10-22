/**
  CAN1 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    can1.h

  @Summary
    This is the generated header file for the CAN1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for CAN1.
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

#ifndef _CAN1_H
#define _CAN1_H

/**
  Section: Included Files
*/

#include "can_types.h"

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: CAN1 Module APIs
*/

/**
  @Summary
    Initializes the CAN1_Initialize.

  @Description
    This routine initializes the CAN1_Initialize.
    This routine must be called before any other CAN1 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    

 @Example
    <code>
    CAN1_Initialize();
    </code>
 */
void CAN1_Initialize(void);

/******************************************************************************
*                                                                             
*    Function:		CAN1_receive
*    Description:       Receives the message from CAN buffer to user buffer                                                                         
*    Arguments:		recCanMsg: pointer to the message object
*    Return Value:      true - Receive successful
*                       false - Receive failure                                                                              
******************************************************************************/
bool CAN1_receive(uCAN_MSG *recCanMsg);

/******************************************************************************
*                                                                             
*    Function:		CAN1_transmit
*    Description:       Transmits the message from user buffer to CAN buffer                                                                        
*    Arguments:		priority: priority of the message to be transmitted
*                       sendCanMsg: pointer to the message object                                        
*    Return Value:      true - Transmit successful
*                       false - Transmit failure                                                                              
******************************************************************************/
bool CAN1_transmit(CAN_TX_PRIOIRTY priority, 
                                    uCAN_MSG *sendCanMsg);

/******************************************************************************                                                                       
*    Function:          CAN1_isBusOff
*    Description:       Checks whether the transmitter in Bus off state                                                                                                   
*    Return Value:      true - Transmitter in Bus Off state
*                       false - Transmitter not in Bus Off state                                                                              
******************************************************************************/
bool CAN1_isBusOff();

/******************************************************************************                                                                 
*    Function:		CAN1_isRXErrorPassive
*    Description:       Checks whether the receive in error passive state                                    
*    Return Value:      true - Receiver in Error Passive state
*                       false - Receiver not in Error Passive state                                                                              
******************************************************************************/
bool CAN1_isRXErrorPassive();

/******************************************************************************                                                                      
*    Function:		CAN1_isTXErrorPassive
*    Description:       Checks whether the transmitter in error passive state                                                                                                             
*    Return Value:      true - Transmitter in Error Passive state
*                       false - Transmitter not in Error Passive state                                                                              
******************************************************************************/
bool CAN1_isTXErrorPassive();

/******************************************************************************                                                                    
*    Function:		CAN1_messagesInBuffer
*    Description:       returns the number of messages that are received                                                                                                               
*    Return Value:      Number of message received
******************************************************************************/
uint8_t CAN1_messagesInBuffer();

/******************************************************************************
*                                                                             
*    Function:		CAN1_sleep
*    Description:       Puts CAN1 module in disable mode.
*    Return Value:      None
*                                                                       
******************************************************************************/
void CAN1_sleep();

/******************************************************************************                                                                    
*    Function:		CAN1_TransmitEnable
*    Description:       Enables Transmit for CAN1                                                                                                                
*    Return Value:      None
******************************************************************************/
void CAN1_TransmitEnable();

/******************************************************************************                                                                    
*    Function:		CAN1_ReceiveEnable
*    Description:       Enables Receive for CAN1                                                                                                                
*    Return Value:      None
******************************************************************************/
void CAN1_ReceiveEnable();

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  //_CAN1_H
/**
 End of File
*/

