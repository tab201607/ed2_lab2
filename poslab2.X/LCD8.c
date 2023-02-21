/* 
 * File: LCD.c  
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Revision history: 
 */

//LCD Functions Developed by electroSome

#include "LCD8.h"



//Controla que puertos se activan en otras funciones
void Lcd_Port(char a) {
    PORTD = a;
    /*if (a & 1)
        D0 = 1;
    else
        D0 = 0;

    if (a & 2)
        D1 = 1;
    else
        D1 = 0;

    if (a & 4)
        D2 = 1;
    else
        D2 = 0;
        
    if (a & 8)
        D3 = 1;
    else
        D3 = 0;
        
    if (a & 16)
        D4 = 1;
    else
        D4 = 0;
       
    if (a & 32)
        D5 = 1;
    else
        D5 = 0;
        
    if (a & 64)
        D6 = 1;
    else
        D6 = 0;
    
    if (a & 128)
        D7 = 1;
    else
        D7 = 0;*/
}

//Manda comandos a los puertos

void Lcd_Cmd(char a) {
    RS = 0; // => RS = 0 // Dato en el puerto lo va interpretar como comando
    Lcd_Port(a);
    EN = 1; // => E = 1
    __delay_ms(4);
    EN = 0; // => E = 0
}

//Elimina todo de la pantalla
void Lcd_Clear(void) {
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b) {
    char temp, z, y;
    if (a == 1) {
        temp = 0x80 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(temp);
        //Lcd_Cmd(y);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(temp);
        //Lcd_Cmd(y);
    }
}

//Incializa el lcd en modo 8 bits

void Lcd_Init(void) {
    __delay_ms(101);
    Lcd_Cmd(0x30);
    __delay_ms(5);
    Lcd_Cmd(0x30);
    __delay_ms(1);
    Lcd_Cmd(0x30);
    __delay_ms(1);
    /////////////////////////////////////////////////////
    Lcd_Cmd(0x38);  //5 especifica font y numero de lineas
    Lcd_Cmd(0x08); //6 display on/off
    Lcd_Cmd(0x01); //7 clear display
    Lcd_Cmd(0x06); //8 Entry mode set
    Lcd_Cmd(0x0C);
}




void Lcd_Write_Char(char a) {
    RS = 1; // => Valores son interpretados como data
    Lcd_Port(a); //Data transfer
    EN = 1;
    __delay_us(40);
    EN = 0;
    RS = 0;
    __delay_us(40);
}

void Lcd_Write_String(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right(void) {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left(void) {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x08);
}


