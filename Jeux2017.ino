void DQP2()
{
  int const NumIter_same=10;
  int const ScoreTol=3;
  
  int sum[nbj_raw_max];
  int Looser=-1;
  int LooserScore=-1;
  bool LoosersTied=false;

  int DeclaredWinners[nbj_max];
  for (int i=0; i<=nbj_raw_max;i++)
  {
    DeclaredWinners[i]=0;
  }
  
  int DeclaredLoosers[nbj_max];
  for (int i=0; i<=nbj_raw_max;i++)
  {
    DeclaredLoosers[i]=0;
  }
  
  int Results[nbj_max][NumIter_same];
  for (int i=0; i<=nbj_raw_max;i++)
  {
    for (int j=0; j<NumIter_same;j++)
    {
      Results[i][j]=0;
    }
  }
  
  bool LooserFound = false;
  int circular_counter=0;
  
  //Init Setup: Mauve comme DQP1
  ActivateBlueLED(100);
  TurnOnAllRedLights();

  int NumActiveOutputs=-1;
  
  do
  {
    ReadInputToggleOutput(nbj_raw);
    for (int i=0; i<=nbj_raw;i++)
    {
      if (DeclaredWinners[i]==1)
      {
        DeactivateRedLight(i);
      }
    }
    delay(15);
    NumActiveOutputs = CheckAllActiveOutputs(nbj_raw);
    
    for(int i=0;i<=nbj_raw;i++)
    {
      Results[i][circular_counter]=OutputState[i];
    }
    
    //Only one or 0 active, check results
    if(NumActiveOutputs==1 || NumActiveOutputs==0)
    {
      //Check each player's score
      for (int i=0; i<=nbj_raw;i++)
      {
        sum[i]=0; //Start at 0
        for (int j=0; j<NumIter_same;j++)
        {
          if(Results[i][j]==HIGH)
          {
            sum[i]++;
          }
        }
        if(sum[i]>LooserScore || OutputState[i])
        {
          Looser=i;
          LooserScore=sum[i];
          LoosersTied=false;
          LooserFound=true;
        }
        else if (sum[i]+ScoreTol>=LooserScore || OutputState[i]==HIGH)
        {
          LoosersTied=true;
          LooserFound=false;
        }
      }
      
      if(LoosersTied)
      {
        for (int i=0; i<=nbj_raw;i++)
        {
          if(sum[i]+ScoreTol>=LooserScore || OutputState[i]==HIGH)
          {
            ActivateRedLight(i);
          }
          else if(OutputState[i]==LOW)
          {
            DeclaredWinners[i]=1;
          }
        }
        LooserScore=0;
        LoosersTied=false;
      }
    }
    
    circular_counter++;
    if (circular_counter==NumIter_same)
    {
      circular_counter=0;
    }
  }while(LooserFound==false);
  
  //EndAll lights
  CheckAllActiveOutputs(nbj_raw);
  for (int i=0; i<=nbj_raw ; i++)
  {
    if (i == Looser || OutputState[i] == HIGH)
    {
      DeclaredLoosers[i]=1;
    }
  }
  ActivateBlueLED(10);
  TurnOffNonActivePlayerRedLights();

  for (int i = 1; i <= 80; i++)
  {
    Tone_Frequency = 2000 - 20 * i;
    tone(Tone_Pin, Tone_Frequency);
    delay(10);
  }
  noTone(Tone_Pin);

  //Identify the Loosers
  for (int e = 1; e <= 4; e++) {
    for (int i=0; i<=nbj_raw ; i++)
    {
      if(DeclaredLoosers[i]==1)
        ActivateRedLight(i);
    }
    delay(500);
    for (int i=0; i<=nbj_raw ; i++)
    {
      if(DeclaredLoosers[i]==1)
      DeactivateRedLight(i);
    }
    delay(500);
  }
}

void MIN()
{
  //Init Setup: Mauve comme DQP1
  ActivateGreenLED(100);
  TurnOnAllRedLights();
  
  int RandTimer=8+random(15);

  double TimeInterval = 1000;
  double TimeDelta=600/RandTimer;
  
  for(int i = 0;i < RandTimer;i++)
  {
    tone(Tone_Pin,250,10);
    delay(400);
    ActivateGreenLED(50);
    tone(Tone_Pin,700,10);
    delay(TimeInterval);
    ActivateGreenLED(100);
    

    TimeInterval-=TimeDelta;
  }

  

  delay(1000);
  MIN();
  
}

