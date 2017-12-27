void AllocateTwoTeams(int nbj)
{
  int NbjAlloueEq1=0;
  int NbjAlloueEq2=0;
  
  for (int i=0; i<=nbj_raw_max ; i++)
  {
    Equipes[i]=-1;
  }
  
  NbEquipes=2;
  if(nbj%2==0)
  {
    NbJoueursEq1=nbj/2;
    NbJoueursEq2=NbJoueursEq1;
  }
  else
  {
    if(random(2)==0)
    {
      NbJoueursEq1=(nbj+1)/2;
      NbJoueursEq2=nbj-NbJoueursEq1;
    }
    else
    {
      NbJoueursEq1=(nbj-1)/2;
      NbJoueursEq2=nbj-NbJoueursEq1;
    }
  }

  for (int i=0; i<=nbj_raw ; i++)
  {
    if(random(2)==0 && NbjAlloueEq1<NbJoueursEq1)
    {
      Equipes[i]=0;
      NbjAlloueEq1++;
    }
    else if(NbjAlloueEq2<NbJoueursEq2)
    {
      Equipes[i]=1;
      NbjAlloueEq2++;
    }
    else
    {
      Equipes[i]=0;
      NbjAlloueEq1++;
    }
  }
  

  
  
}
