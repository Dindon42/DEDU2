#ifdef ENABLE_LOGGING
  #define LOG_ED(a) LOG_GAME(Game_id_ED,a)
#else
  #define LOG_ED(a)
#endif
void EstimeDedu()
{
  //Tunables//
  //Control Game Length
  const int MaxMainGameCycles=16;
  const int AbsoluteMaxMainGameCycles=20;
  
  //Control DEDU speed
  const int Full_Cycle_Min=8;
  const int Full_Cycle_Max=15;
  
  //Control Init
  const int num_start_cycle=4;
  
  //Control sound
  bool NoTone=true;
  //END TUNABLES//
  
  //LOCALS
  int SavedTonePin=Tone_Pin;
  if(NoTone)
  {
    Tone_Pin=9999;
  }
  int Full_Cycle=(random(Full_Cycle_Min,Full_Cycle_Max))*100;
  int GameCounter=0;
  int GameCycles=0;
  const int newtone=25;
  const int newpos=10;
  const int tone_min=200;
  const int game_delay=1;
  bool GoingUp=true;
  int Win=random(0.2*Full_Cycle,0.8*Full_Cycle);
  int LightUp=Full_Cycle/nbj_max;
  int LightCount=0;
  int PlayersInGame=nbj;
  const int num_items=3;
  //0 Abs Score
  //1 Cycles
  //2 GameCounter At click
  int Scores[nbj][num_items];
  for (int i=0; i<nbj; i++)
  {
    for (int j=0; j<num_items; j++)
    {
      Scores[i][j]=-1;
    }
  }
  bool PreviousState[nbj_max]={false};
  bool CurrentState[nbj_max];
  LOG_ED("ESTIME DEDU!");
  LOG_ED("Win");
  LOG_ED(Win);
  LOG_ED("\n");
  LOG_ED("Full_Cycle");
  LOG_ED(Full_Cycle);
  LOG_ED("\n");
  
  //Signature: Dedu monte/descend et lumières individuelles consécutives.  Son Monte descend.
  //Après 1 cycle, le DEDU s'arrête sur le target de victoire et toutes les lumières s'allument.
  //Lancer le jeu avec ReadySound.  Éteindre toutes les lumières, puis commencer.
  for (int i=0; i<num_start_cycle; i++)
  {
    for (int j=0 ; j<Full_Cycle ; j++)
    {
      if(GoingUp)
      {
        if(j%newpos==0) MoveDEDUFlag(((float)j/(float)Full_Cycle)*100);
        if(j%newtone==0) tone(Tone_Pin,tone_min+j,newtone);
      }
      else
      {
        if(j%newpos==0) MoveDEDUFlag((((float)Full_Cycle-(float)j)/(float)Full_Cycle)*100);
        if(j%newtone==0) tone(Tone_Pin,tone_min+Full_Cycle-j,newtone);
      }
      delay(game_delay);
      if(j%LightUp==0)
      {
        if(GoingUp)
        {
          ActivateRedLight(LightCount);
          LightCount++;
        }
        else
        {
          DeactivateRedLight(LightCount);
          LightCount--;
        }
      }
    }
    GoingUp=!GoingUp;
  }
  delay(500);
  TurnOnAllRedLights();
  for (int j=0 ; j<Win ; j++)
  {
    if(GoingUp)
    {
      if(j%newpos==0) MoveDEDUFlag(((float)j/(float)Full_Cycle)*100);
      if(j%newtone==0) tone(Tone_Pin,tone_min+j,newtone);
    }
    delay(game_delay);
  }
  delay(newtone);
  for(int i=0; i<2; i++)
  {
    TurnOffAllRedLights();
    delay(500);
    TurnOnAllRedLights();
    PlayNote(Tone_Pin,tone_min+Win,500,0);
  }
  TurnOffAllRedLights();
  delay(500);
  MoveDEDUFlag(0);
  delay(500);
  
  //Une fois que le jeu démarre, le DEDU va monter/descendre.
  //À tout moment,  les joueurs peuvent cliquer (trans OFF ON) pour faire leur choix.
  //Enregistrer la valeur du DEDU lorsque le joueur pèse, illuminer sa lumière pour indiquer que le choix est fait.

  GoingUp=true;
  //MAIN GAME LOOP
  do
  {
    //Move DEDUFLAG
    if(GoingUp)
    {
      if(GameCounter%newpos==0) MoveDEDUFlag(((float)GameCounter/(float)Full_Cycle)*100);
      if(GameCounter%newtone==0) tone(Tone_Pin,tone_min+GameCounter,newtone);
    }
    else
    {
      if(GameCounter%newpos==0) MoveDEDUFlag((((float)Full_Cycle-(float)GameCounter)/(float)Full_Cycle)*100);
      if(GameCounter%newtone==0) tone(Tone_Pin,tone_min+Full_Cycle-GameCounter,newtone);
    }
    
    //Read current state
    for (int i=0;i<nbj;i++)
    {
      CurrentState[i]=ReadPlayerInput(i)==HIGH? true:false;
      //Detect player press.
      if(!PreviousState[i] && CurrentState[i] && Scores[i][0]==-1)
      {
        //RECORD PLAYER SCORE BASED ON GAMECOUNTER AND CYCLES.
        if(GoingUp) Scores[i][2]=GameCounter;
        else Scores[i][2]=Full_Cycle-GameCounter;
        Scores[i][0]=abs(Win-Scores[i][2]);
        Scores[i][1]=GameCycles;
        ActivateRedLight(i);
        PlayersInGame--;

        
        LOG_ED("\nPlayerPressing!\n");
        LOG_ED("Player:");
        LOG_ED(i);
        LOG_ED("\n");
        LOG_ED("AbsoluteScore:");
        LOG_ED(Scores[i][0]);
        LOG_ED("\n");
        LOG_ED("Scores[i][2]:");
        LOG_ED(Scores[i][2]);
        LOG_ED("\n");
        LOG_ED("GoingUp=");
        LOG_ED(GoingUp);
        LOG_ED("\n");
        LOG_ED("GameCounter=");
        LOG_ED(GameCounter);
        LOG_ED("\n");
        LOG_ED("GameCycles=");
        LOG_ED(GameCycles);
        LOG_ED("\n");
        LOG_ED("PlayersInGame=");
        LOG_ED(PlayersInGame);
        LOG_ED("\n");
        LOG_ED("\n");
      }
    }
    
    //Save current in previous state
    for (int i=0;i<nbj;i++)
    {
      PreviousState[i]=CurrentState[i];
    }
    
    //Increment Counter and Wait.
    GameCounter++;
    delay(game_delay);
    
    //Reset Condition
    if(GameCounter%Full_Cycle==0)
    {
      GameCounter=0;
      GameCycles++;
      GoingUp=!GoingUp;
      if(PlayersInGame<=0) GameCycles=MaxMainGameCycles;
    }
  //Une fois que tout le monde a choisi sa valeur ou que le DEDU a cyclé x fois, arrêter le jeu.
  }while((GameCycles<MaxMainGameCycles || PlayersInGame==nbj) && GameCycles<AbsoluteMaxMainGameCycles);

  //ResetTonePin
  Tone_Pin=SavedTonePin;
  
  //FLAG DOWN, LIGHTS OUT
  MoveDEDUFlag(0);
  TurnOffAllRedLights();

  
  int Winner=-1;
  //Deal with players who have not made their choices at game end.
  for(int i=0; i<nbj; i++)
  {
    if(Scores[i][0]!=-1)
    {
      if(Winner==-1)
      {
        Winner=i;
      }
      else if(Scores[i][0]<Scores[Winner][0] || (Scores[i][0]==Scores[Winner][0] && Scores[i][1]<Scores[Winner][1]))
      {
        Winner=i;
      }
    }
  }

  //No one clicked at game end.
  if(Winner==-1)
  {
    AllLoosers();
  }
  else
  {
    int NumScored=0;
    bool Scored[nbj]={false};
    
    do
    {
      int Player=random(nbj);
      LOG_ED("Player:");
      LOG_ED(Player);
      LOG_ED("\n");
      if(Scored[Player]==false && Player!=Winner)
      {
        Scored[Player]=true;
        NumScored++;

        ActivateGreenLED(20);
        MoveDEDUFlag(((float)Win/(float)Full_Cycle)*100);
        delay(1000);
        ActivateGreenLED(0);
        
        ActivateRedLight(Player);
        delay(500);
        MoveDEDUFlag(((float)Scores[Player][2]/(float)Full_Cycle)*100);
        tone(Tone_Pin,200,200);
        delay(500);
        DeactivateRedLight(Player);
        delay(500);
        ActivateRedLight(Player);
        tone(Tone_Pin,200,200);
        delay(500);
        DeactivateRedLight(Player);
        
        MoveDEDUFlag(((float)Win/(float)Full_Cycle)*100);
      }
    }while (NumScored<(nbj-1));
    
    //WINNER
    ActivateGreenLED(20);
    MoveDEDUFlag(((float)Win/(float)Full_Cycle)*100);
    delay(1000);
    ActivateGreenLED(0);
    ActivateRedLight(Winner);
    delay(500);
    MoveDEDUFlag(((float)Scores[Winner][2]/(float)Full_Cycle)*100);
    WinnerSoundAndLight(Winner);

    
    MoveDEDUFlag(0);
    TurnOffAllLights();
  }
  
  //Pour le score. Rapidement éliminer tous les joueurs sauf les 3 meilleurs.
  //Pour ce faire, montrer le score de victoire, puis celui du joueur. Faire delta-son, puis un buzz et lumière clignotante.
  //Pour le meilleur: cycler entre les positions des 3 meilleurs quelques fois, puis faire le pattern précédent pour les 2 plus bas.
  //Refaire le delta une dernière fois pour le meilleur, puis lui donner winnersoundlight();
}


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
  int DisableJeanRandMin=15200;
  int DisableJeanRandMax=20542;

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
    if(i!=Jean) PlayersInGame[i]=true;
  }
  bool PlayerSafe[nbj]={false};
  for (int i=0; i<nbj; i++)
  {
    if(i!=Jean) PlayerSafe[i]=true;
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
    
    if(DisableJean && !NewRound)
    {
      ActivateGreenLED((100 - (int)(CounterDisableJean*DisableJeanLightFactor))/2);
      CounterDisableJean++;
      if(CounterDisableJean>MaxCounterDisableJean || ((100 - (int)(CounterDisableJean*DisableJeanLightFactor))/2)<2)
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

    if(NewRound)
    {
      ActivateGreenLED(0);
      if(GameCounter%100==0)
      {
        ToggleOutput(RoundLooser);
        Flash++;
      }

      //Prepare for new round
      if(Flash>NewRoundFlash)
      {
        Flash=0;
        NewRound=false;
        DisableJean=false;
        TurnOffAllRedLights();
        ActivateRedLight(Jean);
      }
    }
    
    //Check Winner or JeanPerd
    if(GameCounter>CounterJeanPerd)
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
      if(!DisableJean && !PreviousState[Jean] && ReadPlayerInput(Jean)==HIGH)
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
          if(PlayersInGame[i])
          {
            if(ReadPlayerOutput(i)==HIGH)
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
          DisableJeanRandMin=DisableJeanRandMin-DisableJeanMinDelta;
          DisableJeanRandMax=DisableJeanRandMax-DisableJeanMaxDelta;
          
          if(TargetState) MoveDEDUFlag(100);
          else MoveDEDUFlag(0);
          
          //Reset SafeState, Activate Player LED, Deactivate Jean.
          for (int i=0; i<nbj; i++)
          {
            if(i==Jean) DeactivateRedLight(i);
            if(PlayersInGame[i])
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

    
    if(!JeanPerd && !JeanGagne)
    {
      for (int i=0;i<nbj;i++)
      {
        CurrentState[i]=ReadPlayerInput(i)==HIGH? true:false;
        if(i!=Jean && PlayersInGame[i])
        {
          if(!PreviousState[i] && CurrentState[i])
          {
            ToggleOutput(i);
            if(PlayerSafe[i])
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
        if(PlayersInGame[i])
        {
          NumInGame++;
          if(PlayerSafe[i])
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
      if(NumInGame-NumSafe==1)
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
      if(GameCounter%1000==0)
      {
        LOG_JD("PlayersInGame:");
        LOG_JD(NumInGame);
        LOG_JD("\n");
        LOG_JD("Safe Players:");
        LOG_JD(NumSafe);
        LOG_JD("\n");
      }

      if(NumInGame<=0) JeanGagne=true;
      else if(NumInGame>1) Winner=-1;
      
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

