void UpdateCountByType(int jeu)
{
  int TempType=GameTypes[jeu];

  if (TempType>=50)
  {
    CountType[Game_Type_HO]++;
    TempType-=50;
  }
  CountType[TempType]++;
}

void LogTypeName(int type_id)
{
  //0 GI
  //1 PI
  //2 Eq
  //3 Au
  //4 Ho
  if (type_id==0)
  {
    LOG_GENERAL("GI:");
  }
  else if (type_id==1)
  {
    LOG_GENERAL("PI:");
  }
  else if (type_id==2)
  {
    LOG_GENERAL("Eq:");
  }
  else if (type_id==3)
  {
    LOG_GENERAL("Au:");
  }
  else if (type_id==4)
  {
    LOG_GENERAL("Ho:");
  }
}

void LogScore()
{
  LOG_GENERAL("=========\n");
  LOG_GENERAL("==SCORE==\n");
  LOG_GENERAL("=========\n");
  for(int i=0; i<nbj_max; i++)
  {
    LOG_GENERAL("ID: ");
    LOG_GENERAL(i);
    if (GlobalScore[i]<10)
    {
      LOG_GENERAL("   ");
    }
    else if (GlobalScore[i]<100)
    {
      LOG_GENERAL("  ");
    }
    else
    {
      LOG_GENERAL(" ");
    }
    LOG_GENERAL(GlobalScore[i]);
    LOG_GENERAL("\n");
  }
}

void LogGameCountsByType()
{
  LOG_GENERAL("COUNTS BY TYPE\n");
  for (int i=0; i<NbGameTypes; i++)
  {
    LOG_GENERAL("Id:");
    LOG_GENERAL(i);
    LOG_GENERAL(" ");
    LogTypeName(i);
    if (CountType[i]<10)
    {
      LOG_GENERAL("   ");
    }
    else if (CountType[i]<100)
    {
      LOG_GENERAL("  ");
    }
    else
    {
      LOG_GENERAL(" ");
    }
    LOG_GENERAL(CountType[i]);
    LOG_GENERAL(" ->");
    if ((float)CountType[i]/(float)TotalNbJeux<10)
    {
      LOG_GENERAL(" ");
    }
    LOG_GENERAL(100*(float)CountType[i]/(float)TotalNbJeux);
    LOG_GENERAL("%\n");
  }
}

int SelectGame(int r)
{
  LOG_GENERAL("R:");
  LOG_GENERAL(r);
  LOG_GENERAL("\n");
  for (int i=0; i<NbJeux; i++)
  {
    if (r<=ProbAccumuleeJeux[i])
    {
      return i;
    }
  }
  //Default => Should not happen.
  return Game_id_PQP;
}

void PrepareGame(int game_id)
{
  if (game_id==Game_id_JC)
  {
    int c=CountJeux[Game_id_JC]%NombreChansons;
    BesoinOrdreChansons(c);
    ChansonPourJeu=OrdreChansons[c];
  }
}

void SimulateGame(int game_id)
{
  if(game_id==Game_id_ROI)
  {
    int TempRoi;
    do
    {
      TempRoi=random(nbj);
    }while(TempRoi==JoueurRoi);
    JoueurRoi=TempRoi;
  }
  
  if(game_id==Game_id_MH || game_id==Game_id_TDD || game_id==Game_id_TH)
  {
    JoueurHonte=random(nbj);
  }
  
  if(GameTypes[game_id]==Game_Type_GI || GameTypes[game_id]-50==Game_Type_GI);
  {
    int TempWinner;
    bool KeepGoing;
    
    do
    {
      KeepGoing=false;
      TempWinner=random(nbj);
      if(TempWinner==JoueurPuissant)
      {
        KeepGoing=random(2)==0;
      }
    }while(KeepGoing);
    GlobalScore[TempWinner]++;
  }
}

void PlayGame(int game_id, bool DemoMode)
{
  if (game_id==Game_id_PQP)
  {
    PQP();
  }
  else if (game_id==Game_id_DQP)
  {
    DQP();
  }
  else if (game_id==Game_id_TO)
  {
    TrompeOeil();
  }
  else if (game_id==Game_id_DEDU)
  {
    DEDU();
  }
  else if (game_id==Game_id_MH)
  {
    JoueurHonte=MarqueurHonte(-1,-1);
  }
  else if (game_id==Game_id_DQP2)
  {
    DQP2();
  }
  else if (game_id==Game_id_MIN)
  {
    MIN();
  }
  else if (game_id==Game_id_JC)
  {
    JeuChanson(ChansonPourJeu);
  }
  else if (game_id==Game_id_PC)
  {
    PatateChaude(Game_Mode<=Game_Mode_Medium);
  }
  else if (game_id==Game_id_AR)
  {
    AllRandom();
  }
  else if (game_id==Game_id_UC)
  {
    UltimateChallenge();
  }
  else if (game_id==Game_id_DUEL)
  {
    DeDuel();
  }
  else if (game_id==Game_id_PC2)
  {
    Patate2();
  }
  else if (game_id==Game_id_TH)
  {
    Tourniquet();
  }
  else if (game_id==Game_id_TDD)
  {
    TeamDeDuel();
  }
  else if (game_id==Game_id_TV)
  {
    TourVic();
  }
  else if (game_id==Game_id_PQR)
  {
    PQR();
  }
  else if (game_id==Game_id_PB)
  {
    PressBattle();
  }
  else if (game_id==Game_id_PPV)
  {
    PPV();
  }
  else if (game_id==Game_id_JD)
  {
    JeanDit();
  }
  else if (game_id==Game_id_ED)
  {
    EstimeDedu();
  }
  else if (game_id==Game_id_SEQ)
  {
    SequenceGlobale(DemoMode);
  }
  else if (game_id==Game_id_TB)
  {
    TheButton();
  }
  else if (game_id==Game_id_AR2)
  {
    AR2();
  }
  else if (game_id==Game_id_MIN2)
  {
    MIN2();
  }
  else if (game_id==Game_id_ROI)
  {
    ROI();
  }
  else
  {
    PQP();
  }
}

void LogGameName(int game_id, bool NewLine)
{
  if (game_id==Game_id_PQP)
  {
    LOG_GENERAL("PQP         ");
  }
  else if (game_id==Game_id_DQP)
  {
    LOG_GENERAL("DQP         ");
  }
  else if (game_id==Game_id_TO)
  {
    LOG_GENERAL("Trompe      ");
  }
  else if (game_id==Game_id_DEDU)
  {
    LOG_GENERAL("DEDU        ");
  }
  else if (game_id==Game_id_MH)
  {
    LOG_GENERAL("HONTE       ");
  }
  else if (game_id==Game_id_DQP2)
  {
    LOG_GENERAL("DQP2        ");
  }
  else if (game_id==Game_id_MIN)
  {
    LOG_GENERAL("MINORITE    ");
  }
  else if (game_id==Game_id_JC)
  {
    LOG_GENERAL("Chanson     ");
  }
  else if (game_id==Game_id_PC)
  {
    LOG_GENERAL("Patate      ");
  }
  else if (game_id==Game_id_AR)
  {
    LOG_GENERAL("All Random  ");
  }
  else if (game_id==Game_id_UC)
  {
    LOG_GENERAL("Ulti        ");
  }
  else if (game_id==Game_id_DUEL)
  {
    LOG_GENERAL("DeDuel      ");
  }
  else if (game_id==Game_id_PC2)
  {
    LOG_GENERAL("Patate2     ");
  }
  else if (game_id==Game_id_TH)
  {
    LOG_GENERAL("Tourniquet  ");
  }
  else if (game_id==Game_id_TDD)
  {
    LOG_GENERAL("TeamDeDuel  ");
  }
  else if (game_id==Game_id_TV)
  {
    LOG_GENERAL("TourVic     ");
  }
  else if (game_id==Game_id_PQR)
  {
    LOG_GENERAL("PQR         ");
  }
  else if (game_id==Game_id_PB)
  {
    LOG_GENERAL("PressBatt   ");
  }
  else if (game_id==Game_id_PPV)
  {
    LOG_GENERAL("PPV         ");
  }
  else if (game_id==Game_id_JD)
  {
    LOG_GENERAL("JeanDit     ");
  }
  else if (game_id==Game_id_ED)
  {
    LOG_GENERAL("EstimeDedu  ");
  }
  else if (game_id==Game_id_SEQ)
  {
    LOG_GENERAL("Sequence G  ");
  }
  else if (game_id==Game_id_TB)
  {
    LOG_GENERAL("The Button  ");
  }
  else if (game_id==Game_id_AR2)
  {
    LOG_GENERAL("AR2         ");
  }
  else if (game_id==Game_id_MIN2)
  {
    LOG_GENERAL("MIN2        ");
  }
  else if (game_id==Game_id_ROI)
  {
    LOG_GENERAL("Roi         ");
  }
  else
  {
    LOG_GENERAL("PQP         ");
  }
  if (NewLine) LOG_GENERAL("\n");
}

void ResetProbAfterGame(int game_id)
{
  //Always own game first.
  ResetGameProb(game_id);

  //Check specific games and reset links.
  if (game_id==Game_id_DQP || game_id==Game_id_DQP2)
  {
    ResetGameProb(Game_id_DQP);
    ResetGameProb(Game_id_DQP2);
  }
  else if (game_id==Game_id_PC || game_id==Game_id_PC2)
  {
    DivideGameProb(Game_id_PC,2);
    DivideGameProb(Game_id_PC2,2);
  }
  else if (game_id==Game_id_MH || game_id==Game_id_TH)
  {
    ResetProbHonte();
    ResetProbHonte();
  }
  else if (game_id==Game_id_AR || game_id==Game_id_AR2)
  {
    DivideGameProb(Game_id_AR,2);
    DivideGameProb(Game_id_AR2,2);
  }
  else if (game_id==Game_id_MIN || game_id==Game_id_MIN2)
  {
    DivideGameProb(Game_id_MIN,2);
    DivideGameProb(Game_id_MIN2,2);
  }

  //Additional condition for ROI, should only happen if -1
  if(TotalNbJeux<MinRoundsRoi && JoueurRoi==-1)
  {
    ResetGameProb(Game_id_ROI);
  }
  else if(JoueurRoi==-1)
  {
    MultGameProb(Game_id_ROI,2);
  }
}

void ResetGameProb(int game_id)
{
  if (Game_Mode==Game_Mode_Original)
  {
    DivideGameProb(game_id,2);
  }
  else
  {
    ProbIndivJeuxCurrent[game_id]=0;
  }
}

void DivideGameProb(int game_id,int divisor)
{
  ProbIndivJeuxCurrent[game_id]=ProbIndivJeuxCurrent[game_id]/divisor;
}

void MultGameProb(int game_id,double mult)
{
  ProbIndivJeuxCurrent[game_id]=ProbIndivJeuxCurrent[game_id] * mult;
}

void ResetProbHonte()
{
  ResetGameProb(Game_id_TH);
  ResetGameProb(Game_id_MH);
  DivideGameProb(Game_id_DUEL,2);
  DivideGameProb(Game_id_TDD,2);
}

void ResetProbDEDU()
{
  ResetGameProb(Game_id_DEDU);
}

void LogGameCounts()
{
  LOG_GENERAL("TOTAL DE JEUX:");
  LOG_GENERAL(TotalNbJeux);
  LOG_GENERAL("\n");

  for (int i=0; i<NbJeux; i++)
  {
    LOG_GENERAL("Id: ");
    LOG_GENERAL(i);
    LOG_GENERAL("\t");
    LogGameName(i,false);
    LOG_GENERAL(" ");
    LOG_GENERAL(CountJeux[i]);
    LOG_GENERAL("\n");
  }
}
void LogBaseProb(int game_id)
{
  LOG_GENERAL("ID:");
  LOG_GENERAL(game_id);
  LOG_GENERAL("\t");
  LogGameName(game_id,false);
  LOG_GENERAL(" ProbBase:");
  if (ProbIndivJeux[game_id]<10)
  {
    LOG_GENERAL("  ");
  }
  else if (ProbIndivJeux[game_id]<100)
  {
    LOG_GENERAL(" ");
  }
  LOG_GENERAL(ProbIndivJeux[game_id]);
  LOG_GENERAL("\n");
}

void LogGameProb(int game_id)
{
    LOG_GENERAL("ID:");
    LOG_GENERAL(game_id);
    LOG_GENERAL("\t");
    LogGameName(game_id,false);
    LOG_GENERAL(" P.I.:");
    if (ProbIndivJeuxCurrent[game_id]<10)
    {
      LOG_GENERAL("  ");
    }
    else if (ProbIndivJeuxCurrent[game_id]<100)
    {
      LOG_GENERAL(" ");
    }
    LOG_GENERAL(ProbIndivJeuxCurrent[game_id]);
    LOG_GENERAL(" P.A.:");
    if (ProbAccumuleeJeux[game_id]<10)
    {
      LOG_GENERAL("   ");
    }
    else if (ProbAccumuleeJeux[game_id]<100)
    {
      LOG_GENERAL("  ");
    }
    else if (ProbAccumuleeJeux[game_id]<1000)
    {
      LOG_GENERAL(" ");
    }
    LOG_GENERAL(ProbAccumuleeJeux[game_id]);
    LOG_GENERAL("\n");
}


void ResetJoueursSpeciaux()
{
  JoueurHonte=-1;
  JoueurRoi=-1;
  JoueurPuissant=-1;
}
