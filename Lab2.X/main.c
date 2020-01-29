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


void init(void);
void delay(unsigned char dms);

void main(void) {


}

void init(void) { 
    TRISA =0b00000000; //se define el puerto A como salidas
    TRISC =0b00000000; //se define el puerto C como salidas
    PORTC =0;          //se limpia el puerto C
    TRISD =0b00000000; //se define el puerto D como salidas
    TRISB =0;          //se define el puerto B como salidas
    PORTD =0;          //se limpia el puerto D
    PORTB =0;          //se limpia el puerto B
    PORTA =0;          //se limpia el puerto A
    TRISE =0b11100000; // se definen los primero 3 bits del puerto E como entradas y el resto como salidas
    PORTE =0;          //se limpia el puerto E
    ANSELH =0;
    ANSEL =0;
    
}

void delay(unsigned char dms) {
   
    for (int i= 0; i< dms; i++) {
        for (int j=0; j<255; j++);
    }   
}