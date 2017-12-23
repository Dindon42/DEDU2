
// Credit:
// Midi to Arduino Converter
//     - Andy Tran (extramaster), 2015
// https://www.extramaster.net/tools/midiToArduino/
//
// Process:
// Midi -> Midi tracks -> Note mappings -> Frequency
//
// CC0

// Set this to be the pin that your buzzer resides in. (Note that you can only have one buzzer actively using the PWM signal at a time).
int Tone_Pin = 52;



void setup() {

}


void ChansonDEDU() {
  //Notes
  int Note_G3 = 196;
  int Note_A3 = 220;
  int Note_B3 = 247;
  int Note_C4 = 261;
  int Note_D4 = 294;

  tone(Tone_Pin, Note_B3, 200);
  delay(200);
  delay(150);
  tone(Tone_Pin, Note_B3, 200);
  delay(200);
  delay(150);
  tone(Tone_Pin, Note_B3, 200);
  delay(200);
  delay(150);
/*
g3
g3
g3
b3
b3
c4
c4
d4
b3
g3
g3
d4
b3
g3
c4
b3
a3
g3

*/

}

void loop() {
    // Play midi
    ChansonDEDU();
}


