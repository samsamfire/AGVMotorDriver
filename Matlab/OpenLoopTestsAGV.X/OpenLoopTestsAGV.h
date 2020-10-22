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
 * Model version                  : 1.30
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Thu Oct 22 12:27:14 2020
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
  int16_T U1CH1_e3;                    /* '<Root>/QEI' */
  uint16_T U1CH1;                      /* '<Root>/ADC' */
  uint16_T Switch;                     /* '<Root>/Switch' */
  uint16_T Switch1;                    /* '<Root>/Switch1' */
  uint16_T U1CH1_e;                    /* '<Root>/Rate Transition3' */
  uint16_T U1CH1_m;                    /* '<Root>/QEI' */
  uint16_T U1CH3;                      /* '<Root>/Bitwise Operator2' */
  uint16_T U2Rx;                       /* '<Root>/UART Rx' */
  uint16_T CFunctionCall3_o1;          /* '<Root>/C Function Call3' */
  uint16_T CFunctionCall3_o2;          /* '<Root>/C Function Call3' */
  uint16_T DataTypeConversion;         /* '<Root>/Data Type Conversion' */
  uint16_T Add;                        /* '<Root>/Add' */
  volatile uint16_T RateTransition1_Buffer0;/* '<Root>/Rate Transition1' */
  volatile uint16_T RateTransition2_Buffer0;/* '<Root>/Rate Transition2' */
  uint8_T CFunctionCall3_o3[8];        /* '<Root>/C Function Call3' */
  uint8_T In1[8];                      /* '<S9>/In1' */
  uint8_T U1CH4;                       /* '<Root>/Rate Transition4' */
  uint8_T U2Rx_m;                      /* '<Root>/UART Rx' */
  uint8_T CFunctionCall3_o4;           /* '<Root>/C Function Call3' */
  uint8_T Output_DSTATE;               /* '<S12>/Output' */
  uint8_T Output_DSTATE_d;             /* '<S15>/Output' */
  uint8_T Output_DSTATE_o;             /* '<S2>/Output' */
  volatile uint8_T RateTransition4_Buffer0;/* '<Root>/Rate Transition4' */
} DW_OpenLoopTestsAGV_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Computed Parameter: Vector_Value
   * Referenced by: '<S7>/Vector'
   */
  uint16_T Vector_Value[2];

  /* Computed Parameter: Vector_Value_g
   * Referenced by: '<S8>/Vector'
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

/* External data declarations for dependent source files */
extern const uint16_T OpenLoopTestsAGV_U16GND;/* uint16_T ground */

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
 * Block '<Root>/Bias' : Unused code path elimination
 * Block '<S2>/FixPt Data Type Propagation' : Unused code path elimination
 * Block '<S10>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S11>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S12>/Data Type Propagation' : Unused code path elimination
 * Block '<S13>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S14>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S15>/Data Type Propagation' : Unused code path elimination
 * Block '<S16>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S17>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<Root>/Abs' : Eliminated since data is unsigned
 * Block '<S7>/Out' : Eliminate redundant signal conversion block
 * Block '<S8>/Out' : Eliminate redundant signal conversion block
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
 * '<S1>'   : 'OpenLoopTestsAGV/Compare To Constant'
 * '<S2>'   : 'OpenLoopTestsAGV/Counter Free-Running'
 * '<S3>'   : 'OpenLoopTestsAGV/Digital Output'
 * '<S4>'   : 'OpenLoopTestsAGV/Digital Output1'
 * '<S5>'   : 'OpenLoopTestsAGV/Digital Output2'
 * '<S6>'   : 'OpenLoopTestsAGV/Digital Output3'
 * '<S7>'   : 'OpenLoopTestsAGV/Repeating Sequence Stair'
 * '<S8>'   : 'OpenLoopTestsAGV/Repeating Sequence Stair1'
 * '<S9>'   : 'OpenLoopTestsAGV/Subsystem'
 * '<S10>'  : 'OpenLoopTestsAGV/Counter Free-Running/Increment Real World'
 * '<S11>'  : 'OpenLoopTestsAGV/Counter Free-Running/Wrap To Zero'
 * '<S12>'  : 'OpenLoopTestsAGV/Repeating Sequence Stair/LimitedCounter'
 * '<S13>'  : 'OpenLoopTestsAGV/Repeating Sequence Stair/LimitedCounter/Increment Real World'
 * '<S14>'  : 'OpenLoopTestsAGV/Repeating Sequence Stair/LimitedCounter/Wrap To Zero'
 * '<S15>'  : 'OpenLoopTestsAGV/Repeating Sequence Stair1/LimitedCounter'
 * '<S16>'  : 'OpenLoopTestsAGV/Repeating Sequence Stair1/LimitedCounter/Increment Real World'
 * '<S17>'  : 'OpenLoopTestsAGV/Repeating Sequence Stair1/LimitedCounter/Wrap To Zero'
 */
#endif                                 /* RTW_HEADER_OpenLoopTestsAGV_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
