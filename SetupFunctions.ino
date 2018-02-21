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

void DefineProbJeux()
{
  ProbIndivJeux[Game_id_PQP]= 95;
  ProbIndivJeux[Game_id_DQP]= 30;
  ProbIndivJeux[Game_id_TO]=  21;
  ProbIndivJeux[Game_id_FFA]= 21;
  ProbIndivJeux[Game_id_MH]=  32;
  ProbIndivJeux[Game_id_DQP2]=42;
  ProbIndivJeux[Game_id_MIN]= 66;
  ProbIndivJeux[Game_id_JC]=  55;
  ProbIndivJeux[Game_id_PC]=  70;
  ProbIndivJeux[Game_id_AR]=  70;
  ProbIndivJeux[Game_id_UC]=  70;
  ProbIndivJeux[Game_id_Duel]=60;
  ProbIndivJeux[Game_id_PC2]= 70;
  ProbIndivJeux[Game_id_TH]=  70;
  ProbIndivJeux[Game_id_TDD]= 70;
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
  ProbIndivJeuxCurrent[Game_id_TH]=0;
  ProbIndivJeuxCurrent[Game_id_TDD]=0;
}

void AjustementDelaiHonte()
{
  DelaiPetiteHonte=90 - nbj * 5;
  DelaiHonte=160 - nbj * 7;
}

void LogSetupParams()
{
  LOG_GENERAL("GameMode:");
  LOG_GENERAL(Game_Mode);
  LOG_GENERAL("\n");
  LOG_GENERAL("nbj:");
  LOG_GENERAL(nbj);
  LOG_GENERAL("\n");
  LOG_GENERAL("nbj_raw:");
  LOG_GENERAL(nbj_raw);
  LOG_GENERAL("\n");
  LOG_GENERAL("vitesse:");
  LOG_GENERAL(vitesse);
  LOG_GENERAL("\n");
  LOG_GENERAL("vitesse_raw:");
  LOG_GENERAL(vitesse_raw);
  LOG_GENERAL("\n");
  LOG_GENERAL("JoueurHonte:");
  LOG_GENERAL(JoueurHonte);
  LOG_GENERAL("\n");
  LOG_GENERAL("\n");
  LOG_GENERAL("SETUP COMPLETE");
  LOG_GENERAL("\n");
}
