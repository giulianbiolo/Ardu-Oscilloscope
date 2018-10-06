//****************************************
// Three color 5msps ext AtoD Scope
// By Bob Davis
// UTFT_(C)2012 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// Switches on D12 & D13 determine sweep speed and trigger level
//*******************************************

#include <TVout.h>
#include <fontALL.h>
TVout TV;
// UTFT myGLCD(ILI9325C,8,9,10,11); // 8 - 11
int Input=0;
byte Sample[320];
byte OldSample[320];
int StartSample=0;
int EndSample=0;
int MaxSample=0;
int MinSample=0;
int mode=0;
int dTime=1;
int Trigger=10;
int SampleSize=0;
int SampleTime=0;

void DrawMarkers(){
  TV.draw_line(0, 0, 0, 96, WHITE);
  TV.draw_line(23, 0, 23, 96, WHITE);
  TV.draw_line(45, 0, 45, 96, WHITE);
  TV.draw_line(68, 0, 68, 96, WHITE);
  TV.draw_line(90, 0, 90, 96, WHITE);
  TV.draw_line(120, 0, 120, 96, WHITE);
  TV.draw_line(0, 0, 120, 0, WHITE);
  TV.draw_line(0, 24, 120, 24, WHITE);
  TV.draw_line(0, 48, 120, 48, WHITE);
  TV.draw_line(0, 72, 120, 72, WHITE);
  TV.draw_line(0, 96, 120, 96, WHITE);
}

void setup() {
  TV.begin(PAL, 128, 96);
  pinMode(12, INPUT);
  digitalWrite(12, HIGH);
  pinMode(13, INPUT);
  digitalWrite(13, HIGH);
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  pinMode(18, INPUT);
  pinMode(19, INPUT);
}

void loop() {
// Set the background color(Red, Green, Blue)
  char buf[12]; 
  while(1) {
    DrawMarkers();
    if (digitalRead(13) == 0) mode++;
    if (mode > 10) mode=0;
// Select delay times for scan modes
    if (mode == 0) dTime=0;
    if (mode == 1) dTime=0;
    if (mode == 2) dTime=1;
    if (mode == 3) dTime=2;
    if (mode == 4) dTime=5;
    if (mode == 5) dTime=10;
    if (mode == 6) dTime=20;
    if (mode == 7) dTime=50;
    if (mode == 8) dTime=100;
    if (mode == 9) dTime=200;
    if (mode == 10) dTime=500;
// Select trigger level
    if (digitalRead(12) == 0) Trigger=Trigger+10;
    if (Trigger > 50) Trigger=0;
// Wait for input to be greater than trigger
  while (Input < Trigger){
    Input = PINC;
    }

// Collect the analog data into an array
  if (mode == 0) {
// Read analog port as a parallel port no loop
  StartSample = micros();
    Sample[0]=PINC;
    Sample[1]=PINC;     Sample[2]=PINC;    Sample[3]=PINC;    
    Sample[4]=PINC;     Sample[5]=PINC;    Sample[6]=PINC;
    Sample[7]=PINC;     Sample[8]=PINC;    Sample[9]=PINC;
    Sample[10]=PINC;    Sample[11]=PINC;    Sample[12]=PINC;
    Sample[13]=PINC;    Sample[14]=PINC;    Sample[15]=PINC;
    Sample[16]=PINC;    Sample[17]=PINC;    Sample[18]=PINC;
    Sample[19]=PINC;    Sample[20]=PINC;    Sample[21]=PINC;
    Sample[22]=PINC;    Sample[23]=PINC;    Sample[24]=PINC;
    Sample[25]=PINC;    Sample[26]=PINC;    Sample[27]=PINC;
    Sample[28]=PINC;    Sample[29]=PINC;    Sample[30]=PINC;
    Sample[31]=PINC;    Sample[32]=PINC;    Sample[33]=PINC;
    Sample[34]=PINC;    Sample[35]=PINC;    Sample[36]=PINC;
    Sample[37]=PINC;    Sample[38]=PINC;    Sample[39]=PINC;
    Sample[40]=PINC;    Sample[41]=PINC;    Sample[42]=PINC;
    Sample[43]=PINC;    Sample[44]=PINC;    Sample[45]=PINC;
    Sample[46]=PINC;    Sample[47]=PINC;    Sample[48]=PINC;
    Sample[49]=PINC;    Sample[50]=PINC;    Sample[51]=PINC;
    Sample[52]=PINC;    Sample[53]=PINC;    Sample[54]=PINC;
    Sample[55]=PINC;    Sample[56]=PINC;    Sample[57]=PINC;
    Sample[58]=PINC;    Sample[59]=PINC;    Sample[60]=PINC;
    Sample[61]=PINC;    Sample[62]=PINC;    Sample[63]=PINC;
    Sample[64]=PINC;    Sample[65]=PINC;    Sample[66]=PINC;
    Sample[67]=PINC;    Sample[68]=PINC;    Sample[69]=PINC;
    Sample[70]=PINC;    Sample[71]=PINC;    Sample[72]=PINC;
    Sample[73]=PINC;    Sample[74]=PINC;    Sample[75]=PINC;
    Sample[76]=PINC;    Sample[77]=PINC;    Sample[78]=PINC;
    Sample[79]=PINC;    Sample[80]=PINC;    Sample[81]=PINC;
    Sample[82]=PINC;    Sample[83]=PINC;    Sample[84]=PINC;
    Sample[85]=PINC;    Sample[86]=PINC;    Sample[87]=PINC;
    Sample[88]=PINC;    Sample[89]=PINC;    Sample[90]=PINC;
    Sample[91]=PINC;    Sample[92]=PINC;    Sample[93]=PINC;
    Sample[94]=PINC;    Sample[95]=PINC;    Sample[96]=PINC;
    Sample[97]=PINC;    Sample[98]=PINC;    Sample[99]=PINC;
    Sample[100]=PINC;
  EndSample = micros();
  }
  if (mode == 1) {
// Read analog port as a parallel port no delay
  StartSample = micros();
  for(int xpos=0; xpos<100; xpos++) {
    Sample[xpos]=PINC;
  } 
  EndSample = micros();
  }
  if (mode >= 2) {
// Read analog port as a parallel port variable delay
  StartSample = micros();
  for(int xpos=0; xpos<100; xpos++) {
    Sample[xpos]=PINC;
    delayMicroseconds(dTime);
  } 
  EndSample = micros();
  }

// Display the collected analog data from array
  for(int xpos=0; xpos<99; xpos++) {
// Erase the old stuff
    TV.clear_screen();
    TV.draw_line((xpos+1), (96*(255-OldSample[xpos+1]*4))/240, xpos+2, (96*(255-OldSample[xpos+2]*4))/240, WHITE);
    if (xpos==0) TV.draw_line((120*(xpos+1))/320, 1, (120*(xpos+1))/320, 96); // myGLCD.drawLine (xpos+1, 1, xpos+1, 239);
// Draw the new data
    TV.draw_line(xpos, (96*(255-Sample[xpos]*4))/240, xpos+1, (96*(255-Sample[xpos+1]*4))/240);
  }  

//  Determine sample voltage peak to peak
  MaxSample = Sample[100];
  MinSample = Sample[100];
  for(int xpos=0; xpos<100; xpos++) {
    OldSample[xpos] = Sample[xpos];  
    if (Sample[xpos] > MaxSample) MaxSample=Sample[xpos];
    if (Sample[xpos] < MinSample) MinSample=Sample[xpos];
    }
// display the sample time, delay time and trigger level  
  SampleTime=EndSample-StartSample;
  TV.select_font(font4x6);
  TV.print(90, 4, "uSec.");
 // TV.print(90, 12, "     ");
  TV.print(90, 12, itoa(SampleTime, buf, 10));
  TV.print(90, 28, "Delay");
 // TV.print(90, 36, "     ");
  TV.print(90, 36, itoa(dTime, buf, 10));
  TV.print(90, 52, "Trig.");
  TV.print(90, 60, itoa(Trigger, buf, 10));
// Range of 0 to 64 * 78 = 4992 mV
  SampleSize=(MaxSample-MinSample)*78;
  TV.print(90, 76, "mVolt");
  TV.print(90, 84, itoa(SampleSize, buf, 10));
    } 
}
