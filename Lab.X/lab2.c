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

#define _XTAL_FREQ 8000000

#include <xc.h>
 #include <stdio.h>
 #include <stdlib.h>
#include <stdint.h>
#include "LCD8.h"
#include "adclib.h"
#include <string.h>

void main(void) {
    float output0, output1;
    char ch1, ch0;
    
    //Utiliza PORTA1 y 2 para 
    PORTA = 0;  
    ch0 = 0;
    ch1 = 1;
    adc_setup(0);  
    Lcd_Cmd(0x0E);
    
    adc_channel(ch0);
    adc_channel(ch1);
    
    TRISD = 0x00;
    PORTD = 0x00;
    TRISE = 0x00;
    PORTE = 0x00;
    
    //Iniciamos y configuramos el lcd y donde se indica
    Lcd_Init();
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Volt1  Volt2");
    Lcd_Set_Cursor(2,1);
     Lcd_Write_String("0.00V  0.00V");
       

    
    do {
        __delay_ms(1);
        output0 = adc_volt(ch0);
        //out = (float)output * (5/256);
        output1 = adc_volt(ch1);
        
            //En estos chars vamos a almacenar los strings que mandamos al lcd
        char display0[50]; 
        char display1[50]; 
        
        sprintf(display0, "%.2f", output0);
        sprintf(display1, "%.2f", output1);
        Lcd_Set_Cursor(2,1);
        __delay_us(10);
        Lcd_Write_String(display0);
        Lcd_Set_Cursor(2,8);
        __delay_us(10);
        Lcd_Write_String(display1);
        __delay_ms(10);
    }
    while(1);
}

void __interrupt() Isr(void) {};