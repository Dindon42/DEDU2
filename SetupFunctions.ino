void NombreJoueurs()
{
  //Illumine toutes les LED bleu et envoie un son
  ActivateBlueLED(100);
  tone(Tone_Pin, 1500, 400);

  //Attend l'input des joueurs.
  do
  {
    nbj_raw=FirstActive(nbj_raw_max);
  }
  while (nbj_raw == -1);
  nbj=nbj_raw+1;

  //Tous les bleus à OFF.
  DeactivateBlueLED();

  //Montre aux joueurs les sélections.
  ClignoteEtSon(nbj_raw,500,200,0);
  delay(500);
  TurnOffAllRedLights();
  delay(500);
}


//Fonction de setup pour Vitesse
void Vitesse()
{
  //Vertes à ON
  ActivateGreenLED(100);
  tone(Tone_Pin, 1250, 400);

  do
  {
    vitesse_raw=FirstActive(nbj_raw_max);
  }while (vitesse_raw == -1);
  vitesse=vitesse_raw+1;

  //Lumières vertes OFF
  DeactivateGreenLED();

  //Montre aux joueurs les sélections.
  ClignoteEtSon(vitesse_raw,1000,300,0);
  delay(500);
  TurnOffAllRedLights();
  delay(500);
}

//Game mode selection
void GameMode()
{ 
  ActivateGreenLED(100);
  ActivateBlueLED(100);
  tone(Tone_Pin, 750, 400);
  int Selection=-1;

  //Attend l'input des joueurs.
  do
  {
    Selection=FirstActive(nbj_raw_max);
  }while  (Selection==-1);
  
  //Original_Game
  if (Selection==0)
  {
    Game_Mode = 0;
  }
  else
  //New and improved
  {
    Game_Mode=1;
  }
  
  //Tous les bleus et vert à OFF.
  TurnOffAllLights();
  
  if (Game_Mode==0)
  {
    ClignoteEtSon(4,500,200,0);
  }
  else if(Game_Mode==1)
  {
    ClignoteEtSon(9,900,200,5);
  }
  
  delay(500);
  TurnOffAllRedLights();
  delay(500);
}

void AjustementProbJeuxInit()
{
  for (int i ; i<NbJeux; i++)
  {
    ProbIndivJeuxCurrent[i]=ProbIndivJeux[i];
  }
  //MarqueurHonte initial élevé
  //Quelques jeux nuls initialement
  //Patate2 0 si pas suffisament de joueurs
  ProbIndivJeuxCurrent[Game_id_FFA]=0;
  ProbIndivJeuxCurrent[Game_id_MH]=242;
  ProbIndivJeuxCurrent[Game_id_Duel]=0;
  if (nbj<=5) ProbIndivJeuxCurrent[Game_id_PC2]=0;
  ProbIndivJeuxCurrent[Game_id_Tourn]=0;
  ProbIndivJeuxCurrent[Game_id_TDD]=0;
}

void AjustementDelaiHonte()
{
  DelaiPetiteHonte=90 - nbj * 5;
  DelaiHonte=160 - nbj * 7;
}

