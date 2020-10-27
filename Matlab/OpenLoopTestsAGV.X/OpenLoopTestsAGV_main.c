/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * -------------------------------------------------------------------
 * MPLAB 16-Bit Device Blocks for Simulink v3.47 (09-Oct-2020)
 *
 *   Product Page:  http://www.microchip.com/SimulinkBlocks
 *           Forum: http://www.microchip.com/forums/f192.aspx
 *           Wiki:  http://microchip.wikidot.com/simulink:start
 * -------------------------------------------------------------------
 * File: OpenLoopTestsAGV_main.c
 *
 * Code generated for Simulink model 'OpenLoopTestsAGV'.
 *
 * Model version                  : 1.34
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Sat Oct 24 00:10:18 2020
 */

/* Set Fuses Options */

#pragma config FNOSC = PRI, PWMLOCK = OFF
#pragma config POSCMD = EC, OSCIOFNC = ON, FCKSM = CSECMD
#pragma config FWDTEN = OFF
#pragma config JTAGEN = OFF

#define MCHP_isMainFile
#include "OpenLoopTestsAGV.h"
#include "OpenLoopTestsAGV_private.h"

/* Microchip Global Variables */
int main()
{
  /* Initialize model */

  /* Start Clock Switching */
  if ((OSCCONbits.COSC & 1) && !(OSCCONbits.COSC & 4))/* check not already in PLL mode (0?1) */
  {
    __builtin_write_OSCCONH(0);        /* Clock Switch to non PLL mode */
    __builtin_write_OSCCONL(0x01);     /* Start clock switching */
    __asm__ volatile("nop\n"
                     "nop");
    while (OSCCONbits.COSC != 0) ;
  }

  PLLFBD = 70;                         /* Oscillator PLL : PLLDIV */
  CLKDIV = 0x01;                /* Oscillator PLL : FRCDIV ; PLLPOST ; PLLPRE */
  __builtin_write_OSCCONH(3);        /* Clock Switch to desired configuration */
  __builtin_write_OSCCONL(0x01);       /* Start clock switching */

  /* Configure Pins as Analog or Digital */
  ANSELA = 0x01;
  ANSELB = 0x0C;

  /* Configure Remappables Pins */
  RPINR14 = 0x2627;
  RPINR18 = 0x25;
  RPOR1 = 0x01;
  RPOR4 = 0x1011;

  /* Configure Digitals I/O directions */
  TRISA = 0xFFE7;
  TRISB = 0xF1EC;

  /* Finish clock switching procedure */
  while (OSCCONbits.COSC != 3) ;       /* Wait for Oscillator Stabilisation */
  while (OSCCONbits.LOCK != 1) ;       /* Wait for PLL Stabilisation */

  /* Initialize model */
  OpenLoopTestsAGV_initialize();

  /* Configure Timers */

  /* Enable Time-step */
  AD1CON1 = 0x80E4;                    /* ADC trig the model Time-step */

  /* Main Loop */
  for (;;) ;
}                                      /* end of main() */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
