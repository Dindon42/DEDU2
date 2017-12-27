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
  float Darude[3][39] = {
    {247,247,247,247,247,247,247,247,247,247,247,247,330,330,330,330,330,330,330,294,294,294,294,294,294,294,220,247,247,247,247,247,247,247,247,247,247,247,247},
    {80,80,80,80,200,80,80,80,80,80,80,200,80,80,80,80,80,80,200,80,80,80,80,80,80,200,200,80,80,80,80,200,80,80,80,80,80,80,200},
    {50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50},
    };
  float FurElise[3][35] = {
    {659,622,659,622,659,493,587,523,440,261,329,440,493,329,415,493,523,329,659,622,659,622,659,493,587,523,440,261,329,440,493,293,523,493,440},
    {106.4,100.8,92.5,92.5,78.5,108.9,125.4,106.4,174.8,114,119.1,121.6,144.4,114,125.4,100.1,184.9,13.9,100.1,106.4,88.7,88.7,125.4,129.2,114,115.3,241.9,125.4,114,100.1,241.9,119.1,107.7,111.5,342},
    {83.6,89.2,107.5,107.5,121.5,91.1,74.6,93.6,425.2,86,80.9,78.4,455.6,86,74.6,99.9,615.1,4.4,81.6,93.6,111.3,111.3,74.6,70.8,86,84.7,358.1,74.6,86,99.9,358.1,80.9,92.3,88.5,258},
    };
  float FF6Over[3][33] = {
    {415,466,493,622,493,466,415,466,311,415,466,493,622,493,466,415,466,622,493,554,622,739,622,554,493,554,369,493,466,415,493,466,415},
    {134.6,118.6,109.8,125.7,1962.1,127.5,127.5,595,1615,118.6,116.9,125.7,118.6,1962.1,134.6,134.6,628.6,1630.9,134.6,109.8,143.4,127.5,1970.9,127.5,127.5,586.1,1597.3,109.8,134.6,2319.8,109.8,134.6,2295},
    {65.4,81.4,90.2,74.3,437.9,72.5,72.5,205,385,81.4,83.1,74.3,81.4,437.9,65.4,65.4,171.4,369.1,65.4,90.2,56.6,72.5,429.1,72.5,72.5,213.9,402.7,90.2,65.4,480.2,90.2,65.4,530},
    };
  float FF6BT[3][18] = {
    {293,329,349,440,523,466,391,466,440,293,391,349,311,293,220,233,261,293},
    {112.7,73.6,73.6,93.6,121.5,93.6,100.8,92,259.9,252.7,259.9,135.9,113.5,728.5,121.5,114.3,113.5,841.2},
    {63.7,102.9,102.9,82.9,54.9,82.9,75.7,84.5,93.1,100.3,93.1,40.5,62.9,153.9,54.9,62.1,62.9,245.7},
    };
  float Dammit[3][40] = {
    {130,130,146,146,164,97,97,146,146,164,110,110,146,146,164,87,87,164,164,146,130,130,146,146,164,97,97,146,146,164,110,110,146,146,164,87,87,164,164,146},
    {185.8,83.6,185.8,83.6,185.8,185.8,83.6,185.8,83.6,185.8,185.8,83.6,185.8,83.6,185.8,185.8,83.6,185.8,83.6,185.8,185.8,83.6,185.8,83.6,185.8,185.8,83.6,185.8,83.6,185.8,185.8,83.6,185.8,83.6,185.8,185.8,83.6,185.8,83.6,185.8},
    {89.4,54,89.4,54,89.4,89.4,54,89.4,54,89.4,89.4,54,89.4,54,89.4,89.4,54,89.4,54,89.4,89.4,54,89.4,54,89.4,89.4,54,89.4,54,89.4,89.4,54,89.4,54,89.4,89.4,54,89.4,54,143.6},
    };
  float Menuet[3][32] = {
    {587,391,440,493,523,587,391,391,659,523,587,659,739,783,391,391,523,587,523,493,440,493,523,493,440,391,440,493,440,391,369,391},
    {200.2,75.6,121.6,121.6,113.3,255,141.7,101.5,237.3,122.8,112.2,114.5,114.5,233.7,94.4,103.9,325,65.9,69.7,109.8,120.4,249.1,116.9,109.8,113.3,120.4,260.9,139.3,120.4,125.1,120.4,622.2},
    {155.9,35.6,45.1,45.1,53.3,78.3,191.7,231.8,96,43.9,54.5,52.2,52.2,99.6,238.9,218.4,85.8,50.7,44.2,56.9,46.2,84.2,49.8,56.9,53.3,46.2,72.4,27.4,46.2,41.5,46.2,210.7},
    };
    
  switch(Numero)
  {
    case 0:
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
    case 3:
      NombreDeNotes = sizeof(Darude[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = Darude[i][j];
          }
      }
      RandomMin = 90;
      RandomMax = 130;
      return NombreDeNotes;
      
    case 4:
      NombreDeNotes = sizeof(FurElise[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = FurElise[i][j];
          }
      }
      RandomMin = 90;
      RandomMax = 130;
      return NombreDeNotes;
    case 5:
      NombreDeNotes = sizeof(FF6Over[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = FF6Over[i][j];
          }
      }
      RandomMin = 120;
      RandomMax = 180;
      return NombreDeNotes;
    case 6:
      NombreDeNotes = sizeof(FF6BT[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = FF6BT[i][j];
          }
      }
      RandomMin = 100;
      RandomMax = 150;
      return NombreDeNotes;
    case 7:
      NombreDeNotes = sizeof(Dammit[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = Dammit[i][j];
          }
      }
      RandomMin = 95;
      RandomMax = 125;
      return NombreDeNotes;
    case 8:
      NombreDeNotes = sizeof(Menuet[0]) / sizeof(float);
      for (int i = 0; i < ParamChansons; i++)
      {
          for (int j = 0; j < NombreDeNotes; j++)
          {
              MaChanson[i][j] = Menuet[i][j];
          }
      }
      RandomMin = 100;
      RandomMax = 200;
      return NombreDeNotes;
    default:
      return 0;
  }
}







