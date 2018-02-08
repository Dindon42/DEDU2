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

void DefinirOrdreJoueurs(int equipe,int NombreActions)
{
  int JoueurPrec=0;
  //Reset
  for(int i=0; i<NbNoteMax ; i++)
  {
    OrdreJoueurs[i]=-1;
  }
  
  for(int i=0; i<NombreActions; i++)
  {
    for (int j=JoueurPrec;j<=nbj_raw;j++)
    {
      if(Equipes[j]==equipe)
      {
        OrdreJoueurs[i]=j;
        
        if(j==nbj_raw)
        {
          JoueurPrec=0;
        }
        else
        {
          JoueurPrec=j+1;
        }
        break;
      }
      if(j==nbj_raw)
      {
        j=-1;
      }
    }
  }
}

int ProchainJoueur(int iJoueurActuel,int iNombrePlaces,int iDirection)
{
  int wProchain = -1;
  int wNombrePlaces=iNombrePlaces%nbj_raw;
  
  //Protection
  if((iDirection == 1 || iDirection == -1) && (iJoueurActuel>=0 && iJoueurActuel <= nbj_raw))
  {
    wProchain=iJoueurActuel + wNombrePlaces * iDirection;
  
    //Wrap-Around?
    if (wProchain < 0)
    {
      wProchain = nbj_raw - wProchain;
    }
    else if(wProchain > nbj_raw)
    {
      wProchain = wProchain - nbj_raw;
    }
  
    return wProchain;
  }
  else
  {
    return -1;
  }
}















