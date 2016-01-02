/* ==================================================================================================================
	Arquivo: DELAY.c
	Descri��o: Biblioteca b�sica com fun��es b�sicas como delay, e tratamento de bot�es.
	Port�vel: Fun��o delay ainda n�o port�vel, fun��o do tratamento de bot�es est� port�vel.
	Microcontrolador Utilizado: PIC18F2550.
 ==================================================================================================================*/

#include "DELAY.h"

#define BitSetar(arg,nBit)    ((arg) |=  (1<<nBit)) // Macros para mascarar os bytes, s�o feitas opera��es bit a bit
#define BitLimpar(arg,nBit)   ((arg) &= ~(1<<nBit)) // para setar, limpar, inverter, e testar bits especificos de um byte.
#define BitInverter(arg,nBit) ((arg) ^=  (1<<nBit))
#define BitTestar(arg,nBit)   ((arg) &   (1<<nBit))

// ==================================================================================================================

void delay_ms(int ms)
{
  /* 14 instru��es para uma incrementa��o
   * 1/4MHz = 250ns, 4 ciclos para efetuar uma instru��o no PIC
   * Assim 250ns x 4 = 1us por instru��o,
   * ocorrem 14 por incrementa��o sendo assim 14us por incremento
   * para gerar 0,5s de delay precisaram 35714 incrementos.
   * logo ms 1 ms equivale a 71,4285 incrementos. Sendo assim:  */
  unsigned int numeroIncrementos , i = 0;
  numeroIncrementos = (ms * 71);
  for (i = 0; i < numeroIncrementos; i++);
}
