#include<msp430g2553.h>
#include"sensor.h"
/*
 * sensor.c
 *
 *  Created on: Dec 5, 2013
 *      Author: C15Trevor.Moore
 */
void initSensors(){
    ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
    ADC10CTL1 |= ADC10SSEL1|ADC10SSEL0;                // Select SMCLK
    ADC10CTL1 |= ADC10DIV_7;
    P1DIR |= BIT0|BIT6;                            // Set P1.0 to output direction
    P1OUT &= ~(BIT0|BIT6);
}
void leftSensorTest(){
    ADC10CTL0 &= ~ENC;
    ADC10CTL1 = INCH_3;
    ADC10AE0 |= BIT3;
    ADC10CTL0 |= ENC + ADC10SC;

}

void centerSensorTest(){
    ADC10CTL0 &= ~ENC;
    ADC10CTL1 = INCH_4;
    ADC10AE0 |= BIT4;
    ADC10CTL0 |= ENC + ADC10SC;

}
void rightSensorTest(){
    ADC10CTL0 &= ~ENC;
    ADC10CTL1 = INCH_5;
    ADC10AE0 |= BIT5;
    ADC10CTL0 |= ENC + ADC10SC;

}
void closeLeft(int threshold){
	leftSensorTest();
    __bis_SR_register(CPUOFF + GIE);
	if (ADC10MEM < threshold)
	  P1OUT &= ~BIT0;                       // Clear P1.0 LED off
	else
	  P1OUT |= BIT0;
}
void closeRight(int threshold){
	rightSensorTest();
    __bis_SR_register(CPUOFF + GIE);
	if (ADC10MEM < threshold)
	  P1OUT &= ~BIT6;                       // Clear P1.0 LED off
	else
	  P1OUT |= BIT6;
}

void closeCenter(int threshold){
	centerSensorTest();
    __bis_SR_register(CPUOFF + GIE);
	if (ADC10MEM < threshold)
	  P1OUT &= ~BIT6;                       // Clear P1.0 LED off
	else
	  P1OUT |= BIT6;
}
// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}


