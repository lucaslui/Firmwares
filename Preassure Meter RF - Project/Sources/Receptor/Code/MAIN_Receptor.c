/*
 * Projeto do estudante do 3� ano de engenharia
 * Autor C�digo: Lucas Lui Motta
 * Data: 14/05/2015
 * Assunto Projeto: C�digo do receptor.
 */

#include "CONFIG_BITS.h"
#include <xc.h>         // Biblioteca das defini��es como SFR's bit a bit (struct - campo de bits) Ex: PORTXbits.RAX
#include <pic16f628a.h>  // Bibliotecas para o mapeamento e nomea��es dos SFR's.
#include "DELAY.h"
#include "LCD.h"
#include "SERIAL.h"

void Inicializando_Registradores(void)
{
    INTCON = 0x00;
    OPTION_REG = 0b10000000; // Ref�ncia de clock igual a interno, pull-up resistores do PORTB configurados como disable.
    PCON = 0x08;  // Configurado como 4MHZ de oscilador interno.
    CCP1CON = 0x00;
    CMCON = 0x07;
    TRISA = 0b11110000; // RA0 at� RA3 configurados como sa�da para o LCD.
    TRISB = 0b11110110; // RB0 e RB3 configurados como sa�da para o EN e RS do LCD.
}

void main()
{
    Inicializando_Registradores();
    InicializaSerial();
    Reset_Obrigatorio_LCD();
    Inicializando_LCD();
    Gerador_Frases("Medidor Pressao");
    Cmd_LCD(SEGUNDA_LINHA);
    Gerador_Frases("Valor:");
    Cmd_LCD(0xCC);
    Gerador_Frases("PSI");
    unsigned char temp = 0;
    while(1)
    {
        temp = RecebeSerial();
        Cmd_LCD(0xC7);
        Converter_para_String(temp,4);        
    }
    
}