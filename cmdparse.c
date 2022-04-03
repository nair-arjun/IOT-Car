#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"
#include "ports.h"

char instring[40];
char ipstring[40];
char* cmdstring;
char* ipdisp;
char cmdinterval[12];
char cmdinterval2[12];
int intervaltime;
int intervaltime2;
char* cmdstring2;
char multcmd;
extern char IOT_PB[LARGE_RING_SIZE];
extern char IOT_State;
extern char IOT_State2;
char* numloc;
char* numloc2;
int cmdstringcount = 0;
int cmdstringcount2 = 0;
extern char display_line[4][11];
extern int long_timer;
extern int fiftytimer;
extern char ONEDONE;


void splitCMD(void){
  
  ONEDONE = RESET_STATE;
  intervaltime = 0;
  intervaltime2 = 0;
  strcpy(instring, IOT_PB);
  cmdstring = strtok(instring, "^");
  cmdstring = strtok(NULL, "/r");
  if(strstr(cmdstring, "^")){
    cmdstring2 = strtok(cmdstring, "^");
    cmdstring2 = strtok(NULL, "/r");
    multcmd = YES;
  }
  numloc = cmdstring;
  numloc++;
  if(numloc != NULL){
    intervaltime = *numloc - '0';
  }
  numloc2 = cmdstring2;
  numloc2++;
  if(numloc2 != NULL){
    intervaltime2 = *numloc2 - '0';
  }
  //  convertIntervalJuan();
  //  convertIntervalDos();
  
  
  if(*cmdstring == FORWARD){
    IOT_State = FORWARD;
  }
  else if(*cmdstring == REVERSE){
    IOT_State = REVERSE;
  }
  else if(*cmdstring == RIGHT){
    IOT_State = RIGHT;
  }
  else if(*cmdstring == LEFT){
    IOT_State = LEFT;
  }
  else if(*cmdstring == LEFTFOHFIH){
    IOT_State = LEFTFOHFIH;
  }
  else if(*cmdstring == RIGHTFOHFIH){
    IOT_State = RIGHTFOHFIH;
  }
  else if(*cmdstring == DISPSTAGE){
    IOT_State = DISPSTAGE;
  }
  else if(*cmdstring == LINEFIND){
    IOT_State = LINEFIND;
  }
  
  if(*cmdstring2 == FORWARD){
    IOT_State2 = FORWARD;
  }
  else if(*cmdstring2 == REVERSE){
    IOT_State2 = REVERSE;
  }
  else if(*cmdstring2 == RIGHT){
    IOT_State2 = RIGHT;
  }
  else if(*cmdstring2 == LEFT){
    IOT_State2 = LEFT;
  }
  else if(*cmdstring2 == LEFTFOHFIH){
    IOT_State2 = LEFTFOHFIH;
  }
  else if(*cmdstring2 == RIGHTFOHFIH){
    IOT_State2 = RIGHTFOHFIH;
  }
  TB0CCR1 = TB0R + TB0CCR1_INTERVAL;
  TB0CCR2 = TB0R + TB0CCR2_INTERVAL;
  long_timer = 0;
  fiftytimer = 0;
  //  if(multcmd == YES){
  //    IOT_Drive1(intervaltime);
  //    TB0CCR2 = TB0R + TB0CCR2_INTERVAL;
  //    long_timer = 0;
  //    IOT_Drive2(intervaltime2);
  //  }
  //  else{
  //    IOT_Drive1(intervaltime);
  //  }
}

void displayIP(void){
  strcpy(display_line[2], "10.153.49.");
  strcpy(display_line[3], "    143   ");
  
  //  strcpy(ipstring, IOT_PB);
  //  ipdisp = strtok(ipstring, ",");
  //  ipdisp = strtok(NULL, "\r");
}

void convertIntervalJuan(void){
  if (cmdinterval[0] >= '0' && cmdinterval[0] <= '9')
  {
    intervaltime = cmdinterval[0] - '0';
  }
}
void convertIntervalDos(void){
  if (cmdinterval2[0] >= '0' && cmdinterval2[0] <= '9')
  {
    intervaltime2 = cmdinterval2[0] - '0';
  }
}