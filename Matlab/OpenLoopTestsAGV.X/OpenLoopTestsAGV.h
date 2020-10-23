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
 * File: OpenLoopTestsAGV.h
 *
 * Code generated for Simulink model 'OpenLoopTestsAGV'.
 *
 * Model version                  : 1.34
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Sat Oct 24 00:10:18 2020
 */

#ifndef RTW_HEADER_OpenLoopTestsAGV_h_
#define RTW_HEADER_OpenLoopTestsAGV_h_
#include <string.h>
#ifndef OpenLoopTestsAGV_COMMON_INCLUDES_
# define OpenLoopTestsAGV_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* OpenLoopTestsAGV_COMMON_INCLUDES_ */

#include "OpenLoopTestsAGV_types.h"
#define FCY                            (60000000U)               /* Instruction Frequency FCY set at  60.0 MHz */

/* Include for pic 33E */
#include <xc.h>
#include <libpic30.h>
/* For possible use with C function Call block (delay_ms or delay_us functions might be used by few peripherals) */
#include <libq.h>              /* For possible use with C function Call block */

/* Macros for accessing real-time model data structure */
#ifndef rtmCounterLimit
# define rtmCounterLimit(rtm, idx)     ((rtm)->Timing.TaskCounters.cLimit[(idx)])
#endif

#ifndef rtmStepTask
# define rtmStepTask(rtm, idx)         ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmTaskCounter
# define rtmTaskCounter(rtm, idx)      ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* user code (top of header file) */
#include "can1.h";
#include "ecan1.h";
#include "dma.h";
#include "can_types.h";

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  int16_T U1CH1_e;                     /* '<S8>/QEI' */
  uint16_T U1CH1;                      /* '<S1>/ADC' */
  uint16_T Switch;                     /* '<S7>/Switch' */
  uint16_T Switch1;                    /* '<S7>/Switch1' */
  uint16_T U1CH1_m;                    /* '<S8>/QEI' */
  uint16_T U2Rx;                       /* '<Root>/UART Rx' */
  uint16_T CFunctionCall3_o1;          /* '<S3>/C Function Call3' */
  uint16_T CFunctionCall3_o2;          /* '<S3>/C Function Call3' */
  uint16_T DataTypeConversion;         /* '<S3>/Data Type Conversion' */
  uint16_T Add;                        /* '<S3>/Add' */
  volatile uint16_T RateTransition1_Buffer0;/* '<Root>/Rate Transition1' */
  volatile uint16_T RateTransition2_Buffer0;/* '<Root>/Rate Transition2' */
  uint8_T CFunctionCall3_o3[8];        /* '<S3>/C Function Call3' */
  uint8_T BitwiseOperator1;            /* '<S2>/Bitwise Operator1' */
  uint8_T U2Rx_m;                      /* '<Root>/UART Rx' */
  uint8_T CFunctionCall3_o4;           /* '<S3>/C Function Call3' */
  uint8_T Output_DSTATE;               /* '<S22>/Output' */
  uint8_T Output_DSTATE_d;             /* '<S25>/Output' */
  uint8_T Output_DSTATE_o;             /* '<S16>/Output' */
} DW_OpenLoopTestsAGV_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Computed Parameter: Vector_Value
   * Referenced by: '<S10>/Vector'
   */
  uint16_T Vector_Value[2];

  /* Computed Parameter: Vector_Value_g
   * Referenced by: '<S11>/Vector'
   */
  uint16_T Vector_Value_g[2];
} ConstP_OpenLoopTestsAGV_T;

/* Real-time Model Data Structure */
struct tag_RTM_OpenLoopTestsAGV_T {
  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint16_T TID[6];
      uint16_T cLimit[6];
    } TaskCounters;
  } Timing;
};

/* Block signals and states (default storage) */
extern DW_OpenLoopTestsAGV_T OpenLoopTestsAGV_DW;

/* Constant parameters (default storage) */
extern const ConstP_OpenLoopTestsAGV_T OpenLoopTestsAGV_ConstP;

/* Model entry point functions */
extern void OpenLoopTestsAGV_initialize(void);
extern void OpenLoopTestsAGV_step0(void);
extern void OpenLoopTestsAGV_step1(void);
extern void OpenLoopTestsAGV_step2(void);
extern void OpenLoopTestsAGV_step3(void);
extern void OpenLoopTestsAGV_step4(void);
extern void OpenLoopTestsAGV_step5(void);

/* Real-time Model object */
extern RT_MODEL_OpenLoopTestsAGV_T *const OpenLoopTestsAGV_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S16>/FixPt Data Type Propagation' : Unused code path elimination
 * Block '<S19>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S20>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S7>/Scope' : Unused code path elimination
 * Block '<S22>/Data Type Propagation' : Unused code path elimination
 * Block '<S23>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S24>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S25>/Data Type Propagation' : Unused code path elimination
 * Block '<S26>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S27>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S12>/Abs' : Unused code path elimination
 * Block '<S12>/Bitwise Operator2' : Unused code path elimination
 * Block '<S12>/Rate Transition3' : Unused code path elimination
 * Block '<S12>/Rate Transition4' : Unused code path elimination
 * Block '<S10>/Out' : Eliminate redundant signal conversion block
 * Block '<S11>/Out' : Eliminate redundant signal conversion block
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'OpenLoopTestsAGV'
 * '<S1>'   : 'OpenLoopTestsAGV/ADC configuration'
 * '<S2>'   : 'OpenLoopTestsAGV/CAN Address selection'
 * '<S3>'   : 'OpenLoopTestsAGV/CAN BUS configuration'
 * '<S4>'   : 'OpenLoopTestsAGV/Driver inhibit Inhibited if false'
 * '<S5>'   : 'OpenLoopTestsAGV/Led output'
 * '<S6>'   : 'OpenLoopTestsAGV/MPLAB Device Blocks configuration'
 * '<S7>'   : 'OpenLoopTestsAGV/PWM for H bridge'
 * '<S8>'   : 'OpenLoopTestsAGV/QEI configuration'
 * '<S9>'   : 'OpenLoopTestsAGV/Relay activation via jumper'
 * '<S10>'  : 'OpenLoopTestsAGV/Repeating Sequence Stair'
 * '<S11>'  : 'OpenLoopTestsAGV/Repeating Sequence Stair1'
 * '<S12>'  : 'OpenLoopTestsAGV/UART output '
 * '<S13>'  : 'OpenLoopTestsAGV/CAN BUS configuration/Compare To Constant'
 * '<S14>'  : 'OpenLoopTestsAGV/CAN BUS configuration/Subsystem'
 * '<S15>'  : 'OpenLoopTestsAGV/Driver inhibit Inhibited if false/Digital Output3'
 * '<S16>'  : 'OpenLoopTestsAGV/Led output/Counter Free-Running'
 * '<S17>'  : 'OpenLoopTestsAGV/Led output/Digital Output1'
 * '<S18>'  : 'OpenLoopTestsAGV/Led output/Digital Output2'
 * '<S19>'  : 'OpenLoopTestsAGV/Led output/Counter Free-Running/Increment Real World'
 * '<S20>'  : 'OpenLoopTestsAGV/Led output/Counter Free-Running/Wrap To Zero'
 * '<S21>'  : 'OpenLoopTestsAGV/Relay activation via jumper/Digital Output'
 * '<S22>'  : 'OpenLoopTestsAGV/Repeating Sequence Stair/LimitedCounter'
 * '<S23>'  : 'OpenLoopTestsAGV/Repeating Sequence Stair/LimitedCounter/Increment Real World'
 * '<S24>'  : 'OpenLoopTestsAGV/Repeating Sequence Stair/LimitedCounter/Wrap To Zero'
 * '<S25>'  : 'OpenLoopTestsAGV/Repeating Sequence Stair1/LimitedCounter'
 * '<S26>'  : 'OpenLoopTestsAGV/Repeating Sequence Stair1/LimitedCounter/Increment Real World'
 * '<S27>'  : 'OpenLoopTestsAGV/Repeating Sequence Stair1/LimitedCounter/Wrap To Zero'
 */
#endif                                 /* RTW_HEADER_OpenLoopTestsAGV_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
