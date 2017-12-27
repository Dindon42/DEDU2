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


//Returns the size to read;
int SelectionChanson(int Numero)
{
  
  int NombreDeNotes;
  
  //float MaChanson[3][100];
  float ChansonDEDU[3][18] = {
    {196,196,196,247,247,261,261,349,247,196,196,294,247,196,330,294,247,261},
    {150,150,150,300,300,300,300,600,150,150,150,150,150,150,600,150,150,600},
    {100,200,100,200,200,200,200,200,100,200,100,200,100,400,400,200,100,200},
    };
  float DeadOrAlive1[3][25] = {
    {293,293,293,293,293,293,261,233,261,233,261,233,261,261,233,261,233,261,233,261,293,293,293,174,195},
    {111.4,107.6,130.6,146,117.6,393.5,78.4,149.9,162.9,167.5,169.8,136,311.2,169.8,149.9,142.9,151.4,161.4,135.3,336.6,287.4,289.7,362.7,295.9,427.3},
    {110.8,114.6,91.6,85.5,236.1,132.4,143.8,72.4,59.3,79.7,57.9,76,112.8,71.8,73.3,79.3,81.9,65.5,75.9,114.3,125.5,154.7,100.2,130,87.5},
    };
  float DeadOrAlive2[3][19] = {
    {195,195,195,233,233,174,174,261,233,195,195,293,293,233,233,174,174,261,233},
    {254.2,261.8,248.6,277.8,292.4,105.6,163.9,240.3,300,116,141,125,148.6,133.3,168.7,225,328.5,300.7,200.7},
    {209.7,196.5,162.5,166.7,152.1,116.7,97.2,189.4,120.4,106.2,79.4,99.1,73.6,88.9,97.9,154.6,136.3,127.1,66.9},
    };

    
  switch(Numero)
  {
    case 0:
      /*
      Serial.println(sizeof(ChansonDEDU)/sizeof(ChansonDEDU[0]));
      Serial.println(sizeof(ChansonDEDU[0])/sizeof(float));
      */
      NombreDeNotes=sizeof(ChansonDEDU[0])/sizeof(float);
      
      for(int i=0; i<ParamChansons; i++)
      {
        for(int j=0; j<NombreDeNotes;j++)
        {
          MaChanson[i][j]=ChansonDEDU[i][j];
        }
      }
      RandomMin=100;
      RandomMax=325;
      return NombreDeNotes;
    case 1:
      NombreDeNotes = sizeof(DeadOrAlive1[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = DeadOrAlive1[i][j];
          }
      }
      RandomMin = 90;
      RandomMax = 135;
      return NombreDeNotes;
    case 2:
      NombreDeNotes = sizeof(DeadOrAlive2[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = DeadOrAlive2[i][j];
          }
      }
      RandomMin = 90;
      RandomMax = 160;
      return NombreDeNotes;
    default:
      return 0;
  }
}
      /*
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

*/









