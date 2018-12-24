#ifdef ENABLE_LOGGING
  #define LOG_JD(a) LOG_GAME(Game_id_JD,a)
#else
  #define LOG_JD(a)
#endif
void JeanDit()
{
  WaitForAllNonActive(nbj_raw_max);

  //Tunables
  int CounterJeanPerd=9000;
  const int DisableJeanRandMin=100;
  const int DisableJeanRandMax=542;
  int MaxCounterDisableJean=300;
  
  int Winner=-1;
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

    if(!DisableJean && PreviousState[Jean]==LOW && ReadPlayerInput(Jean)==HIGH)
    {
      //Reverse TargetState
      TargetState=!TargetState;
      DisableJean=true;
      if(TargetState) MoveDEDUFlag(100);
      else MoveDEDUFlag(0);
    }
    
    
    for (int i=0;i<nbj;i++)
    {
      CurrentState[i]=ReadPlayerInput(i)==HIGH? true:false;
    }
    
    //Save current into previous.
    for (int i=0;i<nbj;i++)
    {
      PreviousState[i]=CurrentState[i];
    }
    delay(GameDelay);

    //Check Winner or JeanPerd
    if(GameCounter>CounterJeanPerd)
    {
      JeanPerd=true;
    }
    
    
    GameCounter++;
  }while(Winner==-1 && !JeanPerd && !JeanGagne);

  TurnOffAllLights();
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

