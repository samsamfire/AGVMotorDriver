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

#ifndef _CAN_TYPES_H
#define _CAN_TYPES_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/* CAN message type identifiers */
#define CAN_MSG_DATA    0x01
#define CAN_MSG_RTR     0x02
#define CAN_FRAME_EXT	0x03
#define CAN_FRAME_STD	0x04
#define CAN_BUF_FULL	0x05
#define CAN_BUF_EMPTY	0x06

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
} uCAN_MSG;

/* Operation modes */
typedef enum
{
	CAN_NORMAL_OPERATION_MODE = 0,
	CAN_DISABLE_MODE = 1,
	CAN_LOOPBACK_MODE = 2,
	CAN_LISTEN_ONLY_MODE = 3,
	CAN_CONFIGURATION_MODE = 4,
	CAN_LISTEN_ALL_MESSAGES_MODE = 7
} CAN_OP_MODES;

typedef enum{
    CAN_PRIORITY_HIGH = 0b11,
    CAN_PRIORITY_MEDIUM = 0b10,
    CAN_PRIORITY_LOW = 0b01,
    CAN_PRIORITY_NONE = 0b00
} CAN_TX_PRIOIRTY;

#endif  //_CAN_TYPES_H
/**
 End of File
*/

