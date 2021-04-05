#include "Arduino.h"
#include "ArduinoLowPower.h"
#include "noteFreq.h"

//Buzzer Pin
int buzzer = 6;

//Sets Random Time Sleep Settings
static long minTime = 7200000; // 2 Hours
static long maxTime = 10800000; // 3 Hours
volatile int sleepTime = 10; 

//Melody Settings
int tempo = 180;

//############################### Song Melody ###########################################
int melody[] = {

  // Nokia Ringtone
  // Score available at https://musescore.com/user/29944637/scores/5266155

  NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4,
  NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4,
  NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
  NOTE_A4, 2,
};
//#######################################################################################

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;


//Functions
void randomSleep();
void playMelody();

//Main
void setup() {
  // Pseudo random seed by calling unconnected pin
  randomSeed(analogRead(0));
}

void loop() {
  playMelody();
  randomSleep();
}

// Plays Melody
void playMelody(){
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }//for
}

// Randomizes Sleep time
void randomSleep(){
  sleepTime = random(minTime,maxTime);6
  for (int i = 0; (sleepTime-30000*i) > -1 ;i++){
    LowPower.sleep(sleepTime);
  }
  
}