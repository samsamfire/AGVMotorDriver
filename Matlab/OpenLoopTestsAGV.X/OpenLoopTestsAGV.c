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
 * File: OpenLoopTestsAGV.c
 *
 * Code generated for Simulink model 'OpenLoopTestsAGV'.
 *
 * Model version                  : 1.30
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Thu Oct 22 12:27:14 2020
 */

#include "OpenLoopTestsAGV.h"
#include "OpenLoopTestsAGV_private.h"

const uint16_T OpenLoopTestsAGV_U16GND = 0U;/* uint16_T ground */

/* Block signals and states (default storage) */
DW_OpenLoopTestsAGV_T OpenLoopTestsAGV_DW;

/* Real-time model */
RT_MODEL_OpenLoopTestsAGV_T OpenLoopTestsAGV_M_;
RT_MODEL_OpenLoopTestsAGV_T *const OpenLoopTestsAGV_M = &OpenLoopTestsAGV_M_;

/* Model step function for TID0 */
void OpenLoopTestsAGV_step0(void)      /* Sample time: [0.0002s, 0.0s] */
{
  uint16_T rtb_RateTransition1;
  uint16_T rtb_RateTransition2;

  /* S-Function (MCHP_ADC): '<Root>/ADC' */
  /* MCHP_ADC Block for ADC 1: <Root>/ADC/Output */
  OpenLoopTestsAGV_DW.U1CH1 = ADC1BuffChannelA[0];

  /* RateTransition: '<Root>/Rate Transition1' */
  rtb_RateTransition1 = OpenLoopTestsAGV_DW.RateTransition1_Buffer0;

  /* Saturate: '<Root>/Saturation' */
  if (rtb_RateTransition1 >= 5999U) {
    rtb_RateTransition1 = 5999U;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* RateTransition: '<Root>/Rate Transition2' */
  rtb_RateTransition2 = OpenLoopTestsAGV_DW.RateTransition2_Buffer0;

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/Constant'
   *  Switch: '<Root>/Switch1'
   */
  if (rtb_RateTransition2 > 0U) {
    OpenLoopTestsAGV_DW.Switch = rtb_RateTransition1;
    OpenLoopTestsAGV_DW.Switch1 = 0U;
  } else {
    OpenLoopTestsAGV_DW.Switch = 0U;
    OpenLoopTestsAGV_DW.Switch1 = rtb_RateTransition1;
  }

  /* End of Switch: '<Root>/Switch' */
  /* S-Function (MCHP_Digital_Output_Write): '<S6>/Digital Output Write' incorporates:
   *  Constant: '<Root>/Constant1'
   */
  LATAbits.LATA4 = true;

  /* S-Function (MCHP_Digital_Output_Write): '<S3>/Digital Output Write' incorporates:
   *  S-Function (MCHP_Digital_Input): '<Root>/Digital Input'
   */
  LATAbits.LATA3 = PORTAbits.RA1;

  /* Update for S-Function (MCHP_OC_HW): '<Root>/Output Compare - HW' */

  /* S-Function "dsPIC_PWM_OC" Block: <Root>/Output Compare - HW */
  OC1R = OpenLoopTestsAGV_DW.Switch;
  OC2R = OpenLoopTestsAGV_DW.Switch1;
}

/* Model step function for TID1 */
void OpenLoopTestsAGV_step1(void)      /* Sample time: [0.001s, 0.0s] */
{
  /* RateTransition: '<Root>/Rate Transition3' */
  OpenLoopTestsAGV_DW.U1CH1_e = OpenLoopTestsAGV_DW.U1CH1;

  /* S-Function (MCHP_QEI): '<Root>/QEI' */
  OpenLoopTestsAGV_DW.U1CH1_m = POS1CNTL;
                       /* POS1CNTH is not taken into account (16 bits output) */
  OpenLoopTestsAGV_DW.U1CH1_e3 = VEL1CNT;
                            /* Velocity Counter (Register is Reset when read) */

  /* S-Function (sfix_bitop): '<Root>/Bitwise Operator2' incorporates:
   *  S-Function (MCHP_Digital_Input): '<Root>/Digital Input4'
   */
  OpenLoopTestsAGV_DW.U1CH3 = PORTB & 61440U;

  /* RateTransition: '<Root>/Rate Transition4' */
  OpenLoopTestsAGV_DW.U1CH4 = OpenLoopTestsAGV_DW.RateTransition4_Buffer0;

  /* S-Function (MCHP_UART_Rx): '<Root>/UART Rx' */
  /* MCHP_UART_Rx Block: <Root>/UART Rx/Outputs */
  /* Circular Buffer implementation for UART1 */
  /* Circular Buffer implementation for UART1 */
  {                                    /* Start of Rx reception block */
    unsigned int n = 0;
    if (0U != U1STAbits.URXDA) {       /* Flush internal UART buffer */
      uint_T Tmp;
      _U1RXIE = 0;           /* Flush internal UART buffer, disable interrupt */
      Tmp = ~(MCHP_UART1_Rx.tail - MCHP_UART1_Rx.head);/* head - tail - 1 */
      Tmp &= (Rx_BUFF_SIZE_UART1 - 1);
      /* Tmp =  (head - tail - 1) modulo buffersize Rx_BUFF_SIZE_UART1)	<==> Rx_BUFF_SIZE_UART1 - (head - tail) - 1*/
      while (U1STAbits.URXDA == 1) {
        if (Tmp--) {
          MCHP_UART1_Rx.buffer[MCHP_UART1_Rx.tail] = (uint8_T) U1RXREG;
          MCHP_UART1_Rx.tail = (MCHP_UART1_Rx.tail+1) & (Rx_BUFF_SIZE_UART1 - 1);
        } else {
          unsigned int a;
          do
            a = U1RXREG;
          while (U1STAbits.URXDA == 1);
          break;
        }
      }

      _U1RXIF = 0;                     /* Reset interrupt */
      _U1RXIE = 1;                     /* Re-enable interrupt */
    }

    if (MCHP_UART1_Rx.tail != MCHP_UART1_Rx.head) {
      OpenLoopTestsAGV_DW.U2Rx_m = (uint8_T)
        MCHP_UART1_Rx.buffer[MCHP_UART1_Rx.head];/* Use only the 8 low bytes or RxReg */
      MCHP_UART1_Rx.head = (MCHP_UART1_Rx.head+1) & (Rx_BUFF_SIZE_UART1 - 1);
      n += 1;                          /* Number of character received */
    } else {                           /* Buffer is empty */
      if (U1STAbits.OERR )
        U1STAbits.OERR = 0;            /* Clear UART Rx Overload Error */
      OpenLoopTestsAGV_DW.U2Rx_m = 0;
                   /* Rx buffer empty. Fill-in output vector with given value */
    }

    OpenLoopTestsAGV_DW.U2Rx = n;      /* Number of char received */
  }                                    /* end of Rx reception block */

  /* Update for S-Function (MCHP_UART_TxMatlab): '<Root>/UART Tx-Matlab' */

  /* MCHP_UART_Tx-Matlab Block for UART1: <Root>/UART Tx-Matlab/Outputs */
  {
    register char* array;
    register uint_T LocalTail = MCHP_UART1_Tx.tail;
    /* Tail is a volatile variable. Use local variable to speed-up execution */
    uint_T tmp;
    tmp = ~(LocalTail - MCHP_UART1_Tx.head);
    tmp = tmp & (Tx_BUFF_SIZE_UART1 - 1);/* Modulo Buffer Size */
    if (tmp >= 19) {
      /* CH 1 */
      MCHP_UART1_Tx.buffer[LocalTail] = 5 ;/* Control byte */
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);
      array = (char*) &OpenLoopTestsAGV_DW.U1CH1_e;
      MCHP_UART1_Tx.buffer[LocalTail] = array[0];
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);
      MCHP_UART1_Tx.buffer[LocalTail] = array[1];
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);

      /* CH 2 */
      MCHP_UART1_Tx.buffer[LocalTail] = 21 ;/* Control byte */
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);
      array = (char*) &OpenLoopTestsAGV_DW.U1CH1_m;
      MCHP_UART1_Tx.buffer[LocalTail] = array[0];
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);
      MCHP_UART1_Tx.buffer[LocalTail] = array[1];
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);

      /* CH 3 */
      MCHP_UART1_Tx.buffer[LocalTail] = 37 ;/* Control byte */
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);
      array = (char*) &OpenLoopTestsAGV_DW.U1CH3;
      MCHP_UART1_Tx.buffer[LocalTail] = array[0];
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);
      MCHP_UART1_Tx.buffer[LocalTail] = array[1];
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);

      /* CH 4 */
      MCHP_UART1_Tx.buffer[LocalTail] = 49 ;/* Control byte */
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);
      MCHP_UART1_Tx.buffer[LocalTail] = OpenLoopTestsAGV_DW.U1CH4 ;
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);

      /* CH 5 */
      MCHP_UART1_Tx.buffer[LocalTail] = 69 ;/* Control byte */
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);
      array = (char*) ((uint16_T*) &OpenLoopTestsAGV_U16GND);
      MCHP_UART1_Tx.buffer[LocalTail] = array[0];
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);
      MCHP_UART1_Tx.buffer[LocalTail] = array[1];
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);

      /* CH 6 */
      MCHP_UART1_Tx.buffer[LocalTail] = 81 ;/* Control byte */
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);
      MCHP_UART1_Tx.buffer[LocalTail] = OpenLoopTestsAGV_DW.U2Rx_m ;
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);

      /* CH 7 */
      MCHP_UART1_Tx.buffer[LocalTail] = 101 ;/* Control byte */
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);
      array = (char*) ((uint16_T*) &OpenLoopTestsAGV_U16GND);
      MCHP_UART1_Tx.buffer[LocalTail] = array[0];
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);
      MCHP_UART1_Tx.buffer[LocalTail] = array[1];
      LocalTail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);
    }

    if (MCHP_UART1_Tx.tail != LocalTail) {
      MCHP_UART1_Tx.tail = LocalTail;  /* Push back volatile variable */

      {
        register uint_T LocalHead;
        _U1TXIE = 0;
           /* Disable Interrupt portecting against possible concurrent access */
        _U1TXIF = 0;                   /* Clear Interrupt Flag */
        LocalHead = MCHP_UART1_Tx.head;
        /* Head is a volatile variable. Use local variable to speed-up execution */
        while ((0U == U1STAbits.UTXBF) && (MCHP_UART1_Tx.tail != LocalHead) )/* while UxTXREG buffer is not full */
        {
          U1TXREG = MCHP_UART1_Tx.buffer[LocalHead];
          LocalHead = (LocalHead + 1) & (Tx_BUFF_SIZE_UART1-1);
        }

        MCHP_UART1_Tx.head = LocalHead;/* Push back volatile variable */
        if (MCHP_UART1_Tx.tail != LocalHead)
                /* If remaining values to send present in the circular buffer */
        {
          _U1TXIE = 1;                 /* Enable Interrupt */
        }
      }
    }
  }
}

/* Model step function for TID2 */
void OpenLoopTestsAGV_step2(void)      /* Sample time: [0.1s, 0.0s] */
{
  int16_T i;

  /* S-Function (MCHP_C_function_Call): '<Root>/C Function Call3' */
  OpenLoopTestsAGV_DW.CFunctionCall3_o1 = ECAN1_Simulink_Receive(
    &OpenLoopTestsAGV_DW.CFunctionCall3_o2
    , &OpenLoopTestsAGV_DW.CFunctionCall3_o3[0]
    , &OpenLoopTestsAGV_DW.CFunctionCall3_o4
    );

  /* DataTypeConversion: '<Root>/Data Type Conversion' incorporates:
   *  Constant: '<S1>/Constant'
   *  Logic: '<Root>/Logical Operator1'
   *  RelationalOperator: '<S1>/Compare'
   */
  OpenLoopTestsAGV_DW.DataTypeConversion = (uint16_T)
    ((OpenLoopTestsAGV_DW.CFunctionCall3_o1 != 0U) &&
     (OpenLoopTestsAGV_DW.CFunctionCall3_o2 == 288U));

  /* Sum: '<Root>/Add' incorporates:
   *  Constant: '<Root>/Constant5'
   */
  OpenLoopTestsAGV_DW.Add = OpenLoopTestsAGV_DW.CFunctionCall3_o2 + 1U;

  /* S-Function (MCHP_C_function_Call): '<Root>/C Function Call1' */
  ECAN1_Simulink_Transmit(
    OpenLoopTestsAGV_DW.DataTypeConversion
    , OpenLoopTestsAGV_DW.Add
    , OpenLoopTestsAGV_DW.CFunctionCall3_o4
    , &OpenLoopTestsAGV_DW.CFunctionCall3_o3[0]
    );

  /* Outputs for Enabled SubSystem: '<Root>/Subsystem' incorporates:
   *  EnablePort: '<S9>/Enable'
   */
  if (OpenLoopTestsAGV_DW.CFunctionCall3_o1 > 0U) {
    /* Inport: '<S9>/In1' */
    for (i = 0; i < 8; i++) {
      OpenLoopTestsAGV_DW.In1[i] = OpenLoopTestsAGV_DW.CFunctionCall3_o3[i];
    }

    /* End of Inport: '<S9>/In1' */
  }

  /* End of Outputs for SubSystem: '<Root>/Subsystem' */

  /* RateTransition: '<Root>/Rate Transition4' */
  OpenLoopTestsAGV_DW.RateTransition4_Buffer0 = OpenLoopTestsAGV_DW.In1[1];
}

/* Model step function for TID3 */
void OpenLoopTestsAGV_step3(void)      /* Sample time: [1.0s, 0.0s] */
{
  /* local block i/o variables */
  boolean_T rtb_DataTypeConversion1;
  boolean_T rtb_DataTypeConversion2;

  /* DataTypeConversion: '<Root>/Data Type Conversion1' incorporates:
   *  S-Function (sfix_bitop): '<Root>/Bitwise Operator'
   *  UnitDelay: '<S2>/Output'
   */
  rtb_DataTypeConversion1 = ((OpenLoopTestsAGV_DW.Output_DSTATE_o & 1U) != 0U);

  /* S-Function (MCHP_Digital_Output_Write): '<S4>/Digital Output Write' */
  LATBbits.LATB0 = rtb_DataTypeConversion1;

  /* DataTypeConversion: '<Root>/Data Type Conversion2' incorporates:
   *  S-Function (sfix_bitop): '<Root>/Bitwise Operator1'
   *  UnitDelay: '<S2>/Output'
   */
  rtb_DataTypeConversion2 = ((OpenLoopTestsAGV_DW.Output_DSTATE_o & 2U) != 0U);

  /* S-Function (MCHP_Digital_Output_Write): '<S5>/Digital Output Write' */
  LATBbits.LATB1 = rtb_DataTypeConversion2;

  /* Update for UnitDelay: '<S2>/Output' incorporates:
   *  Constant: '<S10>/FixPt Constant'
   *  Sum: '<S10>/FixPt Sum1'
   */
  OpenLoopTestsAGV_DW.Output_DSTATE_o = (uint8_T)((uint8_T)
    (OpenLoopTestsAGV_DW.Output_DSTATE_o + 1U) & 3);
}

/* Model step function for TID4 */
void OpenLoopTestsAGV_step4(void)      /* Sample time: [2.0s, 0.0s] */
{
  uint16_T rtb_Output;
  uint8_T rtb_FixPtSum1;

  /* MultiPortSwitch: '<S7>/Output' incorporates:
   *  Constant: '<S7>/Vector'
   *  UnitDelay: '<S12>/Output'
   */
  rtb_Output =
    OpenLoopTestsAGV_ConstP.Vector_Value[OpenLoopTestsAGV_DW.Output_DSTATE];

  /* RateTransition: '<Root>/Rate Transition1' */
  OpenLoopTestsAGV_DW.RateTransition1_Buffer0 = rtb_Output;

  /* Sum: '<S13>/FixPt Sum1' incorporates:
   *  Constant: '<S13>/FixPt Constant'
   *  UnitDelay: '<S12>/Output'
   */
  rtb_FixPtSum1 = (uint8_T)(OpenLoopTestsAGV_DW.Output_DSTATE + 1U);

  /* Switch: '<S14>/FixPt Switch' */
  if (rtb_FixPtSum1 > 1) {
    /* Update for UnitDelay: '<S12>/Output' incorporates:
     *  Constant: '<S14>/Constant'
     */
    OpenLoopTestsAGV_DW.Output_DSTATE = 0U;
  } else {
    /* Update for UnitDelay: '<S12>/Output' */
    OpenLoopTestsAGV_DW.Output_DSTATE = rtb_FixPtSum1;
  }

  /* End of Switch: '<S14>/FixPt Switch' */
}

/* Model step function for TID5 */
void OpenLoopTestsAGV_step5(void)      /* Sample time: [4.0s, 0.0s] */
{
  uint16_T rtb_Output;
  uint8_T rtb_FixPtSum1;

  /* MultiPortSwitch: '<S8>/Output' incorporates:
   *  Constant: '<S8>/Vector'
   *  UnitDelay: '<S15>/Output'
   */
  rtb_Output =
    OpenLoopTestsAGV_ConstP.Vector_Value_g[OpenLoopTestsAGV_DW.Output_DSTATE_d];

  /* RateTransition: '<Root>/Rate Transition2' */
  OpenLoopTestsAGV_DW.RateTransition2_Buffer0 = rtb_Output;

  /* Sum: '<S16>/FixPt Sum1' incorporates:
   *  Constant: '<S16>/FixPt Constant'
   *  UnitDelay: '<S15>/Output'
   */
  rtb_FixPtSum1 = (uint8_T)(OpenLoopTestsAGV_DW.Output_DSTATE_d + 1U);

  /* Switch: '<S17>/FixPt Switch' */
  if (rtb_FixPtSum1 > 1) {
    /* Update for UnitDelay: '<S15>/Output' incorporates:
     *  Constant: '<S17>/Constant'
     */
    OpenLoopTestsAGV_DW.Output_DSTATE_d = 0U;
  } else {
    /* Update for UnitDelay: '<S15>/Output' */
    OpenLoopTestsAGV_DW.Output_DSTATE_d = rtb_FixPtSum1;
  }

  /* End of Switch: '<S17>/FixPt Switch' */
}

/* Model initialize function */
void OpenLoopTestsAGV_initialize(void)
{
  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)&OpenLoopTestsAGV_DW, 0,
                sizeof(DW_OpenLoopTestsAGV_T));

  /* Start for S-Function (MCHP_Master): '<Root>/Microchip Master' */

  /* S-Function "Microchip MASTER" initialization Block: <Root>/Microchip Master */

  /* Start for S-Function (MCHP_ADC): '<Root>/ADC' */

  /* MCHP_ADC Block for ADC 1: <Root>/ADC/Initialize */
  AD1CHS0 = 0x00;
  AD1CHS123 = 0x00;
  AD1CON3 = 0x1FFF;
  AD1CON2 = 0x00;

  /* ADC is used to trig the model Time-step. AD1CON1 will be set after the setup-code */
  _AD1IP = 2;                          /*Interrupt Priority : 2*/
  _AD1IF = 0;
  _AD1IE = 1;                          /* Enable ADC Interrupt */

  /* Start for S-Function (MCHP_OC_HW): '<Root>/Output Compare - HW' */
  OC1CON1 = 0x1C0E;
  OC1CON2 = 0x109F;
  OC1RS = 0x176F;
  OC2CON1 = 0x1C0E;
  OC2CON2 = 0x109F;
  OC2RS = 0x176F;

  /* Start for S-Function (MCHP_C_function_Call): '<Root>/C Function Call' */
  ECAN1_Simulink_Init(
                      );

  /* Start for S-Function (MCHP_UART_Config): '<Root>/UART Configuration' */

  /* MCHP_UART_Config Block for UART 1: <Root>/UART Configuration/Initialize */
  U1BRG = 0x4A;                        /* Baud rate: 200000 (+0.00%) */
  U1MODE = 0x8008;
  U1STA = 0x8400;

  /* Configure UART1 using Tx Interruption */
  _U1TXIP = 5;                         /*  Tx Interrupt priority set to 5 */
  _U1TXIF = 0;                         /*  */
  _U1TXIE = 1;                         /* Enable Interrupt */

  /* Configure UART1 Rx Interruption for <Root>/UART Configuration */
  _U1RXIP = 5;                         /* Rx Interrupt priority set to 5 */
  _U1RXIF = 0;                         /*  */
  _U1RXIE = 1;                         /* Enable Interrupt */

  /* Start for S-Function (MCHP_QEI): '<Root>/QEI' */

  /* Initialize QEI 1 Peripheral */
  QEI1LECH = 0x00;                     /* Lower bound (High)*/
  QEI1LECL = 0x00;                     /* Lower bound (Low)*/
  QEI1GECH = 0x00;                     /* Upper bound (High)*/
  QEI1GECL = 0xFFFF;                   /* Upper bound (Low)*/
  QEI1IOC = 0x7000;
  QEI1CON = 0x9800;

  /* InitializeConditions for RateTransition: '<Root>/Rate Transition1' */
  OpenLoopTestsAGV_DW.RateTransition1_Buffer0 = 232U;

  /* InitializeConditions for RateTransition: '<Root>/Rate Transition2' */
  OpenLoopTestsAGV_DW.RateTransition2_Buffer0 = 232U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
