/* ==================================================================================================================
	Arquivo: Funcoes_Basicas.h
	Descri��o: Arquivo HEADER para administra��o das fun��es que ser�o passadas.
 ==================================================================================================================*/
 
#ifndef FUNCOES_BASICAS_Lui /* PROT�TIPOS PARA A PASSAGEM DE FUN��ES */
#define	FUNCOES_BASICAS_Lui /* PROT�TIPOS PARA A PASSAGEM DE FUN��ES */

void delay_ms(int ms);
char DebBotao(volatile near unsigned char *PORT, char nBit, int deboucingTime, char changeState);

#endif /* PROT�TIPOS PARA A PASSAGEM DE FUN��ES */

// ==================================================================================================================

