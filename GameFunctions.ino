int SelectGame(int r)
{
  for(int i=0 ; i<NbJeux ; i++)
  {
    if (r <= ProbAccumuleeJeux[i])
    {
      return i;
    }
  }
  //Default => Should not happen.
  return Game_id_PQP;
}

void PrepareGame(int game_id)
{
  if(game_id==Game_id_JC)
  {
    int c=CountJeux[Game_id_JC]%NombreChansons;
    BesoinOrdreChansons(c);
    ChansonPourJeu=OrdreChansons[c];
  }
}

void PlayGame(int game_id)
{
  if(game_id==Game_id_PQP)
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
  else if (game_id==Game_id_FFA)
  {
    FFA();
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
    PatateChaude();
  }
  else if (game_id==Game_id_AR)
  {
    AllRandom();
  }
  else if (game_id==Game_id_UC)
  {
    UltimateChallenge();
  }
  else if (game_id==Game_id_Duel)
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
  
}

void LogGameName(int game_id, bool NewLine)
{
  if(game_id==Game_id_PQP)
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
  else if (game_id==Game_id_FFA)
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
    LOG_GENERAL("Random      ");
  }
  else if (game_id==Game_id_UC)
  {
    LOG_GENERAL("Ulti        ");
  }
  else if (game_id==Game_id_Duel)
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
  if(NewLine) LOG_GENERAL("\n");
}

void ResetProbAfterGame(int game_id)
{
  //Always own game first.
  ResetGameProb(game_id);

  //Check specific games and reset links.
  if (game_id==Game_id_DQP)
  {
    ResetGameProb(Game_id_DQP2);
  }
  else if (game_id==Game_id_DQP2)
  {
    ResetGameProb(Game_id_DQP);
  }
  else if (game_id==Game_id_PC)
  {
    DivideGameProb(Game_id_PC2,2);
  }
  else if (game_id==Game_id_PC2)
  {
    DivideGameProb(Game_id_PC,2);
  }
  else if (game_id==Game_id_MH)
  {
    ResetProbHonte();
  }
  else if (game_id==Game_id_TH)
  {
    ResetProbHonte();
  }
}

void ResetGameProb(int game_id)
{
  ProbIndivJeuxCurrent[game_id]=0;
}

void DivideGameProb(int game_id,int divisor)
{
  ProbIndivJeuxCurrent[game_id]=ProbIndivJeuxCurrent[game_id]/divisor;
}

void ResetProbHonte()
{
  ResetGameProb(Game_id_TH);
  ResetGameProb(Game_id_MH);
  DivideGameProb(Game_id_Duel,2);
  DivideGameProb(Game_id_TDD,2);
}

void LogGameCounts()
{
  LOG_GENERAL("TOTAL DE JEUX:");
  LOG_GENERAL(TotalNbJeux);
  LOG_GENERAL("\n");

  for(int i=0 ; i<NbJeux ; i++)
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
