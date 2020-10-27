#include "OpenLoopTestsAGV.h"
#include "OpenLoopTestsAGV_private.h"

/* ADC - Interrupt: <S1>/ADC */
volatile uint16_T ADC1BuffChannelA[1];
void __attribute__((__interrupt__,__auto_psv__)) _AD1Interrupt(void)
{
  ADC1BuffChannelA[0] = ADC1BUF0;      /* Copy value from ADC buffer  */

  {
    struct {
      unsigned int Flags1 : 1;
      unsigned int Flags2 : 1;
      unsigned int Flags3 : 1;
      unsigned int Flags4 : 1;
      unsigned int Flags5 : 1;
    } static volatile Overrun __attribute__ ((near)) ;

    struct {
      unsigned int Flags1 : 1;
      unsigned int Flags2 : 1;
      unsigned int Flags3 : 1;
      unsigned int Flags4 : 1;
      unsigned int Flags5 : 1;
    } static volatile event __attribute__ ((near)) ;

    struct {
      uint_T Task1;                   /* 0.001s periodic task. Max value is 5 */
      uint_T Task2;                   /* 0.1s periodic task. Max value is 500 */
      uint_T Task3;                  /* 1.0s periodic task. Max value is 5000 */
      uint_T Task4;                 /* 2.0s periodic task. Max value is 10000 */
      uint_T Task5;                 /* 4.0s periodic task. Max value is 20000 */
    } static volatile taskCounter __attribute__ ((near)) = {
      .Task1 = 1          /* Offset is 0 (-5 + 1 modulo [5 for pre decrement) */
      , .Task2 = 1    /* Offset is 0 (-500 + 1 modulo [500 for pre decrement) */
      , .Task3 = 1  /* Offset is 0 (-5000 + 1 modulo [5000 for pre decrement) */
      , .Task4 = 1/* Offset is 0 (-10000 + 1 modulo [10000 for pre decrement) */
      , .Task5 = 1/* Offset is 0 (-20000 + 1 modulo [20000 for pre decrement) */
    };

    _AD1IF = 0;                        /* Re-enable interrupt */

    /* Check subrate overrun, set rates that need to run this time step*/
    taskCounter.Task1--;               /* Decrement task internal counter */
    if (taskCounter.Task1 == 0) {      /* task dropped on overload */
      taskCounter.Task1 = (uint_T) 5; /* 0.001s periodic task. Max value is 5 */
      event.Flags1 = 1U;               /* Flag tag to be executed */
    }

    taskCounter.Task2--;               /* Decrement task internal counter */
    if (taskCounter.Task2 == 0) {      /* task dropped on overload */
      taskCounter.Task2 = (uint_T) 500;
                                      /* 0.1s periodic task. Max value is 500 */
      event.Flags2 = 1U;               /* Flag tag to be executed */
    }

    taskCounter.Task3--;               /* Decrement task internal counter */
    if (taskCounter.Task3 == 0) {      /* task dropped on overload */
      taskCounter.Task3 = (uint_T) 5000;
                                     /* 1.0s periodic task. Max value is 5000 */
      event.Flags3 = 1U;               /* Flag tag to be executed */
    }

    taskCounter.Task4--;               /* Decrement task internal counter */
    if (taskCounter.Task4 == 0) {      /* task dropped on overload */
      taskCounter.Task4 = (uint_T) 10000;
                                    /* 2.0s periodic task. Max value is 10000 */
      event.Flags4 = 1U;               /* Flag tag to be executed */
    }

    taskCounter.Task5--;               /* Decrement task internal counter */
    if (taskCounter.Task5 == 0) {      /* task dropped on overload */
      taskCounter.Task5 = (uint_T) 20000;
                                    /* 4.0s periodic task. Max value is 20000 */
      event.Flags5 = 1U;               /* Flag tag to be executed */
    }

    /* ---------- Handle model base rate Task 0 ---------- */
    OpenLoopTestsAGV_step0();

    /* Get model outputs here */
    if (_AD1IF ) {
      return;                          /* Will re-enter into the interrupt */
    }

    /* Re-Enable Interrupt. IPL value is 2 at this point */
    _IPL0 = 1;
           /* Re-Enable Scheduler re-entrant interrupt. Lower IPL from 2 to 1 */
    _IPL1 = 0;

    /* Step the model for any subrate */
    /* ---------- Handle Task 1 ---------- */
    if (Overrun.Flags1) {
      return;                    /* Priority to higher rate steps interrupted */
    }

    if (event.Flags1) {
      Overrun.Flags1 = 1;
      do {                             /* Execute task tid 1 */
        event.Flags1 = 0U;
        OpenLoopTestsAGV_step1();

        /* Get model outputs here */
      } while (event.Flags1);

      Overrun.Flags1 = 0U;
    }

    /* ---------- Handle Task 2 ---------- */
    if (Overrun.Flags2) {
      return;                    /* Priority to higher rate steps interrupted */
    }

    if (event.Flags2) {
      Overrun.Flags2 = 1;
      do {                             /* Execute task tid 2 */
        event.Flags2 = 0U;
        OpenLoopTestsAGV_step2();

        /* Get model outputs here */
      } while (event.Flags2);

      Overrun.Flags2 = 0U;
    }

    /* ---------- Handle Task 3 ---------- */
    if (Overrun.Flags3) {
      return;                    /* Priority to higher rate steps interrupted */
    }

    if (event.Flags3) {
      Overrun.Flags3 = 1;
      do {                             /* Execute task tid 3 */
        event.Flags3 = 0U;
        OpenLoopTestsAGV_step3();

        /* Get model outputs here */
      } while (event.Flags3);

      Overrun.Flags3 = 0U;
    }

    /* ---------- Handle Task 4 ---------- */
    if (Overrun.Flags4) {
      return;                    /* Priority to higher rate steps interrupted */
    }

    if (event.Flags4) {
      Overrun.Flags4 = 1;
      do {                             /* Execute task tid 4 */
        event.Flags4 = 0U;
        OpenLoopTestsAGV_step4();

        /* Get model outputs here */
      } while (event.Flags4);

      Overrun.Flags4 = 0U;
    }

    /* ---------- Handle Task 5 ---------- */
    if (Overrun.Flags5) {
      return;                    /* Priority to higher rate steps interrupted */
    }

    if (event.Flags5) {
      Overrun.Flags5 = 1;
      do {                             /* Execute task tid 5 */
        event.Flags5 = 0U;
        OpenLoopTestsAGV_step5();

        /* Get model outputs here */
      } while (event.Flags5);

      Overrun.Flags5 = 0U;
    }

    /* Disable Interrupt. IPL value is 1 at this point */
    _IPL1 = 1;          /* Disable Scheduler Interrupts. Rise IPL from 1 to 2 */
    _IPL0 = 0;
  }
}
