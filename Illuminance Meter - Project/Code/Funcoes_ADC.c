#include "Macros_Basicos.h"
#include "Funcoes_ADC.h"
#include "Enderecando_SFRs.h"

void InicializandoADC(void)
{
  ADCON0 = 0b10000000; //Tempo de convers�o A/D = FOSC/32, RA0 configurado como anal�gico (AN0)
  ADCON1 = 0b10001110; //Justificado a direita ou seja low byte em ADRESL. Somente AN0 como anal�gica o resto como digital I/O e referencia no Vdd e Vss.
  BitSetar(ADCON0, 0);   /*  ADON: bit liga/desliga ADC
                           1 = A/D - Habilita a possibilidade de ligar o ADC.
                           0 = A/D - Desliga o ADC, n�o a mais comsumo de corrente.*/
}

unsigned int LeituraADC(void)
{
  unsigned int valor_adc_temporario = 0;
  BitSetar(ADCON0, 2); /* GO/DONE: A/D Status bit
                         Quando ADON = 1:
                         1 = A/D - Convers�o em progresso (Bit automaticamente limpo ap�s concluir convers�o).
                         0 = A/D - Convers�o n�o mais em progresso.*/

  while (BitTestar(ADCON0, 2)); // Esperando convers�o A/D acabar ou seja status bit igual a 0.
  valor_adc_temporario =  ADRESH ;
  valor_adc_temporario <<=  8 ;
  valor_adc_temporario += ADRESL;
  return (valor_adc_temporario); //retorna valor inteiro.
}