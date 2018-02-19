void Repartiteur()
{
  int max_prob;
  int r;
  int Jeu;

  for (int i=0 ; i<NbJeux ; i++)
  {
    if (i==0)ProbAccumuleeJeux[i]=ProbIndivJeuxCurrent[i];
    else ProbAccumuleeJeux[i]=ProbAccumuleeJeux[i-1]+ProbIndivJeuxCurrent[i];

    //Update for next round
    ProbIndivJeuxCurrent[i]+=(ProbIndivJeux[i]/NumberOfRoundsForFullProb);
      
    //Special case pour DEDUEL, TeamDeDuel et Tourniquet qui ne devrait pas augmenter tant que joueurhonte = -1
    if ((i==Game_id_Duel || i==Game_id_Tourn || i==Game_id_TDD) && JoueurHonte==-1)
    {
      ProbIndivJeuxCurrent[i]=0;
    }
    //Special case pour Patate2 qui ne devrait pas être joué si nbj<=5.  DEDU ne devrait tout simplement pas être joué avec nbj <=5 :D
    if (i==Game_id_PC2 && nbj<=5)
    {
      ProbIndivJeuxCurrent[i]=0;
    }
    //Special case pour TeamDeDuel qui ne devrait pas être joué si nbj<4.
    if (i==Game_id_TDD && nbj<4)
    {
      ProbIndivJeuxCurrent[i]=0;
    }
    
    //Logique si le flag NotMoreThanMaxProb est ON.  Exclusion pour Honte et DEDU
    if (ProbIndivJeuxCurrent[i]>ProbIndivJeux[i] && i!=Game_id_FFA && i!=Game_id_MH && NotMoreThanMaxProb)
    {
      ProbIndivJeuxCurrent[i]=ProbIndivJeux[i];
    }
    //Special case for marqueurhonte et DEDU qui peuvent monter au-dessus de leur limite peu importe...
    else if (i==Game_id_FFA || i==Game_id_MH)
    {
      ProbIndivJeuxCurrent[i]+=(ProbIndivJeux[i]/NumberOfRoundsForFullProb);
    }
    
    LOG_GENERAL("I:");
    LOG_GENERAL(i);
    LOG_GENERAL("  PROB INDIV:");
    LOG_GENERAL(ProbIndivJeuxCurrent[i]);
    LOG_GENERAL("  PROB ACC:");
    LOG_GENERAL(ProbAccumuleeJeux[i]);
    LOG_GENERAL("\n");
  }
  max_prob=ProbAccumuleeJeux[NbJeux-1];
  
  // Debut REPARTITEUR
  r = random(max_prob+1);

  LOG_GENERAL("R:");
  LOG_GENERAL(r);
  LOG_GENERAL("\n");
  
  LOG_GENERAL("MAXPROB:");
  LOG_GENERAL(max_prob);
  LOG_GENERAL("\n");

  Jeu = SelectGame(r);
  LogGameName(Jeu);
  PrepareGame(Jeu);
  if(!SkipGame)
  {
    PlayGame(Jeu);
  }
  else if(Jeu==Game_id_MH)
  {
    JoueurHonte=random(nbj);
  }
  ResetProbAfterGame(Jeu);
  CountJeux[Jeu]++;
  
  if (SkipGame)
  {
    if(DelayIfSkipGame)
    {
      delay(2500);
    }
  }
  
  TotalNbJeux++;
  LogGameCounts();
  
  //JOUEURHONTE
  LOG_GENERAL("JoueurHonte:");
  LOG_GENERAL(JoueurHonte);
  LOG_GENERAL("\n");
}








//POUR DEDU1;
void RepartiteurOriginal()
{
  int r;
  //Index_Jeux
  //0 PQP
  //1 DQP
  //2 TrompeOeil
  //3 FFA
  //4 MarqueurHonte
  int const NbJeuxOrig = 5;
  int const ProbIndivJeux[NbJeuxOrig]={37,45,8,4,6};
  int ProbAccumuleeJeux[NbJeuxOrig];
  int max_prob=0;

  ProbAccumuleeJeux[0]=ProbIndivJeux[0];
  for (int i=1 ; i<NbJeuxOrig ; i++)
  {
    ProbAccumuleeJeux[i]=ProbAccumuleeJeux[i-1]+ProbIndivJeux[i];
  }
  max_prob=ProbAccumuleeJeux[NbJeuxOrig-1];

  
  // Debut REPARTITEUR
  r = random(max_prob+1);

  if (r < ProbAccumuleeJeux[0])
  {
    PQP();
  }
  else if (r < ProbAccumuleeJeux[1])
  {
    DQP();
  }
  else if (r < ProbAccumuleeJeux[2])
  {
    TrompeOeil();
  }
  else if (r < ProbAccumuleeJeux[3])
  {
    FFA();
  }
  else
  {
    MarqueurHonte(-1,-1);
  }
}
