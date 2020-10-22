#include "OpenLoopTestsAGV.h"
#include "OpenLoopTestsAGV_private.h"

/* Declare UART1 Tx Circular Buffer Structure */
MCHP_UART1_TxStr MCHP_UART1_Tx = { .head = 0, .tail = 0 };/* UART1 Tx FIFO */

void __attribute__((__interrupt__,__shadow__,__auto_psv__)) _U1TXInterrupt(void)
{
  register uint_T LocalHead;
  LocalHead = MCHP_UART1_Tx.head;
     /* Head is a volatile variable. Use local variable to speed-up execution */
  while ((0U == U1STAbits.UTXBF) && (MCHP_UART1_Tx.tail != LocalHead) )/* while UxTXREG buffer is not full */
  {
    U1TXREG = MCHP_UART1_Tx.buffer[LocalHead];
    LocalHead = (LocalHead + 1) & (Tx_BUFF_SIZE_UART1-1);
  }

  MCHP_UART1_Tx.head = LocalHead;      /* Push back volatile variable */
  _U1TXIF = 0;                         /*  */
}
