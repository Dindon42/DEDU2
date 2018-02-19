int SelectGame(int r)
{
  if (r <= ProbAccumuleeJeux[Game_id_PQP])
  {
    return Game_id_PQP;
  }
  else if (r <= ProbAccumuleeJeux[Game_id_DQP])
  {
    return Game_id_DQP;
  }
  else if (r <= ProbAccumuleeJeux[Game_id_TO])
  {
    return Game_id_TO;
  }
  else if (r <= ProbAccumuleeJeux[Game_id_FFA])
  {
    return Game_id_FFA;
  }
  else if (r <= ProbAccumuleeJeux[Game_id_MH])
  {
    return Game_id_MH;
  }
  else if (r <= ProbAccumuleeJeux[Game_id_DQP2])
  {
    return Game_id_DQP2;
  }
  else if (r <= ProbAccumuleeJeux[Game_id_MIN])
  {
    return Game_id_MIN;
  }
  else if (r <= ProbAccumuleeJeux[Game_id_JC])
  {
    return Game_id_JC;
  }
  else if (r <= ProbAccumuleeJeux[Game_id_PC])
  {
    return Game_id_PC;
  }
  else if (r <= ProbAccumuleeJeux[Game_id_AR])
  {
    return Game_id_AR;
  }
  else if (r <= ProbAccumuleeJeux[Game_id_UC])
  {
    return Game_id_UC;
  }
  else if (r <= ProbAccumuleeJeux[Game_id_Duel])
  {
    return Game_id_Duel;
  }
  else if (r <= ProbAccumuleeJeux[Game_id_PC2])
  {
    return Game_id_PC2;
  }
  else if (r <= ProbAccumuleeJeux[Game_id_Tourn])
  {
    return Game_id_Tourn;
  }
  else
  {
    return Game_id_TDD;
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
    JeuChanson();
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
  else if (game_id==Game_id_Tourn)
  {
    Tourniquet();
  }
  else if (game_id==Game_id_TDD)
  {
    TeamDeDuel();
  }
}

void LogGameName(int game_id)
{
  if(game_id==Game_id_PQP)
  {
    LOG_GENERAL("PQP");
  }
  else if (game_id==Game_id_DQP)
  {
    LOG_GENERAL("DQP");
  }
  else if (game_id==Game_id_TO)
  {
    LOG_GENERAL("Trompe");
  }
  else if (game_id==Game_id_FFA)
  {
    LOG_GENERAL("DEDU");
  }
  else if (game_id==Game_id_MH)
  {
    LOG_GENERAL("HONTE");
  }
  else if (game_id==Game_id_DQP2)
  {
    LOG_GENERAL("DQP2");
  }
  else if (game_id==Game_id_MIN)
  {
    LOG_GENERAL("MINORITE");
  }
  else if (game_id==Game_id_JC)
  {
    LOG_GENERAL("Chanson");
  }
  else if (game_id==Game_id_PC)
  {
    LOG_GENERAL("Patate");
  }
  else if (game_id==Game_id_AR)
  {
    LOG_GENERAL("Random");
  }
  else if (game_id==Game_id_UC)
  {
    LOG_GENERAL("Ulti");
  }
  else if (game_id==Game_id_Duel)
  {
    LOG_GENERAL("DeDuel");
  }
  else if (game_id==Game_id_PC2)
  {
    LOG_GENERAL("Patate2");
  }
  else if (game_id==Game_id_Tourn)
  {
    LOG_GENERAL("Tourniquet");
  }
  else if (game_id==Game_id_TDD)
  {
    LOG_GENERAL("TeamDeDuel");
  }
  LOG_GENERAL("\n");
}

void ResetProbAfterGame(int game_id)
{
  //Always own game first.
  ResetGameProb(game_id);

  //Check specific games and reset links.
  if(game_id==Game_id_PQP)
  {
    
  }
  else if (game_id==Game_id_DQP)
  {
    ResetGameProb(Game_id_DQP2);
  }
  else if (game_id==Game_id_TO)
  {
    
  }
  else if (game_id==Game_id_FFA)
  {
    
  }
  else if (game_id==Game_id_MH)
  {
    ResetGameProb(Game_id_Tourn);
  }
  else if (game_id==Game_id_DQP2)
  {
    ResetGameProb(Game_id_DQP);
  }
  else if (game_id==Game_id_MIN)
  {
    
  }
  else if (game_id==Game_id_JC)
  {
    
  }
  else if (game_id==Game_id_PC)
  {
    ResetGameProb(Game_id_PC2);
  }
  else if (game_id==Game_id_AR)
  {
    
  }
  else if (game_id==Game_id_UC)
  {
    
  }
  else if (game_id==Game_id_Duel)
  {
    
  }
  else if (game_id==Game_id_PC2)
  {
    ResetGameProb(Game_id_PC);
  }
  else if (game_id==Game_id_Tourn)
  {
    ResetGameProb(Game_id_MH);
  }
  else if (game_id==Game_id_TDD)
  {
    
  }
}

void ResetGameProb(int game_id)
{
  ProbIndivJeuxCurrent[game_id]=0;
}

void LogGameCounts()
{
  LOG_GENERAL("TOTAL DE JEUX:");
  LOG_GENERAL(TotalNbJeux);
  LOG_GENERAL("\n");
  LOG_GENERAL("0  PQP:\t\t\t");
  LOG_GENERAL(CountJeux[0]);
  LOG_GENERAL("\n");
  LOG_GENERAL("1  DQP:\t\t\t");
  LOG_GENERAL(CountJeux[1]);
  LOG_GENERAL("\n");
  LOG_GENERAL("2  TrompeOeil:\t\t");
  LOG_GENERAL(CountJeux[2]);
  LOG_GENERAL("\n");
  LOG_GENERAL("3  FFA:\t\t\t");
  LOG_GENERAL(CountJeux[3]);
  LOG_GENERAL("\n");
  LOG_GENERAL("4  MarqueurHonte:\t");
  LOG_GENERAL(CountJeux[4]);
  LOG_GENERAL("\n");
  LOG_GENERAL("5  DQP2:\t\t");
  LOG_GENERAL(CountJeux[5]);
  LOG_GENERAL("\n");
  LOG_GENERAL("6  MIN:\t\t\t");
  LOG_GENERAL(CountJeux[6]);
  LOG_GENERAL("\n");
  LOG_GENERAL("7  JeuChanson:\t\t");
  LOG_GENERAL(CountJeux[7]);
  LOG_GENERAL("\n");
  LOG_GENERAL("8  PatateChaude:\t");
  LOG_GENERAL(CountJeux[8]);
  LOG_GENERAL("\n");
  LOG_GENERAL("9  AllRandom:\t\t");
  LOG_GENERAL(CountJeux[9]);
  LOG_GENERAL("\n");
  LOG_GENERAL("10 UltimateChallenge:\t");
  LOG_GENERAL(CountJeux[10]);
  LOG_GENERAL("\n");
  LOG_GENERAL("11 DeDuel:\t\t");
  LOG_GENERAL(CountJeux[11]);
  LOG_GENERAL("\n");
  LOG_GENERAL("12 Patate2:\t\t");
  LOG_GENERAL(CountJeux[12]);
  LOG_GENERAL("\n");
  LOG_GENERAL("13 Tourniquet:\t\t");
  LOG_GENERAL(CountJeux[13]);
  LOG_GENERAL("\n");
  LOG_GENERAL("14 TeamDeDuel:\t\t");
  LOG_GENERAL(CountJeux[14]);
  LOG_GENERAL("\n");

}

