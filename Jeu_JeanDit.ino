
#ifdef ENABLE_LOGGING
  #define LOG_JD(a) LOG_GAME(Game_id_JD,a)
#else
  #define LOG_JD(a)
#endif
void JeanDit()
{
  //Tunables
  //GameCounter pour faire perdre Jean.
  int CounterJeanPerd=8000;

  //Nombre de cycles où Jean ne peut pas cliquer.
  int DisableJeanRandMin=15200; //Valeur plus élevée que JeanPerd pour qu'on perde un joueur par manche et Jean ne peut tuer personne.
  int DisableJeanRandMax=20542;
  #define LightMax 12
  //DELTA à chaque nouvelle ronde.
  int DisableJeanMinDelta=(0.7*DisableJeanRandMin/nbj);
  int DisableJeanMaxDelta=(0.6*DisableJeanRandMax/nbj);
  
  //Commencer avec un random pas trop élevé pour le premier round.
  int MaxCounterDisableJean=random(300,500);
  //TUNABLES END//
  
  int Winner=-1;
  int Jean=random(nbj);
  bool PreviousState[nbj_max]={false};
  bool CurrentState[nbj_max];
  const int FlagDelay=10;
  bool DisableJean=true;
  int CounterDisableJean=0;
  float DisableJeanLightFactor=(float)100/(float)MaxCounterDisableJean;
  const int GameDelay=5;
  bool TargetState=false;
  bool PlayersInGame[nbj_max]={false};
  for (int i=0; i<nbj; i++)
  {
    if (i!=Jean) PlayersInGame[i]=true;
  }
  bool PlayerSafe[nbj]={false};
  for (int i=0; i<nbj; i++)
  {
    if (i!=Jean) PlayerSafe[i]=true;
  }
  int GameCounter=0;
  bool JeanPerd=false;
  bool JeanGagne=false;
  int RoundLooser=-1;
  bool NewRound=false;
  int NewRoundFlash=3;
  int Flash=0;
  const int FlashRate=100;
  //À chaque fois que Jean change le DEDU d'état, laisser un temps de réaction.
  //Éliminer le dernier à changer d'état.
  //Donner un temps minimum à Jean pour faire son action.  Graduellement réduire les lumières Vert/Bleu pendant ce temps d'attente.

  //Permettre à chaque joueur de toggler ON/OFF.
  //Au premier pèse, le joueur est safe.
  //Au 2e pese, il perd.

  //Attendre le permier des 2 évènements:
  //1. Jean toggle
  //1.2 Éliminer tous les joueurs actifs qui ne sont pas dans le bon état.
  //1.1 Si Jean Tue tout le monde, il gagne.
  
  //2. Tous les joueurs sauf 1 sont safe.
  //2.1 Si c'est le cas, dire à Jean qu'il peut jouer.

  //Lorsque Jean toggle
  //Éliminer tous ceux qui sont pas safe.
  
  LOG_JD("DisableJeanLightFactor:");
  LOG_JD(DisableJeanLightFactor)
  LOG_JD("\n");
  LOG_JD("MaxCounterDisableJean:");
  LOG_JD(MaxCounterDisableJean)
  LOG_JD("\n");
  LOG_JD("DisableJeanMinDelta:");
  LOG_JD(DisableJeanMinDelta)
  LOG_JD("\n");
  LOG_JD("DisableJeanMaxDelta:");
  LOG_JD(DisableJeanMaxDelta)
  LOG_JD("\n");
  
  //Signature lumineuse/sonore
  ActivateRedLight(Jean);
  if (!SkipLights)
  {
    delay(500);
    for (int i=0; i<100; i++)
    {
      MoveDEDUFlag(i);
      delay(FlagDelay);
    }
    for (int i=0; i<100; i++)
    {
      MoveDEDUFlag(100-i);
      delay(FlagDelay);
    }
  }
  ActivateGreenLED(random(1,LightMax)); //Since Jean est toujours Disable
  
  //Main game.
  do
  {
    if (ReadPlayerInput(Jean))
    {
      LOG_JD("PrevState:");
      LOG_JD(PreviousState[Jean]);
      LOG_JD("\n");
      LOG_JD("DisableJean:");
      LOG_JD(DisableJean);
      LOG_JD("\n");
      LOG_JD("CounterDisableJean:");
      LOG_JD(CounterDisableJean);
      LOG_JD("\n");
      LOG_JD("MaxCounterDisableJean:");
      LOG_JD(MaxCounterDisableJean);
      LOG_JD("\n");
    }
    
    if (DisableJean && !NewRound)
    {
      int PercDisableRemaining=((100 - (int)(CounterDisableJean*DisableJeanLightFactor))/2);
      //ActivateGreenLED(PercDisableRemaining);
      CounterDisableJean++;
      if (CounterDisableJean>MaxCounterDisableJean || PercDisableRemaining<2)
      {
        DisableJean=false;
        CounterDisableJean=0;
        GameCounter=0;
        ActivateGreenLED(0);
        MaxCounterDisableJean=random(DisableJeanRandMin,DisableJeanRandMax);
        DisableJeanLightFactor=(float)100/(float)MaxCounterDisableJean;
        LOG_JD("END_DISABLEJEAN\n:");
        LOG_JD("MaxCounterDisableJean:");
        LOG_JD(MaxCounterDisableJean)
        LOG_JD("\n");
        LOG_JD("DisableJeanLightFactor:");
        LOG_JD(DisableJeanLightFactor)
        LOG_JD("\n");
        LOG_JD("DisableJeanRandMin:");
        LOG_JD(DisableJeanRandMin)
        LOG_JD("\n");
        LOG_JD("DisableJeanRandMax:");
        LOG_JD(DisableJeanRandMax)
        LOG_JD("\n");
      }
    }

    if (NewRound)
    {
      ActivateGreenLED(0);
      if (GameCounter%100==0)
      {
        ToggleOutput(RoundLooser);
        Flash++;
      }

      //Prepare for new round
      if (Flash>NewRoundFlash)
      {
        Flash=0;
        NewRound=false;
        DisableJean=false;
        TurnOffAllRedLights();
        ActivateRedLight(Jean);
      }
    }
    
    //Check Winner or JeanPerd
    if (GameCounter>CounterJeanPerd)
    {
      JeanPerd=true;
    }
    else
    {
      /*
      LOG_JD("DisableJean:");
      LOG_JD(DisableJean);
      LOG_JD("\n");
      LOG_JD("PreviousState[Jean]:");
      LOG_JD(PreviousState[Jean]);
      LOG_JD("\n");
      LOG_JD("ReadPlayerInput(Jean):");
      LOG_JD(ReadPlayerInput(Jean));
      LOG_JD("\n");
      */
      
      //Jean Toggle!
      if (!DisableJean && !PreviousState[Jean] && ReadPlayerInput(Jean))
      {
        LOG_JD("Jean Toggle!\n");
        LOG_JD("\n");
        LOG_JD("TargetState:");
        LOG_JD(TargetState);
        LOG_JD("\n");
        int Count=0;
        //Tue ceux qui ne sont pas dans le bon état.  Check si Jean Gagne.
        for (int i=0; i<nbj; i++)
        {
          if (PlayersInGame[i])
          {
            if (ReadPlayerOutput(i))
            {
              LOG_JD("Disable ");
              LOG_JD(i);
              LOG_JD(";\n");
              DeactivateRedLight(i);
              PlayersInGame[i]=false;
              Buzz();
            }
            else
            {
              Count++;
            }
          }
        }
        
        if (Count==0)
        {
          LOG_JD("Jean Gagne!\n");
          JeanGagne=true;
        }
        else
        {
          LOG_JD("New Round!\n");
          //Reverse TargetState
          TargetState=!TargetState;
          DisableJean=true;
          DisableJeanRandMin=DisableJeanRandMin-DisableJeanMinDelta;
          DisableJeanRandMax=DisableJeanRandMax-DisableJeanMaxDelta;
          ActivateGreenLED(random(1,LightMax)); //Since Jean est toujours Disable
          
          if (TargetState) MoveDEDUFlag(100);
          else MoveDEDUFlag(0);
          
          //Reset SafeState, Activate Player LED, Deactivate Jean.
          for (int i=0; i<nbj; i++)
          {
            if (i==Jean) DeactivateRedLight(i);
            if (PlayersInGame[i])
            {
              LOG_JD("Activate ");
              LOG_JD(i);
              LOG_JD(";\n");
              ActivateRedLight(i);
            }
            else
            {
              DeactivateRedLight(i);
            }
            PlayerSafe[i]=false;
          }
        }
      }
    }

    
    if (!JeanPerd && !JeanGagne)
    {
      for (int i=0;i<nbj;i++)
      {
        CurrentState[i]=ReadPlayerInput(i);
        if (i!=Jean && PlayersInGame[i])
        {
          if (!PreviousState[i] && CurrentState[i])
          {
            ToggleOutput(i);
            if (PlayerSafe[i])
            {
              LOG_JD("Out:");
              LOG_JD(i);
              LOG_JD("\n");
              Buzz();
              PlayersInGame[i]=false;
            }
            else
            {
              LOG_JD("Safe:");
              LOG_JD(i);
              LOG_JD("\n");
              PlayerSafe[i]=true;
            }
          }
        }
      }

      
      int NumInGame=0;
      int NumSafe=0;
      //Save current into previous.  Count players in game.
      for (int i=0;i<nbj;i++)
      {
        PreviousState[i]=CurrentState[i];
        if (PlayersInGame[i])
        {
          NumInGame++;
          if (PlayerSafe[i])
          {
            Winner=i;
            NumSafe++;
          }
          else
          {
            RoundLooser=i;
          }
        }
      }
      
      //Eliminate Round Looser.
      if (NumInGame-NumSafe==1)
      {
        LOG_JD("Looser:");
        LOG_JD(RoundLooser);
        LOG_JD("\n");
        Buzz();
        PlayersInGame[RoundLooser]=false;
        NumInGame--;
        DisableJean=true;
        DisableJeanRandMin=DisableJeanRandMin-DisableJeanMinDelta;
        DisableJeanRandMax=DisableJeanRandMax-DisableJeanMaxDelta;
        NewRound=true;
        GameCounter=0;
      }
      
      //Log at decent pace.
      if (GameCounter%1400==0)
      {
        LOG_JD("PlayersInGame:");
        LOG_JD(NumInGame);
        LOG_JD("\n");
        LOG_JD("Safe Players:");
        LOG_JD(NumSafe);
        LOG_JD("\n");
      }

      
      //Periodically Extinguish Loosers.
      if (GameCounter%620==0)
      {
        for (int i=0;i<nbj;i++)
        {
          if (!PlayersInGame[i] && i!=Jean)
          {
            DeactivateRedLight(i);
          }
        }
      }

      if (NumInGame<=0) JeanGagne=true;
      else if (NumInGame>1) Winner=-1;
      
      GameCounter++;
      delay(GameDelay);
    }
  }while(Winner==-1 && !JeanPerd && !JeanGagne);

  TurnOffAllLights();
  MoveDEDUFlag(0);
  delay(500);

  if (JeanPerd)
  {
    LooserSoundAndLight(Jean,false);
    JoueurHonte=MarqueurHonte(Jean,DelaiPetiteHonte);
    //Reset jeux qui transfèrent la honte
    ResetProbHonte();
  }
  else if (JeanGagne)
  {
    WinnerSoundAndLight(Jean);
    UpdateWinner(Jean);
  }
  else
  {
    //Identify winner
    WinnerSoundAndLight(Winner);
    UpdateWinner(Winner);
  }

  //Reset
  delay(700);
  TurnOffAllLights();
  delay(25);
}

