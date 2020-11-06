
/**
  TMR4 Generated Driver API Source File 

  @Company
    Microchip Technology Inc.

  @File Name
    tmr4.c

  @Summary
    This is the generated source file for the TMR4 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for TMR4. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.169.0
        Device            :  dsPIC33EP256MC502
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB             :  MPLAB X v5.40
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
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

#include <stdio.h>
#include "tmr4.h"

/**
 Section: File specific functions
*/
void (*TMR4_InterruptHandler)(void) = NULL;
void TMR4_CallBack(void);

/**
  Section: Data Type Definitions
*/

/** TMR Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

  @Description
    This defines the object required for the maintenance of the hardware
    instance. This object exists once per hardware instance of the peripheral.

  Remarks:
    None.
*/

typedef struct _TMR_OBJ_STRUCT
{
    /* Timer Elapsed */
    volatile bool           timerElapsed;
    /*Software Counter value*/
    volatile uint8_t        count;

} TMR_OBJ;

static TMR_OBJ tmr4_obj;

/**
  Section: Driver Interface
*/

void TMR4_Initialize (void)
{
    //TMR4 0; 
    TMR4 = 0x00;
    //Period = 0.0005000167 s; Frequency = 60000000 Hz; PR4 30000; 
    PR4 = 0x7530;
    //TCKPS 1:1; T32 16 Bit; TON enabled; TSIDL disabled; TCS FOSC/2; TGATE disabled; 
    T4CON = 0x8000;

    if(TMR4_InterruptHandler == NULL)
    {
        TMR4_SetInterruptHandler(&TMR4_CallBack);
    }

    IFS1bits.T4IF = false;
    IEC1bits.T4IE = true;
	
    tmr4_obj.timerElapsed = false;

}


void __attribute__ ( ( interrupt, no_auto_psv ) ) _T4Interrupt (  )
{
    /* Check if the Timer Interrupt/Status is set */

    //***User Area Begin

    // ticker function call;
    // ticker is 1 -> Callback function gets called everytime this ISR executes
    if(TMR4_InterruptHandler) 
    { 
           TMR4_InterruptHandler(); 
    }

    //***User Area End

    tmr4_obj.count++;
    tmr4_obj.timerElapsed = true;
    IFS1bits.T4IF = false;
}

void TMR4_Period16BitSet( uint16_t value )
{
    /* Update the counter values */
    PR4 = value;
    /* Reset the status information */
    tmr4_obj.timerElapsed = false;
}

uint16_t TMR4_Period16BitGet( void )
{
    return( PR4 );
}

void TMR4_Counter16BitSet ( uint16_t value )
{
    /* Update the counter values */
    TMR4 = value;
    /* Reset the status information */
    tmr4_obj.timerElapsed = false;
}

uint16_t TMR4_Counter16BitGet( void )
{
    return( TMR4 );
}


void __attribute__ ((weak)) TMR4_CallBack(void)
{
    // Add your custom callback code here
}

void  TMR4_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC1bits.T4IE = false;
    TMR4_InterruptHandler = InterruptHandler; 
    IEC1bits.T4IE = true;
}

void TMR4_Start( void )
{
    /* Reset the status information */
    tmr4_obj.timerElapsed = false;

    /*Enable the interrupt*/
    IEC1bits.T4IE = true;

    /* Start the Timer */
    T4CONbits.TON = 1;
}

void TMR4_Stop( void )
{
    /* Stop the Timer */
    T4CONbits.TON = false;

    /*Disable the interrupt*/
    IEC1bits.T4IE = false;
}

bool TMR4_GetElapsedThenClear(void)
{
    bool status;
    
    status = tmr4_obj.timerElapsed;

    if(status == true)
    {
        tmr4_obj.timerElapsed = false;
    }
    return status;
}

int TMR4_SoftwareCounterGet(void)
{
    return tmr4_obj.count;
}

void TMR4_SoftwareCounterClear(void)
{
    tmr4_obj.count = 0; 
}

/**
 End of File
*/
