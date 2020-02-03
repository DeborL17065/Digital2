/* 
 * File:   INTERRUPTS.h
 * Author: debor
 *
 * Created on February 2, 2020, 3:32 PM
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

void CONF_INTERRUPTS (void) {
  //  INTCONbits.PEIE =1;
    PIE1 = 255;
    //PIE1bits.ADIE = 1;
    //PIR1bits.ADIF = 0;
    //INTCONbits.GIE = 1;
}

#endif	/* INTERRUPTS_H */

