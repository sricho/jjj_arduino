#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

int song_count = 100;

void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

const byte MAXIMUM_INPUT_LENGTH = 140;
char input[MAXIMUM_INPUT_LENGTH+1] = {'\0'};
byte currentIndex = 0;

const byte MAXIMUM_SONG_COUNT_LENGTH = 3;
char count_input[MAXIMUM_SONG_COUNT_LENGTH+1] = {'\0'};
byte currentSongCountIndex = 0;

void setup() { 
  Serial.begin(9600);
  Timer1.initialize( 5000 );
  Timer1.attachInterrupt( ScanDMD );
  dmd.selectFont(Arial_Black_16);
  
} 

void loop() { 
  if ( Serial.available() ){
    char inByte;
    inByte = Serial.read();
    
    switch ( inByte ) {
       case 33:
         Serial.readBytesUntil(10, input, MAXIMUM_INPUT_LENGTH);
         print_input_string();
         break;
       case 37:
         clear_count_string();
         Serial.readBytesUntil(10, count_input, 3);
         print_song_count();
         break;
    }
  }
}

void print_song_count(int count) {
  dmd.clearScreen( true );
  song_count = atoi(count_input);
  sprintf(count_input, "%3d", song_count);
  Serial.println(count_input);
  dmd.drawString(1, 1, count_input, MAXIMUM_SONG_COUNT_LENGTH, GRAPHICS_NORMAL);
}

void print_input_string() {
  dmd.clearScreen( true );
 
  dmd.drawMarquee(input, 14, (32*DISPLAYS_ACROSS)-1, 0);
  long start=millis();
  long timer=start;
  boolean ret=false;
  while(!ret){
    if ((timer+90) < millis()) {
      ret=dmd.stepMarquee(-1,0);
      timer=millis();
    }
  }

  clear_input_string();
  print_song_count();
}

void clear_count_string() {
  for (byte i=0; i<=MAXIMUM_SONG_COUNT_LENGTH; i++){
    count_input[i] = '\0';
  }
  currentSongCountIndex = 0; 
}

void clear_input_string() {
  for (byte i=0; i<=MAXIMUM_INPUT_LENGTH; i++){
    input[i] = '\0';
  }
  currentIndex = 0; 
}