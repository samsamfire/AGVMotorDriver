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
 * Model version                  : 1.34
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Sat Oct 24 00:10:18 2020
 */

#include "OpenLoopTestsAGV.h"
#include "OpenLoopTestsAGV_private.h"

/* Block signals and states (default storage) */
DW_OpenLoopTestsAGV_T OpenLoopTestsAGV_DW;

/* Real-time model */
RT_MODEL_OpenLoopTestsAGV_T OpenLoopTestsAGV_M_;
RT_MODEL_OpenLoopTestsAGV_T *const OpenLoopTestsAGV_M = &OpenLoopTestsAGV_M_;

/* Model step function for TID0 */
void OpenLoopTestsAGV_step0(void)      /* Sample time: [0.0002s, 0.0s] */
{
  /* local block i/o variables */
  uint16_T rtb_U1CH3;
  uint16_T rtb_RateTransition1;
  uint16_T rtb_RateTransition2;

  /* S-Function (MCHP_ADC): '<S1>/ADC' */
  /* MCHP_ADC Block for ADC 1: <S1>/ADC/Output */
  OpenLoopTestsAGV_DW.U1CH1 = ADC1BuffChannelA[0];

  /* S-Function (MCHP_Digital_Input): '<Root>/Digital Input4' */
  /* MCHP_Digital_Input Block: <Root>/Digital Input4/Output */
  rtb_U1CH3 = PORTB;

  /* RateTransition: '<Root>/Rate Transition1' */
  rtb_RateTransition1 = OpenLoopTestsAGV_DW.RateTransition1_Buffer0;

  /* Saturate: '<S7>/Saturation' */
  if (rtb_RateTransition1 >= 5999U) {
    rtb_RateTransition1 = 5999U;
  }

  /* End of Saturate: '<S7>/Saturation' */

  /* RateTransition: '<Root>/Rate Transition2' */
  rtb_RateTransition2 = OpenLoopTestsAGV_DW.RateTransition2_Buffer0;

  /* Switch: '<S7>/Switch' incorporates:
   *  Constant: '<S7>/Constant'
   *  Switch: '<S7>/Switch1'
   */
  if (rtb_RateTransition2 > 0U) {
    OpenLoopTestsAGV_DW.Switch = rtb_RateTransition1;
    OpenLoopTestsAGV_DW.Switch1 = 0U;
  } else {
    OpenLoopTestsAGV_DW.Switch = 0U;
    OpenLoopTestsAGV_DW.Switch1 = rtb_RateTransition1;
  }

  /* End of Switch: '<S7>/Switch' */
  /* S-Function (MCHP_Digital_Output_Write): '<S15>/Digital Output Write' incorporates:
   *  Constant: '<S4>/Constant1'
   */
  LATAbits.LATA4 = true;

  /* S-Function (MCHP_Digital_Output_Write): '<S21>/Digital Output Write' incorporates:
   *  S-Function (MCHP_Digital_Input): '<S9>/Digital Input'
   */
  LATAbits.LATA3 = PORTAbits.RA1;

  /* Update for S-Function (MCHP_OC_HW): '<S7>/Output Compare - HW' */

  /* S-Function "dsPIC_PWM_OC" Block: <S7>/Output Compare - HW */
  OC1R = OpenLoopTestsAGV_DW.Switch;
  OC2R = OpenLoopTestsAGV_DW.Switch1;
}

/* Model step function for TID1 */
void OpenLoopTestsAGV_step1(void)      /* Sample time: [0.001s, 0.0s] */
{
  /* local block i/o variables */
  boolean_T rtb_DigitalInput_o1;
  boolean_T rtb_DigitalInput_o2;
  boolean_T rtb_DigitalInput_o3;
  boolean_T rtb_DigitalInput_o4;

  /* S-Function (MCHP_Digital_Input): '<S2>/Digital Input' */
  /* MCHP_Digital_Input Block: <S2>/Digital Input/Output */
  rtb_DigitalInput_o1 = PORTBbits.RB12;/* Read pin B12 */
  rtb_DigitalInput_o2 = PORTBbits.RB13;/* Read pin B13 */
  rtb_DigitalInput_o3 = PORTBbits.RB14;/* Read pin B14 */
  rtb_DigitalInput_o4 = PORTBbits.RB15;/* Read pin B15 */

  /* S-Function (sfix_bitop): '<S2>/Bitwise Operator1' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion'
   *  DataTypeConversion: '<S2>/Data Type Conversion1'
   *  DataTypeConversion: '<S2>/Data Type Conversion2'
   *  DataTypeConversion: '<S2>/Data Type Conversion4'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S2>/Gain3'
   *  Gain: '<S2>/Gain4'
   *  S-Function (sfix_bitop): '<S2>/Bitwise Operator'
   *  Sum: '<S2>/Add'
   */
  OpenLoopTestsAGV_DW.BitwiseOperator1 = (uint8_T)((uint8_T)~(uint8_T)
    (((((uint16_T)rtb_DigitalInput_o2 << 1) + rtb_DigitalInput_o1) + ((uint16_T)
    rtb_DigitalInput_o3 << 2)) + ((uint16_T)rtb_DigitalInput_o4 << 3)) & 15);

  /* S-Function (MCHP_UART_Tx): '<S12>/UART Tx' */
  /* MCHP_UART_Tx Block: <S12>/UART Tx/Outputs */
  {
    uint_T Tmp;
    Tmp = ~(MCHP_UART1_Tx.tail - MCHP_UART1_Tx.head);/* head - tail - 1 */
    Tmp = Tmp & (Tx_BUFF_SIZE_UART1 - 1);
    /* Modulo Buffer Size (Buffer Size is 2^n). Tmp is the buffer free space */

    {
      register uint_T LocalTail = MCHP_UART1_Tx.tail;
      /* Tail is a volatile variable. Use local variable to speed-up execution */
      MCHP_UART1_Tx.buffer[LocalTail] = OpenLoopTestsAGV_DW.BitwiseOperator1;
      MCHP_UART1_Tx.tail = (LocalTail + 1) & (Tx_BUFF_SIZE_UART1 - 1);
    }

    {
      register uint_T LocalHead;
      _U1TXIE = 0;
           /* Disable Interrupt portecting against possible concurrent access */
      _U1TXIF = 0;                     /* Clear Interrupt Flag */
      LocalHead = MCHP_UART1_Tx.head;
      /* Head is a volatile variable. Use local variable to speed-up execution */
      while ((0U == U1STAbits.UTXBF) && (MCHP_UART1_Tx.tail != LocalHead) )/* while UxTXREG buffer is not full */
      {
        U1TXREG = MCHP_UART1_Tx.buffer[LocalHead];
        LocalHead = (LocalHead + 1) & (Tx_BUFF_SIZE_UART1-1);
      }

      MCHP_UART1_Tx.head = LocalHead;  /* Push back volatile variable */
      if (MCHP_UART1_Tx.tail != LocalHead)
                /* If remaining values to send present in the circular buffer */
      {
        _U1TXIE = 1;                   /* Enable Interrupt */
      }
    }
  }

  /* S-Function (MCHP_QEI): '<S8>/QEI' */
  OpenLoopTestsAGV_DW.U1CH1_m = POS1CNTL;
                       /* POS1CNTH is not taken into account (16 bits output) */
  OpenLoopTestsAGV_DW.U1CH1_e = VEL1CNT;
                            /* Velocity Counter (Register is Reset when read) */

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
}

/* Model step function for TID2 */
void OpenLoopTestsAGV_step2(void)      /* Sample time: [0.1s, 0.0s] */
{
  /* S-Function (MCHP_C_function_Call): '<S3>/C Function Call3' */
  OpenLoopTestsAGV_DW.CFunctionCall3_o1 = ECAN1_Simulink_Receive(
    &OpenLoopTestsAGV_DW.CFunctionCall3_o2
    , &OpenLoopTestsAGV_DW.CFunctionCall3_o3[0]
    , &OpenLoopTestsAGV_DW.CFunctionCall3_o4
    );

  /* DataTypeConversion: '<S3>/Data Type Conversion' incorporates:
   *  Constant: '<S13>/Constant'
   *  Logic: '<S3>/Logical Operator1'
   *  RelationalOperator: '<S13>/Compare'
   */
  OpenLoopTestsAGV_DW.DataTypeConversion = (uint16_T)
    ((OpenLoopTestsAGV_DW.CFunctionCall3_o1 != 0U) &&
     (OpenLoopTestsAGV_DW.CFunctionCall3_o2 == 288U));

  /* Sum: '<S3>/Add' incorporates:
   *  Constant: '<S3>/Constant5'
   */
  OpenLoopTestsAGV_DW.Add = OpenLoopTestsAGV_DW.CFunctionCall3_o2 + 1U;

  /* S-Function (MCHP_C_function_Call): '<S3>/C Function Call1' */
  ECAN1_Simulink_Transmit(
    OpenLoopTestsAGV_DW.DataTypeConversion
    , OpenLoopTestsAGV_DW.Add
    , OpenLoopTestsAGV_DW.CFunctionCall3_o4
    , &OpenLoopTestsAGV_DW.CFunctionCall3_o3[0]
    );
}

/* Model step function for TID3 */
void OpenLoopTestsAGV_step3(void)      /* Sample time: [1.0s, 0.0s] */
{
  /* local block i/o variables */
  boolean_T rtb_DataTypeConversion1;
  boolean_T rtb_DataTypeConversion2;

  /* DataTypeConversion: '<S5>/Data Type Conversion1' incorporates:
   *  S-Function (sfix_bitop): '<S5>/Bitwise Operator'
   *  UnitDelay: '<S16>/Output'
   */
  rtb_DataTypeConversion1 = ((OpenLoopTestsAGV_DW.Output_DSTATE_o & 1U) != 0U);

  /* S-Function (MCHP_Digital_Output_Write): '<S17>/Digital Output Write' */
  LATBbits.LATB0 = rtb_DataTypeConversion1;

  /* DataTypeConversion: '<S5>/Data Type Conversion2' incorporates:
   *  S-Function (sfix_bitop): '<S5>/Bitwise Operator1'
   *  UnitDelay: '<S16>/Output'
   */
  rtb_DataTypeConversion2 = ((OpenLoopTestsAGV_DW.Output_DSTATE_o & 2U) != 0U);

  /* S-Function (MCHP_Digital_Output_Write): '<S18>/Digital Output Write' */
  LATBbits.LATB1 = rtb_DataTypeConversion2;

  /* Update for UnitDelay: '<S16>/Output' incorporates:
   *  Constant: '<S19>/FixPt Constant'
   *  Sum: '<S19>/FixPt Sum1'
   */
  OpenLoopTestsAGV_DW.Output_DSTATE_o = (uint8_T)((uint8_T)
    (OpenLoopTestsAGV_DW.Output_DSTATE_o + 1U) & 3);
}

/* Model step function for TID4 */
void OpenLoopTestsAGV_step4(void)      /* Sample time: [2.0s, 0.0s] */
{
  uint16_T rtb_Output;
  uint8_T rtb_FixPtSum1;

  /* MultiPortSwitch: '<S10>/Output' incorporates:
   *  Constant: '<S10>/Vector'
   *  UnitDelay: '<S22>/Output'
   */
  rtb_Output =
    OpenLoopTestsAGV_ConstP.Vector_Value[OpenLoopTestsAGV_DW.Output_DSTATE];

  /* RateTransition: '<Root>/Rate Transition1' */
  OpenLoopTestsAGV_DW.RateTransition1_Buffer0 = rtb_Output;

  /* Sum: '<S23>/FixPt Sum1' incorporates:
   *  Constant: '<S23>/FixPt Constant'
   *  UnitDelay: '<S22>/Output'
   */
  rtb_FixPtSum1 = (uint8_T)(OpenLoopTestsAGV_DW.Output_DSTATE + 1U);

  /* Switch: '<S24>/FixPt Switch' */
  if (rtb_FixPtSum1 > 1) {
    /* Update for UnitDelay: '<S22>/Output' incorporates:
     *  Constant: '<S24>/Constant'
     */
    OpenLoopTestsAGV_DW.Output_DSTATE = 0U;
  } else {
    /* Update for UnitDelay: '<S22>/Output' */
    OpenLoopTestsAGV_DW.Output_DSTATE = rtb_FixPtSum1;
  }

  /* End of Switch: '<S24>/FixPt Switch' */
}

/* Model step function for TID5 */
void OpenLoopTestsAGV_step5(void)      /* Sample time: [4.0s, 0.0s] */
{
  uint16_T rtb_Output;
  uint8_T rtb_FixPtSum1;

  /* MultiPortSwitch: '<S11>/Output' incorporates:
   *  Constant: '<S11>/Vector'
   *  UnitDelay: '<S25>/Output'
   */
  rtb_Output =
    OpenLoopTestsAGV_ConstP.Vector_Value_g[OpenLoopTestsAGV_DW.Output_DSTATE_d];

  /* RateTransition: '<Root>/Rate Transition2' */
  OpenLoopTestsAGV_DW.RateTransition2_Buffer0 = rtb_Output;

  /* Sum: '<S26>/FixPt Sum1' incorporates:
   *  Constant: '<S26>/FixPt Constant'
   *  UnitDelay: '<S25>/Output'
   */
  rtb_FixPtSum1 = (uint8_T)(OpenLoopTestsAGV_DW.Output_DSTATE_d + 1U);

  /* Switch: '<S27>/FixPt Switch' */
  if (rtb_FixPtSum1 > 1) {
    /* Update for UnitDelay: '<S25>/Output' incorporates:
     *  Constant: '<S27>/Constant'
     */
    OpenLoopTestsAGV_DW.Output_DSTATE_d = 0U;
  } else {
    /* Update for UnitDelay: '<S25>/Output' */
    OpenLoopTestsAGV_DW.Output_DSTATE_d = rtb_FixPtSum1;
  }

  /* End of Switch: '<S27>/FixPt Switch' */
}

/* Model initialize function */
void OpenLoopTestsAGV_initialize(void)
{
  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)&OpenLoopTestsAGV_DW, 0,
                sizeof(DW_OpenLoopTestsAGV_T));

  /* Start for S-Function (MCHP_ADC): '<S1>/ADC' */

  /* MCHP_ADC Block for ADC 1: <S1>/ADC/Initialize */
  AD1CHS0 = 0x00;
  AD1CHS123 = 0x00;
  AD1CON3 = 0x1FFF;
  AD1CON2 = 0x00;

  /* ADC is used to trig the model Time-step. AD1CON1 will be set after the setup-code */
  _AD1IP = 2;                          /*Interrupt Priority : 2*/
  _AD1IF = 0;
  _AD1IE = 1;                          /* Enable ADC Interrupt */

  /* Start for S-Function (MCHP_C_function_Call): '<S3>/C Function Call' */
  ECAN1_Simulink_Init(
                      );

  /* Start for S-Function (MCHP_OC_HW): '<S7>/Output Compare - HW' */
  OC1CON1 = 0x1C0E;
  OC1CON2 = 0x109F;
  OC1RS = 0x176F;
  OC2CON1 = 0x1C0E;
  OC2CON2 = 0x109F;
  OC2RS = 0x176F;

  /* Start for S-Function (MCHP_Master): '<S6>/Microchip Master' */

  /* S-Function "Microchip MASTER" initialization Block: <S6>/Microchip Master */

  /* Start for S-Function (MCHP_UART_Config): '<S6>/UART Configuration' */

  /* MCHP_UART_Config Block for UART 1: <S6>/UART Configuration/Initialize */
  U1BRG = 0x95;                        /* Baud rate: 100000 (+0.00%) */
  U1MODE = 0x8008;
  U1STA = 0x8400;

  /* Configure UART1 using Tx Interruption */
  _U1TXIP = 5;                         /*  Tx Interrupt priority set to 5 */
  _U1TXIF = 0;                         /*  */
  _U1TXIE = 1;                         /* Enable Interrupt */

  /* Configure UART1 Rx Interruption for <S6>/UART Configuration */
  _U1RXIP = 5;                         /* Rx Interrupt priority set to 5 */
  _U1RXIF = 0;                         /*  */
  _U1RXIE = 1;                         /* Enable Interrupt */

  /* Start for S-Function (MCHP_QEI): '<S8>/QEI' */

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
