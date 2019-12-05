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
  bool FactorTeamSize=true;
  float TeamSizeScoreRatio[2]={1,1};
  float TeamSizeModifier=1.03;
  float ChansonMod[ParamChansons][NbNoteMax];
  //Pour Chaque joueur: Silence,puis Musique.
  float LeurTemps[ParamChansons-1][NbNoteMax];
  float Scores[2];
  
  NombreNotes=SelectionChanson(id_chanson);
  AllocateTwoTeams(nbj);
  
  if (NbJoueursEq1>NbJoueursEq2 && FactorTeamSize==true)
  {
    TeamSizeScoreRatio[0]=TeamSizeModifier;
  }
  else if (NbJoueursEq2>NbJoueursEq1 && FactorTeamSize==true)
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
  for (int e=0; e<NbEquipes; e++)
  {
    if (LengthScoreFactor)
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
    for (int n=0; n<NombreNotes; n++)
    {
      ChansonMod[0][n]=MaChanson[0][n];
      ChansonMod[1][n]=MaChanson[1][n]/FacteurVitesse;
      ChansonMod[2][n]=MaChanson[2][n]/FacteurVitesse;

      if (LengthScoreFactor)
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
    
    for (int i=0; i<=nbj_raw; i++)
    {
      if (Equipes[i]==e)
      {
        ActivateRedLight(i);
        delay(400);
      }
    }

    delay(1500);
    TurnOffAllRedLights();
    delay(1200);

    //Show the Player
    for (int n=0; n<NombreNotes; n++)
    {
      PlayNoteWithLight(ChansonMod[0][n], ChansonMod[1][n], ChansonMod[2][n],OrdreJoueurs[n]);
    }

    
    TurnOffAllRedLights();
    delay(1500);
    for (int t=0; t<4; t++){
      tone(Tone_Pin,800,10);
      delay(700);
    }
    
    for (int n=0; n<NombreNotes; n++)
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
        
        if (LengthScoreFactor)
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
      
      if (LengthScoreFactor)
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

  for (int i=0; i<2;i++)
  {
    if (Scores[i]>1)
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
  for (int e=0; e<NbEquipes; e++)
  {
    TurnOffAllLights();
    MoveDEDUFlag(0);
    delay(1500);
    CurTone=BaseTone;
    for (int i=0; i<=nbj_raw; i++)
    {
      if (Equipes[i]==e)
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
    
    for (int j=0; j<=Scores[e]*100; j++)
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
  for (int a=1; a<=3; a++)  
  {
    IlluminateTeamRedLights(WinTeam);
    
    for (int i=1; i<=120; i++)
    {
      Tone_Frequency=500 + 30 * i;
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

