#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"
#include "ports.h"

extern volatile unsigned char update_display;
extern volatile unsigned char display_changed;
extern char display_line[4][11];
char brake_check;
extern char line_find;
volatile unsigned int timer_count;

void Check_Wheels(void){
  if(LEFT_FORWARD_SPEED && LEFT_REVERSE_SPEED){
    Wheels_Off();
    P6OUT |= RED_LED;
  }
  if(RIGHT_FORWARD_SPEED && RIGHT_REVERSE_SPEED){
    Wheels_Off();
    P6OUT |= RED_LED;
  }
}


void Wheels_Off(){
  
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM OFF
  
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Left Forward PWM OFF
  
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM OFF
  
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM OFF
  
  
}

void Forward_Move(int rspeed, int lspeed){
  
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM OFF
  RIGHT_FORWARD_SPEED = 18000; // P6.0 Right Forward PWM ON amount
  
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Left Forward PWM OFF
  LEFT_FORWARD_SPEED = 20000; // P6.1 Left Forward PWM ON amount
  
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM OFF
  
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM OFF
  

  
  return;
}

void Reverse_Move(int rspeed, int lspeed){
  
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM OFF
  
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Left Forward PWM OFF
  
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM OFF
  RIGHT_REVERSE_SPEED = rspeed; // P6.2 Right Reverse PWM ON amount
  
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM OFF
  LEFT_REVERSE_SPEED = lspeed; // P6.3 Left Reverse PWM ON amount


  
  return;
}

void Electronic_Braking(void){
Wheels_Off();
brake_check = RESET_STATE;
switch(timer_count){
case 0:
  Wheels_Off();
  break;
case 1:
  Reverse_Move(IOT_RSpeedR, IOT_RSpeedL);
case 2:
  brake_check = DONE;
  Wheels_Off();
  line_find = FIVE_SEC;
default:
  break;
}


}

void Turn_Clockwise(int rspeed, int lspeed){
Wheels_Off();

  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward PWM OFF
  
 
  LEFT_FORWARD_SPEED = lspeed; // P6.1 Left Forward PWM OFF
  
  RIGHT_REVERSE_SPEED = rspeed; // P6.2 Right Reverse PWM ON amount
  
  LEFT_REVERSE_SPEED = WHEEL_OFF; // P6.3 Left Reverse PWM OFF


  
  return;
}

void Reverse_Clockwise(int rspeed, int lspeed){
  Wheels_Off();

  RIGHT_FORWARD_SPEED = rspeed; // P6.0 Right Forward PWM OFF
  
 
  LEFT_FORWARD_SPEED = WHEEL_OFF; // P6.1 Left Forward PWM OFF
  
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse PWM ON amount
  
  LEFT_REVERSE_SPEED = lspeed; // P6.3 Left Reverse PWM OFF

  
  return;
}