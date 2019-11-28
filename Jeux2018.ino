#ifdef ENABLE_LOGGING
  #define LOG_PPV(a) LOG_GAME(Game_id_PPV,a)
#else
  #define LOG_PPV(a)
#endif
void PPV()
{
  
  //TUNABLES
  int WinNumPress=6;
  //END TUNABLES
  int Winner=-1;
  unsigned long Game_Timer=0;
  unsigned long PreviousTotalPressTime[nbj_max]={0};
  unsigned long PressTime[nbj_max]={0};
  unsigned long TotalPressTime;
  int NumPress[nbj_max]={0};
  bool RecordPress;
  int MinimumDiff=25;
  bool PreviousState[nbj_max]={false};
  bool CurrentState;

  WaitForAllNonActive(nbj_raw_max);

  //LUMIERES
  //Paires de lumières rouges qui avance
  ControlAllLights(false,0,0);
  for(int i=0; i<5; i++)
  {
    for(int j=0; j<10; j++)
    {
      if(j%5==i)
      {
        ActivateRedLight(j);
      }
    }
    delay(300);
    TurnOffAllRedLights();
  }
  delay(300);
  //Lumière réplique du jeu
  const int LightDelayDecrement = 75;
  const int LightDelayMin=150;
  int LightDelay = LightDelayMin+WinNumPress*LightDelayDecrement;
  for(int i=0; i<WinNumPress; i++)
  {
    tone(Tone_Pin,400,20);
    TurnOnAllRedLights();
    delay(LightDelay);
    LightDelay-=LightDelayDecrement;
    tone(Tone_Pin,200,20);
    TurnOffAllRedLights();
    delay(150);
  }
  delay(500);
  ControlAllLights(false,0,0);
  delay(1000);
  ControlAllLights(true,0,0);
  ReadySound(500);
  //END LUMIERES
  
  //MAIN GAME
  do
  {
    for (int i=0 ; i<nbj ; i++)
    {
      CurrentState=ReadPlayerInput(i);
      //Record the START PRESS TIMER on trans from LOW to HIGH
      if(!PreviousState[i] && CurrentState)
      {
        PressTime[i]=Game_Timer;
        LOG_PPV("i:");
        LOG_PPV(i);
        LOG_PPV(" PressTime[i]");
        LOG_PPV(PressTime[i]);
        LOG_PPV("\n");
        
        DeactivateRedLight(i);
      }
      //Record the END PRESS TIMER on trans from HIGH to LOW
      else if(PreviousState[i] && !CurrentState)
      {
        RecordPress=true;
        TotalPressTime=Game_Timer-PressTime[i];

        
        LOG_PPV("i:");
        LOG_PPV(i);
        LOG_PPV(" TotalPressTime:");
        LOG_PPV(TotalPressTime);
        LOG_PPV("\n");
        
        if(NumPress[i]!=0)
        {
          //Reset Sequence if this press time is greater than the previous
          if(TotalPressTime+MinimumDiff>=PreviousTotalPressTime[i])
          {
            
            LOG_PPV("i:");
            LOG_PPV(i);
            LOG_PPV(" ResetSeq:");
            LOG_PPV(TotalPressTime);
            LOG_PPV(" vs ");
            LOG_PPV(PreviousTotalPressTime[i]);
            LOG_PPV("\n");
            
            RecordPress=false;
            NumPress[i]=0;
            ActivateRedLight(i);
          }
        }
        
        if(RecordPress)
        {
          LOG_PPV("i:");
          LOG_PPV(i);
          LOG_PPV(" RecordPress:");
          LOG_PPV(NumPress[i]);
          LOG_PPV("\n");
          PreviousTotalPressTime[i]=TotalPressTime;
          NumPress[i]++;
        }
      }
      PreviousState[i]=CurrentState;
      
      //Update Winner
      if(NumPress[i]>=WinNumPress)
      {
        Winner=i;
        LOG_PPV("i:");
        LOG_PPV(i);
        LOG_PPV(" WINNER FOUND:");
        LOG_PPV(Winner);
        LOG_PPV("\n");
      }
    }
    
    //Increment GameTime
    delay(1);
    Game_Timer++;
    
  }while(Winner==-1);

  
  TurnOffAllLights();
  delay(500);

  //Identify winner
  WinnerSoundAndLight(Winner);

  //Reset
  delay(700);
  TurnOffAllLights();
  delay(25);
}


#ifdef ENABLE_LOGGING
  #define LOG_PB(a) LOG_GAME(Game_id_PB,a)
#else
  #define LOG_PB(a)
#endif
void PressBattle()
{ 
  //TUNABLES
  #define GAME_TIME_MIN 2542
  #define GAME_TIME_MAX 4542
  //END TUNABLES
  #define SOUND_TIME 500
  #define GAME_DELAY 5
  int Winner=-1;
  int Game_Time = (random(GAME_TIME_MIN,GAME_TIME_MAX)/GAME_DELAY);
  unsigned long Game_Timer=0;
  int ClicCount[nbj_max]={0};
  bool PreviousState[nbj_max]={false};
  int FlagPerc=100;
  bool PlayersTied;
  int PlayerState[nbj_max]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  int MaxClic;
  int NumPlayersMaxClic;
  int PotentialWinner;
  
  LOG_PB("PRESS BATTLE!\n");
  LOG_PB("Game_Time:");
  LOG_PB(Game_Time);
  LOG_PB("\n");
  
  WaitForAllNonActive(nbj_raw_max);
  
  //LIGHT SETUP
  MoveDEDUFlag(0);
  delay(200);
  int NumLights=random(10,12);
  int FlagIncrement=100/(float)NumLights;
  for (int i=0; i<NumLights ; i++)
  {
    tone(Tone_Pin,400,20);
    TurnOnAllRedLights();
    delay(random(75,100));
    IncrementDEDUFlag(FlagIncrement);
    TurnOffAllRedLights();
    delay(random(50,125));
  }
  MoveDEDUFlag(FlagPerc);
  ReadySound(SOUND_TIME);
  //LIGHT SETUP END

  
  //Prepare
  for(int i=0 ; i<nbj ; i++)
  {
    PlayerState[i]=0;
  }

  //MAIN GAME
  do
  {
    if(Game_Timer<Game_Time)
    {
      Game_Timer++;
      FlagPerc=(float)(Game_Time-Game_Timer)/(float)Game_Time*100; 
    }
    else
    {
      FlagPerc=0;
    }   
    MoveDEDUFlag(FlagPerc);

    for (int i=0 ; i<nbj ; i++)
    {
      if(!PreviousState[i] && ReadPlayerInput(i))
      {
        ClicCount[i]++;
        LOG_PB("i:");
        LOG_PB(i);
        LOG_PB("  count:");
        LOG_PB(ClicCount[i]);
        LOG_PB("\n");
      }
      PreviousState[i]=ReadPlayerInput(i);
    }

    //Check who's in front
    PlayersTied=false;
    MaxClic=0;
    NumPlayersMaxClic=0;
    PotentialWinner=-1;
    //First Check What's the max number of clics.
    for (int i=0 ; i<nbj ; i++)
    {
      if(ClicCount[i]>MaxClic)
      {
        MaxClic=ClicCount[i];
      }
    }
    //Then identify players that have the max cliccount.
    for (int i=0 ; i<nbj ; i++)
    {
      if(ClicCount[i]==MaxClic)
      {
        if(PotentialWinner!=-1)
        {
          PlayersTied=true;
        }
        PotentialWinner=i;
        ActivateRedLight(i);
      }
      else
      {
        DeactivateRedLight(i);
      }
    }
    
    //Check Win Condition if Game Timer is greater than Game_Time and no ties and a potential winner;
    if(Game_Timer>=Game_Time && !PlayersTied && PotentialWinner!=-1)
    {
      Winner=PotentialWinner;
    }
    
    delay(GAME_DELAY);
  }while(Winner==-1);
  
  //WINNER
  delay(500);

  TurnOffAllLights();

  //Identify winner
  WinnerSoundAndLight(Winner);
  
  //Reset
  delay(700);
  MoveDEDUFlag(0);
  TurnOffAllLights();
  delay(25);
}

#ifdef ENABLE_LOGGING
  #define LOG_PQR(a) LOG_GAME(Game_id_PQR,a)
#else
  #define LOG_PQR(a)
#endif
void PQR()
{
  unsigned long GameCounter=0;
  unsigned long GreenCounter=0;
  bool InitialGreenComplete=false;
  int GreenTransMax=500;
  int ReacTime;
  int ReacTimeMin=542;
  int ReacTimeMax=1542;
  int Winner=-1;
  int PercB;
  int PercG;
  int MinB=1;
  int MinG=5;
  int LightIntB=3;
  int LightIntG=42;
  int NumActive;
  int PrevNumActive=-1;
  int WinCondition=-1;
  bool PreviousState[nbj_max];
  int PlayersInGame[nbj_max]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  int StateChanges[nbj_max]={0};
  int ChangeThr=3;
  int PlayersActive;
  bool TriggerEndGame=false;

  LOG_PQR("PREMIER QUI RELACHE\n");
  
  //Init Based on number of players
  for (int i=0; i<=nbj_raw ;i++)
  {
    PlayersInGame[i]=1;
  }

  LOG_PQR("PlayersInGame!\n");
  for (int i=0; i<=nbj_raw_max ;i++)
  {
    LOG_PQR("i:");
    LOG_PQR(i);
    LOG_PQR("  ");
    LOG_PQR(PlayersInGame[i]);
    LOG_PQR("\n");
  }

  ActivateGreenLED(MinG);
  ActivateBlueLED(MinB);
  
  do
  {
    if(!InitialGreenComplete)
    {
      PercG = ((float)GreenCounter/(float)GreenTransMax)*LightIntG;
      PercB = ((float)GreenCounter/(float)GreenTransMax)*LightIntB;
      if(PercG<MinG) PercG=MinG;
      if(PercB<MinB) PercB=MinB;
      ActivateGreenLED(PercG);
      ActivateBlueLED(PercB);
    }
    if(GreenCounter>GreenTransMax && !InitialGreenComplete)
    {
      LOG_PQR("GreenTransComplete\n");
      LOG_PQR("GameCounter:");
      LOG_PQR(GameCounter);
      LOG_PQR("\n");
      InitialGreenComplete=true;
      GameCounter=0;
      LOG_PQR("GameCounter:");
      LOG_PQR(GameCounter);
      LOG_PQR("\n");
    }

    //Record States to compare win condition.
    for(int i=0;i<nbj;i++)
    {
      PreviousState[i]=InputState[i];
    }

    
    ActivateGreenLED(PercG);
    ActivateBlueLED(PercB);
    
    NumActive=0;
    for (int i=0; i<=nbj_raw ;i++)
    {
      if(PlayersInGame[i]==1)
      {
        if (ReadPlayerInput(i))
        {
          NumActive++;
          ActivateRedLight(i);
          InputState[i]=true;
          OutputState[i]=true;
        }
        else
        {
          DeactivateRedLight(i);
          InputState[i]=false;
          OutputState[i]=false;
        }
      }
      
      if(PreviousState[i]!=InputState[i])
      {
        StateChanges[i]++;
      }
      
      if(StateChanges[i]>ChangeThr && !TriggerEndGame)
      {
        LOG_PQR("You're OUT\n");
        PlayersInGame[i]=0;
        DeactivateRedLight(i);
        StateChanges[i]=0;
      }
    }

    //Check if everyone is a spammer.
    if(!TriggerEndGame)
    {
      PlayersActive=0;
      for (int i=0; i<=nbj_raw ;i++)
      {
        if(PlayersInGame[i]==1)
        {
          PlayersActive++;
        }
      }
      
      //Reset Counts if everyone is a dumbass.
      if(PlayersActive==0)
      {
        LOG_PQR("RESET EVERYONE\n");
        for (int i=0; i<=nbj_raw ;i++)
        {
          PlayersInGame[i]=1;
          StateChanges[i]=0;
        }
      }
    }
    
    if(NumActive==WinCondition && TriggerEndGame)
    {
      for(int i=0;i<nbj;i++)
      {
        if(PreviousState[i] && !InputState[i] && PlayersInGame[i]==1)
        {
          Winner=i;
          break;
        }
      }
    }
    else if(!TriggerEndGame)
    {
      if(NumActive==0)
      {
        //LOG_PQR("ResetGameCounter\n");
        GameCounter=0;
      }
      if(NumActive>=1 && NumActive!=PrevNumActive)
      {
        LOG_PQR("WinCondition Change\n");
        WinCondition=NumActive-1;
        LOG_PQR("WinCondition:");
        LOG_PQR(WinCondition);
        LOG_PQR("\n");
        PrevNumActive=NumActive;
        GameCounter=0;
        
        ReacTime=random(ReacTimeMin,ReacTimeMax);
        LOG_PQR("ReacTime:");
        LOG_PQR(ReacTime);
        LOG_PQR("\n");
      }
      
      if(GameCounter>ReacTime && NumActive>=1)
      {
        //Cancel Non-Pressing players
        for (int i=0; i<=nbj_raw ;i++)
        {
          if(!InputState[i])
          {
            PlayersInGame[i]=0;
          }
        }
        
        LOG_PQR("TRIGGER END!\n");
        LOG_PQR("PlayersInGame!\n");
        for (int i=0; i<=nbj_raw_max ;i++)
        {
          LOG_PQR("i:");
          LOG_PQR(i);
          LOG_PQR("  ");
          LOG_PQR(PlayersInGame[i]);
          LOG_PQR("\n");
        }
        
        TriggerEndGame=true;
        PercG=0;
        PercB=0;
      }
    }
    GameCounter++;
    if (!InitialGreenComplete)
    {
      GreenCounter++;
    }
    if(GameCounter>90000)
    {
      LOG_PQR("ResetGameCounter\n");
      GameCounter=0;
    }
  delay(1);
  }while(Winner==-1);

  delay(500);

  TurnOffAllLights();

  //Identify winner
  WinnerSoundAndLight(Winner);
  delay(700);
  TurnOffAllLights();
  delay(25);
}

#ifdef ENABLE_LOGGING
  #define LOG_TOURVIC(a) LOG_GAME(Game_id_TV,a)
#else
  #define LOG_TOURVIC(a)
#endif
void TourVic()
{
  int LightDelay=22+nbj;
  int LightDelayIncrement=1;
  int IncrementProb=10-nbj/2;
  int CurrentCounter=0;
  int LastPlayer=random(nbj);
  int CurrentPlayer=0;
  int DirectionNextPlayer=0;
  int Winner=-1;
  bool ReadyToPress=false;
  bool PlayerIsPressing=false;
  bool ReadytoIncreaseIncrement=false;
  bool IgnorePresses=false;
  bool PlayerHasWon=false;
  int SpamCheckDelay=55;

  if(random(2)==0)
  {
    DirectionNextPlayer=1;
  }
  else
  {
    DirectionNextPlayer=-1;
  }
  CurrentPlayer=WrapAround(LastPlayer+DirectionNextPlayer);
  
  LOG_TOURVIC("CurrentPlayer:");
  LOG_TOURVIC(CurrentPlayer);
  LOG_TOURVIC("\n");
  LOG_TOURVIC("LastPlayer:");
  LOG_TOURVIC(LastPlayer);
  LOG_TOURVIC("\n");
  LOG_TOURVIC("DirectionNextPlayer:");
  LOG_TOURVIC(DirectionNextPlayer);
  LOG_TOURVIC("\n");
  
  //Tout vert pour commencer+Une Lumière
  ActivateRedLight(CurrentPlayer);
  ActivateGreenLED(20);
  
  //Spin the wheel!
  do
  {
    //For the active player, monitor the transitions.  
    //1: ToLow
    //2: ToHigh
    //3: ToLow
    //If this happens during the time the player is active, Good, you are the winner.
    
    /*
    LOG_TOURVIC("CurrentPlayer:");
    LOG_TOURVIC(CurrentPlayer);
    LOG_TOURVIC("\n");
    LOG_TOURVIC("ReadyToPress:");
    LOG_TOURVIC(ReadyToPress);
    LOG_TOURVIC("\n");
    LOG_TOURVIC("PlayerIsPressing:");
    LOG_TOURVIC(PlayerIsPressing);
    LOG_TOURVIC("\n");
    */
    //Monitor initial transition to LOW
    if(!ReadPlayerInput(CurrentPlayer) && !ReadyToPress && !IgnorePresses)
    {
      LOG_TOURVIC("Changing RTP!");
      LOG_TOURVIC("\n");
      ReadyToPress=true;
    }
    
    //Monitor subsequent transition to HIGH
    if(ReadPlayerInput(CurrentPlayer) && ReadyToPress && !PlayerIsPressing && !IgnorePresses)
    {
      LOG_TOURVIC("Changing PIP!")
      LOG_TOURVIC("\n");
      PlayerIsPressing=true;
    }
    
    //Monitor subsequent transition to LOW
    if(!ReadPlayerInput(CurrentPlayer) && PlayerIsPressing && !IgnorePresses)
    {
      LOG_TOURVIC("Player SAFE!")
      LOG_TOURVIC("\n");
      //YOU ARE SAFE.
      IgnorePresses=true;
      PlayerHasWon=true;
      CurrentCounter-=SpamCheckDelay;
    }
    
    delay(1);

    //Check if current player has won and is pressing again.  If so, make him loose.
    if(PlayerHasWon && ReadPlayerInput(CurrentPlayer))
    {
      LOG_TOURVIC("Player LOOSES!")
      LOG_TOURVIC("\n");
      PlayerHasWon=false;
    }
    
    //Enougn time on this guy...  Switch
    if(CurrentCounter>LightDelay)
    {
      if(PlayerHasWon)
      {
        Winner=CurrentPlayer;
      }
      else
      {
        CurrentCounter=0;
        ReadyToPress=false;
        PlayerIsPressing=false;
        IgnorePresses=false;
        PlayerHasWon=false;
        
        
        //If we reach the last guy, increment lightdelay
        if (CurrentPlayer==LastPlayer)
        {
          LightDelay+=LightDelayIncrement;
          LOG_TOURVIC("Increasing LightDelay:")
          LOG_TOURVIC(LightDelay);
          LOG_TOURVIC("\n");
          
          if(ReadytoIncreaseIncrement==true)
          {
            if (random(IncrementProb)==0)
            {
              LightDelayIncrement++;
              LOG_TOURVIC("Increasing Increment:")
              LOG_TOURVIC(LightDelayIncrement);
              LOG_TOURVIC("\n");
            }
            ReadytoIncreaseIncrement=false;
          }
          else
          {
            ReadytoIncreaseIncrement=true;
          }
        }
        
        delay(1);
        
        DeactivateRedLight(CurrentPlayer);
        tone(Tone_Pin, 3500, 3);
        
        //Find the next player
        CurrentPlayer=WrapAround(CurrentPlayer+DirectionNextPlayer);
        ActivateRedLight(CurrentPlayer);
      }
    }
    CurrentCounter++;
    delay(1);
  }while(Winner==-1);

  WinnerSoundAndLight(Winner);

  //Low intensity
  delay(700);
  TurnOffAllLights();
  delay(25);
}

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
  int Direction = 1;
  int FraudulentTeam;
  int GameDelay=2;
  int Fails[nbj_max]={0};
  int FailsMax=0;
  int NumPlayersMaxFail=0;
  int FailPlayerSequenceId=-1;
  int PlayerFound=-1;
  int FailPlayer=-1;

  if(random(2)==0)
  {
    Direction=1;
  }
  else
  {
    Direction=-1;
  }
  
  
  AllocateTwoConsecutiveTeams();

  if(NbJoueursEq1>NbJoueursEq2)
  {
    FactorTeamSize[0]=((float)NbJoueursEq1/(float)NbJoueursEq2)*BigTeamFactor;
  }
  else if(NbJoueursEq2>NbJoueursEq1)
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
    
    for (int i=1; i <50 ; i++)
    {
      ActivateGreenLED(i);
      delay(ForLightDelay);
    }
    delay(LightDelay);
    for(int i=0 ; i<2 ; i++)
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
    for (int i=1; i <50 ; i++)
    {
      ActivateBlueLED(i);
      delay(ForLightDelay);
    }
    delay(LightDelay);
    for(int i=0 ; i<2 ; i++)
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
  if(Direction==1)
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
    for(int i=0 ; i<nbj ; i++)
    {
      if(ReadPlayerInput(i) && (i != Player[0] && i != Player[1]))
      {
        FraudulentTeam=Equipes[i];
        LOG_TEAMDEDUEL("FraudulentTeam:");
        LOG_TEAMDEDUEL(FraudulentTeam);
        LOG_TEAMDEDUEL("\n");

        //Log fail if player not first.
        if(Player[FraudulentTeam]!=InitPlayer[FraudulentTeam])
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
    
    for(int i=0 ; i<=1 ; i++)
    {
      //Check for Release
      if(!ReadPlayerInput(Player[i]) && !HasReleased[i])
      {
        HasReleased[i]=true;
      }

      //Check for Press after release
      if(ReadPlayerInput(Player[i]) && HasReleased[i])
      {
        IsPressing[i]=true;
      }

      //Check for release to switch to nextplayer
      if(!ReadPlayerInput(Player[i]) && IsPressing[i])
      {
        //Turn off light
        DeactivateRedLight(Player[i]);
        HasReleased[i]=false;
        IsPressing[i]=false;

        Player[i]=NextPlayerInTeam(Player[i],i,Direction);
        
        //Activate Next Player Light
        ActivateRedLight(Player[i]);

        //Increase score if back to first player for team.
        if(Player[i]==InitPlayer[i])
        {
          Count[i]++;
          LOG_TEAMDEDUEL("Score:");
          LOG_TEAMDEDUEL(Score);
          LOG_TEAMDEDUEL("\n");
        }
      }
    }

    delay(GameDelay);
    
    if(ScoreIncCounter>ScoreIncreaseIter && ScoreFactor<50)
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
    else if (Score <1)
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
    for (int i=1; i <50 ; i++)
    {
      ActivateGreenLED(i);
      delay(20);
    }
    delay(LightDelay);
    ActivateGreenLED(0);
    IlluminateTeamRedLights(Winner);
    for(int i=0 ; i<2 ; i++)
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
    for (int i=1; i <50 ; i++)
    {
      ActivateBlueLED(i);
      delay(20);
    }
    delay(LightDelay);
    ActivateBlueLED(0);
    IlluminateTeamRedLights(Winner);
    for(int i=0 ; i<2 ; i++)
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
  for (int i=0 ; i<nbj ; i++)
  {
    if(Fails[i]>FailsMax && Equipes[i]!=Winner)
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

  
  if(FailsMax!=0)
  {
    FailPlayerSequenceId=random(NumPlayersMaxFail);
    LOG_TEAMDEDUEL("FailPlayerSequenceId:");
    LOG_TEAMDEDUEL(FailPlayerSequenceId);
    LOG_TEAMDEDUEL("\n");
    for (int i=0 ; i<nbj ; i++)
    {
      if(Fails[i]==FailsMax && Equipes[i]!=Winner)
      {
        PlayerFound++;
      }
      if(PlayerFound==FailPlayerSequenceId)
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


#ifdef ENABLE_LOGGING
  #define LOG_TOURNIQUET(a) LOG_GAME(Game_id_TH,a)
#else
  #define LOG_TOURNIQUET(a)
#endif
void Tourniquet()
{
  int LightDelay=3;
  int LightDelayIncrement=1;
  int CurrentCounter=0;
  int LastPlayer=random(nbj);
  int CurrentPlayer=0;
  int DirectionNextPlayer=0;
  bool PlayersState[nbj_max]={true,true,true,true,true,true,true,true,true,true};
  int NumActivePlayers=nbj;
  int Looser=-1;
  bool ReadyToPress=false;
  bool PlayerIsPressing=false;
  bool ReadytoIncreaseIncrement=false;
  bool IgnorePresses=false;
  int IncrementProb=3;

  if(random(2)==0)
  {
    DirectionNextPlayer=1;
  }
  else
  {
    DirectionNextPlayer=-1;
  }
  CurrentPlayer=WrapAround(LastPlayer+DirectionNextPlayer);
  
  //Tout bleu pour commencer+Une Lumière
  ActivateRedLight(CurrentPlayer);
  ActivateBlueLED(20);
  
  //Spin the wheel!
  do
  {
    //For the active player, monitor the transitions.  
    //1: ToLow
    //2: ToHigh
    //3: ToLow
    //If this happens during the time the player is active, Good, you are not the looser.
    LOG_TOURNIQUET("CurrentPlayer:");
    LOG_TOURNIQUET(CurrentPlayer);
    LOG_TOURNIQUET("\n");
    LOG_TOURNIQUET("ReadyToPress:");
    LOG_TOURNIQUET(ReadyToPress);
    LOG_TOURNIQUET("\n");
    LOG_TOURNIQUET("PlayerIsPressing:");
    LOG_TOURNIQUET(PlayerIsPressing);
    LOG_TOURNIQUET("\n");
    //Monitor initial transition to LOW
    
    if(!ReadPlayerInput(CurrentPlayer) && !ReadyToPress && !IgnorePresses)
    {
      LOG_TOURNIQUET("Changing RTP!");
      LOG_TOURNIQUET("\n");
      ReadyToPress=true;
    }
    
    //Monitor subsequent transition to HIGH
    if(ReadPlayerInput(CurrentPlayer) && ReadyToPress && !PlayerIsPressing && !IgnorePresses)
    {
      LOG_TOURNIQUET("Changing PIP!")
      LOG_TOURNIQUET("\n");
      PlayerIsPressing=true;
    }
    
    //Monitor subsequent transition to LOW
    if(!ReadPlayerInput(CurrentPlayer) && PlayerIsPressing && !IgnorePresses)
    {
      LOG_TOURNIQUET("Player SAFE!")
      LOG_TOURNIQUET("\n");
      //YOU ARE SAFE.
      if(PlayersState[CurrentPlayer])
      {
        NumActivePlayers--;
        PlayersState[CurrentPlayer]=false;
        IgnorePresses=true;

        //Change Last Player if Current Player
        if(CurrentPlayer==LastPlayer)
        {
          LOG_TOURNIQUET("Player was last and is now safe!")
          LOG_TOURNIQUET("\n");
          LOG_TOURNIQUET("Changing LAST PLAYER to:")
          do
          {
            LastPlayer=WrapAround(LastPlayer+DirectionNextPlayer);
          }while(PlayersState[LastPlayer]==false);
          LOG_TOURNIQUET(LastPlayer);
          LOG_TOURNIQUET("\n");
        }
      }
    }
    
    delay(1);
    
    //Find spammers and bring them back in the game.
    for(int i=0; i<=nbj_raw ; i++)
    {
      if(!PlayersState[i] && ReadPlayerInput(i))
      {
        LOG_TOURNIQUET("SPAM PLAYER:");
        LOG_TOURNIQUET(i);
        LOG_TOURNIQUET("\n");
        
        PlayersState[i]=true;
        NumActivePlayers++;
        DeactivateRedLight(i);
      }
    }
    
    delay(1);

    if(NumActivePlayers<=1) 
    {
      break;
    }
    
    //Enougn time on this guy...  Switch
    if(CurrentCounter>LightDelay)
    {
      
      CurrentCounter=0;
      ReadyToPress=false;
      PlayerIsPressing=false;
      IgnorePresses=false;
      
      //If we reach the last guy, increment lightdelay
      if (CurrentPlayer==LastPlayer)
      {
        LightDelay+=LightDelayIncrement;
        LOG_TOURNIQUET("Increasing LightDelay:")
        LOG_TOURNIQUET(LightDelay);
        LOG_TOURNIQUET("\n");
        
        if(ReadytoIncreaseIncrement==true)
        {
          if (random(IncrementProb)==0)
          {
            LightDelayIncrement++;
            LOG_TOURNIQUET("Increasing Increment:")
            LOG_TOURNIQUET(LightDelayIncrement);
            LOG_TOURNIQUET("\n");
          }
          ReadytoIncreaseIncrement=false;
        }
        else
        {
          ReadytoIncreaseIncrement=true;
        }
      }
      
      delay(1);
      //Keep winners lights active, Deactivate my light if im still in this game.
      if(PlayersState[CurrentPlayer]==true)
      {
        DeactivateRedLight(CurrentPlayer);
      }
      
      tone(Tone_Pin, 3500, 3);
      //Find an active player
      do
      {
        CurrentPlayer=WrapAround(CurrentPlayer+DirectionNextPlayer);
      }while(!PlayersState[CurrentPlayer]);
      
      ActivateRedLight(CurrentPlayer);
      
    }
    
    CurrentCounter++;
    delay(1);
  }while(NumActivePlayers>1);

  for(int i=0; i<=nbj_raw ; i++)
  {
    if(PlayersState[i])
    {
      Looser=i;
    }
  }

  //Low intensity
  delay(700);
  TurnOffAllLights();

  LooserSoundAndLight(Looser,false);
  JoueurHonte=MarqueurHonte(Looser,DelaiPetiteHonte);
}


#ifdef ENABLE_LOGGING
  #define LOG_PATATE2(a) LOG_GAME(Game_id_PC2,a)
#else
  #define LOG_PATATE2(a)
#endif
void Patate2()
{
  
  unsigned long basetime=12242;
  unsigned long maxrandtime=4242;
  unsigned long GameTimeMillis = basetime+random(maxrandtime);
  unsigned long GameCounter=0;
  int InitSpread=nbj/2;
  bool ReadyToSwitch[2]={false,false};
  bool PlayerIsPressing[2]={false,false};
  unsigned long PressCounter[2]={0,0};
  int LuckyPlayer[2];
  int DirectionNextPlayer[2]={0,0};
  int ProbOppDir=3;
  unsigned long MinChangeCounter=3500;
  unsigned long ChangeCounter=0;

  #define PenaliteIncrPatate2 2000;
  unsigned long GameCounterPenalite[nbj];
  bool PreviousState[nbj];
  for(int i=0; i<nbj ; i++)
  {
    GameCounterPenalite[i]=0;
    PreviousState[i]=false;
  }

  //Positions of DEDU for different configs.
  int BothPlus = 80;
  int OppDir1 = 60;
  int OppDir2 = 40;
  int BothMinus = 20;
  int DEDUPosition=0;
  
  
  TurnOffAllLights();
  
  //Initialize direction of turn
  if(random(2)==0)
  {
     DirectionNextPlayer[0]=1;
     DirectionNextPlayer[1]=1;
     DEDUPosition=BothPlus;
  }
  else
  {
    DirectionNextPlayer[0]=-1;
    DirectionNextPlayer[1]=-1;
    DEDUPosition=BothMinus;
  }

  if(nbj%2!=0)
  {
    if (random(2)==0)
    {
      InitSpread=InitSpread+1;
    }
  }


  //Start the players furthest apart.
  LuckyPlayer[0]=random(nbj);
  LuckyPlayer[1]=ProchainJoueur(LuckyPlayer[0],InitSpread,DirectionNextPlayer[0]);
  
  LOG_PATATE2("\n");
  LOG_PATATE2("PATATE2");
  LOG_PATATE2("\n");
  LOG_PATATE2("\n");
  LOG_PATATE2("GameTimeMillis:");
  LOG_PATATE2(GameTimeMillis);
  LOG_PATATE2("\n");
  LOG_PATATE2("InitSpread:");
  LOG_PATATE2(InitSpread);
  LOG_PATATE2("\n");
  LOG_PATATE2("DirectionNextPlayer[0]:");
  LOG_PATATE2(DirectionNextPlayer[0]);
  LOG_PATATE2("\n");
  LOG_PATATE2("DirectionNextPlayer[1]:");
  LOG_PATATE2(DirectionNextPlayer[1]);
  LOG_PATATE2("\n");
  LOG_PATATE2("LuckyPlayer[0]:");
  LOG_PATATE2(LuckyPlayer[0]);
  LOG_PATATE2("\n");
  LOG_PATATE2("LuckyPlayer[1]:");
  LOG_PATATE2(LuckyPlayer[1]);
  LOG_PATATE2("\n");
  
  //Lights/DEDU INIT Setup
  ActivateBlueLED(21);
  delay(1200);
  MoveDEDUFlag(DEDUPosition);
  delay(500);
  for(int i=0; i<=1 ; i++)
  {
    ActivateRedLight(LuckyPlayer[i]);
  }

  do
  {
    //Monitor spammers
    for(int i=0; i<nbj; i++)
    {
      bool PP = ReadPlayerInput(i);
      if(PP && !PreviousState[i] && i!=LuckyPlayer[0] && i!=LuckyPlayer[1])
      {
        GameCounterPenalite[i]=GameCounter+PenaliteIncrPatate2;
        
        LOG_PATATE2("Penalite Joueur:");
        LOG_PATATE2(i);
        LOG_PATATE2("\n");
        LOG_PATATE2("GameCounterPenalite[i]:");
        LOG_PATATE2(GameCounterPenalite[i]);
        LOG_PATATE2("\n");
      }
      PreviousState[i]=PP;
    }
    
    ChangeCounter++;
    GameCounter++;
    for (int i=0 ; i<=1 ; i++)
    {
      /*
      LOG_PATATE2("Current Player:");
      LOG_PATATE2(LuckyPlayer[i]);
      LOG_PATATE2("\n");
      LOG_PATATE2("PlayerIsPressing:");
      LOG_PATATE2(PlayerIsPressing[i]);
      LOG_PATATE2("\n");
      LOG_PATATE2("ReadyToSwitch:");
      LOG_PATATE2(ReadyToSwitch[i]);
      LOG_PATATE2("\n");
      LOG_PATATE2("PressCounter:");
      LOG_PATATE2(PressCounter[i]);
      LOG_PATATE2("\n");
      */
      
      //Monitor initial transition to LOW
      if(!ReadPlayerInput(LuckyPlayer[i]) && !ReadyToSwitch[i] && GameCounter>GameCounterPenalite[LuckyPlayer[i]])
      {
        LOG_PATATE2("Change ReadyToSwitch");
        LOG_PATATE2("\n");
        ReadyToSwitch[i]=true;
      }
      
      //Monitor subsequent transition to HIGH
      if(ReadPlayerInput(LuckyPlayer[i]) && ReadyToSwitch[i] && !PlayerIsPressing[i])
      {
        LOG_PATATE2("Change PlayerIsPressing");
        LOG_PATATE2("\n");
        PlayerIsPressing[i]=true;
      }
      
      //Player releases.  Check counter to know in which direction to go.
      if (PlayerIsPressing[i])
      {
        LOG_PATATE2("I have started Pressing");
        LOG_PATATE2("\n");
        //HIGH, Keep counting
        if(ReadPlayerInput(LuckyPlayer[i]))
        {
          LOG_PATATE2("I keep Pressing");
          LOG_PATATE2("\n");
          PressCounter[i]++;
        }
        //LOW, Take Action
        else
        {
          LOG_PATATE2("I Released!!");
          LOG_PATATE2("\n");
          LOG_PATATE2("SwitchingPlayer!!");
          LOG_PATATE2("\n");
          LOG_PATATE2("Current Player:");
          LOG_PATATE2(LuckyPlayer[i]);
          LOG_PATATE2("\n");
          LOG_PATATE2("DirectionNextPlayer:");
          LOG_PATATE2(DirectionNextPlayer[i]);
          LOG_PATATE2("\n");
          LOG_PATATE2("PressCounter:");
          LOG_PATATE2(PressCounter[i]);
          LOG_PATATE2("\n");
          //NORMAL DIRECTION
          if (PressCounter[i]<Patate_PressRev)
          {
            LOG_PATATE2("NORMAL DIR!");
            LOG_PATATE2("\n");
            DeactivateRedLight(LuckyPlayer[i]);
            LuckyPlayer[i]+=DirectionNextPlayer[i];
            tone(Tone_Pin, 800, 15);
          }
          //REV DIR
          else if (PressCounter[i]>=Patate_PressRev && PressCounter[i] < Patate_PressStall)
          {
            LOG_PATATE2("REV DIR!");
            LOG_PATATE2("\n");
            DeactivateRedLight(LuckyPlayer[i]);
            LuckyPlayer[i]-=DirectionNextPlayer[i];
            tone(Tone_Pin, 1200, 15);
          }
          else
          {
            //STALL ON PLAYER, TOO LONG PRESS
            LOG_PATATE2("STALL");
            LOG_PATATE2("\n");
            tone(Tone_Pin, 200+LuckyPlayer[i]*25, 150);
          }
          
          //Reset Counters and player ID
          ReadyToSwitch[i]=false;
          PlayerIsPressing[i]=false;
          PressCounter[i]=0;
          
          LuckyPlayer[i]=WrapAround(LuckyPlayer[i]);

          LOG_PATATE2("New Player:");
          LOG_PATATE2(LuckyPlayer[i]);
          LOG_PATATE2("\n");
          
          //Activate new light;
          ActivateRedLight(LuckyPlayer[i]);
        }
      }
      delay(1);
      
      //Check Win condition between players.
      if(LuckyPlayer[0] == LuckyPlayer[1])
      {
        break;
      }
    }

    //Check change DIR
    if (random(10000)>9995 &&  ChangeCounter>MinChangeCounter)
    {
      
      LOG_PATATE2("GameCounter:");
      LOG_PATATE2(GameCounter);
      LOG_PATATE2("\n");
      LOG_PATATE2("SwitchingSIDE!!");
      LOG_PATATE2("\n");
      
      ChangeCounter=0;
      
      //MAIN DIRECTION
      if (DirectionNextPlayer[0] == 1)
      {
        DirectionNextPlayer[0]=-1;
      }
      else
      {
        DirectionNextPlayer[0]=1;
      }

      //Second Direction
      if(random(ProbOppDir)==0)
      {
        LOG_PATATE2("Opp Directions!!");
        LOG_PATATE2("\n");
        DirectionNextPlayer[1]=-DirectionNextPlayer[0];
      }
      else
      {
        LOG_PATATE2("Same Direction");
        LOG_PATATE2("\n");
        DirectionNextPlayer[1]=DirectionNextPlayer[0];
      }

      //Directions
      if(DirectionNextPlayer[0] == 1 && DirectionNextPlayer[1]==1)
      {
        DEDUPosition=BothPlus;
      }
      else if(DirectionNextPlayer[0] == 1 && DirectionNextPlayer[1]==-1)
      {
        DEDUPosition=OppDir1;
      }
      else if(DirectionNextPlayer[0] == -1 && DirectionNextPlayer[1]==1)
      {
        DEDUPosition=OppDir2;
      }
      else
      {
        DirectionNextPlayer[0] = -1;
        DirectionNextPlayer[1] = -1;
        DEDUPosition=BothMinus;
      }
      MoveDEDUFlag(DEDUPosition);
    }
  }while((LuckyPlayer[0] != LuckyPlayer[1]) && (GameCounter<GameTimeMillis));

  //Both LED on same player OR Game Timeout.
  LOG_PATATE2("GAME OVER");
  LOG_PATATE2("\n");
  
  //Loose Stage
  ActivateBlueLED(5);

  for (int i = 1; i <= 80; i++)
  {
    Tone_Frequency = 2000 - 20 * i;
    tone(Tone_Pin, Tone_Frequency);
    delay(10);
  }
  noTone(Tone_Pin);
  
  //Identify the Looser
  for (int e = 1; e <= 4; e++) {
    ActivateRedLight(LuckyPlayer[0]);
    ActivateRedLight(LuckyPlayer[1]);
    delay(500);
    DeactivateRedLight(LuckyPlayer[0]);
    DeactivateRedLight(LuckyPlayer[1]);
    delay(500);
  }

  //FIN  
  TurnOffAllLights();
  MoveDEDUFlag(0);
  delay(1200);
}
