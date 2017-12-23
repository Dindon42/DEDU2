int Tone_Pin = 52;

void setup() {

  double facteur=2;
  ChansonDEDU(facteur);
}


void ChansonDEDU(double facteur) {
  //Notes
  int Note_G3 = 196;
  int Note_A3 = 220;
  int Note_B3 = 247;
  int Note_C4 = 261;
  int Note_D4 = 294;
  int Note_E4 = 330;
  int Note_F4 = 349;

  
  double joue_croche = 150 / facteur;
  double delay_croche = 100 / facteur;
  double joue_noire = 2*joue_croche;
  double delay_noire = 2*delay_croche;
  double joue_blanche = 4*joue_croche;
  double delay_blanche = 2*delay_croche;

/*
OLD g3,g3,g3,b3,b3,c4,c4,d4,b3,g3,g3,d4,b3,g3,c4,b3,a3,g3
NEW g3,g3,g3,b3,b3,c4,c4,F4,b3,g3,g3,d4,b3,g3,e4,d4,b3,c4

*/

  tone(Tone_Pin, Note_G3, joue_croche);
  delay(joue_croche);
  delay(delay_croche);
  tone(Tone_Pin, Note_G3, joue_croche);
  delay(joue_croche);
  delay(delay_noire);
  tone(Tone_Pin, Note_G3, joue_croche);
  delay(joue_croche);
  delay(delay_croche);
  tone(Tone_Pin, Note_B3, joue_noire);
  delay(joue_noire);
  delay(delay_noire);
  tone(Tone_Pin, Note_B3, joue_noire);
  delay(joue_noire);
  delay(delay_noire);
  tone(Tone_Pin, Note_C4, joue_noire);
  delay(joue_noire);
  delay(delay_noire);
  tone(Tone_Pin, Note_C4, joue_noire);
  delay(joue_noire);
  delay(delay_noire);
  tone(Tone_Pin, Note_F4, joue_blanche);
  delay(joue_blanche);
  delay(delay_blanche);
  tone(Tone_Pin, Note_B3, joue_croche);
  delay(joue_croche);
  delay(delay_croche);
  tone(Tone_Pin, Note_G3, joue_croche);
  delay(joue_croche);
  delay(delay_noire);
  tone(Tone_Pin, Note_G3, joue_croche);
  delay(joue_croche);
  delay(delay_croche);
  tone(Tone_Pin, Note_D4, joue_croche);
  delay(joue_croche);
  delay(delay_noire);
  tone(Tone_Pin, Note_B3, joue_croche);
  delay(joue_croche);
  delay(delay_croche);
  tone(Tone_Pin, Note_G3, joue_croche);
  delay(joue_croche);
  delay(delay_noire);
  delay(delay_noire);
  tone(Tone_Pin, Note_E4, joue_blanche);
  delay(joue_blanche);
  delay(delay_blanche);
  delay(delay_noire);
  tone(Tone_Pin, Note_D4, joue_croche);
  delay(joue_croche);
  delay(delay_noire);
  tone(Tone_Pin, Note_B3, joue_croche);
  delay(joue_croche);
  delay(delay_croche);
  tone(Tone_Pin, Note_C4, joue_blanche);
  delay(joue_blanche);
  delay(delay_blanche);

}

void loop() {
    // Play midi
}


