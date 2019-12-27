void Repartiteur()
{
  int max_prob;
  int Jeu;
  bool ShowGameProb=!DoNotShowGameProb;
  LOG_GENERAL("DEBUT REPARTITEUR\n");
  
  for (int i=0; i<NbJeux; i++)
  {
    if (i==0)ProbAccumuleeJeux[i]=ProbIndivJeuxCurrent[i];
    else ProbAccumuleeJeux[i]=ProbAccumuleeJeux[i-1]+ProbIndivJeuxCurrent[i];

    if (ShowGameProb)
    {
      LogGameProb(i);
    }

    //Update for next round
    ProbIndivJeuxCurrent[i]+=(ProbIndivJeux[i]/NumberOfRoundsForFullProb);
    
    if (NotMoreThanMaxProb)
    {
      //Logique si le flag NotMoreThanMaxProb est ON.  Exclusion pour les évenements speciaux.
      if (ProbIndivJeuxCurrent[i]>ProbIndivJeux[i] && i!=Game_id_FFA && i!=Game_id_MH && i!=Game_id_ROI)
      {
        ProbIndivJeuxCurrent[i]=ProbIndivJeux[i];
      }
    }
  }
  
  max_prob=ProbAccumuleeJeux[NbJeux-1];

  //Check for Min/Max of ProbAcc
  if (max_prob<MinProbAcc)
  {
    MinProbAcc=max_prob;
  }
  if (max_prob>MaxProbAcc)
  {
    MaxProbAcc=max_prob;
  }

  do
  {
    Jeu=SelectGame(random(max_prob)+1);
    LOG_GENERAL("MAXPROB:");
    LOG_GENERAL(max_prob);
    LOG_GENERAL("\n");
  }while(ExclusiveGameType && ExclusiveGameType_ID != GameTypes[Jeu]);
  
  LOG_GENERAL("================\n");
  LOG_GENERAL("JEU:");
  LogGameName(Jeu,true);
  LOG_GENERAL("================\n");
  
  PrepareGame(Jeu);
  if (SkipGame)
  {
    SimulateGame(Jeu);
  }
  else
  {
    PlayGame(Jeu,false);
  }
  ResetProbAfterGame(Jeu);
  CountJeux[Jeu]++;
  UpdateCountByType(Jeu);
  
  if (SkipGame)
  {
    if (DelayIfSkipGame)
    {
      delay(2500);
    }
  }
  
  TotalNbJeux++;
  LogGameCounts();
  LogGameCountsByType();

  //Score
  LogScore();
  //Special event
  HighScoreSpecialEvent();

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
  LOG_GENERAL("JoueurPuissant:");
  LOG_GENERAL(JoueurPuissant);
  LOG_GENERAL("\n");
  LOG_GENERAL("JoueurRoi:");
  LOG_GENERAL(JoueurRoi);
  LOG_GENERAL("\n");
  
  LOG_GENERAL("FIN REPARTITEUR\n");
  LOG_GENERAL("===============\n");
  LOG_GENERAL("\n");
}
