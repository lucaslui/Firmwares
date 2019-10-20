/*==================================================================================================================
 *
 *         PROJETO DE BOLSA INICIA��O CI�NTIFICA (BIC-SAL) DA UNISAL DE AMERICANA
 *                  DEPARTAMENTO DE ENGENHARIA EL�TRICA 2015
 *                             MCU utilizado: PIC18F4520
 *
 *  Autor: Lucas Lui Motta.
 *         Heitor dos Santos Sousa
 *
 *  Projeto: Ohm�metro de Precis�o de 0-10 ohms.
 *
 *  Softwares usados: XC8 - Compilador.
 *					  MPLABX - IDE.
 *
 * ==================================================================================================================
 *  Sobre Licen�a: GNU GPL 2
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 * ==================================================================================================================
 *
 *  Arquivo: Codigo_Main.c
 *
 *	Arquivos do projeto: Codigo_Main.c
 *						 Config_Fusiveis_Externos.h									
 *						 Funcoes_Basicas.h
 *						 Funcoes_Basicas.c
 *						 Funcoes_LCD.h			
 *						 Funcoes_LCD.c
 */
// ==================================================================================================================

#include "pic18f4520.h"
#include "Config_Fusiveis_Externos.h"
#include "Funcoes_Basicas.h"
#include "Funcoes_I2C.h"
#include "Funcoes_LCD.h"

// ==================================================================================================================

// ==================================================================================================================

void Interface_Loading(void) 
{
   Cmd_LCD(LimpaDisplay);                      
   Gerador_Frases("Ligando...");
   Cmd_LCD(SegundaLinhaPrimeiraColuna);
   for(char i = 0; i <= 15; i++) // Criando digitos no formato preenchido
   {                             // para dar a impress�o de uma barra de loading.
        Escrever_LCD(0xFF);
        delay_ms(90);
   }
   Cmd_LCD(LimpaDisplay);     
}

void Interface_Main(void) 
{// Fun��o que escreve a interface de configura��o do kwh da concession�ria.

    Cmd_LCD(LimpaDisplay);               
    Gerador_Frases(" Ohmimetro v1.0 ");
    Cmd_LCD(SegundaLinhaPrimeiraColuna);
    Gerador_Frases("Valor: ");
    Cmd_LCD(0xCA);
    Escrever_LCD(',');
}

void Resistance_Calculation(unsigned value_ad_received)
{
    
}

void Separando_e_Imprimindo_Digitos(unsigned int numero)
{
    unsigned char centena = 0, dezena = 0, unidade = 0;
    centena = (int)(numero / 100);
    dezena = (int)((numero - (100*centena)) / 10);
    unidade = (numero - (100*centena) - (10*dezena));
    
    Cmd_LCD(0xC8);
    Escrever_LCD(Converter_Numero_Para_Caracter(centena));
    Escrever_LCD(Converter_Numero_Para_Caracter(dezena));
    Cmd_LCD(0xCB);
    Escrever_LCD(Converter_Numero_Para_Caracter(unidade));
}

void Inicializando_SFRs(void)
{
    //---------------------- CONFIGURA��ES INICIAS -----------------------------------------------------------------  
    
    OSCCON  = 0b01110000;  // Oscilador interno configirado como 8Mhz.
    
    //------------------ DESABILITANDO ALGUNS PERIF�RICOS ----------------------------------------------------------  
    
    CMCON   = 0x07;        // Comparadores desligados, Pinos configurador como digital I/O.
    ADCON1  = 0x07;        // Desabilita entradas anal�gicas e habilita entradas digitais.
    
    //------------------------ CONFIGURANDO I/O --------------------------------------------------------------------  
    
    TRISA   = 0b11111111;   // PORTA configurada tudo como entrada (Imped�ncia alta).
    TRISB   = 0b11111111;   // PORTB configurada tudo como entrada (Imped�ncia alta).
    TRISC   = 0b11111100;   // RC0, RC1 como sa�da para os pinos do display RS e EN.
    TRISD   = 0b11110000;   // RD0,RD1,RD2,RD3 configurados como sa�da para uso no barramento de 4 bits do display.        
 
    //------------------------- INTERRUP��ES -----------------------------------------------------------------------  
    
    INTCON = 0x00;
    //INTCON  = 0b11000000;   // Global interrup��o habilitado, perif�ricos interrup��es habilitado, TMR0 interrup��o desligado.
    //INTCON2 = 0b10000000;   // Desabilitando resistores de pull-up do PORTB.
    //T0CON   = 0b00000010;   // TMR0 desligado, configurado como temporizador 16 bits, refer�ncia clock interno, com preescaler 1:8.

    //BitSetar(T0CON, 7);   // Ligando temporizador TIMER 0.
      
}

void main(void)
{
    Inicializando_SFRs();
    Inicializando_LCD();	
    Interface_Loading();
    Interface_Main();
    Inicializando_I2C();
	    
    //BitSetar(INTCON, 5);  // Ligando interrup��o Timer0.
        
    unsigned char variavel = 0, variavel_travada = 0;
    unsigned char trava_de_valor = 0;
    unsigned int valor_ad_recebido = 0;
    
    write_msp(0b00011001); // Continous Shot, 15 SPS (16 bits), PGA gain 2 V/V.
    
    while(1)
    {/*
        variavel++;
        if (variavel == 255) variavel = 0;
        delay_ms(300);
        if ((DebBotao(&PORTB, 0, 10, 0)) == 1) // Para travar o ultimo valor no display
        {
            if (trava_de_valor == 0) 
            {
                trava_de_valor = 1;
                variavel_travada = variavel;
            } 
            else trava_de_valor = 0;
        }
        if (trava_de_valor == 0) Separando_e_Imprimindo_Digitos(variavel);
        else Separando_e_Imprimindo_Digitos(variavel_travada);       
    */
        for(int i = 0; i < 2; i++) delay_ms(500);
        valor_ad_recebido = read_msp();
        if (valor_ad_recebido != 0) Separando_e_Imprimindo_Digitos(valor_ad_recebido);
    
    }
}

