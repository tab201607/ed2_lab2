/*
 * File:   uart.c
 * Author: JTP
 *
 * Created on February 19, 2023, 6:34 PM
 */


#include <xc.h>
#include "uart.h"


void UART_RX_config (uint16_t baudrate) {
    TXSTAbits.SYNC = 0; //Lo pone en modo asincrono
    
    //control baudrate
    TXSTAbits.BRGH = 1; //baud rate alto
    BAUDCTLbits.BRG16 = 1; //definicion de baud rate es de 16 digitos
    SPBRG = (char)(baudrate & 0xFF);
    SPBRGH = (char)(baudrate >> 8);
    
    RCSTAbits.SPEN = 1; //configura tx y rx como entrada y salida
    RCSTAbits.RX9 = 0; //RX solo es de 8 digitos
    RCSTAbits.CREN = 1; //Activa la funcion de recibir
};

void UART_TX_config (uint16_t baudrate) {
    TXSTAbits.SYNC = 0; //Lo pone en modo asincrono
    
    //control baudrate
    TXSTAbits.BRGH = 1; //baud rate alto
    BAUDCTLbits.BRG16 = 1; //definicion de baud rate es de 16 digitos
    SPBRG = (char)baudrate & 0x00FF;
    SPBRGH = (char)baudrate >> 8;
    
    RCSTAbits.SPEN = 1; //configura tx y rx como entrada y salida
    RCSTAbits.RX9 = 0; //RX solo es de 8 digitos
    RCSTAbits.CREN = 1; //Activa la funcion de recibir
    
    TXSTAbits.TXEN = 1;
};

void UART_write_char (char character){ 
  while (TXSTAbits.TRMT == 0);
  TXREG = character;
};

char UART_read_char() {
    while (PIR1bits.RCIF == 0);
    PIR1bits.RCIF = 0;
    return RCREG;
};


