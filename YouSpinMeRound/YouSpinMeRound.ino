
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
int tonePin = 52;
void setup() {

}

void YouSpinMeRound() {

    tone(tonePin, 184, 206.25);
    delay(312.5);
    delay(156.25);
    tone(tonePin, 184, 237.1875);
    delay(359.375);
    delay(109.375);
    tone(tonePin, 184, 239.765625);
    delay(363.28125);
    delay(105.46875);
    tone(tonePin, 220, 211.40625);
    delay(320.3125);
    delay(148.4375);
    tone(tonePin, 220, 216.5625);
    delay(328.125);
    delay(140.625);
    tone(tonePin, 164, 152.109375);
    delay(230.46875);
    delay(3.90625);
    tone(tonePin, 164, 152.109375);
    delay(230.46875);
    delay(3.90625);
    tone(tonePin, 246, 226.875);
    delay(343.75);
    delay(125.0);
    tone(tonePin, 184, 229.453125);
    delay(347.65625);
    delay(121.09375);
    tone(tonePin, 184, 97.96875);
    delay(148.4375);
    delay(85.9375);
    tone(tonePin, 184, 118.59375);
    delay(179.6875);
    delay(54.6875);
    tone(tonePin, 246, 116.015625);
    delay(175.78125);
    delay(58.59375);
    tone(tonePin, 246, 110.859375);
    delay(167.96875);
    delay(66.40625);
    tone(tonePin, 220, 108.28125);
    delay(164.0625);
    delay(70.3125);
    tone(tonePin, 220, 97.96875);
    delay(148.4375);
    delay(85.9375);
    tone(tonePin, 164, 239.765625);
    delay(363.28125);
    delay(105.46875);
    tone(tonePin, 164, 239.765625);
    delay(363.28125);
    delay(105.46875);
    tone(tonePin, 246, 239.765625);
    delay(363.28125);
    delay(105.46875);
    tone(tonePin, 220, 239.765625);
    delay(500.28125);

}

void loop() {
    // Play midi
    YouSpinMeRound();
}


