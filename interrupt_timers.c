#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"
#include "ports.h"

extern volatile unsigned int timer_count;
volatile unsigned int iot_count;
extern volatile unsigned char update_display;
volatile unsigned int lcd_count;
volatile unsigned int switchOnePressed;
volatile unsigned int switchTwoPressed;
volatile unsigned int oneDebounceCount;
volatile unsigned int twoDebounceCount;
extern volatile unsigned char display_changed;
extern char display_line[4][11];
volatile unsigned int long_timer;
extern char line_find;
int IOTFLG;
extern char IOT_PB[LARGE_RING_SIZE];
int fiftytimer;
int longest_timer;
int ipDisp;
extern char adc_char[5];



#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
  //------------------------------------------------------------------------------
  // TimerB0 0 Interrupt handler
  //----------------------------------------------------------------------------
  
  
  
  if(timer_count++ >= displayUpdate){
    update_display = 1;
    display_changed = 1;
    timer_count = 0;
  }

  ADCCTL0 |= ADCENC;
  ADCCTL0 |= ADCSC;
  ADCIE |= ADCIE0;
  
  
  
  TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
  //----------------------------------------------------------------------------
}



#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
  //----------------------------------------------------------------------------
  // TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
  //----------------------------------------------------------------------------
  switch(__even_in_range(TB0IV,14)){
  case 0: break; // No interrupt
  case 2: // CCR1 not used
    fiftytimer++;
    if(fiftytimer >= TWENTY){
      fiftytimer = 0;}
    TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TBCCR1
    
    if(switchOnePressed){
      oneDebounceCount++;
      if(oneDebounceCount >= debounceDelay){
        P4IE |= SW1;
        switchOnePressed = 0;
        TB0CCTL0 |= CCIE;
      }
    }
    if(switchTwoPressed){
      twoDebounceCount++;
      if(twoDebounceCount >= debounceDelay){
        P2IE |= SW2;
        switchTwoPressed = 0;
        TB0CCTL0 |= CCIE;
      }
    }
    
    break;
  case 4: 
    long_timer++;
    longest_timer++;
    if(long_timer >=20){long_timer = 0;}
    if(longest_timer >= 9999){longest_timer = 0;}
    HEXtoBCD(longest_timer);
    strcpy(display_line[3],"   ");
    strcat(display_line[3], adc_char);
    strcat(display_line[3], "   ");
    TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TBCCR2
    break;
  case 14: // overflow

    Init_IOT();
    break;
  default: break;
  }
  //----------------------------------------------------------------------------
}



#pragma vector=PORT4_VECTOR
// Create Interrupt Service Routine Function with “__interrupt”
__interrupt void switch_interrupt(void) {
  // Switch 1
  if (P4IFG & SW1) {
    P4IFG &= ~ SW1;
    switchOnePressed = 1;
    oneDebounceCount = 0;
    P4IE &= ~SW1;
    TB0CCTL0 &= ~CCIE;
    
    P2OUT ^= IR_LED;
    
    if(P2OUT & IR_LED){
      strcpy(display_line[1], "  IR ON   ");
    }
    else{
      strcpy(display_line[1], "  IR OFF  ");
    }
    
    if (UCA0BRW == BRW_FIFT){
    }
    else if(UCA0BRW == BRW_FOUR){
        UCA0BRW = BRW_FIFT;
        UCA0MCTLW = CTLW_FIFT;
        strcpy(display_line[3], "  115200  ");
      }
      
    
  }
  // Use a Timer Value to control the debounce
}

#pragma vector=PORT2_VECTOR
// Create Interrupt Service Routine Function with “__interrupt”
__interrupt void switch2_interrupt(void) {
  // Switch 1
  if (P2IFG & SW2) {
    P2IFG &= ~SW2; // IFG SW1 cleared
    switchTwoPressed = 1;
    twoDebounceCount = 0;
    P2IE &= ~SW2;
    TB0CCTL0 &= ~CCIE;
    ipDisp++;
    
    if(ipDisp <= 1){
      displayIP();
    }
    else if(ipDisp > 1){
      strcpy(display_line[2], "          ");
      update_display=1;
      strcpy(display_line[3], "          ");
      update_display=1;
      ipDisp = 0;
    }

    
    
  }
  // Use a Timer Value to control the debounce
}



void Init_Timers(void){
  Init_Timer_B0();
  Init_Timer_B3();
}

void Init_Timer_B0(void) {
  TB0CTL = TBSSEL__ACLK; // ACLK source
  TB0CTL |= TBCLR; // Resets TB0R, clock divider, count direction
  TB0CTL |= MC__CONTINOUS; // Continuous up
  TB0CTL |= ID__1; // Divide clock by 1
  TB0EX0 = TBIDEX__1; // Divide clock by an additional 1
  TB0CCR0 = TB0CCR0_INTERVAL; // CCR0
  TB0CCTL0 |= CCIE; // CCR0 enable interrupt
  TB0CCR1 = TB0CCR1_INTERVAL; // CCR1
  TB0CCTL1 |= CCIE; // CCR1 enable interrupt
  TB0CCR2 = TB0CCR2_INTERVAL; // CCR2
  TB0CCTL2 |= CCIE; // CCR2 enable interrupt
  TB0CTL |= TBIE; // Disable Overflow Interrupt
  TB0CTL &= ~TBIFG; // Clear Overflow Interrupt flag
}

void Init_Timer_B3(void) {
  //------------------------------------------------------------------------------
  // SMCLK source, up count mode, PWM Right Side
  // TB3.1 P6.0 R_FORWARD
  // TB3.2 P6.1 L_FORWARD
  // TB3.3 P6.2 R_REVERSE
  // TB3.4 P6.3 L_REVERSE
  //------------------------------------------------------------------------------
  TB3CTL = TBSSEL__SMCLK; // SMCLK
  TB3CTL |= MC__UP; // Up Mode
  TB3CTL |= TBCLR; // Clear TAR
  TB3CCR0 = WHEEL_PERIOD; // PWM Period
  TB3CCTL1 = OUTMOD_7; // CCR1 reset/set
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM duty cycle
  TB3CCTL2 = OUTMOD_7; // CCR2 reset/set
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Left Forward PWM duty cycle
  TB3CCTL3 = OUTMOD_7; // CCR3 reset/set
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM duty cycle
  TB3CCTL4 = OUTMOD_7; // CCR4 reset/set
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM duty cycle
  //------------------------------------------------------------------------------
}

