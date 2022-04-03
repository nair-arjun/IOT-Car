#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"
#include "ports.h"

unsigned int ADC_Channel;
unsigned int ADC_Left_Detect;
unsigned int ADC_Right_Detect;
unsigned int ADC_Thumbwheel;
char Display_Left_Detect[5];
char Display_Right_Detect[5];
char Display_V_Thumbwheel[5];
char adc_char[5];
unsigned int ADC_Average;



#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
case ADCIV_NONE:
break;
case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
// before its previous conversion result was read.
break;
case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
break;
case ADCIV_ADCHIIFG: // Window comparator interrupt flags
break;
case ADCIV_ADCLOIFG: // Window comparator interrupt flag
break;
case ADCIV_ADCINIFG: // Window comparator interrupt flag
break;
case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
  ADCCTL0 &= ~ADCENC; // Disable ENC bit.
  switch (ADC_Channel++){
    case 0x00: // Channel A2 Interrupt
      ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
      ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
      ADC_Left_Detect = ADCMEM0; // Move result into Global
      ADC_Left_Detect = ADC_Left_Detect >> 2; // Divide the result by 4
      HEXtoBCD(ADC_Left_Detect); // Convert result to String
      strcpy(Display_Left_Detect, adc_char); // Place String in Display
      break;
    case 0x01:
      ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A3
      ADCMCTL0 |= ADCINCH_5; // Enable Next channel A5
      ADC_Right_Detect = ADCMEM0; // Move result into Global
      ADC_Right_Detect = ADC_Right_Detect >> 2; // Divide the result by 4
      HEXtoBCD(ADC_Right_Detect); // Convert result to String
      strcpy(Display_Right_Detect, adc_char); // Place String in Display
      break;
    case 0x02:
      ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A3
      ADCMCTL0 |= ADCINCH_2; // Enable Next channel A2
      ADC_Thumbwheel = ADCMEM0; // Move result into Global
      ADC_Thumbwheel = ADC_Thumbwheel >> 2; // Divide the result by 4
      HEXtoBCD(ADC_Thumbwheel); // Convert result to String
      strcpy(Display_V_Thumbwheel, adc_char); // Place String in Display
      ADC_Channel = RESET_STATE;
      break;
    default:
      break;
  }
ADC_Average = (ADC_Left_Detect + ADC_Right_Detect) >> 1;
ADCIE &= ~ADCIE0;

default:
break;
}
}