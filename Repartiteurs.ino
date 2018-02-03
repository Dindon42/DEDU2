void Repartiteur()
{
  int ProbAccumuleeJeux[NbJeux];
  int max_prob=0;
  int r;

  for (int i=0 ; i<NbJeux ; i++)
  {
    if (i==0)ProbAccumuleeJeux[i]=ProbIndivJeuxCurrent[i];
    else ProbAccumuleeJeux[i]=ProbAccumuleeJeux[i-1]+ProbIndivJeuxCurrent[i];

    //Update for next round
    ProbIndivJeuxCurrent[i]+=(ProbIndivJeux[i]/NumberOfRoundsForFullProb);
      
    //Special case pour DEDUEL qui ne devrait pas augmenter tant que joueurhonte = -1
    if (i==11 && JoueurHonte==-1)
    {
      ProbIndivJeuxCurrent[i]=0;
    }

    if (ProbIndivJeuxCurrent[i]>ProbIndivJeux[i] && i!=4 && NotMoreThanMaxProb)
    {
      ProbIndivJeuxCurrent[i]=ProbIndivJeux[i];
    }
    //Special case for marqueurhonte qui peut monter au-dessus de sa limite peu importe...
    else if (i==4)
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

  if (r < ProbAccumuleeJeux[0])
  {
    LOG_GENERAL("PQP");
    LOG_GENERAL("\n");
    CountJeux[0]++;
    if(!SkipGame)
    {
      PQP();
    }
    ProbIndivJeuxCurrent[0]=0;
  }
  else if (r < ProbAccumuleeJeux[1])
  {
    LOG_GENERAL("DQP");
    LOG_GENERAL("\n");
    CountJeux[1]++;
    if(!SkipGame)
    {
      DQP();
    }
    ProbIndivJeuxCurrent[1]=0;
  }
  else if (r < ProbAccumuleeJeux[2])
  {
    LOG_GENERAL("Trompe");
    LOG_GENERAL("\n");
    CountJeux[2]++;
    if(!SkipGame)
    {
      TrompeOeil();
    }
    ProbIndivJeuxCurrent[2]=0;
  }
  else if (r < ProbAccumuleeJeux[3])
  {
    LOG_GENERAL("DEDU");
    LOG_GENERAL("\n");
    CountJeux[3]++;
    if(!SkipGame)
    {
      FFA();
    }
    ProbIndivJeuxCurrent[3]=0;
  }
  else if (r < ProbAccumuleeJeux[4])
  {
    LOG_GENERAL("HONTE");
    LOG_GENERAL("\n");
    CountJeux[4]++;
    if(!SkipGame)
    {
      JoueurHonte=MarqueurHonte(-1,-1);
    }
    else
    {
      JoueurHonte=random(nbj);
    }
    ProbIndivJeuxCurrent[4]=0;
  }
  else if (r < ProbAccumuleeJeux[5])
  {
    LOG_GENERAL("DQP2");
    LOG_GENERAL("\n");
    CountJeux[5]++;
    if(!SkipGame)
    {
      DQP2();
    }
    ProbIndivJeuxCurrent[5]=0;
  }
  else if (r < ProbAccumuleeJeux[6])
  {
    LOG_GENERAL("MINORITE");
    LOG_GENERAL("\n");
    CountJeux[6]++;
    if(!SkipGame)
    {
      MIN();
    }
    ProbIndivJeuxCurrent[6]=0;
  }
  else if (r < ProbAccumuleeJeux[7])
  {
    LOG_GENERAL("Chanson");
    LOG_GENERAL("\n");
    CountJeux[7]++;
    if(!SkipGame)
    {
      JeuChanson();
    }
    ProbIndivJeuxCurrent[7]=0;
  }
  else if (r < ProbAccumuleeJeux[8])
  {
    LOG_GENERAL("Patate");
    LOG_GENERAL("\n");
    CountJeux[8]++;
    if(!SkipGame)
    {
      PatateChaude();
    }
    ProbIndivJeuxCurrent[8]=0;
  }
  else if (r < ProbAccumuleeJeux[9])
  {
    LOG_GENERAL("Random");
    LOG_GENERAL("\n");
    CountJeux[9]++;
    if(!SkipGame)
    {
      AllRandom();
    }
    ProbIndivJeuxCurrent[9]=0;
  }
  else if (r < ProbAccumuleeJeux[10])
  {
    LOG_GENERAL("Ulti");
    LOG_GENERAL("\n");
    CountJeux[10]++;
    if(!SkipGame)
    {
      UltimateChallenge();
    }
    ProbIndivJeuxCurrent[10]=0;
  }
  else
  {
    LOG_GENERAL("DeDuel");
    LOG_GENERAL("\n");
    CountJeux[11]++;
    if(!SkipGame)
    {
      DeDuel();
    }
    ProbIndivJeuxCurrent[11]=0;
  }

  
  if (SkipGame)
  {
    if(SkipGameDelay)
    {
      delay(2500);
    }
  }
  
  
  TotalNbJeux++;
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
  else {
    MarqueurHonte(-1,-1);
  }
}
