void DefineGameTypes()
{
  //Types
  //0=Gagnant Individuel
  GameTypes[Game_id_PQP]=0;
  GameTypes[Game_id_UC]=0;
  GameTypes[Game_id_Duel]=0;
  GameTypes[Game_id_PQR]=0;
  GameTypes[Game_id_TV]=0;
   
  //1=Perdant individuel
  GameTypes[Game_id_DQP]=1;
  GameTypes[Game_id_PC]=1;
  GameTypes[Game_id_DQP2]=1;
  GameTypes[Game_id_PC2]=1;
  GameTypes[Game_id_AR]=1;
  
  //2=Jeu d'équipe
  GameTypes[Game_id_MIN]=2;
  GameTypes[Game_id_JC]=2;
  
  //3=Autres
  GameTypes[Game_id_TO]=3;
  GameTypes[Game_id_FFA]=3;
  
  //51=Perdant indiv et honte
  GameTypes[Game_id_MH]=51;
  GameTypes[Game_id_TH]=51;
  
  //52=Équipe et honte
  GameTypes[Game_id_TDD]=52;
}

void DefineProbJeux()
{
  int wMode;
  
  //Initialize Prob for the different games under different modes.
  wMode=0;
  //Gagnant Unique
  GameProb[Game_id_PQP][wMode]=400;

  //Perdant Unique
  GameProb[Game_id_DQP][wMode]=350;

  //Honte
  GameProb[Game_id_MH][wMode]=24;

  //Autres
  GameProb[Game_id_TO][wMode]=50;
  GameProb[Game_id_FFA][wMode]=24;

  //===================//
  
  wMode=1;
  //Gagnant Unique
  GameProb[Game_id_PQP][wMode]=120;
  GameProb[Game_id_UC][wMode]=75;
  GameProb[Game_id_Duel][wMode]=75;
  
  //Perdant Unique
  GameProb[Game_id_DQP][wMode]=55;
  GameProb[Game_id_PC][wMode]=60;
  GameProb[Game_id_DQP2][wMode]=55;
  
  //Honte
  GameProb[Game_id_MH][wMode]=35;

  //Équipe
  GameProb[Game_id_MIN][wMode]=60;
  GameProb[Game_id_TDD][wMode]=55;
  
  //Autres
  GameProb[Game_id_TO][wMode]=30;
  GameProb[Game_id_FFA][wMode]=42;

  //===================//
  
  wMode=2;
  //Gagnant Unique
  GameProb[Game_id_PQP][wMode]=90;
  GameProb[Game_id_UC][wMode]=75;
  GameProb[Game_id_Duel][wMode]=75;
  GameProb[Game_id_PQR][wMode]=50;
  GameProb[Game_id_TV][wMode]=50;
  
  //Perdant Unique
  GameProb[Game_id_DQP][wMode]=55;
  GameProb[Game_id_PC][wMode]=60;
  GameProb[Game_id_DQP2][wMode]=55;
  GameProb[Game_id_PC2][wMode]=60;
  GameProb[Game_id_AR][wMode]=75;
  
  //Honte
  GameProb[Game_id_MH][wMode]=35;
  GameProb[Game_id_TH][wMode]=45;

  //Équipe
  GameProb[Game_id_MIN][wMode]=60;
  GameProb[Game_id_TDD][wMode]=55;
  GameProb[Game_id_JC][wMode]=55;
  
  //Autres
  GameProb[Game_id_TO][wMode]=30;
  GameProb[Game_id_FFA][wMode]=42;

  
  //Initialize all games at 0, then check chosen game mode and act accordingly.
  for (int i =0 ; i<NbJeux ; i++)
  {
    ProbIndivJeux[i]=GameProb[i][Game_Mode];
  }

  //Ajuster les prob Master de certains jeux si pas assez de joueurs.
  if (nbj<=5)
  {
    ProbIndivJeux[Game_id_PC2]=0;
    ProbIndivJeux[Game_id_TDD]=0;
    ProbIndivJeux[Game_id_AR]=0;
  }

  //Log Prob.
  for (int i =0 ; i<NbJeux ; i++)
  {
    LogBaseProb(i);
  }
}

void AjustementProbJeuxInit()
{
  for (int i ; i<NbJeux; i++)
  {
    ProbIndivJeuxCurrent[i]=ProbIndivJeux[i];
  }
  //MarqueurHonte initial élevé, FFA 0
  ProbIndivJeuxCurrent[Game_id_FFA]=0;
  ProbIndivJeuxCurrent[Game_id_MH]=242;

  //Certains reset particuliers en fonction de la honte.
  NoHonteProbResets();
}

void NoHonteProbResets()
{
  if(JoueurHonte==-1)
  {
    ProbIndivJeuxCurrent[Game_id_Duel]=0;
    ProbIndivJeuxCurrent[Game_id_TH]=0;
    ProbIndivJeuxCurrent[Game_id_TDD]=0;
  }
}

void NombreJoueurs()
{
  //Illumine toutes les LED bleu et envoie un son
  ActivateBlueLED(100);
  tone(Tone_Pin, 1500, 400);
  delay(500);

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
}


//Fonction de setup pour Vitesse
void Vitesse()
{
  //Vertes à ON
  ActivateGreenLED(100);
  tone(Tone_Pin, 1250, 400);
  delay(500);

  do
  {
    vitesse_raw=FirstActive(nbj_raw_max);
  }while (vitesse_raw == -1);
  vitesse=vitesse_raw+1;

  //Lumières vertes OFF
  DeactivateGreenLED();

  //Montre aux joueurs les sélections.
  ClignoteEtSon(vitesse_raw,1000,300,0);
}

//Game mode selection
void GameMode()
{
  int Selection;
  int OriginalSel;
  
  ActivateGreenLED(100);
  ActivateBlueLED(100);
  tone(Tone_Pin, 750, 400);
  delay(500);

  Selection=-1;
  //Attend l'input des joueurs.
  do
  {
    Selection=FirstActive(nbj_raw_max);
  }while  (Selection==-1);
  OriginalSel=Selection;
  
  //Tous les bleus et vert à OFF.
  TurnOffAllLights();

  //Check for DEMO mode.
  if (Selection>4)
  {
    if(Selection==9)
    {
      AllModes=true;
    }
    Selection-=5;
    EnterDemo=true;
  }

  //Now check game mode.
  if (Selection>2 && Selection<5)
  {
    Game_Mode=2;
  }
  else
  {
    Game_Mode=Selection;
  }
  
  if(OriginalSel<5)
  {
    ClignoteEtSon(Game_Mode,500,200,0);
  }
  else if(OriginalSel==9)
  {
    ClignoteEtSon(OriginalSel,500,200,0);
  }
  else
  {
    ClignoteEtSon(Game_Mode,500,200,5);
  }
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
