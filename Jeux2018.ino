#ifdef ENABLE_LOGGING
  #define LOG_TEAMDEDUEL(a) LOG_GENERAL(a)
#else
  #define LOG_TEAMDEDUEL(a)
#endif
void TeamDeDuel()
{
  int LightDelay=350;
  int ForLightDelay=13;
  int Winner=-1;
  unsigned int Count[2]={0,0};
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
  unsigned long ScoreIncreaseIter=950;
  bool HasReleased[2]={false,false};
  bool IsPressing[2]={false,false};
  int SoundTime=500;
  int Direction = 1;
  int FraudulentTeam;
  int GameDelay=2;

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
      if(ReadPlayerInput(i)==HIGH && (i != Player[0] && i != Player[1]))
      {
        FraudulentTeam=Equipes[i];
        
        //Reset Player to first.
        DeactivateRedLight(Player[FraudulentTeam]);
        HasReleased[FraudulentTeam]=false;
        IsPressing[FraudulentTeam]=false;

        Player[FraudulentTeam]=InitPlayer[FraudulentTeam];
        
        ActivateRedLight(Player[FraudulentTeam]);
      }
    }

    delay(GameDelay);
    
    for(int i=0 ; i<=1 ; i++)
    {
      //Check for Release
      if(ReadPlayerInput(Player[i])==LOW && HasReleased[i]==false)
      {
        HasReleased[i]=true;
      }

      //Check for Press after release
      if(ReadPlayerInput(Player[i])==HIGH && HasReleased[i]==true)
      {
        IsPressing[i]=true;
      }

      //Check for release to switch to nextplayer
      if(ReadPlayerInput(Player[i])==LOW && IsPressing[i]==true)
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
      ActivateGreenLED((Score-50)/3);
      ActivateBlueLED(0);
    }
    else if (Score<50)
    {
      ActivateBlueLED((50-Score)/3);
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
  
}


#ifdef ENABLE_LOGGING
  #define LOG_TOURNIQUET(a) LOG_GAME(13,a)
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

  if(random(2)==0)
  {
    DirectionNextPlayer=1;
  }
  else
  {
    DirectionNextPlayer=-1;
  }
  CurrentPlayer=WrapAround(LastPlayer+DirectionNextPlayer);
  
  //Tout vert pour commencer+Une Lumière
  ActivateRedLight(CurrentPlayer);
  delay(200);
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
    
    if(ReadPlayerInput(CurrentPlayer)==LOW && ReadyToPress==false && IgnorePresses==false)
    {
      LOG_TOURNIQUET("Changing RTP!");
      LOG_TOURNIQUET("\n");
      ReadyToPress=true;
    }
    
    //Monitor subsequent transition to HIGH
    if(ReadPlayerInput(CurrentPlayer)==HIGH && ReadyToPress==true && PlayerIsPressing==false && IgnorePresses==false)
    {
      LOG_TOURNIQUET("Changing PIP!")
      LOG_TOURNIQUET("\n");
      PlayerIsPressing=true;
    }
    
    //Monitor subsequent transition to HIGH
    if(ReadPlayerInput(CurrentPlayer)==LOW && PlayerIsPressing==true && IgnorePresses==false)
    {
      LOG_TOURNIQUET("Player SAFE!")
      LOG_TOURNIQUET("\n");
      //YOU ARE SAFE.
      if(PlayersState[CurrentPlayer]==true)
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
      if(PlayersState[i]==false && ReadPlayerInput(i)==HIGH)
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
        //LightDelayIncrement++;
        
        if(ReadytoIncreaseIncrement==true)
        {
          if (random(4)==0)
          {
            LightDelayIncrement++;
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
      }while(PlayersState[CurrentPlayer]==false);
      
      ActivateRedLight(CurrentPlayer);
      
    }
    
    CurrentCounter++;
    delay(1);
  }while(NumActivePlayers>1);

  for(int i=0; i<=nbj_raw ; i++)
  {
    if(PlayersState[i]==true)
    {
      Looser=i;
    }
  }

  //Low intensity
  delay(700);
  TurnOffAllLights();

  LooserSoundAndLight(Looser);
  JoueurHonte=MarqueurHonte(Looser,90 - nbj * 7);
}


#ifdef ENABLE_LOGGING
  #define LOG_PATATE2(a) LOG_GAME(12,a)
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
  const int PressRev=150;
  const int PressStall=300;
  int LuckyPlayer[2];
  int DirectionNextPlayer[2]={0,0};
  int ProbOppDir=3;
  unsigned long MinChangeCounter=1500;
  unsigned long ChangeCounter=0;

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
  delay(1500);
  MoveDEDUFlag(DEDUPosition);
  delay(500);
  for(int i=0; i<=1 ; i++)
  {
    ActivateRedLight(LuckyPlayer[i]);
  }

  do
  {
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
      if(ReadPlayerInput(LuckyPlayer[i])==LOW && ReadyToSwitch[i]==false)
      {
        LOG_PATATE2("Change ReadyToSwitch");
        LOG_PATATE2("\n");
        ReadyToSwitch[i]=true;
      }
      
      //Monitor subsequent transition to HIGH
      if(ReadPlayerInput(LuckyPlayer[i])==HIGH && ReadyToSwitch[i]==true && PlayerIsPressing[i]==false)
      {
        LOG_PATATE2("Change PlayerIsPressing");
        LOG_PATATE2("\n");
        PlayerIsPressing[i]=true;
      }

      
      
      //Player releases.  Check counter to know in which direction to go.
      if (PlayerIsPressing[i]==true)
      {
        LOG_PATATE2("I have started Pressing");
        LOG_PATATE2("\n");
        //HIGH, Keep counting
        if(ReadPlayerInput(LuckyPlayer[i])==HIGH)
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
          if (PressCounter[i]<PressRev)
          {
            LOG_PATATE2("NORMAL DIR!");
            LOG_PATATE2("\n");
            DeactivateRedLight(LuckyPlayer[i]);
            LuckyPlayer[i]+=DirectionNextPlayer[i];
            tone(Tone_Pin, 800, 15);
          }
          //REV DIR
          else if (PressCounter[i]>=PressRev && PressCounter[i] < PressStall)
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
    if (random(10000)>9992 &&  ChangeCounter>MinChangeCounter)
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
