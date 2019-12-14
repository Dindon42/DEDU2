#ifdef ENABLE_LOGGING
  #define LOG_DEDUEL(a) LOG_GAME(Game_id_DUEL,a)
#else
  #define LOG_DEDUEL(a)
#endif
void DeDuel()
{
  //Joueur 0=VERT
  //Joueur 1=BLEU
  int Joueurs[2]={-1,-1};
  unsigned long ClicCount[2]={0,0};
  int Winner=-1;
  int DeltaClic=0;
  bool HasReleased[2]={false};
  float Score=50;
  float ScoreFactor=1;
  float ScoreIncrease=0.27;
  int Chanson=CHANSON_FinalCtd1ID;
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


  if (JoueurHonte!=-1)
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
    
    for (int i=1; i<50; i++)
    {
      ActivateGreenLED(i);
      delay(ForLightDelay);
    }
    delay(LightDelay);
    for (int i=0; i<2; i++)
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
    for (int i=1; i<50; i++)
    {
      ActivateBlueLED(i);
      delay(ForLightDelay);
    }
    delay(LightDelay);
    for (int i=0; i<2; i++)
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
        
        if (Chanson==CHANSON_FinalCtd1ID)
        {
          Chanson=CHANSON_FinalCtd2ID;
        }
        else
        {
          Chanson=CHANSON_FinalCtd1ID;
        }
        NombreNotes=SelectionChanson(Chanson);
      }
    }
    
    
    //UpdateHasReleased
    for (int i=0; i<=1 ;i++)
    {
      if (!ReadPlayerInput(Joueurs[i]) && !HasReleased[i])
      {
        HasReleased[i]=true;
      }
      delay(ReactionDelay);
      if (HasReleased[i] && ReadPlayerInput(Joueurs[i]))
      {
        HasReleased[i]=false;
        ClicCount[i]++;
        
        LOG_DEDUEL("Clic+:");
        LOG_DEDUEL(i);
        LOG_DEDUEL("\n");
      }
    }

    if (ScoreIncCounter>ScoreIncreaseIter && ScoreFactor<50)
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
    for (int i=1; i<50; i++)
    {
      ActivateGreenLED(i);
      delay(20);
    }
    delay(LightDelay);
    WinnerSoundAndLight(Joueurs[0]);
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
    ActivateRedLight(Joueurs[1]);
    for (int i=0; i<2; i++)
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
  
  UpdateWinner(Winner);
  if (TransfertHonte && Winner==Joueurs[1])
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
