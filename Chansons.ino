void BesoinOrdreChansons(int c)
{
  LOG_GENERAL("C:");
  LOG_GENERAL(c);
  LOG_GENERAL("\n");
  if(c==0)
  {
    DefinirOrdreChansons();
  }
}
void DefinirOrdreChansons()
{
  bool NotGood=false;
  
  LOG_GENERAL("ORDRE");
  LOG_GENERAL("\n");
  for(int i=0;i<NombreChansons;i++)
  {
    do
    {
      NotGood=false;
      OrdreChansons[i]=random(NombreChansons);
      if (i==0)
      {
        if(OrdreChansons[i]==OrdreChansons[NombreChansons-1])
        {
          NotGood=true;
        }
      }
      else
      {
        for(int j=0 ; j<i ; j++)
        {
          if(OrdreChansons[i]==OrdreChansons[j])
          {
            NotGood=true;
            break;
          }
        }
      }
    }while(NotGood);
    LOG_GENERAL("i:");
    LOG_GENERAL(i);
    LOG_GENERAL(" OrdreChansons:");
    LOG_GENERAL(OrdreChansons[i]);
    LOG_GENERAL("\n");
  }
  LOG_GENERAL("\n");
}

void JoueChanson(int Chanson,float FacteurVitesse, bool RandVitesse)
{
  int NombreNotes=SelectionChanson(Chanson);
  int myRand;
  float FactVit=FacteurVitesse;



  LOG_GENERAL("===============\n");
  LOG_GENERAL("= JoueChanson =\n");
  LOG_GENERAL("===============\n");
  
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
    PlayNote(MaChanson[0][n], MaChanson[1][n]/FactVit, MaChanson[2][n]/FactVit);
  }

  

  LOG_GENERAL("===================\n");
  LOG_GENERAL("= JoueChanson FIN =\n");
  LOG_GENERAL("===================\n");
}

//Returns the number of notes.
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
      RandomMin=130;
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
      pf=(float *)FurElise;
      NombreDeNotes = sizeof(FurElise[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 80;
      RandomMax = 130;
      return NombreDeNotes;
    case 4:
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
    case 5:
      pf=(float *)Menuet;
      NombreDeNotes = sizeof(Menuet[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 80;
      RandomMax = 135;
      return NombreDeNotes;
    case 6:
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
      RandomMax = 140;
      return NombreDeNotes;
    case 7:
      pf = (float*)Cantina;
      NombreDeNotes = sizeof(Cantina[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 85;
      RandomMax = 115;
      return NombreDeNotes;
    case 8:
      pf = (float*)Scatman1;
      NombreDeNotes = sizeof(Scatman1[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 85;
      RandomMax = 105;
      return NombreDeNotes;
    case 9:
      pf = (float*)Scatman2;
      NombreDeNotes = sizeof(Scatman2[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 85;
      RandomMax = 105;
      return NombreDeNotes;
    case 10:
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
    case 11:
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
    case 12:
      pf = (float*)ctd2;
      NombreDeNotes = sizeof(ctd2[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 100;
      RandomMax = 155;
      return NombreDeNotes;
    default:
      pf = (float*)Tetris;
      NombreDeNotes = sizeof(Tetris[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);
          }
      }
      RandomMin = 115;
      RandomMax = 160;
      return NombreDeNotes;
/*
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
case 5:
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
case 6:
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

*/

  }
}







