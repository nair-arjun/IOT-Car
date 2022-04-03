#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"
#include "ports.h"

void Init_Ports1(void);

void Init_Ports(void)
{
  Init_Ports1();
  Init_Ports2();
  Init_Ports3(USE_GPIO);
  Init_Ports4();
  Init_Ports5();
  Init_Ports6();
}

void Init_Ports1(void)
{
  P1DIR = 0x00;
  P1OUT = 0x00;
  
  P1SEL0 &= ~RED_LED;
  P1SEL1 &= ~RED_LED;
  P1OUT &= ~RED_LED;
  P1DIR |= RED_LED;
  
  P1SELC |= A1_SEEED;
  
  P1SEL0 |= V_DETECT_L; // Channel A2
  P1SEL1 |= V_DETECT_L;
  
  P1SEL0 |= V_DETECT_R; // Channel A3
  P1SEL1 |= V_DETECT_R;
  
  P1SELC |= A4_SEEED;
  
  P1SEL0 |= V_THUMB; // Channel A5
  P1SEL1 |= V_THUMB;
  
  P1SEL0 |= UCA0TXD;
  P1SEL1 &= ~UCA0TXD;
  
  P1SEL0 |= UCA0RXD;
  P1SEL1 &= ~UCA0RXD;
}

void Init_Ports2(void)
{
  P2OUT = 0x00; // P2 set Low
  P2DIR = 0x00; // Set P2 direction to output
  P2SEL0 &= ~DAC_ENB; // P2_0 GPIO operation
  P2SEL1 &= ~DAC_ENB; // P2_0 GPIO operation
  P2OUT &= ~DAC_ENB; // Direction = output
  P2DIR |= DAC_ENB; // Direction = output
  P2SEL0 &= ~IR_LED; // IR_LED GPIO operation
  P2SEL1 &= ~IR_LED; // IR_LED GPIO operation
  P2OUT &= ~IR_LED; // Initial Value = Low / Off
  P2DIR |= IR_LED; // Direction = output
  P2SEL0 &= ~P2_2; // P2_2 GPIO operation
  P2SEL1 &= ~P2_2; // P2_2 GPIO operation
  P2DIR &= ~P2_2; // Direction = input
  P2SEL0 &= ~SW2; // SW2 Operation
  P2SEL1 &= ~SW2; // SW2 Operation
  P2OUT |= SW2; // Configure pullup resistor
  P2DIR &= ~SW2; // Direction = input
  P2REN |= SW2; // Enable pullup resistor
  P2IES |= SW2; // P2.0 Hi/Lo edge interrupt
  P2IFG &= ~SW2; // Clear all P2.6 interrupt flags
  P2IE |= SW2; // P2.6 interrupt enabled
  P2SEL0 &= ~IOT_RUN; // IOT_RUN GPIO operation
  P2SEL1 &= ~IOT_RUN; // IOT_RUN GPIO operation
  P2OUT &= ~IOT_RUN; // Initial Value = Low / Off
  P2DIR |= IOT_RUN; // Direction = input
  P2SEL0 &= ~P2_5; // P2_5 GPIO operation
  P2SEL1 &= ~P2_5; // P2_5 GPIO operation
  P2DIR &= ~P2_5; // Direction = input
  P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
  P2SEL1 |= LFXOUT; // LFXOUT Clock operation
  P2SEL0 &= ~LFXIN; // LFXIN Clock operation
  P2SEL1 |= LFXIN; // LFXIN Clock operation
}

void Init_Ports3(char gpio)
{
  P3OUT = 0x00;
  P3DIR = 0x00;
  
  P3SEL0 &= ~TEST_PROBE;
  P3SEL1 &= ~TEST_PROBE;
  P3OUT |= TEST_PROBE;
  P3DIR |= TEST_PROBE;
  
  P3SEL0 |= OPT_INT;
  P3SEL1 |= OPT_INT;
  
  P3SEL0 |= OA2N;
  P3SEL1 |= OA2N;
  
  P3SEL0 |= OA2P;
  P3SEL1 |= OA2P;
  
  if(gpio == USE_GPIO){
  
    P3SEL0 &= ~SMCLK_OUT;
    P3SEL1 &= ~SMCLK_OUT;
    P3DIR |= SMCLK_OUT;
  
  }
  else if(gpio == USE_SMCLK){
    
    P3SEL0 |= SMCLK_OUT;
    P3SEL1 &= ~SMCLK_OUT;
    P3DIR |= SMCLK_OUT;
  }
    
  
  P3SEL0 |= DAC_CNTL;
  P3SEL1 |= DAC_CNTL;
  
  P3SEL0 |= IOT_LINK;
  P3SEL1 |= IOT_LINK;
  P3DIR  |= IOT_LINK;
  
  P3SEL0 |= IOT_EN;
  P3SEL1 |= IOT_EN;
  P3OUT  &= ~IOT_EN;
  P3DIR  |= IOT_EN;

}

void Init_Ports4(void)
{
  P4OUT = 0x00; // P4 set Low
  P4DIR = 0x00; // Set P4 direction to output
  P4SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
  P4SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
  P4OUT |= RESET_LCD; // Set RESET_LCD Off [High]
  P4DIR |= RESET_LCD; // Set RESET_LCD direction to output
  P4SEL0 &= ~SW1; // SW1 GPIO operation
  P4SEL1 &= ~SW1; // SW1 GPIO operation
  P4OUT |= SW1; // Configure pullup resistor
  P4DIR &= ~SW1; // Direction = input
  P4REN |= SW1; // Enable pullup resistor
  P4IES |= SW1; // P4.2 Hi/Lo edge interrupt
  P4IFG &= ~SW1; // Clear all P2.6 interrupt flags
  P4IE |= SW1; // P4.2 interrupt enabled
  P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
  P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation
  P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
  P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation
  P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
  P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
  P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]
  P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output
  P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
  P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation
  P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
  P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation
  P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
  P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation
}

void Init_Ports5(void)
{
  P5OUT = 0x00;
  P5DIR = 0x00;
  
  P5SEL0 |= CHECK_BAT;
  P5SEL1 |= CHECK_BAT;
  
  P5SEL0 |= V_BAT;
  P5SEL1 |= V_BAT;
  
  P5SEL0 |= V_DAC;
  P5SEL1 |= V_DAC;
  
  P5SEL0 |= V_3_3;
  P5SEL1 |= V_3_3;
  
  P5SEL0 &= ~IOT_BOOT;
  P5SEL1 &= ~IOT_BOOT;
  P5OUT |= IOT_BOOT;
}

void Init_Ports6(void)
{
  P6OUT = 0x00;
  P6DIR = 0x00;
  // P6 set to low
  // Set P5 direction to output
  P6SEL1 &= ~R_FORWARD;
  P6SEL0 |= R_FORWARD;
  P6DIR |= R_FORWARD;
  // R FORWARD pin
  // R FORWARD pin
  P6SEL1 &= ~L_FORWARD;
  P6SEL0 |= L_FORWARD;
  P6DIR |= L_FORWARD;
  // L_FORWARD pin
  // L FORWARD pin
  P6SEL1 &= ~R_REVERSE;
  P6SEL0 |= R_REVERSE;
  P6DIR |= R_REVERSE;
  // R REVERSE pin
  // R_REVERSE pin
  P6SEL1 &= ~L_REVERSE;
  P6SEL0 |= L_REVERSE;
  P6DIR |= L_REVERSE;
  // L_REVERSE pin
  // REVERSE pin
  // LCD BACKLITE pin
  // LCD_BACKLITE pin
  P6SEL1 &= ~LCD_BACKLITE;
  P6SEL0 &= ~LCD_BACKLITE;
  P6OUT |= LCD_BACKLITE;
  P6DIR |= LCD_BACKLITE;
  P6SEL1 &= -P6_5;
  P6SEL0 &= ~P6_5;
  // P6OUT &= ~P6_5;
  P6DIR &= ~P6_5;
  // P6_5 pin
  // P6_5 pin
  P6SEL1 &= ~GRN_LED;
  P6SEL0 &= ~GRN_LED;
  P6OUT &= ~GRN_LED;
  P6DIR |= GRN_LED;
  // GRN_LED pin
  // GRN LED pin

}