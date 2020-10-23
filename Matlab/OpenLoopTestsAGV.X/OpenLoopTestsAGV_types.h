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
 * File: OpenLoopTestsAGV_types.h
 *
 * Code generated for Simulink model 'OpenLoopTestsAGV'.
 *
 * Model version                  : 1.34
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Sat Oct 24 00:10:18 2020
 */

#ifndef RTW_HEADER_OpenLoopTestsAGV_types_h_
#define RTW_HEADER_OpenLoopTestsAGV_types_h_

/* Declare UART1 Tx Circular Buffer Structure */
#define Tx_BUFF_SIZE_UART1             (128)

typedef struct MCHP_UART1_TxStr{
  volatile uint8_T buffer[Tx_BUFF_SIZE_UART1];/* Size Rx_BUFF_SIZE_UART1 is 128 */
  volatile uint_T tail;
  /* tail is the index for the next value to be read from the Circular buffer */
  volatile uint_T head;
  /* head is the index for the next value to be written into the Circular buffer */
} MCHP_UART1_TxStr;

/* Declare UART1 Rx Circular Buffer Structure */
#define Rx_BUFF_SIZE_UART1             (128)

typedef struct MCHP_UART1_RxStr{
  volatile uint8_T buffer[Rx_BUFF_SIZE_UART1];/* Size Rx_BUFF_SIZE_UART1 is 128 */
  volatile uint_T tail;
  /* tail is the index for the next value to be written into the Circular buffer */
  uint_T head;
  /* head is the index for the next value to be read from the Circular buffer */
} MCHP_UART1_RxStr;

/* To read the UART1 Rx Circular with a custom code: read the next value: buffer[head], then increment head index by 1 modulo Rx_BUFF_SIZE_UART1 (=128).
   code example:
   if ((0U != U1STAbits.URXDA) != 0)
   if (MCHP_UART1_Rx.tail != MCHP_UART1_Rx.head)	{  		// is buffer not empty ?
   output = (uint8_T) MCHP_UART1_Rx.buffer[MCHP_UART1_Rx.head ++];     // Read one char
   MCHP_UART1_Rx.head &= (Rx_BUFF_SIZE_UART1-1); 	// modulo : use a simple bitewise "and" operator as <Rx_BUFF_SIZE_UART1> is a power of 2
   }
 */

/* Forward declaration for rtModel */
typedef struct tag_RTM_OpenLoopTestsAGV_T RT_MODEL_OpenLoopTestsAGV_T;

#endif                                /* RTW_HEADER_OpenLoopTestsAGV_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
