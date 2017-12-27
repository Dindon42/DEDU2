void OneUp()
{
  tone(Tone_Pin,NOTE_E6,125);
  delay(130);
  tone(Tone_Pin,NOTE_G6,125);
  delay(130);
  tone(Tone_Pin,NOTE_E7,125);
  delay(130);
  tone(Tone_Pin,NOTE_C7,125);
  delay(130);
  tone(Tone_Pin,NOTE_D7,125);
  delay(130);
  tone(Tone_Pin,NOTE_G7,125);
  delay(125);
  noTone(Tone_Pin);
}

void YouSpinMeRound(double facteur)
{
int Note_1 = 184;
int Note_2 = 220;
int Note_3 = 164;
int Note_4 = 246;

    tone(Tone_Pin, Note_1, 206.25 / facteur);
    delay(312.5 / facteur);
    delay(156.25 / facteur);
    tone(Tone_Pin, Note_1, 237.1875 / facteur);
    delay(359.375 / facteur);
    delay(109.375 / facteur);
    tone(Tone_Pin, Note_1, 239.765625 / facteur);
    delay(363.28125 / facteur);
    delay(105.46875 / facteur);
    tone(Tone_Pin, Note_2, 211.40625 / facteur);
    delay(320.3125 / facteur);
    delay(148.4375 / facteur);
    tone(Tone_Pin, Note_2, 216.5625 / facteur);
    delay(328.125 / facteur);
    delay(140.625 / facteur);
    tone(Tone_Pin, Note_3, 152.109375 / facteur);
    delay(230.46875 / facteur);
    delay(3.90625 / facteur);
    tone(Tone_Pin, Note_3, 152.109375 / facteur);
    delay(230.46875 / facteur);
    delay(3.90625 / facteur);
    tone(Tone_Pin, Note_4, 226.875 / facteur);
    delay(343.75 / facteur);
    delay(125.0 / facteur);
    tone(Tone_Pin, Note_1, 229.453125 / facteur);
    delay(347.65625 / facteur);
    delay(121.09375 / facteur);
    tone(Tone_Pin, Note_1, 97.96875 / facteur);
    delay(148.4375 / facteur);
    delay(85.9375 / facteur);
    tone(Tone_Pin, Note_1, 118.59375 / facteur);
    delay(179.6875 / facteur);
    delay(54.6875 / facteur);
    tone(Tone_Pin, Note_4, 116.015625 / facteur);
    delay(175.78125 / facteur);
    delay(58.59375 / facteur);
    tone(Tone_Pin, Note_4, 110.859375 / facteur);
    delay(167.96875 / facteur);
    delay(66.40625 / facteur);
    tone(Tone_Pin, Note_2, 108.28125 / facteur);
    delay(164.0625 / facteur);
    delay(70.3125 / facteur);
    tone(Tone_Pin, Note_2, 97.96875 / facteur);
    delay(148.4375 / facteur);
    delay(85.9375 / facteur);
    tone(Tone_Pin, Note_3, 239.765625 / facteur);
    delay(363.28125 / facteur);
    delay(105.46875 / facteur);
    tone(Tone_Pin, Note_3, 239.765625 / facteur);
    delay(363.28125 / facteur);
    delay(105.46875 / facteur);
    tone(Tone_Pin, Note_3, 239.765625 / facteur);
    delay(363.28125 / facteur);
    delay(105.46875 / facteur);
    tone(Tone_Pin, Note_2, 239.765625 / facteur);
    delay(500.28125 / facteur);
}

void ChansonDEDU(double facteur)
{
  //Notes
  int G3 = 196;
  int A3 = 220;
  int B3 = 247;
  int C4 = 261;
  int D4 = 294;
  int E4 = 330;
  int F4 = 349;

  int numNotes=18;

  double Base_Time = 150 / facteur;
  double Play_Time[3]={Base_Time,2*Base_Time,4*Base_Time};
  double Base_Time_W = 100 / facteur;
  double Wait_Time[4]={Base_Time_W,2*Base_Time_W,2*Base_Time_W,4*Base_Time_W};

  double Notes[numNotes]    =       {G3,  G3, G3, B3, B3, C4, C4, F4, B3, G3, G3, D4, B3, G3, E4, D4, B3, C4};
  int Play_Time_Index[numNotes] =   {0,   0,  0,  1,  1,  1,  1,  2,  0,  0,  0,  0,  0,  0,  2,  0,  0,  2};
  int Wait_Time_Index[numNotes] =   {0,   1,  0,  1,  1,  1,  1,  2,  0,  1,  0,  1,  0,  3,  3,  1,  0,  2};
  
  for (int i=0 ; i<numNotes ; i++)
  {
    PlayNote(Tone_Pin,Notes[i],Play_Time[Play_Time_Index[i]],Wait_Time[Wait_Time_Index[i]]);
  }
}
