/* ==================================================================================================================
	Arquivo: Funcoes_LCD.h
	Descri��o: Arquivo HEADER para administra��o das fun��es que ser�o passadas.
 ==================================================================================================================*/

#ifndef FUNCOES_LCD_Lui /* PROT�TIPOS PARA A PASSAGEM DE FUN��ES */
#define	FUNCOES_LCD_Lui /* PROT�TIPOS PARA A PASSAGEM DE FUN��ES */

const char LIMPAR_DISPLAY = 0x01;
const char SEGUNDA_LINHA = 0xC0;

void Reset_Obrigatorio_LCD(void);
void Inicializando_LCD(void);
void Cmd_LCD(char cmd);
void Escrever_Lcd(char caracter);
void Gerador_Frases(const unsigned char vetorFrase[]);
char ConverterNumeroParaCaracter(char numero);
void Converter_para_String(unsigned int valor_int, unsigned char digitos);

#endif /* PROT�TIPOS PARA A PASSAGEM DE FUN��ES */
