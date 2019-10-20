// ===============================================================================================================================================================

#include <PIC16F688.h>
#include "Funcoes_SERIAL.h"

// ===============================================================================================================================================================

void EnviaSerial(unsigned char dados)
{
    //while(PIR1bits.TXIF == 0);	// aguarda o registro ficar dispon�vel
    TXREG = dados; 		// coloca o valor para ser enviado
}

// ===============================================================================================================================================================

void InicializaSerial(void)
{
    TRISCbits.TRISC4 = 0;   // pino do serial configuado como saida TX.
    TXSTA = 0b00101100;	    // Habilita transmiss�o, 8 bits de transmissao, modo ass�ncrono, alta velocidade.
    RCSTA = 0b10000000;	    // Porta serial ligada (pinos RX e TX), desabilitada recepta��o dados.
    BAUDCTL = 0b00001000;   // Saida serial TX configurado como n�o barrado, modulo gerador baudrate com 16 bits. sem auto baudrate e sem estouro com auto baudrate.
    SPBRGH = 0x00;          // configura para 56k.
    SPBRG = 207;	    // 207 em decimal valor para velocidade baudrate em 9.6k.    
}

// ===============================================================================================================================================================
