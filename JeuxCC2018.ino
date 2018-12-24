#ifdef ENABLE_LOGGING
  #define LOG_JD(a) LOG_GAME(Game_id_JD,a)
#else
  #define LOG_JD(a)
#endif
void JeanDit()
{
  WaitForAllNonActive(nbj_raw_max);

  //Tunables
  int CounterJeanPerd=6000;
  const int DisableJeanRandMin=100;
  const int DisableJeanRandMax=542;
  int MaxCounterDisableJean=300;
  
  int Winner=-1;
  int Players=nbj;
  int Jean=random(nbj);
  Jean=5;
  bool PreviousState[nbj];
  bool CurrentState[nbj];
  const int FlagDelay=15;
  bool DisableJean=true;
  int CounterDisableJean=0;
  float DisableJeanLightFactor=(float)100/(float)MaxCounterDisableJean;
  const int GameDelay=5;
  bool TargetState=false;
  bool PlayersInGame[nbj]={false};
  for (int i=0; i<nbj; i++)
  {
    if(i!=Jean) PlayersInGame[i]=true;
  }
  bool PlayerSafe[nbj]={false};
  int GameCounter=0;
  bool JeanPerd=false;
  bool JeanGagne=false;
  
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
  //Signature lumineuse/sonore
  ActivateRedLight(Jean);
  if(!SkipLights)
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

  //Main game.
  do
  {
    if(ReadPlayerInput(Jean)==HIGH)
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
    
    if(DisableJean)
    {
      ActivateGreenLED((100 - (int)(CounterDisableJean*DisableJeanLightFactor))/2);
      CounterDisableJean++;
      if(CounterDisableJean>MaxCounterDisableJean || ((100 - (int)(CounterDisableJean*DisableJeanLightFactor))/2)<1)
      {
        DisableJean=false;
        CounterDisableJean=0;
        GameCounter=0;
        ActivateGreenLED(0);
        MaxCounterDisableJean=random(DisableJeanRandMin,DisableJeanRandMax);
        LOG_JD("END_DISABLEJEAN\n:");
        LOG_JD("MaxCounterDisableJean:");
        LOG_JD(MaxCounterDisableJean)
        LOG_JD("\n");
      }
    }
    
    //Check Winner or JeanPerd
    if(GameCounter>CounterJeanPerd)
    {
      JeanPerd=true;
    }
    else
    {
      //Jean Toggle!
      if(!DisableJean && !PreviousState[Jean] && ReadPlayerInput(Jean)==HIGH)
      {
        LOG_JD("Jean Toggle!\n");
        LOG_JD("\n");
        LOG_JD("TargetState:");
        LOG_JD(TargetState);
        LOG_JD("\n");
        int TargetOutput = TargetState ? HIGH:LOW;
        LOG_JD("TargetOutput:");
        LOG_JD(TargetOutput);
        LOG_JD("\n");
        int Count=0;
        //Tue ceux qui ne sont pas dans le bon état.  Check si Jean Gagne.
        for (int i=0; i<nbj; i++)
        {
          if(PlayersInGame[i])
          {
            if(ReadPlayerOutput(i)!=TargetOutput)
            {
              LOG_JD("Disable ");
              LOG_JD(i);
              LOG_JD(";\n");
              DeactivateRedLight[i];
              PlayersInGame[i]=false;
              Buzz();
            }
            else
            {
              Count++;
            }
          }
        }
        
        if(Count==0)
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
          if(TargetState) MoveDEDUFlag(100);
          else MoveDEDUFlag(0);
          
          //Reset SafeState
          for (int i=0; i<nbj; i++)
          {
            PlayerSafe[i]=false;
          }
        }
      }
    }

    
    if(!JeanPerd && !JeanGagne)
    {
      for (int i=0;i<nbj;i++)
      {
        if(i!=Jean && PlayersInGame[i])
        {
          CurrentState[i]=ReadPlayerInput(i)==HIGH? true:false;
          if(!PreviousState[i] && CurrentState[i])
          {
            if(PlayerSafe[i])
            {
              Buzz();
              PlayersInGame[i]=false;
              DeactivateRedLight(i);
            }
            else
            {
              LOG_JD("Safe:");
              LOG_JD(i);
              LOG_JD("\n");
              PlayerSafe[i]=true;
              ToggleOutput(i);
            }
          }
        }
      }

      
      int Count=0;
      //Save current into previous.  Count players in game.
      for (int i=0;i<nbj;i++)
      {
        PreviousState[i]=CurrentState[i];
        if(PlayersInGame[i])
        {
          Count++;
          Winner=i;
        }
      }
      
      if(Count>1) Winner=-1;
      if(Count==0) JeanGagne=true;
      
      GameCounter++;
      delay(GameDelay);
    }
  }while(Winner==-1 && !JeanPerd && !JeanGagne);

  TurnOffAllLights();
  MoveDEDUFlag(0);
  delay(500);

  if(JeanPerd)
  {
    LooserSoundAndLight(Jean);
    JoueurHonte=MarqueurHonte(Jean,DelaiPetiteHonte);
  }
  else if(JeanGagne)
  {
    WinnerSoundAndLight(Jean);
  }
  else
  {
    //Identify winner
    WinnerSoundAndLight(Winner);
  }

  //Reset
  delay(700);
  TurnOffAllLights();
  delay(25);
}

