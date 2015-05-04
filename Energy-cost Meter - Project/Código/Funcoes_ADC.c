/* ==================================================================================================================

	Arquivo: Funcoes_ADC.c
	Descri��o: Biblioteca para ADC de 10 bits.
	Port�vel: N�o port�vel, necessita ajustes dependendo do microcontrolador utilizado.
	Microcontrolador Utilizado: PIC18F2550.

 ==================================================================================================================*/

#include "Definindo_SFRs.h"
#include "Funcoes_ADC.h"

// ==================================================================================================================

#define BitSetar(arg,nBit)    ((arg) |=  (1<<nBit)) // Macros para mascarar os bytes, s�o feitas opera��es bit a bit
#define BitLimpar(arg,nBit)   ((arg) &= ~(1<<nBit)) // para setar, limpar, inverter, e testar bits especificos de um byte.
#define BitInverter(arg,nBit) ((arg) ^=  (1<<nBit))
#define BitTestar(arg,nBit)   ((arg) &   (1<<nBit))

// ==================================================================================================================

#define GODONE 1 // Defines para o bom entendimento do c�digo.
#define ADON 0

// ==================================================================================================================


void Inicializando_ADC(void)
{
  ADCON0 = 0b00000000; // Selecionado CANAL 0, ou seja habilita convers�o A/D neste primeiro momento no pino AN0.
  ADCON1 = 0b00001101; // Tens�es de refer�ncia = VDD e GND, AN0 e AN1 configurados como pino anal�gico.
  ADCON2 = 0b10101110; // Justificado a direita, tempo de aquisi��o de dados 12 TAD, velocidade convers�o FOSC/64.
  BitSetar(ADCON0, ADON);   /*  ADON: bit liga/desliga ADC
                                1 = A/D - Habilita a possibilidade de ligar o ADC.
                                0 = A/D - Desliga o ADC, n�o a mais comsumo de corrente.*/
}

unsigned int Leitura_ADC(void)
{
  unsigned int valor_adc_temporario = 0;
  BitSetar(ADCON0, GODONE); // GO/DONE: Emite o "GO" da opera��o de convers�o A/D.

  while (BitTestar(ADCON0, GODONE)); // Esperando convers�o A/D acabar ou seja status bit igual a 0.
  valor_adc_temporario =  ADRESH ;   // Convers�o A/D de 10 bits, sendo assim eles s�o armazenados em dois registradores, 
  valor_adc_temporario <<=  8 ;      // ADRESH(high) e ADRESHL (low). Em seguida, � atribuido o resultado da parte alta na vari�vel local 
  valor_adc_temporario += ADRESL;    // criada (int - 16 bits), em seguida deslocada 8 vezes a esquerda, colocando-a no devido 
                                     // lugar, em seguida s� � atribuida a parte baixa na mesma v�riavel.
  return (valor_adc_temporario);     // Retorna valor inteiro (resultado da convers�o).
}
