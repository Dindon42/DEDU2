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
    PlayGame(Jeu,false);
  }
  else
  {
    SimulateGame(Jeu);
  }
  ResetProbAfterGame(Jeu);
  CountJeux[Jeu]++;
  UpdateCountByType(Jeu);
  
  if (SkipGame)
  {
    if(DelayIfSkipGame)
    {
      delay(2500);
    }
  }
  
  TotalNbJeux++;
  LogGameCounts();
  LogGameCountsByType();

  //Reset Prob for special conditions
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
