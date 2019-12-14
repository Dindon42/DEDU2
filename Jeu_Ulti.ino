#ifdef ENABLE_LOGGING
  #define LOG_ULTI(a) LOG_GAME(Game_id_UC,a)
#else
  #define LOG_ULTI(a)
#endif

void UltimateChallenge()
{
  //Pour lumières
  int NumSteps=15;
  int MaxIntensity=100;
  int CurrentIntensity=0;
  int TimeDelay=18;

  //Pour délai entre les lumières
  long DelayCounter;
  long LightCounterPlayer[nbj_max];
  unsigned long mindelay;
  unsigned long maxdelay;
  unsigned long SelectedDelay;
  int NbPlayersStillInGame;
  //Pour délai entre les jeux
  mindelay=1500;
  maxdelay=5252;
  int ToneTime=300;
  int LightTime=500;
  
  //PlayerStates
  int nPotPlayers;
  int nPlayersForRound;
  int nPlayersSelected;
  int RoundWinner;
  int nWinners;
  int nLoosers;
  int Ultimatewinner;
  
  int ReadyToPlay=0;
  int GuaranteedPlay=2;
  int InGame=3;
  int Winner=1;
  int Looser=-1;
  int Inactive=99;

  
  bool HasReleased[nbj_max];
  int PlayerState[nbj_max];
  //InitPlayers
  for (int i=0;i<nbj_max;i++)
  {
    PlayerState[i]=Inactive;
  }
  for (int i=0;i<=nbj_raw;i++)
  {
    PlayerState[i]=ReadyToPlay;
  }

  //Identification Lumineuse du jeu: sinwave
  for (int j=0;j<4;j++)
  {
    for (int i=0; i<NumSteps; i++)
    {
      ControlAllLights(false,CurrentIntensity,CurrentIntensity);
      CurrentIntensity+=MaxIntensity/NumSteps;
      delay(TimeDelay);
    }
  
    
    for (int i=0; i<NumSteps-1; i++)
    {
      CurrentIntensity-=MaxIntensity/NumSteps;
      ControlAllLights(false,CurrentIntensity,CurrentIntensity);
      delay(TimeDelay);
    }
  }
  
  ControlAllLights(false,0,0);
  LOG_ULTI("NEW GAME!!\n");
  do
  {
    
    NbPlayersStillInGame=0;
    for (int i=0;i<nbj;i++)
    {
      if (PlayerState[i]!=Looser)
      {
        NbPlayersStillInGame++;
      }
    }

    LOG_ULTI("NbPlayersStillInGame:");
    LOG_ULTI(NbPlayersStillInGame);
    LOG_ULTI("\n");
    
    SelectedDelay=random(mindelay,maxdelay);
    LOG_ULTI("SelectedDelay:");
    LOG_ULTI(SelectedDelay);
    LOG_ULTI("\n");

    
    DelayCounter=0;
    for (int i=0;i<=nbj_raw;i++)
    {
      LightCounterPlayer[i]=0;
    }
    
    //Check if people press
    do
    {
      for (int i=0;i<=nbj_raw;i++)
      {
        if (ReadPlayerInput(i) && PlayerState[i]!=Looser)
        {
          LOG_ULTI("PressLooser: ");
          LOG_ULTI(i);
          LOG_ULTI("\n");
          
          if (PlayerState[i]!=Looser)
          {
            NbPlayersStillInGame--;
            LightCounterPlayer[i]=LightTime;
          }
          PlayerState[i]=Looser;
          ActivateRedLight(i);
          tone(Tone_Pin,800,ToneTime);
          if (DelayCounter<2*LightTime)
          {
            DelayCounter=0;
          }
          else
          {
            DelayCounter-=2*LightTime;
          }
        }
        if (LightCounterPlayer[i]>0)
        {
          LightCounterPlayer[i]--;
        }
        else
        {
          DeactivateRedLight(i);
        }
      }
      DelayCounter++;
      delay(1);
    }while(DelayCounter<SelectedDelay && NbPlayersStillInGame!=1);


    LOG_ULTI("OUTOFTHELOOP");
    LOG_ULTI("\n");
    LOG_ULTI("PlayerStates");
    
    LOG_ULTI("\n");
    for (int i=0; i<nbj; i++)
    {
      LOG_ULTI("  ");
      LOG_ULTI(PlayerState[i]);
    }
    LOG_ULTI("\n");
      
    //Check if only one person left.
    if (NbPlayersStillInGame==1)
    {
      delay(500);
      noTone(Tone_Pin);
      TurnOffAllRedLights();
      
      for (int i=0;i<nbj;i++)
      {
        if (PlayerState[i]!=Looser)
        {
          PlayerState[i]=Winner;
          break;
        }
      }
      LOG_ULTI("PlayerStates");
      LOG_ULTI("\n");
      for (int i=0; i<nbj; i++)
      {
        LOG_ULTI("  ");
        LOG_ULTI(PlayerState[i]);
      }
      LOG_ULTI("\n");
    }
    else
    {
      TurnOffAllRedLights();
      //Assign At least 2 players from activeplayers
      //if only 1 active player, make him guaranteed play
      nPotPlayers=0;
      for (int i=0;i<nbj;i++)
      {
        if (PlayerState[i]==ReadyToPlay || PlayerState[i]==GuaranteedPlay)
        {
          nPotPlayers++;
        }
      }
      //If not enough potential players, check some conditions
      if (nPotPlayers<2)
      {
        for (int i=0;i<nbj;i++)
        {
          //Set Ready player as guaranteed play
          if (PlayerState[i]==ReadyToPlay)
          {
            PlayerState[i]=GuaranteedPlay;
          }
  
          //Set Winners as Ready toplay
          if (PlayerState[i]==Winner)
          {
            PlayerState[i]=ReadyToPlay;
          }
          
        }
      }
      
      //Recheck potential players
      nPotPlayers=0;
      for (int i=0;i<nbj;i++)
      {
        if (PlayerState[i]==ReadyToPlay || PlayerState[i]==GuaranteedPlay)
        {
          nPotPlayers++;
        }
      }
  
      
      if (nPotPlayers==nbj && nbj>=4)
      {
        nPlayersForRound=random(2,nPotPlayers-1);
        LOG_ULTI("PlayersFirstRound:");
      }
      else
      {
        nPlayersForRound=random(2,nPotPlayers+1);
        LOG_ULTI("PlayersOtherRounds:");
      }
  
      LOG_ULTI(nPlayersForRound);
      LOG_ULTI("\n");
      LOG_ULTI("nPotPlayers:");
      LOG_ULTI(nPotPlayers);
      LOG_ULTI("\n");
      
      //Select Players for round
      //First select the guaranteed players.
      nPlayersSelected=0;
      for (int i=0; i<nbj;i++)
      {
        if (PlayerState[i]==GuaranteedPlay)
        {
          nPlayersSelected++;
          PlayerState[i]=InGame;
        }
      }
  
      //Select players for round.
      do
      {
        for (int i=0; i<nbj;i++)
        {
          if (PlayerState[i]==ReadyToPlay)
          {
            if (random(20,30)>28)
            {
              nPlayersSelected++;
              PlayerState[i]=InGame;
            }
          }
          if (nPlayersSelected==nPlayersForRound)
          {
            break;
          }
        }
      }while (nPlayersSelected<nPlayersForRound);
  
      LOG_ULTI("nPlayersSelected:");
      LOG_ULTI(nPlayersSelected);
      LOG_ULTI("\n");

      
      LOG_ULTI("PlayerStates");
      LOG_ULTI("\n");
      for (int i=0; i<nbj; i++)
      {
        LOG_ULTI("  ");
        LOG_ULTI(PlayerState[i]);
      }
      LOG_ULTI("\n");
  
      //Reset HasReleased for in-game players and set light
      for (int i=0; i<nbj;i++)
      {
        if (PlayerState[i]==InGame)
        {
          HasReleased[i]=false;
          ActivateRedLight(i);
        }
      }
      
      RoundWinner=-1;
      //Main loop for current game.
      do
      {
        //UpdateHasReleased;
        for (int i=0; i<nbj;i++)
        {
          //Check if players not in game press...
          if (PlayerState[i]!=Looser && PlayerState[i]!=InGame && ReadPlayerInput(i))
          {
            PlayerState[i]=Looser;
            ActivateRedLight(i);
          }
          if (PlayerState[i]==InGame && !ReadPlayerInput(i) && !HasReleased[i])
          {
            HasReleased[i]=true;
          }
          delay(15);
          if (PlayerState[i]==InGame && HasReleased[i] && ReadPlayerInput(i))
          {
            //WINNER
            RoundWinner=i;
            DeactivateRedLight(i);
            break;
          }
        }
      }while(RoundWinner==-1);
      
      //WinSound
      for (int i=1; i<=120; i++)
      {
        Tone_Frequency=500 + 30 * i;
        tone(Tone_Pin, Tone_Frequency, 3);
        delay(3);
      }
      noTone(Tone_Pin);
      //Flash winner light
      for (int i=0; i<2; i++)
      {
        DeactivateRedLight(RoundWinner);
        delay(500);
        ActivateRedLight(RoundWinner);
        delay(500);
      }
      TurnOffAllRedLights();
      ActivateGreenLED(0);
      
      //Update playerstates
      for (int i=0; i<nbj;i++)
      {
        if (PlayerState[i]==InGame)
        {
          if (i==RoundWinner)
          {
            PlayerState[i]=Winner;
          }
          else
          {
            PlayerState[i]=Looser;
          }
        }
      }
    }
      
    nWinners=0;
    nLoosers=0;
    for (int i=0;i<nbj_max;i++)
    {
      if (PlayerState[i]==Winner)
      {
        Ultimatewinner=i;
        nWinners++;
      }
      if (PlayerState[i]==Looser) nLoosers++;
    }
    
    if (nWinners==1 && nLoosers==(nbj-1))
    {
      Ultimatewinner=Ultimatewinner;
    }
    else
    {
      Ultimatewinner=-1;
    }
  
  }while(Ultimatewinner==-1);

  //Flash Ultimatewinner light, move the flag.
  ControlAllLights(false,0,0);
  delay(500);
  CurrentIntensity=0;
  for (int i=0; i<NumSteps; i++)
  {
    ActivateGreenLED(CurrentIntensity);
    CurrentIntensity+=MaxIntensity/NumSteps;
    delay(TimeDelay);
    
  }
  OneUp();
  for (int i=0; i<2; i++)
  {
    ActivateGreenLED(0);
    ActivateRedLight(Ultimatewinner);
    delay(500);
    ActivateGreenLED(100);
    DeactivateRedLight(Ultimatewinner);
    delay(500);
  }
  UpdateWinner(Ultimatewinner);
  ControlAllLights(false,0,0);
}


