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
#include "INTERRUPTS.h"
#include "TMR0.h"

#define ALARMA       RA4
#define PULSADOR_I   RA6
#define PULSADOR_D   RA7
#define T1           RA2
#define T2           RA3
#define VARIABLE     RA5
#define _XTAL_FREQ   4000000

uint8_t DISPLAY[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71}; // definimos el vector que contiede los valores a desplegar en el display
void init(void);
void CONTADORES(void);
void delay(unsigned char dms);
void MUL_DISPLAY (void);
uint8_t Estado1 =0;
uint8_t Estado2 =0;

uint8_t DEC=0;
uint8_t UNI=0;
uint8_t CONT1=0;

void main(void) {
    init(); 
    CONF_ADC(); // configuración del ADC
    CONF_TMR0(); // Configuración del TMR0
    while (1){
        
        CONTADORES();
        if (ADRESH > CONT1){ALARMA =1;} //alarma que indica cuando el valor analogico AN4 es mayor que el contador.
        else {ALARMA =0;} 
      
    }
    
    return;
}



void __interrupt() isr(void){
    if (INTCONbits.T0IF == 1){ 
        INTCONbits.T0IF = 0; //limpiamos la bandera del TMR0
        TMR0 = 210; 
        MUL_DISPLAY ();      //se muestra el valor en los displays
    }
    
    if (PIR1bits.ADIF ==1){  
        PORTD = CONT1; 
        PIR1bits.ADIF =0;  //limpiamos la bandera 
    }
    else {
        ADCON0bits.GO_DONE =1; //se inicia la conversión
        while(ADCON0bits.GO_DONE ==1); 
    }
    
    
}

void MUL_DISPLAY (void){
        UNI =  ADRESH& 0X0F; // seleccionamos los primeros 4 bits
        DEC = (ADRESH & 0XF0)>>4; // hacemos swap nibbles para tener el valor de los ultimos 4 bits
        PORTC =0; // limpiamos el PORTC
        if(T1 ==0){
            T2 =0;// apagamos el transistor del segundo display
            PORTC = DISPLAY[UNI]; 
            T1 = 1; //encendemos el transistor del primer display
        }
        else {
            T1 = 0;// apagamos el transistor del primer display
            PORTC = DISPLAY[DEC];
            T2 =1; // encendemos el transistor del segundo display
        }
}


void CONTADORES(void){
   
    if (PULSADOR_I ==1){   
        Estado1 =1;
    }
    if (Estado1 ==1 && PULSADOR_I ==0){ //boton con antirebote
        Estado1 =0;
        CONT1++ ;      //se incrementa el contador
    }  
    if (PULSADOR_D ==1){   
        Estado2 =1;
    }
    if (Estado2 ==1 && PULSADOR_D ==0){ //boton con antirebote
        Estado2 =0;
        CONT1-- ;   //se decrementa el contador  
    } 
}

void init(void) { 
    TRISA =0b11100000; // los ultimos 3 bits como entradas
    TRISE =0b00000000; 
    TRISC =0b00000000; //se define el puerto C como salidas
    TRISD =0b00000000; //se define el puerto D como salidas
    PORTC =0;          //se limpia el puerto C
    PORTD =0;          //se limpia el puerto D
    PORTA =0;          //se limpia el puerto A
    PORTE =0;          //se limpia el puerto E
    ANSELH =0;
    ANSEL =0; 
}

void delay(unsigned char dms) {
   
    for (int i= 0; i< dms; i++) {
        for (int j=0; j<255; j++);
    }   
}