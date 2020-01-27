
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

#define  Led_G1          RB3
#define  Led_G2          RB4
#define  Led_R           RB0
#define  Led_N           RB1
#define  Led_V           RB2
#define  PULSADOR_INICIO RE0
#define  PULSADOR_J1     RE1
#define  PULSADOR_J2     RE2


int  DISPLAY[4]={0x4F,0x5B,0x06,0x3F};
void init(void);
void delay(unsigned char dms);
void juego(void);
char Jugador1 = 0;
char Jugador2 = 0;
char Estado1  =0;
char Estado2  =0;



void main(void) {
    init();
    
    while (1) {
        
        
        if (PULSADOR_INICIO != 0) {
            delay(100);
            while((PULSADOR_INICIO ==1));  //ANTIREBOTE 
            unsigned char f=0;
            Jugador1 = 0; //limpiando la variable
            Jugador2 = 0;
            PORTD =0;
            PORTA =0;
            Led_G1 =0;
            Led_G2 =0;
            for(f=0;f<4;f++){
                delay(200);
                PORTC=DISPLAY[f];
                delay(200);  
                switch(f){
                case 0:
                Led_R =1;  
                Led_N =0;
                Led_V =0;
                    break;
                case 1:
                Led_R =0; 
                Led_N =1;
                Led_V =0;
                    break;
                case 2:
                Led_R =0; 
                Led_N =0;
                Led_V =1;
                    break;
                case 3: 
                Led_R =0; 
                Led_N =0;
                Led_V =1;
                do {
                juego(); 
                if (Led_G1 !=0) {PORTC=DISPLAY[2];}
                else if (Led_G2 !=0) {PORTC=DISPLAY[1];}
                }while((Led_G1==0)&&(Led_G2==0));
                
                    break;         
            }   
            }        
            
        }  
   //     else {
           // PORTC=DISPLAY[2]; //3
   //     }
            
      
    }  
   // return;
}

void juego(void){
    
    if (PULSADOR_J1 !=0){
        Estado1 =1;
    }
    if (Estado1 ==1 && PULSADOR_J1 ==0){
        Estado1 =0;
   
        Jugador1 = Jugador1 + 1;
        PORTA = 1 << Jugador1 -1 ;
        if (Jugador1 == 8) {Led_G1=1;}      
    }
    
    if (PULSADOR_J2 !=0){
        Estado2 =1;
    }
    if (Estado2 ==1 && PULSADOR_J2 ==0 ){
        Estado2=0;
        
        Jugador2 = Jugador2 + 1;
        PORTD = 1<< Jugador2 -1;
        if (Jugador2 == 8) {Led_G2=1;}      
    }   
}
   

void init(void) {
    TRISA =0b00000000;
    TRISC =0b00000000;
    PORTC =0;
    TRISD =0b00000000;
    TRISB =0;
    PORTD =0;
    PORTB =0;
    PORTA =0;
    TRISE =0b11100000;
    PORTE =0;
    ANSELH =0;
    ANSEL =0;
    
}

void delay(unsigned char dms) {
   
    for (int i= 0; i< dms; i++) {
        for (int j=0; j<255; j++);
    }
    
}

