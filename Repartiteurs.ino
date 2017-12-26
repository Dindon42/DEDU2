void Repartiteur()
{
  RepartiteurOriginal();
}

void RepartiteurOriginal()
{
  //Index_Jeux
  //0 PQP
  //1 DQP
  //2 TrompeOeil
  //3 FFA
  //4 MarqueurHonte

  
  
  // Debut REPARTITEUR
  r = random(101);

  if (r < 37)
  {
    PQP();
  }
  else if (r < 82)
  {
    DQP();
  }
  else if (r < 90)
  {
    TrompeOeil();
  }
  else if (r < 94)
  {
    FFA();
  }
  else {
    MarqueurHonte();
  }
  // fin REPARTITEUR
}
