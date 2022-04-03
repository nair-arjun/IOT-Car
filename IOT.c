#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"
#include "ports.h"

//-----------------------------------------------------------------------------------------------------------------------------------
//
//  Description - This file contains all the code relevant to initialize 
//                the IOT module, obtain the IP address, and setup the server
//
//   Arjun Nair
//
//-----------------------------------------------------------------------------------------------------------------------------------


extern int IOTFLG;
extern char IOT_MSG_SND[LARGE_RING_SIZE];
extern char IOT_PB[LARGE_RING_SIZE];
extern char USB_MSG_SND[LARGE_RING_SIZE];
extern char display_line[4][11];
extern int long_timer;
extern char IOT_State;
extern char IOT_State2;
extern int intervaltime;
extern int intervaltime2;


void Init_IOT(void){
  switch(IOTFLG){
  case 0:
    P3OUT &= ~IOT_EN;
    IOTFLG++;
    break;
  case 1:
    IOTFLG++;
    break;
  case 2:
    IOTFLG++;
    break;
  case 3:
    P3OUT |= IOT_EN;
    strcpy(display_line[0], "  IOT ON  ");
    IOTFLG++;
    break;
  case 4:
    IOTFLG++;
    break;
  case 5:
    IOTFLG++;
    break;
  case 6:
    strcpy(IOT_MSG_SND, "AT+CIPMUX=1");
    transmit_stuffA0();
    strcpy(display_line[0], "  MUX ON  ");
    IOTFLG++;
    break;
  case 7:
    strcpy(IOT_MSG_SND, "AT+CIFSR");
    transmit_stuffA0();
    strcpy(display_line[0], "GETTING IP"); 
    IOTFLG++;
    break;
  case 8:
    IOTFLG++;
    break;
  case 9:
    strcpy(IOT_MSG_SND, "AT+CIPSTART=0,\"UDP\",\"0.0.0.0\",42069,42069,2");
    transmit_stuffA0();
    IOTFLG++;
    strcpy(display_line[0], "SERVER ON ");
    P6OUT |= GRN_LED;
    break;
  case 10:
    P6OUT &= ~GRN_LED;
    strcpy(display_line[0], "RDY 4 CMD");
    break;
  default: break;
  }
}

void IOT_Drive1(){
  
}

void IOT_Drive2(void){
  
}