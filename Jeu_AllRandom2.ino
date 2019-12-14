
#ifdef ENABLE_LOGGING
  #define LOG_AR2(a) LOG_GAME(Game_id_AR2,a)
#else
  #define LOG_AR2(a)
#endif
void AR2()
{
  //TUNABLES
  int RandFactor=random(11,62);
  int RandFactorModifThreshold=random(42,84);
  #define AR2_NoBots false
  int AR2_WinCondToggleRand=random(125,200);
  #define AR2_ENDGAME_RANDFACTOR 50
  #define AR2_DeduMasterClickMin 1
  #define AR2_DeduMasterClickMax 5
  #define AR2_BUZZERS_MIN 10
  #define AR2_BUZZERS_MAX 12
  #define AR2_G_LED_MIN 13
  #define AR2_G_LED_MAX 13
  #define AR2_B_LED_MIN 14
  #define AR2_B_LED_MAX 14
  #define AR2_GB_LED_MIN 15
  #define AR2_GB_LED_MAX 15
  //MAX NUMASSIGNMENTS NE PEUT PAS ÊTRE PLUS GRAND QUE LA GRANDEUR DE ARRAY EQUIPES-nbj.
  #define AR2_NumAssignments 16
  int AR2_GAMEDELAY=random(10,25);
  int AR2_GRACETIME=random(7242,10042);
  #define AR2_NOTETIME 200
  //END TUNABLES

  //LOG
  LOG_AR2("=--=--=\n");
  LOG_AR2("=-AR2-=\n");
  LOG_AR2("=--=--=\n");
  LOG_AR2("RandFactor: ");
  LOG_AR2(RandFactor);
  LOG_AR2("\n");
  LOG_AR2("RandFactorModifThreshold: ");
  LOG_AR2(RandFactorModifThreshold);
  LOG_AR2("\n");
  LOG_AR2("AR2_GAMEDELAY: ");
  LOG_AR2(AR2_GAMEDELAY);
  LOG_AR2("\n");
  LOG_AR2("AR2_GRACETIME: ");
  LOG_AR2(AR2_GRACETIME);
  LOG_AR2("\n");
  LOG_AR2("AR2_WinCondToggleRand: ");
  LOG_AR2(AR2_WinCondToggleRand);
  LOG_AR2("\n");
  
  
  //LUMIERES
  if (!SkipLights)
  {
    MaxRandom(10,true);
  }
  //END LUMIERES
  
  //Inputs Mappings
  //DEDU (Condition de victoire) + DEDUMASTER
  bool OutputArray[AR2_NumAssignments]={false};
  bool PreviousState[AR2_NumAssignments]={false};
  int OutputMapping[AR2_NumAssignments];
  int WinCondition=0;
  bool RefreshNotes=true;
  bool PlayersInGame[AR2_NumAssignments];
  int SumActivePlayers=0;
  //Setting all input mappings to -1
  for (int i=0; i<AR2_NumAssignments; i++)
  {
    PlayersInGame[i]=true;
    OutputMapping[i]=-1;
  }
  //int LightMapping[4]={0,6,15,24};
  int LightMapping[4]={0,8,24,42};
  int ToneMapping[8]={261,293,329,350,392,440,494,523};
  unsigned long GameCounter=0;
  unsigned long RandIncreaseCounter=0;
  int DeduMaster=random(nbj);
  int DeduMasterClicks=0;
  int DeduMasterNextAction=random(AR2_DeduMasterClickMin, AR2_DeduMasterClickMax);
  int Looser=-1;
  bool GraceTimeOver=false;
  bool TriggerEndGame=false;
  
  //Assignations des états initiaux
  //Diviser les joueurs actifs en 2
  //Assigner les états initiaux
  //Diviser les joueurs non-actifs en 2
  //Assigner les états initiaux
  AllocateTwoTeams(nbj);
  for (int i=0; i<nbj; i++)
  {
    OutputArray[i]=Equipes[i]==1;
  }

  AllocateTwoTeams(AR2_NumAssignments-nbj);
  for (int i=nbj; i<AR2_NumAssignments; i++)
  {
    OutputArray[i]=Equipes[i-nbj]==1;
  }
  //Print des états initiaux
  LOG_AR2("Initial states\n");
  for (int i=0; i<AR2_NumAssignments; i++)
  {
    LOG_AR2("i: ");
    LOG_AR2(i);
    LOG_AR2("  State: ");
    LOG_AR2(OutputArray[i]);
    LOG_AR2("\n");
  }
  
  //Assign Random Mapping to each player
  int PosAssigned=0;
  LOG_AR2("Assigning Player Mappings\n")
  for (int i=0; i<AR2_NumAssignments; i++)
  {
    //LOG_AR2("Assigning Player: ")
    //LOG_AR2(i);
    //LOG_AR2("\n");
    do
    {
      bool NumAlreadyAllocated=false;
      int r=random(AR2_NumAssignments);
      //LOG_AR2("Wanting to assign mapping: ")
      //LOG_AR2(r);
      //LOG_AR2("\n");
      for (int j=0; j<i; j++)
      {
        if (OutputMapping[j]==r)
        {
          //LOG_AR2("Mapping already assigned to player: ")
          //LOG_AR2(j);
          //LOG_AR2("\n");
          NumAlreadyAllocated=true;
          break;
        }
      }
  
      if (!NumAlreadyAllocated)
      {
        //LOG_AR2("Mapping not already assigned.\nAssigning it to player: ")
        //LOG_AR2(i);
        //LOG_AR2("\n");
        OutputMapping[i]=r;
      }
    }while(OutputMapping[i]==-1);
  }

  //Print des Mappings
  LOG_AR2("Input Mapping\n");
  for (int i=0; i<AR2_NumAssignments; i++)
  {
    LOG_AR2("i: ");
    LOG_AR2(i);
    LOG_AR2("  NewMapping: ")
    LOG_AR2(OutputMapping[i]);
    LOG_AR2("\n");
  }
  LOG_AR2("DeduMaster: ");
  LOG_AR2(DeduMaster);
  LOG_AR2("\n");
  LOG_AR2("DeduMasterNextAction: ");
  LOG_AR2(DeduMasterNextAction);
  LOG_AR2("\n");
  
  //Initial win condition
  if (random(2)==0)
  {
    WinCondition=AR2ToggleWinCondition(WinCondition, TriggerEndGame);
  }

  TurnOffAllLights();
  delay(500);
  SetAr2Outputs(OutputArray, OutputMapping, WinCondition, AR2_NOTETIME, ToneMapping, LightMapping, false);
  delay(500);
  ReadySound(500);

  //////////////////
  //MAIN GAME LOOP//
  //////////////////
  do
  {
    if (RandIncreaseCounter>RandFactorModifThreshold)
    {
      //Speed up The AutoBots at end of game
      if (TriggerEndGame)
      {
        if(RandFactor>3) RandFactor--;
      }
      else
      {
        RandFactor++;
      }
      LOG_AR2("New RandFactor: ");
      LOG_AR2(RandFactor);
      LOG_AR2("\n");
      RandIncreaseCounter=0;
    }
    
    //RandomFactor ToggleWinCondition
    if (random(AR2_WinCondToggleRand)==0)
    {
      WinCondition=AR2ToggleWinCondition(WinCondition, TriggerEndGame);
    }
    //RefreshNotes False by default.
    RefreshNotes=false;
    
    //Read Input and Modify Assignments.
    for (int i=0; i<AR2_NumAssignments; i++)
    {
      bool CurrentState;
      if (i<nbj)
      {
        CurrentState=ReadPlayerInput(i);
      }
      else
      {
        if(AR2_NoBots)
        {
          CurrentState=false;
          if(TriggerEndGame) CurrentState=random(2)==0;
        }
        else
        {
          //AUTOMATED PLAYERS DO RANDOM ACTION
          CurrentState=random(RandFactor)==0;
        }
        
      }
      
      if (!PreviousState[i] && CurrentState && PlayersInGame[i])
      {
        //New click registered.
        //Reverse output array if player clicks.
        OutputArray[i]=!OutputArray[i];

        //Slowly stop auto-spammers as they reach goal condition
        if (TriggerEndGame && i!=Looser)
        {
          if (WinCondition==0 && !OutputArray[i] || WinCondition==nbj && OutputArray[i])
          {
            LOG_AR2("One Less: ");
            LOG_AR2(i);
            LOG_AR2("\n");
            PlayersInGame[i]=false;
          }
        }

        //Check if music Buzzer Musician
        if (OutputMapping[i]>=AR2_BUZZERS_MIN && OutputMapping[i]<=AR2_BUZZERS_MAX)
        {
          RefreshNotes=true;
        }

        //Check DEDUMASTER actions.
        if (i==DeduMaster)
        {
          LOG_AR2("DeduMasterClicks++\n");
          DeduMasterClicks++;
          if (DeduMasterClicks==DeduMasterNextAction)
          {
            LOG_AR2("TOGGLING FROM DEDUMASTER!\n");
            WinCondition=AR2ToggleWinCondition(WinCondition, TriggerEndGame);

            //Compute next DEDUMASTER
            DeduMaster=random(nbj);
            DeduMasterClicks=0;
            DeduMasterNextAction=random(AR2_DeduMasterClickMin, AR2_DeduMasterClickMax);
            LOG_AR2("DeduMaster: ");
            LOG_AR2(DeduMaster);
            LOG_AR2("\n");
            LOG_AR2("DeduMasterNextAction: ");
            LOG_AR2(DeduMasterNextAction);
            LOG_AR2("\n");
          }    
        }
      }
      PreviousState[i]=CurrentState;
    }
    SetAr2Outputs(OutputArray, OutputMapping, WinCondition, AR2_NOTETIME, ToneMapping, LightMapping, RefreshNotes);
    delay(AR2_GAMEDELAY);
    RandIncreaseCounter++;
    
    if (!GraceTimeOver)
    {
      GameCounter+=AR2_GAMEDELAY;
      if (GameCounter>AR2_GRACETIME)
      {
        LOG_AR2("GRACETIME over\n");
        GraceTimeOver=true;
      }
    }

    if (abs(CountActivePlayers(OutputArray, nbj)-WinCondition)==1 && !TriggerEndGame  && GraceTimeOver)
    {
      LOG_AR2("Trigger End Game\n");
      LOG_AR2("\n");
      RandFactor=AR2_ENDGAME_RANDFACTOR;
      TriggerEndGame=true;
      //Identify the Looser based on wincondition
      for (int i=0; i<nbj; i++)
      {
        if (WinCondition==0)
        {
          if (OutputArray[i])
          {
            Looser=i;
          }
          else
          {
            PlayersInGame[i]=false;
          }
        }
        else
        {
          if (!OutputArray[i])
          {
            Looser=i;
          }
          else
          {
            PlayersInGame[i]=false;
          }
        }
      }
    }

    SumActivePlayers=0;
    for (int i=0; i<AR2_NumAssignments; i++)
    {
      if (PlayersInGame[i])
      {
        SumActivePlayers++;
      }
    }
  }while(SumActivePlayers!=1);


  LOG_AR2("OUT OF MAIN LOOP");
  
  //Flash looser with its mapping
  for (int i=0; i<4; i++)
  {
    delay(800);
    OutputArray[Looser]=!OutputArray[Looser];
    if (OutputMapping[Looser]>=AR2_BUZZERS_MIN && OutputMapping[i]<=AR2_BUZZERS_MAX)
    {
      RefreshNotes=true;
    }
    SetAr2Outputs(OutputArray, OutputMapping, WinCondition, AR2_NOTETIME, ToneMapping, LightMapping, RefreshNotes);
  }
  
  delay(500);
  TurnOffAllLights();
  delay(500);
  
  SingleLooserSoundAndLight(Looser);
  
  MoveDEDUFlag(0);
  TurnOffAllLights();
  
}

int AR2ToggleWinCondition(int WinCondition,bool EndGame)
{
  if (EndGame) return WinCondition;
  //LOG_AR2("TOGGLING WINCONDITION\n");
  if (WinCondition==0) return nbj;
  else return 0;
}

void SetAr2Outputs(bool OutputArray[], int OutputMapping[], int WinCondition, int NoteTime, int ToneMapping[], int LightMapping[], bool RefreshNotes)
{
  if (WinCondition==0)
  {
    MoveDEDUFlag(1);
  }
  else
  {
    MoveDEDUFlag(100);
  }
  
  //Mappings.
  //0 to 9 ->LED 1 à 10
  //10, 11, 12, 13 ->BUZZER 1, 2, 3, 4
  //14, 15 ->LED G 1, 2
  //16, 17 ->LED B 1, 2
  int SumTone=0;
  int SumGreenLED=0;
  int SumBlueLED=0;
  for (int i=0; i<AR2_NumAssignments; i++)
  {
    if (OutputMapping[i]<10)
    {
      SetRedLight(OutputMapping[i],OutputArray[i]);
    }
    else if (OutputMapping[i]<=AR2_BUZZERS_MAX)
    {
      if (OutputArray[i]) SumTone++;
    }
    else if (OutputMapping[i]<=AR2_G_LED_MAX)
    {
      if (OutputArray[i]) SumGreenLED++;
    }
    else if (OutputMapping[i]<=AR2_B_LED_MAX)
    {
      if (OutputArray[i]) SumBlueLED++;
    }
    else
    {
      if (OutputArray[i])
      {
        SumGreenLED++;
        SumBlueLED++;
      }
    }
  }
  if (RefreshNotes) tone(Tone_Pin,ToneMapping[SumTone],NoteTime);
  ActivateGreenLED(LightMapping[SumGreenLED]);
  ActivateBlueLED(LightMapping[SumBlueLED]);
}

