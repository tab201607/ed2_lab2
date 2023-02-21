/*
 * File:   prelab.c
 * Author: JacobT
 *
 * Created on February 16, 2023, 11:38 PM
 */

#pragma config FOSC = EXTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
 #include <stdio.h>
 #include <stdlib.h>
#include <stdint.h>
#include "LCD4.h"
#include "adclib.h"

void main(void) {
    int output;
    float out;
    char ch;
    PORTA = 0;
    
    TRISC = 0;
    PORTC = 0;
    
    ch = 0;
    adc_setup(0);  
    adc_channel(ch);
    TRISD = 0x00;
    Lcd_Init();
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Voltage:");
    Lcd_Set_Cursor(2,5);
     Lcd_Write_String("V");
        
    do {
        
        __delay_ms(1);
        output = (int)adc_RO(ch);
        PORTC = adc_RO(ch);
        //out = (float)output * (5/256);
        out = adc_volt(ch);
        char display[50]; 
        sprintf(display, "%.2f", out);
        Lcd_Set_Cursor(2,1);
        __delay_us(10);
        Lcd_Write_String(display);
    }
    while(1);
}

void __interrupt() Isr(void) {};