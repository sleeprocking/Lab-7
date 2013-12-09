#include <msp430g2553.h>
#include"sensor.h"

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
  ADC10CTL1 |= ADC10SSEL1|ADC10SSEL0;                // Select SMCLK
  ADC10CTL1 |= ADC10DIV_7;
  P1DIR |= BIT0|BIT6;                            // Set P1.0 to output direction
  P1OUT &= ~(BIT0|BIT6);
  for (;;) {

            closeLeft(0x250);

            closeRight(0x275);
         }

}
