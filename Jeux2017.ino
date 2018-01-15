#ifdef ENABLE_LOGGING
  #define LOG_DEDUEL(a) LOG_GAME(11,a)
#else
  #define LOG_DEDUEL(a)
#endif
void DeDuel()
{
  //Joueur 0 = VERT
  //Joueur 1 = BLEU
  int Joueurs[2]={-1,-1};
  long ClicCount[2]={0,0};
  int Winner=-1;
  int DeltaClic=0;
  int NewDeltaClic=0;
  bool HasReleased[2]={false,false};
  float Score=50;
  float ScoreFactor=1;
  float ScoreIncrease=0.3;
  unsigned long GameCounter=0;
  unsigned long ScoreIncreaseIter=200;
  int LightDelay=350;
  int ForLightDelay=13;
  int SoundTime=500;

  if(JoueurHonte!=-1)
  {
    LOG_DEDUEL("HONTE EXISTANTE");
    LOG_DEDUEL("\n");
    Joueurs[1]=JoueurHonte;
    do
    {
      Joueurs[0]=random(nbj);
    }while (Joueurs[0]==Joueurs[1] || Joueurs[0]==-1);
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
    delay(1000);
    for (int i=1; i <50 ; i++)
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
    for (int i=1; i <50 ; i++)
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
  
  
  ActivateRedLight(Joueurs[0]);
  ActivateRedLight(Joueurs[1]);
  ReadySound(SoundTime);
  DeactivateRedLight(Joueurs[0]);
  DeactivateRedLight(Joueurs[1]);

  
  //MainGame
  do
  {
    GameCounter++;
    //UpdateHasReleased
    for (int i=0; i<=1 ;i++)
    {
      /*
      LOG_DEDUEL("\n");
      LOG_DEDUEL("i:");
      LOG_DEDUEL(i);
      LOG_DEDUEL("\n");
      LOG_DEDUEL("Joueurs[]:");
      LOG_DEDUEL(Joueurs[i]);
      LOG_DEDUEL("\n");
      LOG_DEDUEL("HasReleased[]:");
      LOG_DEDUEL(HasReleased[i]);
      LOG_DEDUEL("\n");
      */

      
      if(ReadPlayerInput(Joueurs[i])==LOW && HasReleased[i]==false)
      {
        HasReleased[i]=true;
      }
      delay(5);
      if(HasReleased[i]==true && ReadPlayerInput(Joueurs[i])==HIGH)
      {
        HasReleased[i]=false;
        ClicCount[i]++;
        
        LOG_DEDUEL("Clic+:");
        LOG_DEDUEL(i);
        LOG_DEDUEL("\n");
      }
    }

    if(GameCounter>ScoreIncreaseIter)
    {
      GameCounter=0;
      ScoreFactor=ScoreFactor*(ScoreIncrease+1);
        LOG_DEDUEL("New Score Factor");
        LOG_DEDUEL(ScoreFactor);
        LOG_DEDUEL("\n");
    }
    
    DeltaClic=ClicCount[0]-ClicCount[1];
    Score=50+DeltaClic*ScoreFactor;
    

    //Update lights/DEDU based on score
    MoveDEDUFlag(Score);
    if (Score>50)
    {
      ActivateGreenLED(2*(Score-50));
      ActivateBlueLED(0);
    }
    else if (Score<50)
    {
      ActivateBlueLED(2*(50-Score));
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
    else if (Score <1)
    {
      Winner=Joueurs[1];
    }
    
    /*
    LOG_DEDUEL("GameCounter:");
    LOG_DEDUEL(GameCounter);
    LOG_DEDUEL("\n");
    LOG_DEDUEL("CLIC 0:");
    LOG_DEDUEL(ClicCount[0]);
    LOG_DEDUEL("\n");
    LOG_DEDUEL("CLIC 1:");
    LOG_DEDUEL(ClicCount[1]);
    LOG_DEDUEL("\n");
    LOG_DEDUEL("Delta Clic:");
    LOG_DEDUEL(DeltaClic);
    LOG_DEDUEL("\n");
    LOG_DEDUEL("Score");
    LOG_DEDUEL(Score);
    LOG_DEDUEL("\n");
    LOG_DEDUEL("ScoreFactor:");
    LOG_DEDUEL(ScoreFactor);
    LOG_DEDUEL("\n");
    */
  }while(Winner==-1);


  WinnerSound();
  //GAGNANT TROUVÉ
  LOG_DEDUEL("Winner:");
  LOG_DEDUEL(Winner);
  LOG_DEDUEL("\n");

  if (Winner==Joueurs[0])
  {
    for (int i=1; i <50 ; i++)
    {
      ActivateGreenLED(i);
      delay(20);
    }
    delay(LightDelay);
    ActivateGreenLED(0);
    ActivateRedLight(Joueurs[0]);
    for(int i=0 ; i<2 ; i++)
    {
      WinnerSound();
      delay(LightDelay);
      DeactivateRedLight(Joueurs[0]);
      ActivateGreenLED(100);
      delay(LightDelay);
      ActivateRedLight(Joueurs[0]);
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
  ControlAllLights(false,0,0);
}

#ifdef ENABLE_LOGGING
  #define LOG_ULTI(a) LOG_GAME(10,a)
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
        if(ReadPlayerInput(i)==HIGH && PlayerState[i]!=Looser)
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
          if (PlayerState[i]!=Looser && PlayerState[i]!=InGame && ReadPlayerInput(i)==HIGH)
          {
            PlayerState[i]=Looser;
            ActivateRedLight(i);
          }
          if(PlayerState[i]==InGame && ReadPlayerInput(i)==LOW && HasReleased[i]==false)
          {
            HasReleased[i]=true;
          }
          delay(15);
          if(PlayerState[i]==InGame && HasReleased[i]==true && ReadPlayerInput(i)==HIGH)
          {
            //WINNER
            RoundWinner=i;
            DeactivateRedLight(i);
            break;
          }
        }
      }while(RoundWinner==-1);
      
      //WinSound
      for (int i = 1; i <= 120; i++)
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
  delay(1500);
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
      if(ReadPlayerInput(i)==HIGH || ReadPlayerOutput(i)==HIGH)
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
  }while(looserfound==false);



  //SCORE
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
    
    ActivateRedLight(Looser);
    
    delay(500);


    DeactivateRedLight(Looser);
    
    delay(500);
  }
  DeactivateBlueLED();
}


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
  
  int RandTimer=3+random(12);

  float TimeInterval = 900;
  float TimeDelta;
  
  for(int i = 0;i < RandTimer;i++)
  {
    tone(Tone_Pin,250,10);
    delay(400);
    ActivateGreenLED(50);
    tone(Tone_Pin,700,10);
    delay(TimeInterval);
    ActivateGreenLED(100);

    TimeInterval-=(float)(random(300,900)/RandTimer);
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
    allloosers=true;
  }
  else if(Sum0>Sum1) // Low Looses
  {
    for (int i=0; i<=nbj_raw;i++)
    {
      if (InputState[i]==LOW)
        DeclaredLoosers[i]=1;
    }
    allloosers=false;
  }
  else if(Sum1>Sum0)//HIGH Looses
  {
    for (int i=0; i<=nbj_raw;i++)
    {
      if (InputState[i]==HIGH)
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

  if (noloosers==false && allloosers==false )
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
  else if(noloosers==false && allloosers==true)
  {
    ActivateBlueLED(20);
    
    //Sound for Loosers.
    for(int i=0 ; i<4 ; i++)
    {
      tone(Tone_Pin,800,700);
      DeactivateBlueLED();
      TurnOnAllRedLights();
      delay(LightDelay);
      TurnOffAllRedLights();
      ActivateBlueLED(20);
      delay(LightDelay);
    }
  }
  TurnOffAllLights();
}


#ifdef ENABLE_LOGGING
  #define LOG_CHANSON(a) LOG_GAME(7,a)
#else
  #define LOG_CHANSON(a)
#endif

void JeuChanson()
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
  float ScoreWeightPlay=0.75;
  float ScoreWeightWait=1-ScoreWeightPlay;
  //Set White Lights
  ActivateBlueLED(100);
  ActivateGreenLED(100);
  TurnOnAllRedLights();
  delay(2500);
  
  NombreNotes=SelectionChanson(random(NombreChansons));
  
  AllocateTwoTeams(nbj);

  //Répéter pour chaque équipe
  for (int e = 0; e<NbEquipes ; e++)
  {
    //OrdreJoueurs
    DefinirOrdreJoueurs(e,NombreNotes);

    //Definir Facteur Vitesse
    myRand= random(RandomMin,RandomMax);
    FacteurVitesse=(float) myRand/100;

    LOG_CHANSON("Chanson Mod:");
    LOG_CHANSON("\n");
    //Transform MaChanson
    for(int n=0; n<NombreNotes; n++)
    {
      ChansonMod[0][n]=MaChanson[0][n];
      ChansonMod[1][n]=MaChanson[1][n]/FacteurVitesse;
      ChansonMod[2][n]=MaChanson[2][n]/FacteurVitesse;

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
    
    LOG_CHANSON("FacteurVitesse:");
    LOG_CHANSON(FacteurVitesse);
    LOG_CHANSON("\n");

    
    TurnOffAllRedLights();
    DeactivateBlueLED();
    DeactivateGreenLED();
    delay(1200);
    
    for(int i=0 ; i<=nbj_raw ; i++)
    {
      if(Equipes[i]==e)
      {
        ActivateRedLight(i);
        delay(800);
      }
    }

    delay(500);
    TurnOffAllRedLights();
    delay(1500);

    //Show the Player
    for(int n=0; n<NombreNotes; n++)
    {
      PlayNoteWithLight(Tone_Pin, ChansonMod[0][n], ChansonMod[1][n], ChansonMod[2][n],OrdreJoueurs[n]);
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
      do{
        noTone(Tone_Pin);
        delay(5);
      }while(ReadPlayerInput(OrdreJoueurs[n])==LOW);
      LeurTemps[0][n]=TimeDiff();
      TakeTime();
      do{
        tone(Tone_Pin,ChansonMod[0][n], 20);
        delay(5);
      }while(ReadPlayerInput(OrdreJoueurs[n])==HIGH);
      LeurTemps[1][n]=TimeDiff();
      noTone(Tone_Pin);
      DeactivateRedLight(OrdreJoueurs[n]);
    }

    //LOG DES SCORES
    LOG_CHANSON("Scores Chansons");
    LOG_CHANSON("\n");

    
    LOG_CHANSON("TEMPS ORIGINAL");
    LOG_CHANSON("\n");

    for (int n=0; n<NombreNotes; n++)
    {
      //WAIT
      LOG_CHANSON(n);
      LOG_CHANSON(":  WaitPlayer:");
      LOG_CHANSON(LeurTemps[0][n]);
      LOG_CHANSON("  WaitSong:  ");
      LOG_CHANSON(ChansonMod[2][n]);
      LOG_CHANSON("  Score:  ");
      LOG_CHANSON(RelativeError(LeurTemps[0][n],ChansonMod[2][n]));
      LOG_CHANSON("\n");

      
      //PLAY
      LOG_CHANSON(n);
      LOG_CHANSON(":  PressPlayer:");
      LOG_CHANSON(LeurTemps[1][n]);
      LOG_CHANSON("  PressSong:  ");
      LOG_CHANSON(ChansonMod[1][n]);
      LOG_CHANSON("  Score:  ");
      LOG_CHANSON(RelativeError(LeurTemps[1][n],ChansonMod[1][n]));
      LOG_CHANSON("\n");
    }
    
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
        ScoreWait[e]+=IndivScore;
      }
      
      //PlayTime
      IndivScore=RelativeError(LeurTemps[1][n],ChansonMod[1][n]);
      ScorePlay[e]+=IndivScore;
    }
    ScoreWait[e]=ScoreWait[e]/(NombreNotes-1);
    ScorePlay[e]=ScorePlay[e]/NombreNotes;
    
    Scores[e]=ScoreWait[e]*ScoreWeightWait + ScorePlay[e]*ScoreWeightPlay;
    
    LOG_CHANSON("Equipe:");
    LOG_CHANSON(e);
    LOG_CHANSON("  Score:");
    LOG_CHANSON(Scores[e]);
    LOG_CHANSON("  Wait:");
    LOG_CHANSON(ScoreWait[e]);
    LOG_CHANSON("  Play:");
    LOG_CHANSON(ScorePlay[e]);
    LOG_CHANSON("\n");
  }

  
  
  LOG_CHANSON("Score Weight Play:");
  LOG_CHANSON(ScoreWeightPlay);
  LOG_CHANSON("\n");
  LOG_CHANSON("Score Weight Wait:");
  LOG_CHANSON(ScoreWeightWait);
  LOG_CHANSON("\n");
  
  //
  LOG_CHANSON("FinalScore 0:");
  LOG_CHANSON(Scores[0]);
  LOG_CHANSON("\nFinalScore 1:");
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
  for (int a = 1 ; a <= 3 ; a++)  
  {
    IlluminateTeamRedLights(WinTeam);
    
    for (int i = 1; i <= 120; i++)
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



#ifdef ENABLE_LOGGING
  #define LOG_PATATE(a) LOG_GAME(8,a)
#else
  #define LOG_PATATE(a)
#endif
void PatateChaude()
{

  unsigned long basetime=4242;
  unsigned long maxrandtime=10242;
  int TimeDec=300;
  unsigned long GameTimeMillis = basetime+random(maxrandtime);
  bool ReadyToSwitch=false;
  
  TurnOffAllLights();
  //Lights Setup
  ActivateBlueLED(21);
  delay(1500);

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
  
  TakeTime();
  do
  {
    if(ReadPlayerInput(LuckyPlayer)==LOW)
    {
      ReadyToSwitch=true;
    }

    if(ReadPlayerInput(LuckyPlayer)==HIGH && ReadyToSwitch==true)
    {
      //Deactivate my Light;
      DeactivateRedLight(LuckyPlayer);
      GameTimeMillis-=(random(50,TimeDec));
      //GoToNextPlayer
      LuckyPlayer+=NextPlayer;
      if (LuckyPlayer>nbj_raw)
      {
        LuckyPlayer=0;
      }
      else if (LuckyPlayer < 0)
      {
        LuckyPlayer=nbj_raw;
      }
      
      //Activate new lucky Player
      ActivateRedLight(LuckyPlayer);
      tone(Tone_Pin, 800+LuckyPlayer*50, 2);
      ReadyToSwitch=false;
    }
    
    if (random(10000)>9996)
    {
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
    delay(1);
  }while(TimeDiff()<GameTimeMillis);

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
    ActivateRedLight(LuckyPlayer);
    delay(500);
    DeactivateRedLight(LuckyPlayer);
    delay(500);
  }

  TurnOffAllLights();
  MoveDEDUFlag(0);
  delay(1200);
}


#ifdef ENABLE_LOGGING
  #define LOG_RANDOM(a) LOG_GAME(9,a)
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
  int PreviousState[nbj_max]={LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};
  int LightState[nbj_max]={LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};
  int PrevLightState[nbj_max]={LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};
  int OutputSum;
  int Looser=-1;
  int DEDUmaster=-1;
  int DEDUmasterProb=5;

  LOG_RANDOM("ALLRANDOM\n");
  
  //InitialSetup CYAN
  TurnOffAllLights();
  
  ActivateBlueLED(10);
  ActivateGreenLED(22);
  delay(1300);

  if(random(DEDUmasterProb)==DEDUmasterProb-1)
  {
    DEDUmaster=random(nbj);
    LOG_RANDOM("DEDUMASTER:");
    LOG_RANDOM(DEDUmaster);
    LOG_RANDOM("\n");
  }
  
  //Initial Lights setup: 50/50 Lit vs Not Lit
  AllocateTwoTeams(nbj);

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

       if(NumAlreadyAllocated==false)
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
      LightState[i]=HIGH;
      PrevLightState[i]=HIGH;
    }
    LOG_RANDOM("Player:");
    LOG_RANDOM(i);
    LOG_RANDOM("  Light:");
    LOG_RANDOM(NewAssignment[i]);
    LOG_RANDOM("\n");
  }

  
  //WinCondition will be checked by a sum of lightstates.

  if(DEDUmaster==-1)
  {
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
  }
  else
  {
    if(ReadPlayerOutput(NewAssignment[DEDUmaster])==LOW)
    {
      Wincondition=1;
      MoveDEDUFlag(0);
    }
    else
    {
      Wincondition=nbj-1;
      MoveDEDUFlag(100);
    }
  }


  int d3=500;
  tone(Tone_Pin, 1700,d3);
  delay(2*d3);
  tone(Tone_Pin, 1700,d3);
  delay(2*d3);
  tone(Tone_Pin, 2800,d3*1.5);
  delay(d3*1.5);

  //Main game.
  do
  {
    //Change win condition randomly
    if(DEDUmaster==-1)
    {
      if(random(30000)>29900)
      {
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
      }
    }
    OutputSum=0;
    for (int i=0 ; i<=nbj_raw ; i++)
    {
      
      //IF PLAYER IS HIGH AND PREV IS LOW, Toggle his light
      if (ReadPlayerInput(i)==HIGH && PreviousState[i]==LOW)
      {
        LightState[i]=ToggleOutput(NewAssignment[i]);
      }
      PreviousState[i]=ReadPlayerInput(i);
      OutputSum+=LightState[i];

      if(i==DEDUmaster)
      {
        if(ReadPlayerOutput(NewAssignment[DEDUmaster])==LOW)
        {
          Wincondition=1;
          MoveDEDUFlag(0);
        }
        else
        {
          Wincondition=nbj-1;
          MoveDEDUFlag(100);
        }
      }
    }

    //Win Condition
    if (OutputSum == Wincondition)
    { 
      if (Wincondition==1)
      {
        for (int i=0 ; i<=nbj_raw ; i++)
        {
          if(LightState[i]==HIGH)
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
          if(LightState[i]==LOW)
          {
            Looser=i;
            break;
          }
        }
      }
    }
    else
    {
      for (int i=0 ; i<=nbj_raw ; i++)
      {
        PrevLightState[i]=LightState[i];
      }
    }
    
    delay(15);
  }while(Looser==-1);


  
  for (int i = 1; i <= 80; i++)
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
  for (int e = 1; e <= 4; e++) {
    ActivateRedLight(Looser);
    delay(500);
    DeactivateRedLight(Looser);
    delay(500);
  }
  MoveDEDUFlag(0);
  TurnOffAllLights();
}

























