#ifdef ENABLE_LOGGING
  #define LOG_DEDUEL(a) LOG_GAME(Game_id_DUEL,a)
#else
  #define LOG_DEDUEL(a)
#endif
void DeDuel()
{
  //Joueur 0 = VERT
  //Joueur 1 = BLEU
  int Joueurs[2]={-1,-1};
  unsigned long ClicCount[2]={0,0};
  int Winner=-1;
  int DeltaClic=0;
  bool HasReleased[2]={false};
  float Score=50;
  float ScoreFactor=1;
  float ScoreIncrease=0.27;
  int FinalCtd1ID=11;
  int FinalCtd2ID=12;
  int Chanson=FinalCtd1ID;
  long MusicCounter=0;
  long NextMusicEventCtr=-1;
  int MusicEventId=0;
  int DelayBetweenSongs=300;
  unsigned long ScoreIncCounter=0;
  unsigned long ScoreIncreaseIter=950;
  int ReactionDelay=1;
  int LightDelay=350;
  int ForLightDelay=13;
  int SoundTime=500;
  int NombreNotes;
  int myRand;
  int myRandMin=260;
  int myRandMax=280;
  float MusicIncrease=0.04;
  float FactVit;
  bool TransfertHonte=false;
  int TransfertHonteProb=3;


  if(JoueurHonte!=-1)
  {
    LOG_DEDUEL("HONTE EXISTANTE");
    LOG_DEDUEL("\n");
    Joueurs[1]=JoueurHonte;
    
    LOG_DEDUEL("JoueurHonte:");
    LOG_DEDUEL(JoueurHonte);
    LOG_DEDUEL("\n");
    do
    {
      Joueurs[0]=random(nbj);
    }while (Joueurs[0]==Joueurs[1] || Joueurs[0]==-1);
    
    TransfertHonte=((int)random(TransfertHonteProb)==0);
    LOG_DEDUEL("TransfertHonte:");
    LOG_DEDUEL(TransfertHonte);
    LOG_DEDUEL("\n");
  }
  else
  {
    LOG_DEDUEL("HONTE NON-EXISTANTE");
    LOG_DEDUEL("\n");
    Joueurs[1]=random(nbj);
    do
    {
      Joueurs[0]=random(nbj);
    }while (Joueurs[0]==Joueurs[1] || Joueurs[0]==-1);
  }
  LOG_DEDUEL("Joueur0:");
  LOG_DEDUEL(Joueurs[0]);
  LOG_DEDUEL("\n");
  LOG_DEDUEL("Joueur1:");
  LOG_DEDUEL(Joueurs[1]);
  LOG_DEDUEL("\n");
  
  //SetupInitial
  //Dedu au centre
  //vert allume de 0 à 100
  //Ident le joueur vert.
  //Lights off
  //bleu de 0 à 100
  //Ident le bleu

  if (!SkipLights)
  {
    MoveDEDUFlag(50);
    delay(500);
    
    for (int i=1; i<50 ; i++)
    {
      ActivateGreenLED(i);
      delay(ForLightDelay);
    }
    delay(LightDelay);
    for(int i=0 ; i<2 ; i++)
    {
      ActivateRedLight(Joueurs[0]);
      ActivateGreenLED(0);
      delay(LightDelay);
      DeactivateRedLight(Joueurs[0]);
      ActivateGreenLED(100);
      delay(LightDelay);
    }
    ControlAllLights(false,0,0);
    delay(2*LightDelay);
    for (int i=1; i<50 ; i++)
    {
      ActivateBlueLED(i);
      delay(ForLightDelay);
    }
    delay(LightDelay);
    for(int i=0 ; i<2 ; i++)
    {
      ActivateRedLight(Joueurs[1]);
      ActivateBlueLED(0);
      delay(LightDelay);
      DeactivateRedLight(Joueurs[1]);
      ActivateBlueLED(100);
      delay(LightDelay);
    }
    ControlAllLights(false,0,0);
  }
  
  NombreNotes=SelectionChanson(Chanson);
  myRand= random(myRandMin,myRandMax);
  FactVit=(float) myRand/100;
  LOG_DEDUEL("FactVit:");
  LOG_DEDUEL(FactVit);
  LOG_DEDUEL("\n");

  ReadySound(SoundTime);
  ActivateRedLight(Joueurs[0]);
  ActivateRedLight(Joueurs[1]);

  LOG_DEDUEL("MusicCounter:");
  LOG_DEDUEL(MusicCounter);
  LOG_DEDUEL("\n");
  LOG_DEDUEL("NextMusicEventCtr:");
  LOG_DEDUEL(NextMusicEventCtr);
  LOG_DEDUEL("\n");
  
  //MainGame
  do
  {

    //PLAY NOTES
    if (MusicCounter>NextMusicEventCtr)
    {
      
      LOG_DEDUEL("JOUE UNE NOTE!");
      LOG_DEDUEL("\n");
      LOG_DEDUEL("MusicEventId:");
      LOG_DEDUEL(MusicEventId);
      LOG_DEDUEL("\n");
      tone(Tone_Pin, MaChanson[0][MusicEventId], MaChanson[1][MusicEventId]/FactVit);
      NextMusicEventCtr=MaChanson[1][MusicEventId]/FactVit+MaChanson[2][MusicEventId]/FactVit;

      
      MusicCounter=0;
      MusicEventId++;
      if (MusicEventId==NombreNotes)
      {
        NextMusicEventCtr+=DelayBetweenSongs/FactVit;
        MusicEventId=0;
        
        if(Chanson==FinalCtd1ID)
        {
          Chanson=FinalCtd2ID;
        }
        else
        {
          Chanson=FinalCtd1ID;
        }
        NombreNotes=SelectionChanson(Chanson);
      }
    }
    
    
    //UpdateHasReleased
    for (int i=0; i<=1 ;i++)
    {
      if(!ReadPlayerInput(Joueurs[i]) && !HasReleased[i])
      {
        HasReleased[i]=true;
      }
      delay(ReactionDelay);
      if(HasReleased[i] && ReadPlayerInput(Joueurs[i]))
      {
        HasReleased[i]=false;
        ClicCount[i]++;
        
        LOG_DEDUEL("Clic+:");
        LOG_DEDUEL(i);
        LOG_DEDUEL("\n");
      }
    }

    if(ScoreIncCounter>ScoreIncreaseIter && ScoreFactor<50)
    {
      ScoreIncCounter=0;
      ScoreFactor=ScoreFactor*(ScoreIncrease+1);
      LOG_DEDUEL("New Score Factor:");
      LOG_DEDUEL(ScoreFactor);
      LOG_DEDUEL("\n");

      FactVit=FactVit*(MusicIncrease+1);
      LOG_DEDUEL("New FactVit:");
      LOG_DEDUEL(FactVit);
      LOG_DEDUEL("\n");
    }
    
    DeltaClic=ClicCount[0]-ClicCount[1];
    Score=50+DeltaClic*ScoreFactor;
    

    //Update lights/DEDU based on score
    MoveDEDUFlag(Score);
    if (Score>50)
    {
      ActivateGreenLED((Score-50));
      ActivateBlueLED(0);
    }
    else if (Score<50)
    {
      ActivateBlueLED((50-Score));
      ActivateGreenLED(0);
    }
    else
    {
      ActivateBlueLED(0);
      ActivateGreenLED(0);
    }

    if (Score>99)
    {
      Winner=Joueurs[0];
    }
    else if (Score<1)
    {
      Winner=Joueurs[1];
    }

    
    MusicCounter++;
    ScoreIncCounter++;

  }while(Winner==-1);

  DeactivateRedLight(Joueurs[0]);
  DeactivateRedLight(Joueurs[1]);
  OneUp();
  //GAGNANT TROUVÉ
  LOG_DEDUEL("Winner:");
  LOG_DEDUEL(Winner);
  LOG_DEDUEL("\n");

  if (Winner==Joueurs[0])
  {
    for (int i=1; i<50 ; i++)
    {
      ActivateGreenLED(i);
      delay(20);
    }
    delay(LightDelay);
    WinnerSoundAndLight(Joueurs[0]);
  }
  else
  {
    for (int i=1; i<50 ; i++)
    {
      ActivateBlueLED(i);
      delay(20);
    }
    delay(LightDelay);
    ActivateBlueLED(0);
    ActivateRedLight(Joueurs[1]);
    for(int i=0 ; i<2 ; i++)
    {
      WinnerSound();
      delay(LightDelay);
      DeactivateRedLight(Joueurs[1]);
      ActivateBlueLED(100);
      delay(LightDelay);
      ActivateRedLight(Joueurs[1]);
      ActivateBlueLED(0);
    }
  }

  
  
  delay(300);
  MoveDEDUFlag(0);
  delay(500);
  ControlAllLights(false,0,0);
  delay(500);
  
  if(TransfertHonte && Winner==Joueurs[1])
  {
    ///BRUIT ET TRANSFERT HONTE
    LooserSoundAndLight(Joueurs[0],false);
    JoueurHonte=MarqueurHonte(Joueurs[0],DelaiPetiteHonte);
    //Reset jeux qui transfèrent la honte
    ResetProbHonte();
    
    LOG_DEDUEL("Nouveau JoueurHonte:");
    LOG_DEDUEL(JoueurHonte);
    LOG_DEDUEL("\n");
  }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    for (int i=0 ; i<NumSteps ; i++)
    {
      ControlAllLights(false,CurrentIntensity,CurrentIntensity);
      CurrentIntensity+=MaxIntensity/NumSteps;
      delay(TimeDelay);
    }
  
    
    for (int i=0 ; i<NumSteps-1 ; i++)
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
    for(int i=0;i<=nbj_raw;i++)
    {
      LightCounterPlayer[i]=0;
    }
    
    //Check if people press
    do
    {
      for(int i=0;i<=nbj_raw;i++)
      {
        if(ReadPlayerInput(i) && PlayerState[i]!=Looser)
        {
          LOG_ULTI("PressLooser: ");
          LOG_ULTI(i);
          LOG_ULTI("\n");
          
          if(PlayerState[i]!=Looser)
          {
            NbPlayersStillInGame--;
            LightCounterPlayer[i]=LightTime;
          }
          PlayerState[i]=Looser;
          ActivateRedLight(i);
          tone(Tone_Pin,800,ToneTime);
          if(DelayCounter<2*LightTime)
          {
            DelayCounter=0;
          }
          else
          {
            DelayCounter-=2*LightTime;
          }
        }
        if(LightCounterPlayer[i]>0)
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
    for(int i=0 ; i<nbj; i++)
    {
      LOG_ULTI("  ");
      LOG_ULTI(PlayerState[i]);
    }
    LOG_ULTI("\n");
      
    //Check if only one person left.
    if(NbPlayersStillInGame==1)
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
      for(int i=0 ; i<nbj; i++)
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
      if(nPotPlayers<2)
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
        if(PlayerState[i]==GuaranteedPlay)
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
          if(PlayerState[i]==ReadyToPlay)
          {
            if(random(20,30)>28)
            {
              nPlayersSelected++;
              PlayerState[i]=InGame;
            }
          }
          if(nPlayersSelected==nPlayersForRound)
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
      for(int i=0 ; i<nbj; i++)
      {
        LOG_ULTI("  ");
        LOG_ULTI(PlayerState[i]);
      }
      LOG_ULTI("\n");
  
      //Reset HasReleased for in-game players and set light
      for (int i=0; i<nbj;i++)
      {
        if(PlayerState[i]==InGame)
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
          if(PlayerState[i]==InGame && !ReadPlayerInput(i) && !HasReleased[i])
          {
            HasReleased[i]=true;
          }
          delay(15);
          if(PlayerState[i]==InGame && HasReleased[i] && ReadPlayerInput(i))
          {
            //WINNER
            RoundWinner=i;
            DeactivateRedLight(i);
            break;
          }
        }
      }while(RoundWinner==-1);
      
      //WinSound
      for (int i = 1; i<= 120; i++)
      {
        Tone_Frequency = 500 + 30 * i;
        tone(Tone_Pin, Tone_Frequency, 3);
        delay(3);
      }
      noTone(Tone_Pin);
      //Flash winner light
      for (int i=0 ; i<2 ; i++)
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
        if(PlayerState[i]==InGame)
        {
          if(i==RoundWinner)
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
      if(PlayerState[i]==Winner)
      {
        Ultimatewinner=i;
        nWinners++;
      }
      if(PlayerState[i]==Looser) nLoosers++;
    }
    
    if(nWinners==1 && nLoosers==(nbj-1))
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
  for (int i=0 ; i<NumSteps ; i++)
  {
    ActivateGreenLED(CurrentIntensity);
    CurrentIntensity+=MaxIntensity/NumSteps;
    delay(TimeDelay);
    
  }
  OneUp();
  for (int i=0 ; i<2 ; i++)
  {
    ActivateGreenLED(0);
    ActivateRedLight(Ultimatewinner);
    delay(500);
    ActivateGreenLED(100);
    DeactivateRedLight(Ultimatewinner);
    delay(500);
  }
  
  ControlAllLights(false,0,0);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DQP2()
{
  int const NumIter_same=10;
  int const ScoreTol=3;
  
  int sum[nbj_raw_max];
  int Looser=-1;
  int LooserCount=0;
  bool looserfound=false;
  //Init Setup: Mauve comme DQP1
  ActivateBlueLED(100);
  TurnOnAllRedLights();

  int NumActiveOutputs=-1;
  
  do
  {
    ReadInputToggleOutput(nbj_raw);
    delay(random(5,30));

    
    LooserCount=0;
    looserfound=false;
    for (int i=0;i<=nbj_raw;i++)
    {
      if(ReadPlayerInput(i) || ReadPlayerOutput(i))
      {
        LooserCount++;
        Looser=i;
      }
    }
    
    if(LooserCount==1)
    {
      looserfound=true;
    }
    else if(LooserCount==0)
    {
      TurnOnAllRedLights();
      delay(20);
    }
  }while(!looserfound);



  //SCORE
  ActivateBlueLED(10);
  TurnOffNonActivePlayerRedLights();

  

  for (int i = 1; i<= 80; i++)
  {
    Tone_Frequency = 2000 - 20 * i;
    tone(Tone_Pin, Tone_Frequency);
    delay(10);
  }
  noTone(Tone_Pin);

  //Identify the Loosers
  for (int e = 1; e<= 4; e++) {
    
    ActivateRedLight(Looser);
    
    delay(500);


    DeactivateRedLight(Looser);
    
    delay(500);
  }
  DeactivateBlueLED();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MIN()
{
  int Sum0 = 0;
  int Sum1 = 0;
  bool allloosers;
  bool noloosers=false;
  int DeclaredLoosers[nbj_max];
  int LightDelay=800;
  for (int i=0; i<=nbj_raw_max;i++)
  {
    DeclaredLoosers[i]=0;
  }
  
  //Init Setup: Mauve comme DQP1
  ActivateGreenLED(100);
  TurnOnAllRedLights();
  
  int RandTimer=5+random(9);

  float TimeInterval = 900;
  float TimeDelta;
  
  for(int i = 0;i<RandTimer;i++)
  {
    tone(Tone_Pin,250,10);
    delay(400);
    ActivateGreenLED(50);
    tone(Tone_Pin,700,10);
    delay(TimeInterval);
    ActivateGreenLED(100);

    TimeInterval-=(float)(random(300,900)/RandTimer);
  }
  TurnOffAllRedLights();
  DeactivateGreenLED();
  delay(500);
  CheckAllActive(nbj_raw);
  delay(500);

  for (int i=0; i<=nbj_raw ; i++)
  {
    if (InputState[i])
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
    allloosers=true;
  }
  else if(Sum0>Sum1) // Low Looses
  {
    for (int i=0; i<=nbj_raw;i++)
    {
      if (!InputState[i])
      {
        DeclaredLoosers[i]=1;
      }
    }
    allloosers=false;
  }
  else if(Sum1>Sum0)//HIGH Looses
  {
    for (int i=0; i<=nbj_raw;i++)
    {
      if (InputState[i])
        DeclaredLoosers[i]=1;
    }
    allloosers=false;
  }
  else//NoLoosers, start over.
  {
    ActivateGreenLED(100);
    OneUp();
    for(int i=0 ; i<4 ; i++)
    {
      DeactivateGreenLED();
      delay(LightDelay);
      ActivateGreenLED(100);
      delay(LightDelay);
    }
    
    TurnOffAllLights();
    noloosers=true;
  }

  if (!noloosers && !allloosers)
  {
    ActivateGreenLED(20);
    
    OneUp();
    //Sound for winners.
    for(int i=0 ; i<4 ; i++)
    {
      for (int i=0; i<=nbj_raw;i++)
      {
        if (DeclaredLoosers[i]==0)
          ActivateRedLight(i);
      }
      DeactivateGreenLED();
      delay(LightDelay);
      for (int i=0; i<=nbj_raw;i++)
      {
        if (DeclaredLoosers[i]==0)
          DeactivateRedLight(i);
      }
      ActivateGreenLED(20);
      delay(LightDelay);
    }
  }
  else if(!noloosers && allloosers)
  {
    AllLoosersSoundAndLight();
  }
  TurnOffAllLights();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ENABLE_LOGGING
  #define LOG_CHANSON(a) LOG_GAME(Game_id_JC,a)
#else
  #define LOG_CHANSON(a)
#endif

void JeuChanson(int id_chanson)
{
  LOG_CHANSON("CHANSON START");
  LOG_CHANSON("\n");
  
  int NombreNotes;
  int NumberOfScores;
  int myRand;
  int ProchainJoueur;
  float FacteurVitesse;
  int ToneIncrease=200;
  int BaseTone=800;
  int CurTone;
  int WinTeam;
  float IndivScore;
  float ScorePlay[2];
  float ScoreWait[2];
  float ScoreWeightPlay=0.66;
  float ScoreWeightWait=1-ScoreWeightPlay;
  bool LengthScoreFactor=true;
  float PlayTotal;
  float WaitTotal;
  float ScoreWeight;
  float CumulativeWait;
  float CumulativePlay;
  bool FactorTeamSize = true;
  float TeamSizeScoreRatio[2]={1,1};
  float TeamSizeModifier=1.03;
  float ChansonMod[ParamChansons][NbNoteMax];
  //Pour Chaque joueur: Silence,puis Musique.
  float LeurTemps[ParamChansons-1][NbNoteMax];
  float Scores[2];
  
  NombreNotes=SelectionChanson(id_chanson);
  AllocateTwoTeams(nbj_max);
  
  if(NbJoueursEq1>NbJoueursEq2 && FactorTeamSize==true)
  {
    TeamSizeScoreRatio[0]=TeamSizeModifier;
  }
  else if(NbJoueursEq2>NbJoueursEq1 && FactorTeamSize==true)
  {
    TeamSizeScoreRatio[1]=TeamSizeModifier;
  }

  LOG_CHANSON("TeamSizeScoreRatio[0]:");
  LOG_CHANSON(TeamSizeScoreRatio[0]);
  LOG_CHANSON("\n");
  LOG_CHANSON("TeamSizeScoreRatio[1]:");
  LOG_CHANSON(TeamSizeScoreRatio[1]);
  LOG_CHANSON("\n");

  //Set White Lights
  ActivateBlueLED(100);
  ActivateGreenLED(100);
  TurnOnAllRedLights();
  delay(2000);

  //Répéter pour chaque équipe
  for (int e = 0; e<NbEquipes ; e++)
  {
    if(LengthScoreFactor)
    {
      PlayTotal=0;
      WaitTotal=0;
      CumulativeWait=0;
      CumulativePlay=0;
    }
    
    //OrdreJoueurs
    DefinirOrdreJoueurs(e,NombreNotes);

    //Definir Facteur Vitesse
    myRand= random(ChansonFacteurRandomMin,ChansonFacteurRandomMax);
    FacteurVitesse=(float) myRand/100;

    LOG_CHANSON("Chanson Mod:");
    LOG_CHANSON("\n");
    //Transform MaChanson
    for(int n=0; n<NombreNotes; n++)
    {
      ChansonMod[0][n]=MaChanson[0][n];
      ChansonMod[1][n]=MaChanson[1][n]/FacteurVitesse;
      ChansonMod[2][n]=MaChanson[2][n]/FacteurVitesse;

      if(LengthScoreFactor)
      {
        PlayTotal+=ChansonMod[1][n];
        if (n<NombreNotes-1)
        {
          WaitTotal+=ChansonMod[2][n];
        }
      }
      
      LOG_CHANSON(n);
      LOG_CHANSON(":  OrigPlay:");
      LOG_CHANSON(MaChanson[1][n]);
      LOG_CHANSON("  NewPlay:");
      LOG_CHANSON(ChansonMod[1][n]);
      LOG_CHANSON(":  OrigWait:");
      LOG_CHANSON(MaChanson[2][n]);
      LOG_CHANSON("  NewWait:");
      LOG_CHANSON(ChansonMod[2][n]);
      LOG_CHANSON("\n");
    }
    
    LOG_CHANSON("PlayTotal:");
    LOG_CHANSON(PlayTotal);
    LOG_CHANSON("\n");
    LOG_CHANSON("WaitTotal:");
    LOG_CHANSON(WaitTotal);
    LOG_CHANSON("\n");
    LOG_CHANSON("FacteurVitesse:");
    LOG_CHANSON(FacteurVitesse);
    LOG_CHANSON("\n");
    
    TurnOffAllRedLights();
    DeactivateBlueLED();
    DeactivateGreenLED();
    delay(1000);
    
    for(int i=0 ; i<=nbj_raw ; i++)
    {
      if(Equipes[i]==e)
      {
        ActivateRedLight(i);
        delay(400);
      }
    }

    delay(1500);
    TurnOffAllRedLights();
    delay(1200);

    //Show the Player
    for(int n=0; n<NombreNotes; n++)
    {
      PlayNoteWithLight(ChansonMod[0][n], ChansonMod[1][n], ChansonMod[2][n],OrdreJoueurs[n]);
    }

    
    TurnOffAllRedLights();
    delay(1500);
    for(int t=0; t<4 ; t++){
      tone(Tone_Pin,800,10);
      delay(700);
    }
    
    for(int n=0; n<NombreNotes; n++)
    {
      ActivateRedLight(OrdreJoueurs[n]);
      TakeTime();
      do
      {
        noTone(Tone_Pin);
        delay(5);
      }while(!ReadPlayerInput(OrdreJoueurs[n]));
      LeurTemps[0][n]=TimeDiff();
      TakeTime();
      do{
        tone(Tone_Pin,ChansonMod[0][n], 20);
        delay(5);
      }while(ReadPlayerInput(OrdreJoueurs[n]));
      LeurTemps[1][n]=TimeDiff();
      noTone(Tone_Pin);
      DeactivateRedLight(OrdreJoueurs[n]);
    }

    //LOG DES SCORES
    LOG_CHANSON("Scores Chansons");
    LOG_CHANSON("\n");

    
    LOG_CHANSON("TEMPS ORIGINAL");
    LOG_CHANSON("\n");
    
    //ResetScore
    Scores[e]=0;
    ScorePlay[e]=0;
    ScoreWait[e]=0;
    
    for (int n=0; n<NombreNotes; n++)
    {
      if (n!=0)
      {
        //WaitTime
        IndivScore=RelativeError(LeurTemps[0][n],ChansonMod[2][n-1]);
        
        CumulativeWait+=ChansonMod[2][n-1];
        
        if(LengthScoreFactor)
        {
          ScoreWeight=ChansonMod[2][n-1]/WaitTotal;
        }
        else
        {
          ScoreWeight=1/(NombreNotes-1);
        }

        ScoreWait[e]+=IndivScore*ScoreWeight;
        
        //WAIT LOG
        LOG_CHANSON(n);
        LOG_CHANSON(":  WaitPlayer:");
        LOG_CHANSON(LeurTemps[0][n]);
        LOG_CHANSON("  WaitSong:  ");
        LOG_CHANSON(ChansonMod[2][n-1]);
        LOG_CHANSON("  IndivScore:  ");
        LOG_CHANSON(IndivScore);
        LOG_CHANSON("  ScoreWeight:  ");
        LOG_CHANSON(ScoreWeight);
        LOG_CHANSON("  CumulativeWait:  ");
        LOG_CHANSON(CumulativeWait);
        LOG_CHANSON("\n");
        
      }
      
      //PlayTime
      IndivScore=RelativeError(LeurTemps[1][n],ChansonMod[1][n]);

      CumulativePlay+=ChansonMod[1][n];
      
      if(LengthScoreFactor)
      {
        ScoreWeight=ChansonMod[1][n]/PlayTotal;
      }
      else
      {
        ScoreWeight=1/NombreNotes;
      }

      ScorePlay[e]+=IndivScore*ScoreWeight;

        //PLAY LOG
        LOG_CHANSON(n);
        LOG_CHANSON(":  PressPlayer:");
        LOG_CHANSON(LeurTemps[1][n]);
        LOG_CHANSON("  PressSong:  ");
        LOG_CHANSON(ChansonMod[1][n]);
        LOG_CHANSON("  IndivScore:  ");
        LOG_CHANSON(IndivScore);
        LOG_CHANSON("  ScoreWeight:  ");
        LOG_CHANSON(ScoreWeight);
        LOG_CHANSON("  CumulativePlay:  ");
        LOG_CHANSON(CumulativePlay);
    }
    
    Scores[e]=(ScoreWait[e]*ScoreWeightWait + ScorePlay[e]*ScoreWeightPlay)*TeamSizeScoreRatio[e];
    
    LOG_CHANSON("\n");
    LOG_CHANSON("\n");
    LOG_CHANSON("Equipe:");
    LOG_CHANSON(e);
    LOG_CHANSON("  Score:");
    LOG_CHANSON(Scores[e]);
    LOG_CHANSON("  ScoreWait:");
    LOG_CHANSON(ScoreWait[e]);
    LOG_CHANSON("  ScorePlay:");
    LOG_CHANSON(ScorePlay[e]);
    LOG_CHANSON("  CumulativeWait:  ");
    LOG_CHANSON(CumulativeWait);
    LOG_CHANSON("  WaitTotal:  ");
    LOG_CHANSON(WaitTotal);
    LOG_CHANSON("  CumulativePlay:  ");
    LOG_CHANSON(CumulativePlay);
    LOG_CHANSON("  PlayTotal:  ");
    LOG_CHANSON(PlayTotal);
    
    LOG_CHANSON("\n");
    LOG_CHANSON("\n");
    LOG_CHANSON("\n");
  }

  
  
  LOG_CHANSON("Score Weight Play:");
  LOG_CHANSON(ScoreWeightPlay);
  LOG_CHANSON("\n");
  LOG_CHANSON("Score Weight Wait:");
  LOG_CHANSON(ScoreWeightWait);
  LOG_CHANSON("\n");
  
  //
  LOG_CHANSON("FinalScoreBeforeMod 0:");
  LOG_CHANSON(Scores[0]);
  LOG_CHANSON("\nFinalScoreBeforeMod 1:");
  LOG_CHANSON(Scores[1]);
  LOG_CHANSON("\n");
  
  //Winning Team
  if (Scores[0]>Scores[1])
  {
    WinTeam=0;
    Scores[0]=Scores[0]*1.15;
    Scores[1]=Scores[1]*0.85;
  }
  else
  {
    WinTeam=1;
    Scores[0]=Scores[0]*0.85;
    Scores[1]=Scores[1]*1.15;
  }

  for (int i=0 ; i<2;i++)
  {
    if(Scores[i]>1)
    {
      Scores[i]=1;
    }
  }
  
  LOG_CHANSON("FinalScore 0:");
  LOG_CHANSON(Scores[0]);
  LOG_CHANSON("\nFinalScore 1:");
  LOG_CHANSON(Scores[1]);
  LOG_CHANSON("\n");

  
  //Game complete.  Scoring!
  for (int e = 0; e<NbEquipes ; e++)
  {
    TurnOffAllLights();
    MoveDEDUFlag(0);
    delay(1500);
    CurTone=BaseTone;
    for(int i=0 ; i<=nbj_raw ; i++)
    {
      if(Equipes[i]==e)
      {
        ActivateRedLight(i);
        tone(Tone_Pin,CurTone,100);
        delay(200);
        CurTone+=ToneIncrease;
      }
    }

    delay(2000);
    TurnOnAllRedLights();
    delay(250);
    
    for(int j=0 ; j<=Scores[e]*100 ; j++)
    {
      ActivateGreenLED(j);
      ActivateBlueLED(j);
      MoveDEDUFlag(j);
      noTone(Tone_Pin);
      tone(Tone_Pin,800+20*j,300);
      delay(25);
    }
    delay(2000);
    
    MoveDEDUFlag(0);
    TurnOffAllLights();
  }

  delay(500);

  //Winner found, lights on/off!
  for (int a = 1 ; a<= 3 ; a++)  
  {
    IlluminateTeamRedLights(WinTeam);
    
    for (int i = 1; i<= 120; i++)
    {
      Tone_Frequency = 500 + 30 * i;
      tone(Tone_Pin, Tone_Frequency, 3);
      delay(3);
    }
    noTone(Tone_Pin);
    delay (500);
    TurnOffAllRedLights();
    
    ActivateGreenLED(20);
    delay(500);
    DeactivateGreenLED();
  }
  delay(2000);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ENABLE_LOGGING
  #define LOG_PATATE(a) LOG_GAME(Game_id_PC,a)
#else
  #define LOG_PATATE(a)
#endif
void PatateChaude(bool SimpleControls)
{
  unsigned long basetime=5242;
  unsigned long maxrandtime=12242;
  unsigned long GameTimeMillis = basetime+random(maxrandtime);
  unsigned long GameCounter=0;
  unsigned long PressCounter=0;
  int TimeDecMin=42;
  int TimeDecMax=242;
  bool ReadyToSwitch=false;
  int ReactTimeMin=84;
  int ReactTimeMax=2420;
  unsigned long GameCounterPenalite[nbj];
  bool PlayerIsPressing=false;
  bool PreviousState[nbj];
  for(int i=0; i<nbj ; i++)
  {
    GameCounterPenalite[i]=0;
    PreviousState[i]=false;
  }
  #define PenaliteIncrPatate 2000;
  #define Patate_PressRev 150
  #define Patate_PressStall 300

  LOG_PATATE("GameTimeMillis:");
  LOG_PATATE(GameTimeMillis);
  LOG_PATATE("\n");
  GameCounter=0;
  TurnOffAllLights();
  //Lights Setup
  ActivateBlueLED(21);
  delay(1200);

  int LuckyPlayer = random(nbj);
  int NextPlayer;

  
  if(random(2)==0)
  {
     NextPlayer=1;
  }
  else
  {
    NextPlayer=-1;
  }


  MoveDEDUFlag(((float)GameTimeMillis/(float)(basetime+maxrandtime)*random(50,75)));
  delay(500);
  ActivateRedLight(LuckyPlayer);
  
  do
  {
    //Monitor spammers
    for(int i=0; i<nbj ; i++)
    {
      if(ReadPlayerInput(i) && !PreviousState[i] && i!=LuckyPlayer)
      {
        GameCounterPenalite[i]=GameCounter+PenaliteIncrPatate;
        
        LOG_PATATE("Penalite Joueur:");
        LOG_PATATE(i);
        LOG_PATATE("\n");
        LOG_PATATE("GameCounterPenalite[i]:");
        LOG_PATATE(GameCounterPenalite[i]);
        LOG_PATATE("\n");
      }
    }
    
    if(!ReadPlayerInput(LuckyPlayer) && GameCounter>GameCounterPenalite[LuckyPlayer])
    {
      ReadyToSwitch=true;
    }
    
    if(ReadPlayerInput(LuckyPlayer) && ReadyToSwitch && !PlayerIsPressing)
    {
      LOG_PATATE("Change PlayerIsPressing");
      LOG_PATATE("\n");
      PlayerIsPressing=true;
    }


      //CHECK RELEASE
    if (PlayerIsPressing==true)
    {
      LOG_PATATE("I have started Pressing");
      LOG_PATATE("\n");
      //HIGH, Keep counting
      if(ReadPlayerInput(LuckyPlayer))
      {
        LOG_PATATE("I keep Pressing");
        LOG_PATATE("\n");
        PressCounter++;
      }
      else
      {
        LOG_PATATE("SwitchingPlayer!!");
        LOG_PATATE("\n");
        LOG_PATATE("GameTimeMillisIN:");
        LOG_PATATE(GameTimeMillis);
        LOG_PATATE("\n");
        LOG_PATATE("GameCounter:");
        LOG_PATATE(GameCounter);
        LOG_PATATE("\n");
        LOG_PATATE("PressCounter:");
        LOG_PATATE(PressCounter);
        LOG_PATATE("\n");
        //NORMAL DIRECTION
        if (PressCounter<Patate_PressRev || SimpleControls)
        {
          LOG_PATATE("NORMAL DIR!");
          LOG_PATATE("\n");
          DeactivateRedLight(LuckyPlayer);
          LuckyPlayer+=NextPlayer;
          tone(Tone_Pin, 800, 15);
        }
        //REV DIR
        else if (PressCounter>= Patate_PressRev && PressCounter<Patate_PressStall)
        {
          LOG_PATATE("REV DIR!");
          LOG_PATATE("\n");
          DeactivateRedLight(LuckyPlayer);
          LuckyPlayer-=NextPlayer;
          tone(Tone_Pin, 1200, 15);
        }
        else
        {
          //STALL ON PLAYER, TOO LONG PRESS
          LOG_PATATE("STALL");
          LOG_PATATE("\n");
          tone(Tone_Pin, 300, 150);
        }
        
        LOG_PATATE("REDUCING TIME!!");
        LOG_PATATE("\n");
        GameTimeMillis-=(random(TimeDecMin,TimeDecMax));
  
        //AddTimeToAllowReaction
        if (GameTimeMillis-GameCounter<ReactTimeMin)
        {
          LOG_PATATE("\n");
          LOG_PATATE("GIVING MORE TIME!!");
          LOG_PATATE("\n");
          GameTimeMillis+=(random(ReactTimeMin,ReactTimeMax));
        }
        
        LOG_PATATE("GameTimeMillisAFTER:");
        LOG_PATATE(GameTimeMillis);
        LOG_PATATE("\n");

        //Correct New LuckyPlayer
        LuckyPlayer=WrapAround(LuckyPlayer);
        //Activate new lucky Player
        ActivateRedLight(LuckyPlayer);
        ReadyToSwitch=false;
        PlayerIsPressing=false;
        PressCounter=0;
      }
    }
    
    if (random(10000)>9996)
    {
      
      LOG_PATATE("SwitchingSIDE!!");
      LOG_PATATE("\n");
      
      if (NextPlayer == 1)
      {
        NextPlayer=-1;

        //Decrease Flag
        MoveDEDUFlag(random(ServoAnglePercent()));
      }
      else
      {
        //IncreaseFlag
        NextPlayer=1;
        MoveDEDUFlag(random(ServoAnglePercent(),100));
      }
    }

    for(int i=0; i<nbj; i++)
    {
      PreviousState[i]=ReadPlayerInput(i);
    }
    delay(1);
    GameCounter++;
  }while(GameCounter<GameTimeMillis);

  ActivateBlueLED(5);
  
  for (int i = 1; i<= 80; i++)
  {
    Tone_Frequency = 2000 - 20 * i;
    tone(Tone_Pin, Tone_Frequency);
    delay(10);
  }
  noTone(Tone_Pin);
  
  //Identify the Looser
  for (int e = 1; e<= 4; e++) {
    ActivateRedLight(LuckyPlayer);
    delay(500);
    DeactivateRedLight(LuckyPlayer);
    delay(500);
  }

  TurnOffAllLights();
  MoveDEDUFlag(0);
  delay(1200);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ENABLE_LOGGING
  #define LOG_RANDOM(a) LOG_GAME(Game_id_AR,a)
#else
  #define LOG_RANDOM(a)
#endif
void AllRandom()
{
  int Wincondition;
  int NewAssignment[nbj_max]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  bool NumAlreadyAllocated=false;
  int PosAssigned=0;
  int r;
  int r2;
  bool PreviousState[nbj_max]={false};
  bool LightState[nbj_max]={false};
  int OutputSum;
  int Looser=-1;
  int DEDUmaster=-1;
  int DEDUmasterProb=2;
  int DEDUmasterChangeProb=4;
  int DEDUmasterPressCounter=0;
  int DEDUmasterNextChange=random(1,DEDUmasterChangeProb);
  bool Toggle;
  long RandomProb=30000;
  long RandomProbThr=29900;
  #define AR_GraceTime 4242
  #define AR_GAMEDELAY 5
  int GameTimer=0;
  bool GraceTimeOver=false;

  LOG_RANDOM("ALLRANDOM\n");
  
  //InitialSetup CYAN
  TurnOffAllLights();
  
  ActivateBlueLED(10);
  ActivateGreenLED(22);

  if(random(DEDUmasterProb)==0)
  {
    DEDUmaster=random(nbj);
    LOG_RANDOM("DEDUmasterNextChange:");
    LOG_RANDOM(DEDUmasterNextChange);
    LOG_RANDOM("\n");
    RandomProbThr=29950;
  }
  LOG_RANDOM("DEDUMASTER:");
  LOG_RANDOM(DEDUmaster);
  LOG_RANDOM("\n");
  LOG_RANDOM("RandomProbThr:");
  LOG_RANDOM(RandomProbThr);
  LOG_RANDOM("\n");
  
  //Initial Lights setup: 50/50 Lit vs Not Lit
  AllocateTwoTeams(nbj_max);

  //Fill Random Array
  do
  {
    r = random(nbj);
    
    if(NewAssignment[r]==-1)
    {
      do
      {
       NumAlreadyAllocated=false;
       
       r2=random(nbj);
       
       for(int j=0;j<=nbj_raw;j++)
       {
        
        if (NewAssignment[j]==r2)
        {
          
          NumAlreadyAllocated=true;
          break;
        }
       }

       if(!NumAlreadyAllocated)
       {
        NewAssignment[r]=r2;
        PosAssigned++;
       }
       
      }while(NewAssignment[r]==-1);
    }
  }while(PosAssigned<nbj);



  //Activate Based on  assignment from previous call
  for(int i=0 ; i<=nbj_raw ; i++)
  {
    if(Equipes[i]==0)
    {
      ActivateRedLight(NewAssignment[i]);
      LightState[i]=true;
    }
    LOG_RANDOM("Player:");
    LOG_RANDOM(i);
    LOG_RANDOM("  Light:");
    LOG_RANDOM(NewAssignment[i]);
    LOG_RANDOM("\n");
  }
  
  delay(800);
  if(random(2)==0)
  {
    Wincondition=1;
    MoveDEDUFlag(0);
  }
  else
  {
    Wincondition=nbj-1;
    MoveDEDUFlag(100);
  }

  delay(800);
  ReadySound(500);

  //Main game.
  do
  {
    //Change win condition randomly regardless of DEDUMASTER
    if(random(RandomProb)>RandomProbThr)
    {
      LOG_RANDOM("Changing WinCond:");
      if(random(2)==0)
      {
        LOG_RANDOM("LOW");
        Wincondition=1;
        MoveDEDUFlag(0);
      }
      else
      {
        LOG_RANDOM("HIGH");
        Wincondition=nbj-1;
        MoveDEDUFlag(100);
      }
      LOG_RANDOM("\n");
    }
    
    OutputSum=0;
    for (int i=0 ; i<=nbj_raw ; i++)
    {
      Toggle=false;
      //IF PLAYER IS HIGH AND PREV IS LOW, Toggle his light
      if (ReadPlayerInput(i) && !PreviousState[i])
      {
        Toggle=true;
        LightState[i]=ToggleOutput(NewAssignment[i]);
      }
      PreviousState[i]=ReadPlayerInput(i);
      OutputSum+=LightState[i];

      if(i==DEDUmaster && Toggle)
      {
        LOG_RANDOM("DEDUmasterPressCounter:");
        LOG_RANDOM(DEDUmasterPressCounter);
        LOG_RANDOM("\n");
        if(DEDUmasterPressCounter==DEDUmasterNextChange)
        {
          LOG_RANDOM("Change FLAG:");
          LOG_RANDOM("\n");
          if(Wincondition==1)
          {
            Wincondition=nbj-1;
            MoveDEDUFlag(100);
          }
          else
          {
            Wincondition=1;
            MoveDEDUFlag(0);
          }
          DEDUmasterNextChange=random(0,DEDUmasterChangeProb);
          DEDUmasterPressCounter=0;
          LOG_RANDOM("DEDUmasterPressCounter:");
          LOG_RANDOM(DEDUmasterPressCounter);
          LOG_RANDOM("\n");
          LOG_RANDOM("DEDUmasterNextChange:");
          LOG_RANDOM(DEDUmasterNextChange);
          LOG_RANDOM("\n");
        }
        else
        {
          DEDUmasterPressCounter++;
        }
      }
    }

    //Win Condition
    if (OutputSum == Wincondition && GraceTimeOver)
    {
      if (Wincondition==1)
      {
        for (int i=0 ; i<=nbj_raw ; i++)
        {
          if(LightState[i])
          {
            Looser=i;
            break;
          }
        }
      }
      else
      {
        for (int i=0 ; i<=nbj_raw ; i++)
        {
          if(!LightState[i])
          {
            Looser=i;
            break;
          }
        }
      }
    }
    
    delay(AR_GAMEDELAY);
    if(!GraceTimeOver)
    {
      GameTimer+=AR_GAMEDELAY;
      if(GameTimer>AR_GraceTime)
      {
        GraceTimeOver=true;
        LOG_RANDOM("GraceTimeOver\n");
      }
    }
  }while(Looser==-1);


  
  for (int i = 1; i<= 80; i++)
  {
    Tone_Frequency = 2000 - 20 * i;
    tone(Tone_Pin, Tone_Frequency);
    delay(10);
  }
  noTone(Tone_Pin);
  delay(700);

  TurnOffAllRedLights();
  ActivateGreenLED(5);
  ActivateBlueLED(5);

  delay(700);
  
  //Identify the Looser
  for (int e = 1; e<= 4; e++) {
    ActivateRedLight(Looser);
    delay(500);
    DeactivateRedLight(Looser);
    delay(500);
  }
  MoveDEDUFlag(0);
  TurnOffAllLights();
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////













