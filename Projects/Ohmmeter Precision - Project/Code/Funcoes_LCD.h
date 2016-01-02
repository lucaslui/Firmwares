/* ==================================================================================================================
	Arquivo: Funcoes_LCD.h
	Descri��o: Arquivo HEADER para administra��o das fun��es que ser�o passadas.
 ==================================================================================================================*/

#ifndef Funcoes_LCD /* PROT�TIPOS PARA A PASSAGEM DE FUN��ES */
#define	Funcoes_LCD /* PROT�TIPOS PARA A PASSAGEM DE FUN��ES */

#define LimpaDisplay 0x01
#define SegundaLinhaPrimeiraColuna 0xC0

void Inicializando_LCD(void);
void Cmd_LCD(char cmd);
void Escrever_LCD(char caracter);
void Gerador_Frases(const unsigned char vetorFrase[]);
char Converter_Numero_Para_Caracter(char numero);
void Converter_Para_String(unsigned int valor_int, unsigned char digitos);

#endif /* PROT�TIPOS PARA A PASSAGEM DE FUN��ES */

//==================================================================================================================