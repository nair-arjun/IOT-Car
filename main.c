//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Jim Carlson
//  Jan 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
#include "macros.h"
#include "ports.h"
//#include  "LCD.h"

#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1

// Function Prototypes
void main(void);
void Init_Conditions(void);
void Init_LEDs(void);

// Global Variables
volatile char slow_input_down;
extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;
extern volatile unsigned int timer_count;
char project5state;
extern volatile unsigned int ADC_Left_Detect;
extern volatile unsigned int ADC_Right_Detect;
char line_find;
extern char Display_Left_Detect[5];
extern char Display_Right_Detect[5];
extern unsigned int ADC_Average;
extern unsigned int long_timer;
char test_line[10];
extern char USB_MSG_SND[LARGE_RING_SIZE];
extern char IOT_MSG_SND[LARGE_RING_SIZE];
extern char* cmdstring;
extern char* cmdstring2;
char IOT_State;
char IOT_State2;
extern char multcmd;
extern int intervaltime;
extern int intervaltime2;
extern char MSG_RCVD;
char ONEDONE;
extern int fiftytimer;
char DONEXT;
char find_line;


void main(void){
  //------------------------------------------------------------------------------
  // Main Program
  // This is the main routine for the program. Execution of code starts here.
  // The operating system is Back Ground Fore Ground.
  //
  //------------------------------------------------------------------------------
  
  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
  
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_Serial_UCA0();                   // Initialize Serial 1
  Init_Serial_UCA1();
  
  Init_LCD();                          // Initialize LCD
  Init_ADC();
  //  ClrDisplay();
  // Place the contents of what you want on the display, in between the quotes
  // Limited to 10 characters per line
  //  strcpy(display_line[0], "   NCSU   ");
  //  strcpy(display_line[1], " WOLFPACK ");
  //  strcpy(display_line[2], "  ECE306  ");
  
  project5state = RESET_STATE;
  line_find = RESET_STATE;
  ONEDONE = RESET_STATE;
  
  
  //------------------------------------------------------------------------------
  // Begining of the "While" Operating System
  //------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    
    Check_Wheels();
    
    switch(IOT_State){
    case RESET_STATE:
      Wheels_Off();
      break;
    case FORWARD:
      Forward_Move(IOT_FSpeedR, IOT_FSpeedL);
      if(long_timer >= intervaltime){
        Wheels_Off();
        long_timer = 0;
        IOT_State = RESET_STATE;
        ONEDONE = YES;
      }
      break;
    case REVERSE:
      Reverse_Move(IOT_RSpeedR, IOT_RSpeedR);
      if(long_timer >= intervaltime){
        Wheels_Off();
        long_timer = 0;
        IOT_State = RESET_STATE;
        ONEDONE = YES;
      }
      break;
    case RIGHT:
      Reverse_Clockwise(IOT_TSpeedR, IOT_TSpeedL);
      if(fiftytimer >= NINETYTIME){
        Wheels_Off();
        fiftytimer = 0;
        IOT_State = RESET_STATE;
        ONEDONE = YES;
      }
      break;
    case LEFT:
      Turn_Clockwise(IOT_TSpeedR, IOT_TSpeedL);
      if(fiftytimer >= NINETYTIME){
        Wheels_Off();
        fiftytimer = 0;
        IOT_State = RESET_STATE;
        ONEDONE = YES;
      }
      break;
    case LEFTFOHFIH:
      Reverse_Clockwise(IOT_TSpeedR, IOT_TSpeedL);
      if(fiftytimer >= FOHFIHTIME){
        Wheels_Off();
        fiftytimer = 0;
        IOT_State = RESET_STATE;
        ONEDONE = RESET_STATE;
      }
      break;
    case RIGHTFOHFIH:
      Turn_Clockwise(IOT_TSpeedR, IOT_TSpeedL);
      if(fiftytimer >= FOHFIHTIME){
        Wheels_Off();
        fiftytimer = 0;
        IOT_State = RESET_STATE;
        ONEDONE = RESET_STATE;
      }
      break;
    case LINEFIND:
      find_line = START_FIND;
      break;
    case DISPSTAGE:
      switch(intervaltime){
      case 1:
        strcpy(display_line[0], " STAGE 01 ");
        IOT_State = RESET_STATE;
        break;
      case 2:
        strcpy(display_line[0], " STAGE 02 ");
        IOT_State = RESET_STATE;
        break;
      case 3:
        strcpy(display_line[0], " STAGE 03 ");
        IOT_State = RESET_STATE;
        break;
      case 4:
        strcpy(display_line[0], " STAGE 04 ");
        IOT_State = RESET_STATE;
        break;
      case 5:
        strcpy(display_line[0], " STAGE 05 ");
        IOT_State = RESET_STATE;
        break;
      case 6:
        strcpy(display_line[0], " STAGE 06 ");
        IOT_State = RESET_STATE;
        break;
      case 7:
        strcpy(display_line[0], " STAGE 07 ");
        IOT_State = RESET_STATE;
        break;
      case 8:
        strcpy(display_line[0], " STAGE 08 ");
        IOT_State = RESET_STATE;
        break;
      case 9:
        strcpy(display_line[0], " STAGE 09 ");
        IOT_State = RESET_STATE;
        break;
      }
      break;
    default: break;
    }
    
    if((multcmd == YES) && (ONEDONE == YES)){
      switch(IOT_State2){
      case RESET_STATE:
        Wheels_Off();
        break;
      case FORWARD:
        Forward_Move(IOT_FSpeedR, IOT_FSpeedL);
        if(long_timer >= intervaltime2){
          Wheels_Off();
          long_timer = 0;
          IOT_State2 = RESET_STATE;
          ONEDONE = RESET_STATE;
        }
        break;
      case REVERSE:
        Wheels_Off();
        Reverse_Move(IOT_RSpeedR, IOT_RSpeedL);
        if(long_timer >= intervaltime2){
          Wheels_Off();
          long_timer = 0;
          IOT_State2 = RESET_STATE;
          ONEDONE = RESET_STATE;
        }
        break;
      case RIGHT:
        Turn_Clockwise(IOT_TSpeedR, IOT_TSpeedL);
        if(long_timer >= NINETYTIME){
          Wheels_Off();
          long_timer = 0;
          IOT_State2 = RESET_STATE;
          ONEDONE = RESET_STATE;
        }
        break;
      case LEFT:
        Reverse_Clockwise(IOT_TSpeedR, IOT_TSpeedL);
        if(long_timer >= NINETYTIME){
          Wheels_Off();
          long_timer = 0;
          IOT_State2 = RESET_STATE;
          ONEDONE = RESET_STATE;
        }
        break;
      case LEFTFOHFIH:
        Reverse_Clockwise(IOT_TSpeedR, IOT_TSpeedL);
        if(fiftytimer >= FOHFIHTIME){
          Wheels_Off();
          fiftytimer = 0;
          IOT_State2 = RESET_STATE;
          ONEDONE = RESET_STATE;
        }
        break;
      case RIGHTFOHFIH:
        Turn_Clockwise(IOT_TSpeedR, IOT_TSpeedL);
        if(fiftytimer >= FOHFIHTIME){
          Wheels_Off();
          fiftytimer = 0;
          IOT_State2 = RESET_STATE;
          ONEDONE = RESET_STATE;
        }
        break;
      default: break;
      }
      
      
    }
    
    switch(line_find){
    case START_FIND:
      if((ADC_Left_Detect < BLACK) && (ADC_Right_Detect < BLACK)){
        Forward_Move(8000,8000);
      }
      else if((ADC_Left_Detect > BLACK) || (ADC_Right_Detect > BLACK)){
        line_find = FOUND;
        break;
      break;
      case FOUND:
       if((ADC_Left_Detect > BLACK) && (ADC_Right_Detect > BLACK)){
        Forward_Move(5000,5000);
      }
       else if((ADC_Left_Detect< BLACK) && (ADC_Right_Detect > BLACK)){
         Turn_Clockwise(5000,5000);
       }
       else if((ADC_Left_Detect > BLACK) && (ADC_Right_Detect < BLACK)){
         Reverse_Clockwise(5000,5000);
       }
       else if((ADC_Left_Detect < BLACK) && (ADC_Right_Detect < BLACK)){
         Reverse_Move(5000,5000);
       }
       break;
    }
    }
    
    //    if(!(multcmd == YES)){
    //      switch(IOT_State){
    //      case RESET_STATE:
    //        Wheels_Off();
    //        break;
    //      case FORWARD:
    //        Wheels_Off();
    //        Forward_Move();
    //        if(long_timer >= intervaltime){
    //          Wheels_Off();
    //          long_timer = 0;
    //          IOT_State = RESET_STATE;
    //          break;
    //        }
    //      case REVERSE:
    //        Wheels_Off();
    //        Reverse_Move();
    //        if(long_timer >= intervaltime){
    //          Wheels_Off();
    //          long_timer = 0;
    //          IOT_State = RESET_STATE;
    //          break;
    //        }
    //      default: break;
    //
    //    }
    //    }
    //       else{
    //       switch(IOT_State){
    //      case RESET_STATE:
    //        Wheels_Off();
    //        break;
    //      case FORWARD:
    //        Wheels_Off();
    //        Forward_Move();
    //        if(long_timer >= intervaltime){
    //          Wheels_Off();
    //          long_timer = 0;
    //          IOT_State = RESET_STATE;
    //          break;
    //        }
    //       }
    //      switch(IOT_State2){
    //      case RESET_STATE:
    //        Wheels_Off();
    //        break;
    //      case FORWARD:
    //        Wheels_Off();
    //        Forward_Move();
    //        if(long_timer >= intervaltime2){
    //          Wheels_Off();
    //          long_timer = 0;
    //          IOT_State2 = RESET_STATE;
    //          break;
    //        }
    //        case REVERSE:
    //        Wheels_Off();
    //        Reverse_Move();
    //        if(long_timer >= intervaltime2){
    //          Wheels_Off();
    //          long_timer = 0;
    //          IOT_State2 = RESET_STATE;
    //          break;
    //        }
    //       }
    //       }
    //
    //    
    //    
    //    
    
    Display_Process();
  }
  //------------------------------------------------------------------------------
}

void Init_Conditions(void){
  //------------------------------------------------------------------------------
  
  int i;
  for(i=0;i<11;i++){
    display_line[0][i] = RESET_STATE;
    display_line[1][i] = RESET_STATE;
    display_line[2][i] = RESET_STATE;
    display_line[3][i] = RESET_STATE;
  }
  display_line[0][10] = 0;
  display_line[1][10] = 0;
  display_line[2][10] = 0;
  display_line[3][10] = 0;
  
  display[0] = &display_line[0][0];
  display[1] = &display_line[1][0];
  display[2] = &display_line[2][0];
  display[3] = &display_line[3][0];
  update_display = 0;
  
  
  // Interrupts are disabled by default, enable them.
  enable_interrupts();
  //------------------------------------------------------------------------------
}

void Display_Process(void){
  if(update_display){
    update_display = 0;
    if(display_changed){
      display_changed = 0;
      Display_Update(0,0,0,0);
    }
  }
}


void Init_LEDs(void){
  //------------------------------------------------------------------------------
  // LED Configurations
  //------------------------------------------------------------------------------
  // Turns on both LEDs
  P1OUT &= ~RED_LED;
  P6OUT &= ~GRN_LED;
  //------------------------------------------------------------------------------
}


