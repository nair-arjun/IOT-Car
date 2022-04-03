#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"
#include "ports.h"

volatile unsigned int iot_rx_ring_wr;
char IOT_Char_Rx[SMALL_RING_SIZE] ;
int process_buffer[LARGE_RING_SIZE];
int iot_pb_index;
char IOT_PB[LARGE_RING_SIZE];
int UCA0_index;
char IOT_TX_FLG;
char IOT_MSG_SND[LARGE_RING_SIZE];
char IOT_Glob;
char MSG_RCVD;

volatile unsigned int usb_rx_ring_wr;
char USB_Char_Rx[SMALL_RING_SIZE] ;
int process_buffer[LARGE_RING_SIZE];
int usb_pb_index;
char USB_PB[LARGE_RING_SIZE];
int UCA1_index;
char USB_TX_FLG;
char USB_MSG_SND[LARGE_RING_SIZE];

#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
  unsigned int temp_A0;
  switch(__even_in_range(UCA0IV,0x08)){
  case 0: // Vector 0 - no interrupt
    break;
  case 2: // Vector 2 - RXIFG
    temp_A0 = iot_rx_ring_wr++;
    IOT_Char_Rx[temp_A0] = UCA0RXBUF; // RX -> IOT_Char_Rx character
    IOT_PB[iot_pb_index] = IOT_Char_Rx[temp_A0];
    if (iot_rx_ring_wr >= (sizeof(IOT_Char_Rx))){
      iot_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
    }
    if (IOT_PB[iot_pb_index++] == '\n'){
      IOT_PB[iot_pb_index-2] = NULL;
      iot_pb_index = BEGINNING;
      if(strstr(IOT_PB, "+IPD")){
        splitCMD();
      }
      strcpy(USB_MSG_SND, IOT_PB);
      transmit_stuffA1();
    }
    
    break;
  case 4: // Vector 4 – TXIFG
    if(IOT_MSG_SND[UCA0_index] != NULL){
      UCA0TXBUF = IOT_MSG_SND[UCA0_index++];
    }
    else if(IOT_TX_FLG == RTRNFLG){
      UCA0TXBUF = RTRNFLG;
      IOT_TX_FLG = LINEFD;
    }
    else if(IOT_TX_FLG == LINEFD){
      UCA0TXBUF = LINEFD;
      IOT_TX_FLG = RESET_STATE;
    }
    else{
      UCA0IE &= ~UCTXIE;
    }
    break;
    
  default: break;
  }
}
//------------------------------------------------------------------------------

void Init_Serial_UCA0(void){
  //------------------------------------------------------------------------------
  // TX error (%) RX error (%)
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
  // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
  // 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
  // 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
  // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
  // 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
  //------------------------------------------------------------------------------
  // Configure eUSCI_A0 for UART mode
  UCA0CTLW0 = 0;
  UCA0CTLW0 |= UCSWRST ; // Put eUSCI in reset
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
  UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
  UCA0CTLW0 &= ~UCPEN; // No Parity
  UCA0CTLW0 &= ~UCSYNC;
  UCA0CTLW0 &= ~UC7BIT;
  UCA0CTLW0 |= UCMODE_0;
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
  // UCA?MCTLW = UCSx + UCFx + UCOS16
  UCA0BRW = 4 ; // 115,200 baud
  UCA0MCTLW = 0x5551;
  UCA0CTLW0 &= ~UCSWRST ; // release from reset
  //  UCA0TXBUF = 0x00; // Prime the Pump
  UCA0IE |= UCRXIE; // Enable RX interrupt
  //------------------------------------------------------------------------------
}

void transmit_stuffA0(void){
  
  UCA0_index = BEGINNING;
  IOT_TX_FLG = RTRNFLG;
  UCA0TXBUF = IOT_MSG_SND[UCA0_index++];
  UCA0IE |= UCTXIE;
}

#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
  unsigned int temp_A1;
  switch(__even_in_range(UCA1IV,0x08)){
  case 0: // Vector 0 - no interrupt
    break;
  case 2: // Vector 2 - RXIFG
    IOT_Glob = ONST;
    temp_A1 = usb_rx_ring_wr++;
    USB_Char_Rx[temp_A1] = UCA1RXBUF; // RX -> USB_Char_Rx character
    USB_PB[usb_pb_index] = USB_Char_Rx[temp_A1];
    if (usb_rx_ring_wr >= (sizeof(USB_Char_Rx))){
      usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
    }
    if (USB_PB[usb_pb_index++] == '\n'){
      USB_PB[usb_pb_index-2] = NULL;
      usb_pb_index = BEGINNING;
      strcpy(IOT_MSG_SND, USB_PB);
      transmit_stuffA0();
    }
    break;
  case 4: // Vector 4 – TXIFG
    if(USB_MSG_SND[UCA1_index] != NULL){
      UCA1TXBUF = USB_MSG_SND[UCA1_index++];
    }
    else if(USB_TX_FLG == RTRNFLG){
      UCA1TXBUF = RTRNFLG;
      USB_TX_FLG = LINEFD;
    }
    else if(USB_TX_FLG == LINEFD){
      UCA1TXBUF = LINEFD;
      USB_TX_FLG = RESET_STATE;
    }
    else{
      UCA1IE &= ~UCTXIE;
    }
    break;
    
  default: break;
  }
}
//------------------------------------------------------------------------------


void Init_Serial_UCA1(void){
  //------------------------------------------------------------------------------
  // TX error (%) RX error (%)
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
  // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
  // 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
  // 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
  // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
  // 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
  //------------------------------------------------------------------------------
  // Configure eUSCI_A1 for UART mode
  IOT_Glob = OFFST;
  UCA1CTLW0 = 0;
  UCA1CTLW0 |= UCSWRST ; // Put eUSCI in reset
  UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA1CTLW0 &= ~UCMSB; // MSB, LSB select
  UCA1CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
  UCA1CTLW0 &= ~UCPEN; // No Parity
  UCA1CTLW0 &= ~UCSYNC;
  UCA1CTLW0 &= ~UC7BIT;
  UCA1CTLW0 |= UCMODE_0;
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
  // UCA?MCTLW = UCSx + UCFx + UCOS16
  UCA1BRW = 4 ; // 115,200 baud
  UCA1MCTLW = 0x5551;
  UCA1CTLW0 &= ~UCSWRST ; // release from reset
  //  UCA1TXBUF = 0x00; // Prime the Pump
  UCA1IE |= UCRXIE; // Enable RX interrupt
  //------------------------------------------------------------------------------
}

void transmit_stuffA1(void){
  
  UCA1_index = BEGINNING;
  USB_TX_FLG = RTRNFLG;
  UCA1TXBUF = USB_MSG_SND[UCA1_index++];
  UCA1IE |= UCTXIE;
}
