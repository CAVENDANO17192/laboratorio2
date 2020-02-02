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

#define  seg1    RD0
#define  seg2    RD1
#define _XTAL_FREQ  4000000


void analogico(void);
void desplegar(void);
void display(void);
void NIBBLES(void);
void TOGGLE(void);




unsigned char DISPLAY1[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
unsigned char DISPLAY2[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
char BANDERA;

unsigned char x;
unsigned char y;
unsigned char ADC;

void __interrupt() ISR(void){
       // desplegar();
    TOGGLE();
        TMR0IF=0;
        TMR0= 2;
        PORTA = ADC;
        return;
}
    

void main(void)
{
   // oscilador interno
    
    OSCCONbits.IRCF = 0b101; //2Mhz
    OSCCONbits.OSTS= 0;
    OSCCONbits.HTS = 0;
    OSCCONbits.LTS = 0;
    OSCCONbits.SCS = 1;
    
    
    
    ANSEL = 0b00000000;
    ANSELH = 0b00100000;
    TRISA = 0b00000000;
    TRISB = 0b00100011; 
    TRISC = 0b00000000;
    TRISD = 0b00000000;
    TRISE = 0;
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    // adc
    
    ADCON0bits.ADCS0 = 1;
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.CHS0 = 1;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 1;
    ADCON0bits.CHS3 = 1;
    ADCON0bits.ADON = 1;   // adc on
    ADCON1bits.ADFM = 0;
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
    
    //timer 0
    OPTION_REGbits.nRBPU = 1;
    OPTION_REGbits.INTEDG = 0;
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.T0SE = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 0b000; // 1:2 tmr0 rate 
    TMR0 = 2;
   
    // interrupciones intcon
    INTCONbits.GIE = 1;
    //INTCONbits.PEIE= 1;
    INTCONbits.T0IE= 1;
    //INTCONbits.INTE= 0; //prender despues
    //INTCONbits.RBIE= 0; //prender despues
    INTCONbits.T0IF= 1;
    //INTCONbits.INTF= 0;
    //INTCONbits.RBIF= 0;
    
    
    
    
    x=0;
    BANDERA = 0;
    analogico();
    return;
}
    
    void analogico(void){
        while(1){
        
        __delay_ms(1);
        if(ADCON0bits.GO_DONE == 0){
            ADCON0bits.GO_DONE = 1;   
        }
        ADC = ADRESH;
        x= ADRESH;
        y = ADRESH;
        NIBBLES();
        //PORTA = ADC;
        
       desplegar();
       
        }
        
    }
    
    void desplegar(void){
       PORTC = 0;
        seg1 = 0;
        seg2 = 0;
        if(BANDERA ==1){
            PORTC = DISPLAY1[x];
            seg1 = 1;
            seg2=0;
            //BANDERA = 0;
            return;
        }
        if(BANDERA == 0){
            
            PORTC = DISPLAY2[y];
            seg2 = 1;
            seg1 = 0;
            //BANDERA = 1;
            return;
        }
        

    }
   
    void NIBBLES(void){
        x = x & 0x0F;
        y = ((y & 0xF0)>>4);
        
        return;
        
    }
   
    void TOGGLE (void){
        if(BANDERA==1){
            BANDERA =0;
        }
        else{
            BANDERA = 1;
        }
    }
   