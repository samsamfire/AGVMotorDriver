/**
  ECAN1 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    ecan1.h

  @Summary
    This is the generated header file for the ECAN1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for ECAN1.
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

#ifndef _ECAN1_H
#define _ECAN1_H

/**
  Section: Included Files
*/
#include <xc.h>
#include "can_types.h"

#warning deprecate ("\nThis will be removed in future MCC releases. \nUse can_types.h file CAN message type identifiers instead. ")
/* ECAN message type identifiers */
#define CAN1_MSG_DATA    0x01
#define CAN1_MSG_RTR     0x02
#define CAN1_FRAME_EXT	0x03
#define CAN1_FRAME_STD	0x04
#define CAN1_BUF_FULL	0x05
#define CAN1_BUF_EMPTY	0x06

typedef union {
    struct {
        uint32_t id;
        uint8_t idType;
        uint8_t msgtype;
        uint8_t dlc;
        uint8_t data0;
        uint8_t data1;
        uint8_t data2;
        uint8_t data3;
        uint8_t data4;
        uint8_t data5;
        uint8_t data6;
        uint8_t data7;
    } frame;
    unsigned char array[16];
} uCAN1_MSG __attribute__((deprecate ("\nThis will be removed in future MCC releases. \nUse can_types.h file uCAN_MSG instead. ")));

/* Operation modes */
typedef enum
{
	CAN1_NORMAL_OPERATION_MODE = 0,
	CAN1_DISABLE_MODE = 1,
	CAN1_LOOPBACK_MODE = 2,
	CAN1_LISTEN_ONLY_MODE = 3,
	CAN1_CONFIGURATION_MODE = 4,
	CAN1_LISTEN_ALL_MESSAGES_MODE = 7
}ECAN1_OP_MODES __attribute__((deprecated ("\nThis will be removed in future MCC releases. \nUse can_types.h file CAN_OP_MODES instead. ")));

typedef enum{
    ECAN1_PRIORITY_HIGH = 0b11,
    ECAN1_PRIORITY_MEDIUM = 0b10,
    ECAN1_PRIORITY_LOW = 0b01,
    ECAN1_PRIORITY_NONE = 0b00
} ECAN1_TX_PRIOIRTY __attribute__((deprecated ("\nThis will be removed in future MCC releases. \nUse can_types.h file CAN_TX_PRIOIRTY instead. ")));

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: ECAN1 Module APIs
*/

/**
  @Summary
    Initializes the ECAN1_Initialize.

  @Description
    This routine initializes the ECAN1_Initialize.
    This routine must be called before any other ECAN1 routine is called.
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
    ECAN1_Initialize();
    </code>
 */
void ECAN1_Initialize(void) __attribute__((deprecate ("\nThis will be removed in future MCC releases. \nUse CAN1_Initialize instead. ")));

/******************************************************************************
*                                                                             
*    Function:		ECAN1_receive
*    Description:       Receives the message from CAN buffer to user buffer                                                                         
*    Arguments:		recCanMsg: pointer to the message object
*    Return Value:      true - Receive successful
*                       false - Receive failure                                                                              
******************************************************************************/
bool ECAN1_receive(uCAN1_MSG *recCanMsg) __attribute__((deprecate ("\nThis will be removed in future MCC releases. \nUse CAN1_receive instead. "))); 

/******************************************************************************
*                                                                             
*    Function:		ECAN1_transmit
*    Description:       Transmits the message from user buffer to CAN buffer                                                                        
*    Arguments:		priority: priority of the message to be transmitted
*                       sendCanMsg: pointer to the message object                                        
*    Return Value:      true - Transmit successful
*                       false - Transmit failure                                                                              
******************************************************************************/
bool ECAN1_transmit(ECAN1_TX_PRIOIRTY priority, 
                                    uCAN1_MSG *sendCanMsg) __attribute__((deprecate ("\nThis will be removed in future MCC releases. \nUse CAN1_transmit instead. "))); 

/******************************************************************************                                                                       
*    Function:          ECAN1_isBusOff
*    Description:       Checks whether the transmitter in Bus off state                                                                                                   
*    Return Value:      true - Transmitter in Bus Off state
*                       false - Transmitter not in Bus Off state                                                                              
******************************************************************************/
bool ECAN1_isBusOff() __attribute__((deprecate ("\nThis will be removed in future MCC releases. \nUse CAN1_isBusOff instead. "))); 

/******************************************************************************                                                                 
*    Function:		ECAN1_isRXErrorPassive
*    Description:       Checks whether the receive in error passive state                                    
*    Return Value:      true - Receiver in Error Passive state
*                       false - Receiver not in Error Passive state                                                                              
******************************************************************************/
bool ECAN1_isRXErrorPassive() __attribute__((deprecate ("\nThis will be removed in future MCC releases. \nUse CAN1_isRXErrorPassive instead. ")));

/******************************************************************************                                                                      
*    Function:		ECAN1_isTXErrorPassive
*    Description:       Checks whether the transmitter in error passive state                                                                                                             
*    Return Value:      true - Transmitter in Error Passive state
*                       false - Transmitter not in Error Passive state                                                                              
******************************************************************************/
bool ECAN1_isTXErrorPassive() __attribute__((deprecate ("\nThis will be removed in future MCC releases. \nUse CAN1_isTXErrorPassive instead. ")));

/******************************************************************************                                                                    
*    Function:		ECAN1_messagesInBuffer
*    Description:       returns the number of messages that are received                                                                                                               
*    Return Value:      Number of message received
******************************************************************************/
uint8_t ECAN1_messagesInBuffer() __attribute__((deprecate ("\nThis will be removed in future MCC releases. \nUse CAN1_messagesInBuffer instead. ")));

/******************************************************************************
*                                                                             
*    Function:		ECAN1_sleep
*    Description:       Puts ECAN1 module in disable mode.
*    Return Value:      None
*                                                                       
******************************************************************************/
void ECAN1_sleep() __attribute__((deprecate ("\nThis will be removed in future MCC releases. \nUse CAN1_sleep instead. ")));

/******************************************************************************                                                                    
*    Function:		ECAN1_TransmitEnable
*    Description:       Enables Transmit for ECAN1                                                                                                                
*    Return Value:      None
******************************************************************************/
void ECAN1_TransmitEnable() __attribute__((deprecate ("\nThis will be removed in future MCC releases. \nUse CAN1_TransmitEnable instead. ")));

/******************************************************************************                                                                    
*    Function:		ECAN1_ReceiveEnable
*    Description:       Enables Receive for ECAN1                                                                                                                
*    Return Value:      None
******************************************************************************/
void ECAN1_ReceiveEnable() __attribute__((deprecate ("\nThis will be removed in future MCC releases. \nUse CAN1_ReceiveEnable instead. ")));

/* Null weak implementations of callback functions. */
void ECAN1_CallbackBusOff(void) __attribute__((deprecate("\nThis will be removed in future MCC releases. \nUse CAN1_CallbackBusOff instead. ")));
void ECAN1_CallbackTxErrorPassive(void) __attribute__((deprecate("\nThis will be removed in future MCC releases. \nUse CAN1_CallbackTxErrorPassive instead. ")));
void ECAN1_CallbackRxErrorPassive(void) __attribute__((deprecate("\nThis will be removed in future MCC releases. \nUse CAN1_CallbackRxErrorPassive instead. ")));
void ECAN1_CallbackMessageReceived(void) __attribute__((deprecate("\nThis will be removed in future MCC releases. \nUse CAN1_CallbackMessageReceived instead. ")));
void ECAN1_CallbackRxBufferOverflow() __attribute__((deprecate("\nThis will be removed in future MCC releases. \nUse CAN1_CallbackRxBufferOverflow instead. ")));

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  //_ECAN1_H
/**
 End of File
*/

