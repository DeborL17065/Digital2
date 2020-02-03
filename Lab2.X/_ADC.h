/* 
 * File:   _ADC.h
 * Author: debor
 *
 * Created on January 29, 2020, 9:49 AM
 */

#ifndef _ADC_H
#define	_ADC_H


void CONF_ADC(void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.ADIE =1;
    PIR1bits.ADIF =0;
    ADCON0 = 0b01010001; //AN4
    ADCON1 = 0b00000000;
}

#endif	/* _ADC_H */

