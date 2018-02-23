void Repartiteur()
{
  int max_prob;
  int r;
  int Jeu;
  bool ShowGameProb=!DoNotShowGameProb;
  LOG_GENERAL("DEBUT REPARTITEUR\n");
  
  for (int i=0 ; i<NbJeux ; i++)
  {
    if (i==0)ProbAccumuleeJeux[i]=ProbIndivJeuxCurrent[i];
    else ProbAccumuleeJeux[i]=ProbAccumuleeJeux[i-1]+ProbIndivJeuxCurrent[i];

    if(ShowGameProb)
    {
      LogGameProb(i);
    }

    //Update for next round
    ProbIndivJeuxCurrent[i]+=(ProbIndivJeux[i]/NumberOfRoundsForFullProb);
    
    if(NotMoreThanMaxProb)
    {
      //Logique si le flag NotMoreThanMaxProb est ON.  Exclusion pour Honte et DEDU
      if (ProbIndivJeuxCurrent[i]>ProbIndivJeux[i] && i!=Game_id_FFA && i!=Game_id_MH)
      {
        ProbIndivJeuxCurrent[i]=ProbIndivJeux[i];
      }
      //Special case for marqueurhonte et DEDU qui peuvent monter au-dessus de leur limite peu importe...
      else if (i==Game_id_FFA || i==Game_id_MH)
      {
        ProbIndivJeuxCurrent[i]+=(ProbIndivJeux[i]/NumberOfRoundsForFullProb);
      }
    }
  }
  
  max_prob=ProbAccumuleeJeux[NbJeux-1];

  //Check for Min/Max of ProbAcc
  if(max_prob<MinProbAcc)
  {
    MinProbAcc=max_prob;
  }
  if(max_prob>MaxProbAcc)
  {
    MaxProbAcc=max_prob;
  }
  
  // Debut REPARTITEUR
  r = random(1,max_prob+1);

  LOG_GENERAL("R:");
  LOG_GENERAL(r);
  LOG_GENERAL("\n");
  
  LOG_GENERAL("MAXPROB:");
  LOG_GENERAL(max_prob);
  LOG_GENERAL("\n");

  Jeu = SelectGame(r);
  
  LOG_GENERAL("================\n");
  LOG_GENERAL("JEU:");
  LogGameName(Jeu,true);
  LOG_GENERAL("================\n");
  
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

  //Reset Prob for special conditions
  LowPlayersProbResets();
  NoHonteProbResets();

  
  LOG_GENERAL("MinProbAcc:");
  LOG_GENERAL(MinProbAcc);
  LOG_GENERAL("\n");
  LOG_GENERAL("MaxProbAcc:");
  LOG_GENERAL(MaxProbAcc);
  LOG_GENERAL("\n");
  
  //JOUEURHONTE
  LOG_GENERAL("JoueurHonte:");
  LOG_GENERAL(JoueurHonte);
  LOG_GENERAL("\n");
  
  
  LOG_GENERAL("FIN REPARTITEUR\n");
  LOG_GENERAL("===============\n");
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
