/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BOOT_CAN_MESSAGES_H
#define	BOOT_CAN_MESSAGES_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "mcc_generated_files/can_types.h"


//Maximum bytes that can be sent in a can frame is 8

#define MAX_DATA_LENGTH 8

enum BOOT_COMMAND_RESPONSES
{
    COMMAND_SUCCESS = 0x01,
    READ_FLASH_RESULT = 0x05,
    UNSUPPORTED_COMMAND = 0xFF,
    BAD_ADDRESS = 0xFE,
    BAD_LENGTH  = 0xFD,
    VERIFY_FAIL = 0xFC,
    BAD_DLC = 0xFB
};

enum BOOT_COMMAND
{
    READ_VERSION = 0x11,
    READ_FLASH = 0x01,
    
    WRITE_FLASH = 0x02,
    UNLOCK_FLASH = 0x0C,
    FLASH_DATA = 0x0D,
    ERASE_FLASH = 0x03,
    CALC_CHECKSUM = 0x08,
    RESET_DEVICE = 0x09,
    SELF_VERIFY = 0x0A,
    GET_MEMORY_ADDRESS_RANGE_COMMAND = 0x0B,
    
};


//////////HOST COMMANDS//////////////

struct __attribute__((__packed__)) CMD_NO_DATA{
    
    uint8_t cmd;
};

struct __attribute__((__packed__)) RSP_NO_DATA{
    
    uint8_t cmd;
};

struct __attribute__((__packed__)) CMD_WITH_DATA{
    
    uint8_t cmd;
    uint8_t dataLength;
    uint8_t data[MAX_DATA_LENGTH];
    
};

struct __attribute__((__packed__)) RSP_WITH_DATA{
    
    uint8_t cmd;
    uint8_t dataLength;
    uint8_t data[MAX_DATA_LENGTH];
};


struct __attribute__((__packed__)) RSP_GET_ADDRESS{
    
    CAN_MSG_OBJ msgTx;
};



#endif	/* XC_HEADER_TEMPLATE_H */

