/*PROB DE JEUX PAR CATEGORIE*/ 
/*
Mode Original
Id:0 GI: 180 -> 33.33%
Id:1 PI: 186 -> 34.44%
Id:2 Eq:   0 -> 0.00%
Id:3 Au: 174 -> 32.22%
Id:4 Ho:  53 -> 9.81%
*/
/*
Mode Medium
Id:0 GI: 256 -> 48.95%
Id:1 PI: 143 -> 27.34%
Id:2 Eq:  52 -> 9.94%
Id:3 Au:  72 -> 13.77%
Id:4 Ho:  38 -> 7.27%
*/
/*
Mode Avance
Id:0 GI: 259 -> 50.88%
Id:1 PI: 144 -> 28.29%
Id:2 Eq:  71 -> 13.95%
Id:3 Au:  35 -> 6.88%
Id:4 Ho:  61 -> 11.98%
*/
/*
Mode Expert
Id:0 GI: 251 -> 47.63%
Id:1 PI: 155 -> 29.41%
Id:2 Eq:  92 -> 17.46%
Id:3 Au:  29 -> 5.50%
Id:4 Ho:  60 -> 11.39%
*/
/*
Mode Experimental
Id:0 GI: 207 -> 41.73%
Id:1 PI: 139 -> 28.02%
Id:2 Eq: 128 -> 25.81%
Id:3 Au:  22 -> 4.44%
Id:4 Ho:  49 -> 9.88%
*/

void DefineProbJeux()
{
  int wMode;
  
  //Initialize Prob for the different games under different modes.

  //===================//
  
  //ORIGINAL DEDU D'ERIC - 5 jeux
  wMode=0;
  //Gagnant Unique
  GameProb[Game_id_PQP][wMode]=210;

  //Perdant Unique
  GameProb[Game_id_DQP][wMode]=190;

  //Honte
  GameProb[Game_id_MH][wMode]=35;

  //Autres
  GameProb[Game_id_TO][wMode]=50;
  GameProb[Game_id_FFA][wMode]=40;
  
  //===================//
  
  //Mode plus avancé, mais pas trop complexe - 10 jeux.
  wMode=1;
  //Gagnant Unique
  GameProb[Game_id_PQP][wMode]=120;
  GameProb[Game_id_UC][wMode]=75;
  GameProb[Game_id_PB][wMode]=80;
  GameProb[Game_id_ED][wMode]=100;
  
  //Perdant Unique
  GameProb[Game_id_DQP][wMode]=40;
  GameProb[Game_id_PC][wMode]=90;
  
  //Honte
  GameProb[Game_id_MH][wMode]=30;

  //Équipe
  GameProb[Game_id_MIN][wMode]=60;
  
  //Autres
  GameProb[Game_id_TO][wMode]=30;
  GameProb[Game_id_FFA][wMode]=45;
    //===================//
  
  //Mode AVANCE - 15 jeux
  wMode=2;
  //Gagnant Unique
  GameProb[Game_id_PQP][wMode]=160;
  GameProb[Game_id_UC][wMode]=120;
  GameProb[Game_id_DUEL][wMode]=100;
  GameProb[Game_id_PB][wMode]=80;
  GameProb[Game_id_PQR][wMode]=100;
  GameProb[Game_id_ED][wMode]=120;
  GameProb[Game_id_JD][wMode]=100;
  
  //Perdant Unique
  GameProb[Game_id_DQP][wMode]=80;
  GameProb[Game_id_DQP2][wMode]=80;
  GameProb[Game_id_PC][wMode]=120;
  GameProb[Game_id_PC2][wMode]=120;
  
  //Honte
  GameProb[Game_id_MH][wMode]=70;

  //Équipe
  GameProb[Game_id_MIN][wMode]=120;
  GameProb[Game_id_TDD][wMode]=110;
  
  //Autres
  GameProb[Game_id_TO][wMode]=0;
  GameProb[Game_id_FFA][wMode]=84;
  
  //===================//
  
  //Mode Expert - 20 jeux
  wMode=3;
  //Gagnant Unique
  GameProb[Game_id_PQP][wMode]=160;
  GameProb[Game_id_UC][wMode]=120;
  GameProb[Game_id_DUEL][wMode]=100;
  GameProb[Game_id_PB][wMode]=80;
  GameProb[Game_id_PQR][wMode]=100;
  GameProb[Game_id_TV][wMode]=100;
  GameProb[Game_id_PPV][wMode]=100;
  GameProb[Game_id_ED][wMode]=120;
  GameProb[Game_id_JD][wMode]=100;
  
  //Perdant Unique
  GameProb[Game_id_DQP][wMode]=80;
  GameProb[Game_id_DQP2][wMode]=80;
  GameProb[Game_id_PC][wMode]=120;
  GameProb[Game_id_PC2][wMode]=120;
  GameProb[Game_id_AR][wMode]=150;
  
  //Honte
  GameProb[Game_id_MH][wMode]=70;
  GameProb[Game_id_TH][wMode]=90;

  //Équipe
  GameProb[Game_id_MIN][wMode]=110;
  GameProb[Game_id_TDD][wMode]=120;
  GameProb[Game_id_JC][wMode]=120;
  
  //Autres
  GameProb[Game_id_TO][wMode]=0;
  GameProb[Game_id_FFA][wMode]=84;
  //===================//
  
  //Mode EXPÉRIMENTAL.  Les nouveaux jeux passent par ici.
  wMode=4;

  //Set Game Probs to previous mode.
  for (int i=0; i<NbJeux; i++)
  {
    GameProb[i][wMode]=GameProb[i][wMode-1];
  }
  //Add experimental modes here:
  GameProb[Game_id_SEQ][wMode]=120;
  GameProb[Game_id_TB][wMode]=120;
  GameProb[Game_id_AR2][wMode]=100;
  GameProb[Game_id_MIN2][wMode]=80;
  GameProb[Game_id_ROI][wMode]=80;
  //Override for Min2, un peu plus de honte.
  GameProb[Game_id_MIN][wMode]=80;
  GameProb[Game_id_TH][wMode]=120;
  GameProb[Game_id_AR][wMode]=100;
  
  //===================//
  
  //Initialization des Prob de base des jeux en fn du mode sélectionné.
  for (int i =0; i<NbJeux; i++)
  {
    ProbIndivJeux[i]=GameProb[i][Game_Mode];
  }

  //Ajuster les prob Master de certains jeux si pas assez de joueurs.
  if (nbj<=5)
  {
    ProbIndivJeux[Game_id_PC2]=0;
    ProbIndivJeux[Game_id_TDD]=0;
    ProbIndivJeux[Game_id_AR]=0;
    ProbIndivJeux[Game_id_JD]=0;
    ProbIndivJeux[Game_id_TB]=0;
    ProbIndivJeux[Game_id_AR2]=0;
  }

  //Log Prob.
  for (int i =0; i<NbJeux; i++)
  {
    LogBaseProb(i);
  }
}

void DefineGameTypes()
{
  //DEFINE GAME TYPES.
  //SET DEFAULT TO -1;
  for (int i=0; i<NbJeux; i++)
  {
    GameTypes[i]=-1;
  }
  
  //Types
  //0=Gagnant Individuel
  GameTypes[Game_id_PQP]=Game_Type_GI;
  GameTypes[Game_id_UC]=Game_Type_GI;
  GameTypes[Game_id_DUEL]=Game_Type_GI;
  GameTypes[Game_id_PQR]=Game_Type_GI;
  GameTypes[Game_id_TV]=Game_Type_GI;
  GameTypes[Game_id_PB]=Game_Type_GI;
  GameTypes[Game_id_PPV]=Game_Type_GI;
  GameTypes[Game_id_JD]=Game_Type_GI;
  GameTypes[Game_id_ED]=Game_Type_GI;
  GameTypes[Game_id_MIN2]=Game_Type_GI;
   
  //1=Perdant individuel
  GameTypes[Game_id_DQP]=Game_Type_PI;
  GameTypes[Game_id_PC]=Game_Type_PI;
  GameTypes[Game_id_DQP2]=Game_Type_PI;
  GameTypes[Game_id_PC2]=Game_Type_PI;
  GameTypes[Game_id_AR]=Game_Type_PI;
  GameTypes[Game_id_AR2]=Game_Type_PI;
  
  //2=Jeu d'équipe
  GameTypes[Game_id_MIN]=Game_Type_EQ;
  GameTypes[Game_id_JC]=Game_Type_EQ;
  GameTypes[Game_id_SEQ]=Game_Type_EQ;
  GameTypes[Game_id_TB]=Game_Type_EQ;
  
  //3=Autres
  GameTypes[Game_id_TO]=Game_Type_AU;
  GameTypes[Game_id_FFA]=Game_Type_AU;
  GameTypes[Game_id_ROI]=Game_Type_AU;
  
  //51=Perdant indiv et honte
  GameTypes[Game_id_MH]=Game_Type_PIH;
  GameTypes[Game_id_TH]=Game_Type_PIH;
  
  //52=Équipe et honte
  GameTypes[Game_id_TDD]=Game_Type_EQH;

  for (int i=0; i<NbJeux; i++)
  {
    if (GameTypes[i]==-1)
    {
      LOG_GENERAL("GAME_TYPE NON DEFINI POUR JEU: ");
      LOG_GENERAL(i);
      LOG_GENERAL("\n");
    }
  }
}

void AjustementProbJeuxInit()
{
  for (int i; i<NbJeux; i++)
  {
    ProbIndivJeuxCurrent[i]=ProbIndivJeux[i];
  }
  //MarqueurHonte initial élevé, FFA et ROI 0
  ProbIndivJeuxCurrent[Game_id_FFA]=0;
  ProbIndivJeuxCurrent[Game_id_ROI]=0;
  if (Game_Mode!=Game_Mode_Original)
  {
    ProbIndivJeuxCurrent[Game_id_MH]=424;
  }
  //Certains reset particuliers en fonction de la honte.
  NoHonteProbResets();
}

void NoHonteProbResets()
{
  if (JoueurHonte==-1)
  {
    ProbIndivJeuxCurrent[Game_id_DUEL]=0;
    ProbIndivJeuxCurrent[Game_id_TH]=0;
    ProbIndivJeuxCurrent[Game_id_TDD]=0;
  }
}

void AdjustNumRoundsFullProb()
{
  if (Game_Mode==Game_Mode_Original)          NumberOfRoundsForFullProb=5;
  else if (Game_Mode==Game_Mode_Medium)       NumberOfRoundsForFullProb=7;
  else if (Game_Mode==Game_Mode_Avance)       NumberOfRoundsForFullProb=9;
  else if (Game_Mode==Game_Mode_Expert)       NumberOfRoundsForFullProb=12;
  else if (Game_Mode==Game_Mode_Experimental) NumberOfRoundsForFullProb=12;
  else NumberOfRoundsForFullProb=4;
}

bool NombreJoueurs()
{
  //Illumine toutes les LED bleu et envoie un son
  ActivateBlueLED(100);
  tone(Tone_Pin, 1500, 400);
  delay(500);
  #define DELAYREDEFINE 400
  #define NBJDELAY 5
  #define NBJ_BASETONE 200
  #define NBJ_TONEINC 100
  bool Redefine=false;

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
  ClignoteEtSon(nbj_raw,NBJ_BASETONE,NBJ_TONEINC,0);

  int count=0;
  do
  {
    delay(NBJDELAY);
    count+=NBJDELAY;
    
    if (count>DELAYREDEFINE) Redefine=true;
    
  }while (ReadPlayerInput(nbj_raw) && !Redefine);

  if (Redefine)
  {
    //Montre aux joueurs les sélections.
    ClignoteEtSon(nbj_raw,NBJ_BASETONE,NBJ_TONEINC,0);
  }

  return Redefine;
}

void RedefinePlayerPins(bool Auto)
{
  #define OutPinStart 31
  #define OutPinInterval 2
  #define InPinStart 24
  #define InPinInterval 2
  if (Auto)
  {
    //Pin definitions
    for (int i=0; i<=nbj_raw_max;i++)
    {
      int Pin;
      //LED ROUGE des joueurs
      Pin=OutPinStart+OutPinInterval*i;
      pinMode(Pin, OUTPUT);
      PlayerOutputPins[i]=Pin;
      
      //Manettes.
      Pin=InPinStart+InPinInterval*i;
      pinMode(Pin, INPUT);
      PlayerInputPins[i]=Pin;
    }
  }
  else
  {
    int AssignedPins[nbj_max]={false};
    int NewPins[nbj_max];
    for (int i=0; i<nbj_max; i++)
    {
      NewPins[i]=-1;
    }
    
    ActivateBlueLED(100);
    tone(Tone_Pin, 1500, 400);
    
    for (int i=0; i<nbj; i++)
    {
      bool ValidAssignment;
      do
      {
        ValidAssignment=true;
        int P=-1;
        do
        {
          P=FirstActive(nbj_raw_max);
        }while(P==-1);
        LOG_GENERAL("PRESS:");
        LOG_GENERAL(P);
        LOG_GENERAL("\n");

        if (i!=0)
        {
          for (int j=0; j<i; j++)
          {
            if (P==NewPins[j])
            {
              ValidAssignment=false;
            }
          }
        }
        
        if (ValidAssignment)
        {
          NewPins[i]=P;
          ActivateRedLight(P);
          AssignedPins[P]=true;
        }
        delay(25);
      }while (!ValidAssignment);
    }

    LOG_GENERAL("Assigned Pins:\n");
    for (int i=0; i<nbj_max; i++)
    {
      LOG_GENERAL(i);
      LOG_GENERAL(":");
      LOG_GENERAL(AssignedPins[i]);
      LOG_GENERAL(":");
      LOG_GENERAL(NewPins[i]);
      LOG_GENERAL("\n");
    }

    
    //Reorder the pins so that the game makes sense.
    int TempPins[nbj];
    int TempPinAssigned[nbj_max]={false};
    int index;
    for (int i=0; i<nbj; i++)
    {
      int Min=99;
      for (int j=0; j<nbj_max; j++)
      {
        if (AssignedPins[j] && !TempPinAssigned[j])
        {
          index=j;
          break;
        }
      }
      
      LOG_GENERAL("Min Unassigned:");
      LOG_GENERAL(NewPins[index]);
      LOG_GENERAL("\n");
      TempPins[i]=index;
      TempPinAssigned[index]=true;
    }

    for (int i=0; i<nbj; i++)
    {
      NewPins[i]=TempPins[i];
    }
    
    LOG_GENERAL("After Reordering Pins:\n");
    for (int i=0; i<nbj_max; i++)
    {
      LOG_GENERAL(i);
      LOG_GENERAL(":");
      LOG_GENERAL(AssignedPins[i]);
      LOG_GENERAL(":");
      LOG_GENERAL(NewPins[i]);
      LOG_GENERAL("\n");
    }
    
    //Assign the rest automatically
    for (int i=nbj; i<nbj_max; i++)
    {
      for (int j=0; j<nbj_max; j++)
      {
        if (!AssignedPins[j])
        {
          NewPins[i]=j;
          AssignedPins[j]=true;
          break; 
        }
      }
    }
        
    LOG_GENERAL("Final Reordering Pins with empty slots:\n");
    for (int i=0; i<nbj_max; i++)
    {
      LOG_GENERAL(i);
      LOG_GENERAL(":");
      LOG_GENERAL(AssignedPins[i]);
      LOG_GENERAL(":");
      LOG_GENERAL(NewPins[i]);
      LOG_GENERAL("\n");
    }

    delay(200);
    ActivateBlueLED(0);
    TurnOffAllRedLights();
    delay(500);
    ActivateBlueLED(100);

    //Reassign the new pins
    for (int i=0; i<nbj_max; i++)
    {
      int Pin;
      Pin=OutPinStart+OutPinInterval*NewPins[i];
      PlayerOutputPins[i]=Pin;

      Pin=InPinStart+InPinInterval*NewPins[i];
      PlayerInputPins[i]=Pin;
    }

    //ClignoteEtSon
    ClignoteEtSon(nbj_raw,500,200,0);
    TurnOffAllLights();
  }
}

//Fonction de setup pour Vitesse
void Vitesse()
{
  #define V_BASETONE 300
  #define V_TONEINC 150
  
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
  ClignoteEtSon(vitesse_raw,V_BASETONE,V_TONEINC,0);
}

//Game mode selection
void GameMode()
{
  
  #define GM_BASETONE 500
  #define GM_TONEINC 50
  
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
    Selection-=5;
    EnterDemo=true;
  }

  //Now check game mode.
  if (Selection>NbModes-1 && Selection<5)
  {
    Game_Mode=NbModes-1;
  }
  else
  {
    Game_Mode=Selection;
  }
  
  if (OriginalSel<5)
  {
    ClignoteEtSon(Game_Mode,GM_BASETONE,GM_TONEINC,0);
  }
  else
  {
    ClignoteEtSon(Game_Mode,GM_BASETONE,GM_TONEINC,5);
  }

  if (EnterDemo)
  {
    delay(750);
    if (ReadPlayerInput(OriginalSel))
    {
      AllModes=true;
      ClignoteEtSon(Game_Mode,GM_BASETONE,GM_TONEINC,5);
    }
  }
  
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
  LOG_GENERAL("JoueurPuissant:");
  LOG_GENERAL(JoueurPuissant);
  LOG_GENERAL("\n");
  LOG_GENERAL("JoueurRoi:");
  LOG_GENERAL(JoueurRoi);
  LOG_GENERAL("\n");
  LOG_GENERAL("Pins des Joueurs:\n");
  for (int i=0; i<nbj_max; i++)
  {
    LOG_GENERAL(i);
    LOG_GENERAL(": In:");
    LOG_GENERAL(PlayerInputPins[i]);
    LOG_GENERAL(", Out:");
    LOG_GENERAL(PlayerOutputPins[i]);
    LOG_GENERAL("\n");
  }
  LOG_GENERAL("\n");
  LOG_GENERAL("\n");
  LOG_GENERAL("SETUP COMPLETE");
  LOG_GENERAL("\n");
}
