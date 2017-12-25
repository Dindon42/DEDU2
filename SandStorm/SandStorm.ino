/*
 Darude - Sandstorm

 (c) Jordi Agricola 2014

 Speaker on port 8
 
 */
 #include "pitches.h"

// notes in the melody:

// note durations: 4 = quarter note, 8 = eighth note, etc.:
  
 int shortTone = 80;
 int longTone = 200;
 int standardDelay = 50;
 int delayBetweenBars = 50;
 int Tone_Pin = 52;

void setup() {

}

void loop() {
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, longTone); 
  delay(longTone);
  noTone(Tone_Pin);
  delay(delayBetweenBars);
  
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay); 
  tone(Tone_Pin,NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, longTone); 
  delay(longTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  
   tone(Tone_Pin,  NOTE_E4, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay); 
  tone(Tone_Pin,NOTE_E4, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_E4, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_E4, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_E4, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_E4, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_E4, longTone); 
  delay(longTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  
  
   tone(Tone_Pin,  NOTE_D4, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay); 
  tone(Tone_Pin,NOTE_D4, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_D4, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_D4, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_D4, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_D4, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_D4, longTone); 
  delay(longTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  
  tone(Tone_Pin, NOTE_A3, longTone);
  delay(longTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, longTone); 
  delay(longTone);
  noTone(Tone_Pin);
  delay(delayBetweenBars);
  
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay); 
  tone(Tone_Pin,NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, longTone); 
  delay(longTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  
  tone(Tone_Pin, NOTE_E4, longTone);
  delay(longTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, longTone); 
  delay(longTone);
  noTone(Tone_Pin);
  delay(delayBetweenBars);
  
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay); 
  tone(Tone_Pin,NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, shortTone);
  delay(shortTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  tone(Tone_Pin,  NOTE_B3, longTone); 
  delay(longTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  
  tone(Tone_Pin, NOTE_E4, longTone); 
  delay(longTone);
  noTone(Tone_Pin);
  delay(standardDelay);
  
}
