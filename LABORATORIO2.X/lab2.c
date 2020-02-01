/*
 * File:   CARRERAS.c
 * Author: CHARLIE
 *
 * Created on 22 de enero de 2020, 14:41
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>


#define _XTAL_FREQ  4000000

void analogico(void);
void desplegar(void);
char x;



void main(void)
{
    OSCCONbits.IRCF = 0b110;
    
    ANSEL = 0b00000000;
    ANSELH = 0b00100000;
    TRISA = 0b00000000;
    TRISB = 0b00100011; 
    TRISC = 0b00000000;
    TRISD = 0b00000000;
    TRISE = 0;
    PORTA = 0;
    PORTB = 0b00100011;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    ADCON0bits.ADCS0 = 1;
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.CHS0 = 1;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 1;
    ADCON0bits.CHS3 = 1;
    ADCON1bits.ADFM = 0;
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
    analogico();
    return;
}
    
    void analogico(void){
        while(1){
        __delay_ms(1);
        ADCON0bits.ADON = 1;
        if(ADCON0bits.GO_DONE == 0){
            ADCON0bits.GO_DONE = 1;
            
        }
        
        desplegar();
        }
        
    }
    
    void desplegar(void){
        
        PORTA = ADRESH;
        return;
    
    }