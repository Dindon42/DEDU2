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
  DeactivateBlueLED();

  loop();
}

void MIN()
{
  int Sum0 = 0;
  int Sum1 = 0;
  
  int DeclaredLoosers[nbj_max];
  for (int i=0; i<=nbj_raw_max;i++)
  {
    DeclaredLoosers[i]=0;
  }
  
  //Init Setup: Mauve comme DQP1
  ActivateGreenLED(100);
  TurnOnAllRedLights();
  
  int RandTimer=5+random(15);

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
  CheckAllActive(nbj_raw);
  
  TurnOffAllRedLights();
  DeactivateGreenLED();
  delay(1000);

  for (int i=0; i<=nbj_raw ; i++)
  {
    if (InputState[i]==HIGH)
      Sum1++;
    else
      Sum0++;
  }

  //ALL LOSERS
  if(Sum0==0||Sum1==0)
  {
    for (int i=0; i<=nbj_raw;i++)
    {
      DeclaredLoosers[i]=1;
    }
  }
  else if(Sum0>Sum1) // Low Looses
  {
    for (int i=0; i<=nbj_raw;i++)
    {
      if (InputState[i]==LOW)
        DeclaredLoosers[i]=1;
    }
  }
  else if(Sum1>Sum0)//HIGH Looses
  {
    for (int i=0; i<=nbj_raw;i++)
    {
      if (InputState[i]==HIGH)
        DeclaredLoosers[i]=1;
    }
  }
  else//NoLoosers, start over.
  {
    ActivateGreenLED(100);
    OneUp();
    for(int i=0 ; i<4 ; i++)
    {
      DeactivateGreenLED();
      delay(500);
      ActivateGreenLED(100);
      delay(500);
    }
    
    DeactivateGreenLED();
    loop();
  }

  //Sound for loosers.
  for(int i=0 ; i<4 ; i++)
  {
    tone(Tone_Pin,800,500);
    for (int i=0; i<=nbj_raw;i++)
    {
      if (DeclaredLoosers[i]==1)
        ActivateRedLight(i);
    }
    delay(700);
    for (int i=0; i<=nbj_raw;i++)
    {
      if (DeclaredLoosers[i]==1)
        DeactivateRedLight(i);
    }
    delay(700);
  }
  loop();
}

void JeuChanson()
{
  int NombreNotes;
  int myRand;
  int ProchainJoueur;
  float FacteurVitesse;

  //Set White Lights
  ActivateBlueLED(100);
  ActivateGreenLED(100);
  TurnOnAllRedLights();
  //delay(5000);
  delay(500);
  
  NombreNotes=SelectionChanson(0);
  myRand= random(RandomMin,RandomMax);
  FacteurVitesse=myRand/100;

  
  Serial.print("NombreNotes:");
  Serial.println(NombreNotes);
  
  Serial.print("Fact:");
  Serial.println(FacteurVitesse);

  AllocateTwoTeams(nbj);

  //Répéter pour chaque équipe
  for (int e = 0; e<NbEquipes ; e++)
  {
    //OrdreJoueurs
    DefinirOrdreJoueurs(e,NombreNotes);
    
    
      
    TurnOffAllRedLights();
    DeactivateBlueLED();
    DeactivateGreenLED();
    //delay(2000);
    delay(500);
    
    Serial.println("EQUIPES:");
    for(int i=0 ; i<=nbj_raw ; i++)
    {
      if(Equipes[i]==e)
      {
        ActivateRedLight(i);
        delay(1000);
      }
      Serial.print("  ");
      Serial.print(Equipes[i]);
    }
    Serial.println();

    
    Serial.println("OrdreJoueurs:");
    for(int i=0;i<NombreNotes;i++)
    {
      Serial.print("  ");
      Serial.print(OrdreJoueurs[i]);
    }
    Serial.println("");
    
    
    delay(500);
    TurnOffAllRedLights();
    delay(1500);

    
    //Show the Player
    for(int n=0; n<NombreNotes; n++)
    {
      PlayNoteWithLight(Tone_Pin, MaChanson[0][n], MaChanson[1][n]/FacteurVitesse, MaChanson[2][n]/FacteurVitesse,OrdreJoueurs[n]);
    }

    
    TurnOffAllRedLights();
    delay(1500);
    for(int t=0; t<4 ; t++)
    {
      tone(Tone_Pin,800,10);
      delay(700);
    }
    delay(25000);
    JeuChanson();
  
    
    for(int i=0; i<NombreNotes; i++)
    {
      
    }
  
  }
  delay(2000);
}


























