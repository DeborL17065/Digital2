
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

#define  Led_G1          RB3 // definimos el pin para la led que indicara si el jugador 1 fue el ganador
#define  Led_G2          RB4 // definimos el pin para la led que indicara si el jugador 2 fue el ganador
#define  Led_R           RB0 // definimos el pin para la led roja del semaforo
#define  Led_N           RB1 // definimos el pin para la led naranja del semaforo
#define  Led_V           RB2 // definimos el pin para la led verde del semaforo
#define  PULSADOR_INICIO RE0 // definimos el pin para el pulsador de inicio
#define  PULSADOR_J1     RE1 // definimos el pin para el pulsador del jugador 1
#define  PULSADOR_J2     RE2 // definimos el pin para el pulsador del jugador 2


int  DISPLAY[4]={0x4F,0x5B,0x06,0x3F}; // definimos el vector que contiede los valores a desplegar en el display
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
            unsigned char f=0; //definimos la variable del contador 
            Jugador1 = 0; //limpiando la variable
            Jugador2 = 0; //limpiando la variable
            PORTD =0;  //limpiando el Puerto D
            PORTA =0; //limpiando el Puerto A
            Led_G1 =0; //limpiando la variable
            Led_G2 =0; //limpiando la variable
            for(f=0;f<4;f++){
                delay(200);
                PORTC=DISPLAY[f]; //definimos que la posición del vector dependera de la variable f del contador
                delay(200);  
                switch(f){ // SEMAFORO
                case 0:    //Semaforo en rojo
                Led_R =1;  
                Led_N =0;
                Led_V =0;
                    break;
                case 1:   // semaforo en naranja
                Led_R =0; 
                Led_N =1;
                Led_V =0;
                    break;
                case 2:  //semaforo en verde
                Led_R =0; 
                Led_N =0;
                Led_V =1;
                    break;
                case 3:  //semaforo en verde y el tiempo del contador a finalizado
                Led_R =0; 
                Led_N =0;
                Led_V =1;
                do {
                juego();  //se inicia el juego 
                if (Led_G1 !=0) {PORTC=DISPLAY[2];} //si el jugador 1 ha ganado se desplegara un 1 en el display
                else if (Led_G2 !=0) {PORTC=DISPLAY[1];} //si el jugador 2 ha ganado se desplegara un 2 en el display
                }while((Led_G1==0)&&(Led_G2==0)); // el bucle continuara hasta que alguno de los ds jugadores gane
                
                    break;         
            }   
            }        
            
        }  
      
    }  
  
}

void juego(void){
    
    if (PULSADOR_J1 !=0){   //se define un antirebote
        Estado1 =1;
    }
    if (Estado1 ==1 && PULSADOR_J1 ==0){ //cuando el pulsador se suelta se incrementa el contador del jugador1
        Estado1 =0;
   
        Jugador1 = Jugador1 + 1;   //se incrementa con cada pulsación
        PORTA = 1 << Jugador1 -1 ; // el resultado se observa en el puerto A
        if (Jugador1 == 8) {Led_G1=1;}      //si el jugador 1 completa sus leds se encendera la led que indica que el jugador 1 gano
    }
    
    if (PULSADOR_J2 !=0){  //se define un antirebote
        Estado2 =1;
    }
    if (Estado2 ==1 && PULSADOR_J2 ==0 ){ //cuando el pulsador se suelta se incrementa el contador del jugador2
        Estado2=0;
        
        Jugador2 = Jugador2 + 1;   //se incrementa con cada pulsación
        PORTD = 1<< Jugador2 -1;   // el resultado se observa en el puerto D
        if (Jugador2 == 8) {Led_G2=1;}      //si el jugador 2 completa sus leds se encendera la led que indica que el jugador 2 gano
    }   
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

