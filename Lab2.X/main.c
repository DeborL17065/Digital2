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
#include <pic16F887.h>
#include <stdint.h>
#include  "_ADC.h"

#define ALARMA       RA4
#define PULSADOR_I   RE0
#define PULSADOR_D   RE1
#define T1           RA2
#define T2           RA3
#define VARIABLE     RA5
#define _XTAL_FREQ   4000000

int  DISPLAY[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71}; // definimos el vector que contiede los valores a desplegar en el display
void init(void);
void CONTADORES(void);
void delay(unsigned char dms);
char Estado1 =0;
char Estado2 =0;

uint8_t DEC=0;
uint8_t UNI=0;

uint8_t CONT1=0;

void main(void) {
    init();
    CONF_ADC();
    while (1){
        CONTADORES(); 
        ADCON0bits.GO_DONE =1;
        __delay_ms(10);
        if (ADRESH > CONT1){ALARMA =1;}
        else {ALARMA =0;}
      
    }
    
    return;
}



void __interrupt() isr(void){
    
    //PORTD = ADRESH;
    if (PIR1bits.ADIF ==1){ 
        
        
        UNI =  ADRESH& 0X0F;
        DEC = (ADRESH & 0XF0)>>4;
        PORTC =0;
        PORTC = DISPLAY[UNI];
        T1 = 1;
        __delay_ms(2);
        T1 = 0;
        PORTC = DISPLAY[DEC];
        T2 =1;
        __delay_ms(2);
        T2=0;  
        
        PIR1bits.ADIF =0;
        
    }
    
    
    

}


void CONTADORES(void){
   
    if (PULSADOR_I ==1){   
        Estado1 =1;
    }
    if (Estado1 ==1 && PULSADOR_I ==0){
        Estado1 =0;
        CONT1 = CONT1 + 1;       
    }  
    if (PULSADOR_D ==1){   
        Estado2 =1;
    }
    if (Estado2 ==1 && PULSADOR_D ==0){
        Estado2 =0;
        CONT1 = CONT1 - 1;     
    } 
}

void init(void) { 
    TRISA =0b00100000; 
    TRISE =0b00000011; 
    TRISC =0b00000000; //se define el puerto C como salidas
    TRISD =0b00000000; //se define el puerto D como salidas
    PORTC =0;          //se limpia el puerto C
    PORTD =0;          //se limpia el puerto D
    PORTA =0;          //se limpia el puerto A
    PORTE =0; 
    ANSELH =0;
    ANSEL =0; 
}

void delay(unsigned char dms) {
   
    for (int i= 0; i< dms; i++) {
        for (int j=0; j<255; j++);
    }   
}