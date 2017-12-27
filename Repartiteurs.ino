void Repartiteur()
{
  //Index_Jeux
  //0 PQP
  //1 DQP
  //2 TrompeOeil
  //3 FFA
  //4 MarqueurHonte
  //5 TLMPareil
  int const NbJeux = 6;
  int const ProbIndivJeux[NbJeux]={42,42,21,12,12,42};
  int ProbAccumuleeJeux[NbJeux];
  int max_prob=0;

  ProbAccumuleeJeux[0]=ProbIndivJeux[0];
  for (int i=1 ; i<NbJeux ; i++)
  {
    ProbAccumuleeJeux[i]=ProbAccumuleeJeux[i-1]+ProbIndivJeux[i];
  }
  max_prob=ProbAccumuleeJeux[NbJeux-1];

  
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
  else if (r < ProbAccumuleeJeux[4])
  {
    MarqueurHonte();
  }
  else
  {
    TLMPareil();
  }
}


void RepartiteurOriginal()
{
  //Index_Jeux
  //0 PQP
  //1 DQP
  //2 TrompeOeil
  //3 FFA
  //4 MarqueurHonte
  int const NbJeux = 5;
  int const ProbIndivJeux[NbJeux]={37,45,8,4,6};
  int ProbAccumuleeJeux[NbJeux];
  int max_prob=0;

  ProbAccumuleeJeux[0]=ProbIndivJeux[0];
  for (int i=1 ; i<NbJeux ; i++)
  {
    ProbAccumuleeJeux[i]=ProbAccumuleeJeux[i-1]+ProbIndivJeux[i];
  }
  max_prob=ProbAccumuleeJeux[NbJeux-1];

  
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
    MarqueurHonte();
  }
}
