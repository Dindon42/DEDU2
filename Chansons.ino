void JoueChanson(int Chanson,float FacteurVitesse, bool RandVitesse)
{
  int NombreNotes=SelectionChanson(Chanson);
  int myRand;
  float FactVit=FacteurVitesse;
  
  LOG_GENERAL("NombreNotes:");
  LOG_GENERAL(NombreNotes);
  LOG_GENERAL("\n");
  LOG_GENERAL("RandVitesse:");
  LOG_GENERAL(RandVitesse);
  LOG_GENERAL("\n");

  if(RandVitesse)
  {
    myRand= random(RandomMin,RandomMax);
    FactVit=(float) myRand/100;
  }
  
  
  LOG_GENERAL("FactVit:");
  LOG_GENERAL(FactVit);
  LOG_GENERAL("\n");
  
  for (int n=0 ; n<NombreNotes ; n++)
  {
    //PlayNote(int Tone_Pin, float Freq, float PlayTime, float WaitTime)
    PlayNote(Tone_Pin, MaChanson[0][n], MaChanson[1][n]/FactVit, MaChanson[2][n]/FactVit);
  }
}


void OneUp()
{
  tone(Tone_Pin,1319,125);
  delay(130);
  tone(Tone_Pin,1568,125);
  delay(130);
  tone(Tone_Pin,2637,125);
  delay(130);
  tone(Tone_Pin,2093,125);
  delay(130);
  tone(Tone_Pin,2349,125);
  delay(130);
  tone(Tone_Pin,3136,125);
  delay(125);
  noTone(Tone_Pin);
}

//Returns the size to read;
int SelectionChanson(int Numero)
{
  float *pf;
  
  int NombreDeNotes;
  switch(Numero)
  {
    case 0:
      pf=(float *)ChansonDEDU;
      NombreDeNotes=sizeof(ChansonDEDU[0])/sizeof(float);
      for(int i=0; i<ParamChansons; i++)
      {
        for(int j=0; j<NombreDeNotes;j++)
        {
          MaChanson[i][j]=pgm_read_float(pf+i*NombreDeNotes+j);
        }
      }
      RandomMin=100;
      RandomMax=250;
      return NombreDeNotes;
    case 1:
      pf=(float *)DeadOrAlive1;
      NombreDeNotes = sizeof(DeadOrAlive1[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 90;
      RandomMax = 135;
      return NombreDeNotes;
    case 2:
      pf=(float *)DeadOrAlive2;
      NombreDeNotes = sizeof(DeadOrAlive2[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 90;
      RandomMax = 160;
      return NombreDeNotes;
    case 3:
      pf=(float *)Darude;
      NombreDeNotes = sizeof(Darude[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 90;
      RandomMax = 130;
      return NombreDeNotes;
      
    case 4:
      pf=(float *)FurElise;
      NombreDeNotes = sizeof(FurElise[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 90;
      RandomMax = 130;
      return NombreDeNotes;
    case 5:
      pf=(float *)FF6Over;
      NombreDeNotes = sizeof(FF6Over[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 130;
      RandomMax = 180;
      return NombreDeNotes;
    case 6:
      pf=(float *)FF6BT;
      NombreDeNotes = sizeof(FF6BT[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 100;
      RandomMax = 150;
      return NombreDeNotes;
    case 7:
      pf=(float *)Dammit;
      NombreDeNotes = sizeof(Dammit[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 95;
      RandomMax = 125;
      return NombreDeNotes;
    case 8:
      pf=(float *)Menuet;
      NombreDeNotes = sizeof(Menuet[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 90;
      RandomMax = 150;
      return NombreDeNotes;
    case 9:
      pf = (float*)WhatIsLove;
      NombreDeNotes = sizeof(WhatIsLove[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 100;
      RandomMax = 185;
      return NombreDeNotes;
    case 10:
      pf = (float*)SWTheme;
      NombreDeNotes = sizeof(SWTheme[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 90;
      RandomMax = 150;
      return NombreDeNotes;
    case 11:
      pf = (float*)Cantina;
      NombreDeNotes = sizeof(Cantina[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 95;
      RandomMax = 125;
      return NombreDeNotes;
  case 12:
    pf = (float*)Scatman1;
    NombreDeNotes = sizeof(Scatman1[0]) / sizeof(float);
    for (int i = 0; i < ParamChansons; i++)
    {
        for (int j = 0; j < NombreDeNotes; j++)
        {
            MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
        }
    }
    RandomMin = 95;
    RandomMax = 120;
    return NombreDeNotes;
  case 13:
    pf = (float*)Scatman2;
    NombreDeNotes = sizeof(Scatman2[0]) / sizeof(float);
    for (int i = 0; i < ParamChansons; i++)
    {
        for (int j = 0; j < NombreDeNotes; j++)
        {
            MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
        }
    }
    RandomMin = 95;
    RandomMax = 120;
    return NombreDeNotes;
  case 14:
    pf = (float*)Boten2;
    NombreDeNotes = sizeof(Boten2[0]) / sizeof(float);
    for (int i = 0; i < ParamChansons; i++)
    {
        for (int j = 0; j < NombreDeNotes; j++)
        {
            MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
        }
    }
    RandomMin = 100;
    RandomMax = 150;
    return NombreDeNotes;
  case 15:
    pf = (float*)ctd1;
    NombreDeNotes = sizeof(ctd1[0]) / sizeof(float);
    for (int i = 0; i < ParamChansons; i++)
    {
        for (int j = 0; j < NombreDeNotes; j++)
        {
            MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
        }
    }
    RandomMin = 105;
    RandomMax = 155;
    return NombreDeNotes;
    
    default:
      return 0;
  }
}







