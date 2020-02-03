/* 
 * File:   TMR0.h
 * Author: debor
 *
 * Created on February 2, 2020, 3:03 PM
 */

#ifndef TMR0_H
#define	TMR0_H




void CONF_TMR0(void){
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS2 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 1;
    
    //INTCONbits.GIE = 1;
    INTCONbits.T0IE = 1;
    INTCONbits.T0IF = 0;
    OSCCON = 0b01100001;
    TMR0= 61;
    
    


}

#endif	/* TMR0_H */

