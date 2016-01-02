// =============================================================================
//          INTRODU��O AOS MICROPROCESADORES - MARCUS VINICIUS ATAIDE
//
// QUEST�O 6 - Fazer um programa para acionar os display's de 7 segmento, 
//             fazendo-os exibir de 0 � 9, na sequ�ncia, com frequ�ncia de
//             varredura de 15Hz, podendo ser interrompido com o apertar de
//             um bot�o tipo push-button.
//
// Autores: Lucas Lui Motta                 RA: 120004538
//          Gustavo Baryotto dos Santos     RA: 120002146
//          Lu�s Garcia                     RA: 080010871
//          Guilherme Fedato                RA: 120001629
//
// Softwares: 
//            MPLAB X v3.0 (Ambiente de Desenvolvimento)
//            XC8 v1.34 (Compilador)
//            Protheus 8 (Simulador Eletr�nico)
//
// =============================================================================

// ======================= BIBLIOTECAS UTILIZADAS ==============================

#include <pic18f4520.h>
#include "Codigo_Basicos.h"
#include "Config_Bits.h"

// ================= DEFINI��ES DOS SEGMENTOS DO DISPLAY =======================

#define zero    0b00111111; // G desligado,  numero 0 no display.
#define um      0b00000110; // B e C ligado, numero 1 no display.
#define dois    0b01011011; // F e C desligado, numero 2 no display.
#define tres    0b01001111; // F e E desligado, numero 3 no display.
#define quatro  0b01100110; // A, D, E desligado, numero 4 no display.
#define cinco   0b01101101; // B e E desligado, numero 5 no display.
#define seis    0b01111101; // B desligaado, numero 6 no display.
#define sete    0b00000111; // A, B, C ligado, numero 7 no display.
#define oito    0b01111111; // Tudo ligado,  numero 8 no display.
#define nove    0b01101111; // E desligado,  numero 9 no display

// ======================= VARIAVEIS GLOBAIS====================================

unsigned char display_alvo = 0; // Vari�vel utilizada na comuta��o do display.
unsigned char trava = 0;        // Vari�vel utilizada na l�gica do bot�o hold.
unsigned char unidade = 9;      // Vari�vel que ser� incrementada e mostrada no 
                                // display de 7 segmentos.

// =============================================================================

unsigned char numeroDisplay(unsigned char numero) 
{
  // Fun��o que recebe o valor num�rico da vari�vel numero e transforma no valor
  // correspondente em bin�rio para o display de 7 segmentos.
  switch(numero)
  {
   case 0:
     return zero;
   case 1:
     return um;
   case 2:
     return dois;
   case 3:
     return tres;
   case 4:
     return quatro;
   case 5:
     return cinco;
   case 6:
     return seis;
   case 7:
     return sete;
   case 8:
     return oito;
   case 9:
     return nove;
  }
  return (0);
}

void ComutacaoDisplay(void) // Procedimento de multiplexa��o dos display.
{                           // Projeto com 4 display de 7 segmentos de 1 unidade
  switch(display_alvo)
  {
   case 0:
     PORTAbits.RA2 = 0;
     PORTD = 0;
     PORTD = numeroDisplay(unidade);
     PORTAbits.RA5 = 1;
     display_alvo = 1;
     break;
   case 1:
     PORTAbits.RA5 = 0;
     PORTD = 0;
     PORTD = numeroDisplay(unidade);
     PORTAbits.RA4 = 1;
     display_alvo = 2;
     break;
   case 2:
     PORTAbits.RA4 = 0;
     PORTD = 0;
     PORTD = numeroDisplay(unidade);
     PORTAbits.RA3 = 1;
     display_alvo = 3;
     break;
   case 3:
     PORTAbits.RA3 = 0;
     PORTD = 0;
     PORTD = numeroDisplay(unidade);
     PORTAbits.RA2 = 1;
     display_alvo = 0;
     break;
  }
}

void interrupt TMR0_TMR1(void)
{
   if (INTCONbits.TMR0IF == 1) // Teste flag TMR0IF para ver se houve 
   {                           // interrup��o por estouro do TIMER0.
       
    // Osc. Interno 8Mhz, Clock interno PIC = 8Mhz/4 = 2Mhz ou seja cada ciclo �
    // 500ns, com Preescaler de 1:256, 256x500ns para um incremento ficando
    // assim 128us por incremento, para que a varredura do display seja de 15Hz 
    // � necess�rio que cada display mude a 60Hz, ou seja, 16,67ms para cada 
    // troca de display, logo, o registrador TMR0L deve conter um valor para
    // para esse tempo, assim fazemos 16,67ms / 128us = 130 se o TMR0L vai at� 
    // 255, fazemos 255 - 130 = 125, esse valor deve ser sempre carregado no
    // registrador para que o estouro do temporizador ocorra no tempo certo.
    
    INTCONbits.TMR0IF = 0;  // Limpando flag de estouro da interrup��o.    
    TMR0L = 0x7D;           // Valor de reinicializa��o TMR0 para alcan�ar
                            // 16,67ms na transi��o de um display para o outro.
    
    ComutacaoDisplay(); // Chama fun��o que faz a transi��o entre os displays.
   }  
}

void Inicializando_SFRs()
{
//========================== REGISTRADOR CONFIG. OSCILADOR =====================
    
    OSCCON = 0b01110010;    
    
//========================== REGISTRADORES PERIF�RICOS =========================
    
    ADCON1 = 0x07;
    CMCON = 0x07;
    T0CON   = 0b01000111;  // TMR0 desligado, configurado como temporizador 8 
                           // bits, refer�ncia clock interno, com preescaler 1:8
    
//========================== REGISTRADORES DE INTERRUP��O ======================
    
    INTCON = 0b11000000;
    INTCON2 = 0x00;
    
//======================= REGISTRADORES DE ENTRADAS/SAIDAS ==================
    
    TRISA = 0b11000011; // RA2,RA3,RA4 e RA5 configurados como sa�dA.
    TRISB = 0xFF;       // RB1 configurado como entrada para o botao de trava.
    TRISC = 0xFF;   // PORTC inteiro configurado como entrada (Alta imped�ncia)
    TRISD = 0x00;   // PORTD inteiro configura como sa�da para alimentar os 
                    // segmentos do display
    
//==============================================================================
}

void main()
{
    Inicializando_SFRs(); 

    TMR0L = 0x7D; // Valor dado ao registrador temporizador para alcan�ar
                  // 16,67ms na transi��o de um display para o outro. 
    T0CONbits.TMR0ON = 1;   // Habilitando Timer0.
    INTCONbits.TMR0IE = 1;  // Ligando interrup��o Timer0.
    while(1)
    {
        for(unsigned int i = 0; i < 60000; i++)
        {
            if((DebBotao(&PORTB, 1, 5, 0)) == 1) 
            {
                if(trava == 1) trava = 0;
                else trava = 1;
            }
            if(((i % 6000) == 0) && (trava == 0))
            {
                unidade++;
                if(unidade == 10) unidade = 0;                    
            }
        }        
    }
}