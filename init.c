#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"
#include "ports.h"

extern char display_line[4][11];
extern char *display[4];
extern volatile unsigned int update_display_count;
extern volatile unsigned char update_display;
//extern unsigned int wheel_on_count;
//extern char wheels_on;

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
  update_display_count = 0;

  // Interrupts are disabled by default, enable them.
  enable_interrupts();

  //wheels_on = 0;
  //wheel_on_count = 0;
  //------------------------------------------------------------------------------
}
