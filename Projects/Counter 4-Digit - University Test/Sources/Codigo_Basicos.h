/* =============================================================================
	Arquivo: Codigo_Basicos.h
	Descri��o: Arquivo HEADER para administra��o das fun��es que ser�o passadas.
 ===============================================================================
 
#ifndef Codigo_Basicos /* PROT�TIPOS PARA A PASSAGEM DE FUN��ES */
#define	Codigo_Basicos /* PROT�TIPOS PARA A PASSAGEM DE FUN��ES */

void delay_ms(int ms);
char DebBotao(volatile unsigned char *PORT, char nBit, int deboucingTime, char changeState);

#endif /* PROT�TIPOS PARA A PASSAGEM DE FUN��ES */

// =============================================================================
