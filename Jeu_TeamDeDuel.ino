
#ifdef ENABLE_LOGGING
  #define LOG_TEAMDEDUEL(a) LOG_GAME(Game_id_TDD,a)
#else
  #define LOG_TEAMDEDUEL(a)
#endif
void TeamDeDuel()
{
  int LightDelay=350;
  int ForLightDelay=13;
  int Winner=-1;
  unsigned int Count[2]={0};
  float FactorTeamSize[2]={1,1};
  float BigTeamFactor=1.03;
  int Player[2];
  int InitPlayer[2];
  int Delta=0;
  float BaseScore=50;
  float Score=BaseScore;
  float ScoreFactor=1;
  float ScoreIncrease=0.27;
  unsigned long ScoreIncCounter=0;
  unsigned long ScoreIncreaseIter=750;
  bool HasReleased[2]={false};
  bool IsPressing[2]={false};
  int SoundTime=500;
  int Direction=1;
  int FraudulentTeam;
  int GameDelay=2;
  int Fails[nbj_max]={0};
  int FailsMax=0;
  int NumPlayersMaxFail=0;
  int FailPlayerSequenceId=-1;
  int PlayerFound=-1;
  int FailPlayer=-1;

  if (random(2)==0)
  {
    Direction=1;
  }
  else
  {
    Direction=-1;
  }
  
  
  AllocateTwoConsecutiveTeams();

  if (NbJoueursEq1>NbJoueursEq2)
  {
    FactorTeamSize[0]=((float)NbJoueursEq1/(float)NbJoueursEq2)*BigTeamFactor;
  }
  else if (NbJoueursEq2>NbJoueursEq1)
  {
    FactorTeamSize[1]=((float)NbJoueursEq2/(float)NbJoueursEq1)*BigTeamFactor;
  }

  LOG_TEAMDEDUEL("FactorTeamSize[0]:");
  LOG_TEAMDEDUEL(FactorTeamSize[0]);
  LOG_TEAMDEDUEL("\n");
  LOG_TEAMDEDUEL("FactorTeamSize[1]:");
  LOG_TEAMDEDUEL(FactorTeamSize[1]);
  LOG_TEAMDEDUEL("\n");
  
  
  if (!SkipLights)
  {
    MoveDEDUFlag(50);
    delay(500);
    
    for (int i=1; i<50; i++)
    {
      ActivateGreenLED(i);
      delay(ForLightDelay);
    }
    delay(LightDelay);
    for (int i=0; i<2; i++)
    {
      IlluminateTeamRedLights(0);
      ActivateGreenLED(0);
      delay(LightDelay);
      TurnOffAllRedLights();
      ActivateGreenLED(100);
      delay(LightDelay);
    }
    ControlAllLights(false,0,0);
    delay(2*LightDelay);
    for (int i=1; i<50; i++)
    {
      ActivateBlueLED(i);
      delay(ForLightDelay);
    }
    delay(LightDelay);
    for (int i=0; i<2; i++)
    {
      IlluminateTeamRedLights(1);
      ActivateBlueLED(0);
      delay(LightDelay);
      TurnOffAllRedLights();
      ActivateBlueLED(100);
      delay(LightDelay);
    }
    ControlAllLights(false,0,0);
  }

  //Remember first player from each team
  if (Direction==1)
  {
    InitPlayer[0]=0;
    InitPlayer[1]=NbJoueursEq1;
  }
  else
  {
    InitPlayer[0]=NbJoueursEq1-1;
    InitPlayer[1]=nbj_raw;
  }

  //Init Player to first player from each team
  Player[0]=InitPlayer[0];
  Player[1]=InitPlayer[1];

  ReadySound(SoundTime);
  ActivateRedLight(Player[0]);
  ActivateRedLight(Player[1]);
  
  do
  {
    ScoreIncCounter++;
    //Check for Fraudulent pressers
    for (int i=0; i<nbj; i++)
    {
      if (ReadPlayerInput(i) && (i!=Player[0] && i!=Player[1]))
      {
        FraudulentTeam=Equipes[i];
        LOG_TEAMDEDUEL("FraudulentTeam:");
        LOG_TEAMDEDUEL(FraudulentTeam);
        LOG_TEAMDEDUEL("\n");

        //Log fail if player not first.
        if (Player[FraudulentTeam]!=InitPlayer[FraudulentTeam])
        {
          Fails[i]++;
          LOG_TEAMDEDUEL("FailPlayer:");
          LOG_TEAMDEDUEL(i);
          LOG_TEAMDEDUEL("\n");
          LOG_TEAMDEDUEL("Fails[i]:");
          LOG_TEAMDEDUEL(Fails[i]);
          LOG_TEAMDEDUEL("\n");
          
          //Reset Player to first.
          DeactivateRedLight(Player[FraudulentTeam]);
          HasReleased[FraudulentTeam]=false;
          IsPressing[FraudulentTeam]=false;
  
          Player[FraudulentTeam]=InitPlayer[FraudulentTeam];
          
          ActivateRedLight(Player[FraudulentTeam]);
        }
        
      }
    }

    delay(GameDelay);
    
    for (int i=0; i<=1; i++)
    {
      //Check for Release
      if (!ReadPlayerInput(Player[i]) && !HasReleased[i])
      {
        HasReleased[i]=true;
      }

      //Check for Press after release
      if (ReadPlayerInput(Player[i]) && HasReleased[i])
      {
        IsPressing[i]=true;
      }

      //Check for release to switch to nextplayer
      if (!ReadPlayerInput(Player[i]) && IsPressing[i])
      {
        //Turn off light
        DeactivateRedLight(Player[i]);
        HasReleased[i]=false;
        IsPressing[i]=false;

        Player[i]=NextPlayerInTeam(Player[i],i,Direction);
        
        //Activate Next Player Light
        ActivateRedLight(Player[i]);

        //Increase score if back to first player for team.
        if (Player[i]==InitPlayer[i])
        {
          Count[i]++;
          LOG_TEAMDEDUEL("Score:");
          LOG_TEAMDEDUEL(Score);
          LOG_TEAMDEDUEL("\n");
        }
      }
    }

    delay(GameDelay);
    
    if (ScoreIncCounter>ScoreIncreaseIter && ScoreFactor<50)
    {
      ScoreIncCounter=0;
      ScoreFactor=ScoreFactor*(ScoreIncrease+1);
      LOG_TEAMDEDUEL("New Score Factor:");
      LOG_TEAMDEDUEL(ScoreFactor);
      LOG_TEAMDEDUEL("\n");
      LOG_TEAMDEDUEL("Score:");
      LOG_TEAMDEDUEL(Score);
      LOG_TEAMDEDUEL("\n");
    }

    //Update the score based on count for each team
    Score=BaseScore + ((float)Count[0]*FactorTeamSize[0]*ScoreFactor) - ((float)Count[1]*FactorTeamSize[1]*ScoreFactor);
    MoveDEDUFlag(Score);
    if (Score>50)
    {
      ActivateGreenLED((Score-50)/1.5);
      ActivateBlueLED(0);
    }
    else if (Score<50)
    {
      ActivateBlueLED((50-Score)/1.5);
      ActivateGreenLED(0);
    }
    else
    {
      ActivateBlueLED(0);
      ActivateGreenLED(0);
    }

    if (Score>99)
    {
      Winner=0;
    }
    else if (Score<1)
    {
      Winner=1;
    }
    
  }while(Winner==-1);

  LOG_TEAMDEDUEL("Winner:");
  LOG_TEAMDEDUEL(Winner);
  LOG_TEAMDEDUEL("\n");

  TurnOffAllRedLights();
  OneUp();
  
  if (Winner==0)
  {
    for (int i=1; i<50; i++)
    {
      ActivateGreenLED(i);
      delay(20);
    }
    delay(LightDelay);
    ActivateGreenLED(0);
    IlluminateTeamRedLights(Winner);
    for (int i=0; i<2; i++)
    {
      WinnerSound();
      delay(LightDelay);
      TurnOffAllRedLights();
      ActivateGreenLED(100);
      delay(LightDelay);
      IlluminateTeamRedLights(Winner);
      ActivateGreenLED(0);
    }
  }
  else
  {
    for (int i=1; i<50; i++)
    {
      ActivateBlueLED(i);
      delay(20);
    }
    delay(LightDelay);
    ActivateBlueLED(0);
    IlluminateTeamRedLights(Winner);
    for (int i=0; i<2; i++)
    {
      WinnerSound();
      delay(LightDelay);
      TurnOffAllRedLights();
      ActivateBlueLED(100);
      delay(LightDelay);
      IlluminateTeamRedLights(Winner);
      ActivateBlueLED(0);
    }
  }
  
  delay(300);
  MoveDEDUFlag(0);
  delay(500);
  ControlAllLights(false,0,0);
  delay(500);

  //Logic for HonteTransfer
  //Trouver le joueur avec le plus grand nombre de fail dans l'équipe perdante.
  for (int i=0; i<nbj; i++)
  {
    if (Fails[i]>FailsMax && Equipes[i]!=Winner)
    {
      FailsMax=Fails[i];
      NumPlayersMaxFail=1;
    }
    else if (Fails[i]==FailsMax && Equipes[i]!=Winner)
    {
      NumPlayersMaxFail++;
    }
    LOG_TEAMDEDUEL("[i]=");
    LOG_TEAMDEDUEL(i);
    LOG_TEAMDEDUEL(" - Fails[i]:");
    LOG_TEAMDEDUEL(Fails[i]);
    LOG_TEAMDEDUEL("\n");
  }
  LOG_TEAMDEDUEL("FailsMax:");
  LOG_TEAMDEDUEL(FailsMax);
  LOG_TEAMDEDUEL("\n");
  LOG_TEAMDEDUEL("NumPlayersMaxFail:");
  LOG_TEAMDEDUEL(NumPlayersMaxFail);
  LOG_TEAMDEDUEL("\n");

  
  if (FailsMax!=0)
  {
    FailPlayerSequenceId=random(NumPlayersMaxFail);
    LOG_TEAMDEDUEL("FailPlayerSequenceId:");
    LOG_TEAMDEDUEL(FailPlayerSequenceId);
    LOG_TEAMDEDUEL("\n");
    for (int i=0; i<nbj; i++)
    {
      if (Fails[i]==FailsMax && Equipes[i]!=Winner)
      {
        PlayerFound++;
      }
      if (PlayerFound==FailPlayerSequenceId)
      {
        FailPlayer=i;
        break;
      }
    }
    
    ///BRUIT ET TRANSFERT HONTE
    LooserSoundAndLight(FailPlayer,false);
    JoueurHonte=MarqueurHonte(FailPlayer,DelaiPetiteHonte);
    //Reset des jeux qui transferent la honte.
    ResetProbHonte();
    
    LOG_TEAMDEDUEL("Nouveau JoueurHonte:");
    LOG_TEAMDEDUEL(JoueurHonte);
    LOG_TEAMDEDUEL("\n");
    
  }
}


