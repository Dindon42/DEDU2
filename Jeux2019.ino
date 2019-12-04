////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ENABLE_LOGGING
  #define LOG_MIN2(a) LOG_GAME(Game_id_MIN2,a)
#else
  #define LOG_MIN2(a)
#endif
void MIN2()
{
  #define MIN2_StartTicTimerThreshold  825
  #define MIN2_EndTicTimerThresholdMin 350
  #define MIN2_EndTicTimerThresholdMax 425
  #define MIN2_TicTimerDecrementFactorMin  92 //0 to 100
  #define MIN2_TicTimerDecrementFactorMax 102 //0 to 100
  int TicTimer=0;
  int RoundTicCounter;
  unsigned long GameTimer=0;
  int PlayerPressCounter[nbj];
  bool PreviousState[nbj]={false};
  bool PlayersInGame[nbj];
  bool CurrentState;
  int ActivePlayers=0;
  bool TwoWinners=false;
  

  //Init
  for (int i=0; i<nbj; i++)
  {
    PlayersInGame[i]=true;
  }
  LOG_MIN2("========\n");
  LOG_MIN2("==MIN2==\n");
  LOG_MIN2("========\n");
  //MAIN GAME
  do
  {
    //Prep Round
    int TicTimerThreshold=MIN2_StartTicTimerThreshold;
    int RoundTicTimerThreshold=random(MIN2_EndTicTimerThresholdMin, MIN2_EndTicTimerThresholdMax);
    bool Tic=true;
    int RoundNumTic=0;
    bool RoundLoosers[nbj];
    int MIN2_MaxClicks;
    ActivePlayers=0;
    
    LOG_MIN2("RoundTicTimerThreshold:");
    LOG_MIN2(RoundTicTimerThreshold);
    LOG_MIN2("\n");
    
    ActivateGreenLED(100);
    ActivateGreenLED(24);
    TurnOnAllRedLights();
    for (int i=0; i<nbj; i++)
    {
      RoundLoosers[i]=false;
      if (PlayersInGame[i])
      {
        ActivePlayers++;
        PlayerPressCounter[i]=0;
      }
      else
      {
        PlayerPressCounter[i]=-1;
      }
    }
    MIN2_MaxClicks=ActivePlayers;
    LOG_MIN2("MIN2_MaxClicks:");
    LOG_MIN2(MIN2_MaxClicks);
    LOG_MIN2("\n");
    
    //OneRound
    do
    {
      if (TicTimer>=TicTimerThreshold)
      {
        if (Tic)
        {
          tone(Tone_Pin,700,10);
        }
        else
        {
          tone(Tone_Pin,250,10);
          RoundTicCounter++;
        }
        for (int i=0; i<nbj; i++)
        {
          if (PlayersInGame[i])
          {
            if (Tic) DeactivateRedLight(i);
            else ActivateRedLight(i);
          }
        }
        
        Tic=!Tic;
        TicTimer=0;
        TicTimerThreshold=(float)TicTimerThreshold*(float)(random(MIN2_TicTimerDecrementFactorMin, MIN2_TicTimerDecrementFactorMax))/100;
        RoundNumTic++;
        LOG_MIN2("TicTimerThreshold:");
        LOG_MIN2(TicTimerThreshold);
        LOG_MIN2("\n");
      }

      for (int i=0; i<nbj; i++)
      {
        CurrentState=ReadPlayerInput(i) && PlayersInGame[i];
        if (CurrentState && !PreviousState[i] && PlayerPressCounter[i]<=MIN2_MaxClicks-2)
        {
          PlayerPressCounter[i]++;
        }
        PreviousState[i]=CurrentState;
      }
  
      //Update Timers;
      GameTimer++;
      TicTimer++;
      delay(1);
    }while(TicTimerThreshold>RoundTicTimerThreshold);

    delay(200);
    TurnOffAllLights();
    
    LOG_MIN2("RoundComplete\n");
    LOG_MIN2("RoundNumTic:");
    LOG_MIN2(RoundNumTic);
    LOG_MIN2("\n");

    //Reset ClickGroups
    int ClickGroups[MIN2_MaxClicks];
    for (int i=0; i<MIN2_MaxClicks; i++)
    {
      ClickGroups[i]=0;
    }
    
    //Log Counts
    for (int i=0; i<nbj; i++)
    {
      LOG_MIN2("ID: ");
      LOG_MIN2(i);
      LOG_MIN2(" Clicks: ");
      LOG_MIN2(PlayerPressCounter[i]);
      LOG_MIN2("\n");
      if (PlayersInGame[i])
      {
        ClickGroups[PlayerPressCounter[i]]++;
      }
    }

    //Step 1: Remove Largest group.
    int MinGroup=-1;
    int MaxGroup=-1;
    int LargestGroup_NumPlayers=-1;
    bool GroupsToEliminate[MIN2_MaxClicks]={false};
    int NumActiveGroups=0;
    for (int i=0; i<MIN2_MaxClicks; i++)
    {
      LOG_MIN2("Group ID: ");
      LOG_MIN2(i);
      LOG_MIN2(" ClickGroups[i]: ");
      LOG_MIN2(ClickGroups[i]);
      LOG_MIN2("\n");
      if (ClickGroups[i]>0)
      {
        if(MinGroup==-1) MinGroup=i;
        if(i>MaxGroup) MaxGroup=i;
        NumActiveGroups++;
      }
      if (ClickGroups[i]>LargestGroup_NumPlayers)
      {
        LargestGroup_NumPlayers=ClickGroups[i];
      }
    }

    bool AllGroupsTied=true;
    LOG_MIN2("GroupsToEliminate\n");
    for (int i=0; i<MIN2_MaxClicks; i++)
    {
      if (ClickGroups[i]!=LargestGroup_NumPlayers && ClickGroups[i]>0)
      {
        AllGroupsTied=false;
      }
      if (ClickGroups[i]==LargestGroup_NumPlayers)
      {
        GroupsToEliminate[i]=true;
      }
      LOG_MIN2("Group ID: ");
      LOG_MIN2(i);
      LOG_MIN2(" Eliminate?: ");
      LOG_MIN2(GroupsToEliminate[i]);
      LOG_MIN2("\n");
    }
    LOG_MIN2("LargestGroup_NumPlayers: ");
    LOG_MIN2(LargestGroup_NumPlayers);
    LOG_MIN2("\n");
    LOG_MIN2("AllGroupsTied: ");
    LOG_MIN2(AllGroupsTied);
    LOG_MIN2("\n");
    LOG_MIN2("NumActiveGroups: ");
    LOG_MIN2(NumActiveGroups);
    LOG_MIN2("\n");
    LOG_MIN2("MinGroup: ");
    LOG_MIN2(MinGroup);
    LOG_MIN2("\n");
    LOG_MIN2("MaxGroup: ");
    LOG_MIN2(MaxGroup);
    LOG_MIN2("\n");
    
    if (!AllGroupsTied || NumActiveGroups==1)
    {
      for (int i=0; i<nbj; i++)
      {
        if (PlayersInGame[i] && GroupsToEliminate[PlayerPressCounter[i]])
        {
          RoundLoosers[i]=true;
          PlayersInGame[i]=false;
        }
      }
      MultiLooserSoundAndLight(RoundLoosers, nbj);
    }
    else
    {
      //If All groups are tied and two players in game... Two Winners declared.
      TwoWinners=ActivePlayers==2;
      LOG_MIN2("TwoWinners: ");
      LOG_MIN2(TwoWinners);
      LOG_MIN2("\n");
      
      if (!TwoWinners)
      {
        //All groups are tied.
        //Eliminate Min and Max Clickers.
        for (int i=0; i<nbj; i++)
        {
          if (PlayersInGame[i] && (PlayerPressCounter[i]==MinGroup || PlayerPressCounter[i]==MaxGroup))
          {
            RoundLoosers[i]=true;
            PlayersInGame[i]=false;
          }
        }
        MultiLooserSoundAndLight(RoundLoosers, nbj);
      }
    }
    ActivePlayers=CountActivePlayers(PlayersInGame, nbj);
    //Next Round.
    delay(500);
    LOG_MIN2("ActivePlayers: ");
    LOG_MIN2(ActivePlayers);
    LOG_MIN2("\n");
    LOG_MIN2("TwoWinners: ");
    LOG_MIN2(TwoWinners);
    LOG_MIN2("\n");
  }while(ActivePlayers>1 && !TwoWinners);

  LOG_MIN2("END GAME\n");
  
  TurnOffAllLights();
  delay(700);
  
  //A winner is you
  if (ActivePlayers>0)
  {
    ControlPlayerRedLights(PlayersInGame, nbj, true, true);
    ActivateGreenLED(20);
    OneUp();
    TurnOffAllLights();
    delay(500);
    //winning ceremony
    MultipleWinnerSoundAndLight(PlayersInGame, nbj);
    LOG_MIN2("END GAME2\n");
    UpdateWinners(PlayersInGame, nbj);
  }
  else
  {
    AllLoosersSoundAndLight();
  }
  TurnOffAllLights();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ENABLE_LOGGING
  #define LOG_AR2(a) LOG_GAME(Game_id_AR2,a)
#else
  #define LOG_AR2(a)
#endif
void AR2()
{
  //TUNABLES
  int RandFactor=random(10,25);
  int RandFactorModifThreshold=random(40,60);
  #define AR2_WinCondToggleRand 125
  #define AR2_ENDGAME_RANDFACTOR 75
  #define DeduMasterClickMin 1
  #define DeduMasterClickMax 5
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
  #define AR2_GAMEDELAY 20
  #define AR2_GRACETIME 7242
  #define AR2_NOTETIME 200
  //END TUNABLES

  
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
  LOG_AR2("=--=--=\n");
  LOG_AR2("=-AR2-=\n");
  LOG_AR2("=--=--=\n");
  //int LightMapping[4]={0,6,15,24};
  int LightMapping[4]={0,8,24,42};
  int ToneMapping[8]={261,293,329,350,392,440,494,523};
  unsigned long GameCounter=0;
  unsigned long RandIncreaseCounter=0;
  int DeduMaster=random(nbj);
  int DeduMasterClicks=0;
  int DeduMasterNextAction=random(DeduMasterClickMin, DeduMasterClickMax);
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
      LOG_AR2("New RandFactor: ");
      LOG_AR2(RandFactor);
      LOG_AR2("\n");
      
      //Speed up The AutoBots at end of game
      if (TriggerEndGame)
      {
        RandFactor--;
        RandFactorModifThreshold--;
      }
      else
      {
        RandFactor++;
        RandFactorModifThreshold++;
      }
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
        //AUTOMATED PLAYERS DO RANDOM ACTION
        //CurrentState=random(RandFactor)==0;
      }
      
      if (!PreviousState[i] && CurrentState && PlayersInGame[i])
      {
        //New click registered.
        //Reverse output array if player clicks.
        OutputArray[i]=!OutputArray[i];

        //Slowly stop auto-spammers as they reach goal condition
        if (TriggerEndGame && i!=Looser)
        {
          if (WinCondition==0)
          {
            if (!OutputArray[i])
            {
              LOG_AR2("One Less: ");
              LOG_AR2(i);
              LOG_AR2("\n");
              PlayersInGame[i]=false;
            }
          }
          else
          {
            if (OutputArray[i])
            {
              LOG_AR2("One Less: ");
              LOG_AR2(i);
              LOG_AR2("\n");
              PlayersInGame[i]=false;
            }
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
            DeduMasterNextAction=random(DeduMasterClickMin, DeduMasterClickMax);
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

    if (abs(SumPlayerOutput(OutputArray, nbj)-WinCondition)==1 && !TriggerEndGame  && GraceTimeOver)
    {
      LOG_AR2("Trigger End Game\n");
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

int SumPlayerOutput(bool OutputArray[], int ArrSize)
{
  int Sum=0;
  for (int i=0; i<ArrSize; i++)
  {
    if (OutputArray[i]) Sum++;
  }
  return Sum;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ENABLE_LOGGING
  #define LOG_TB(a) LOG_GAME(Game_id_TB,a)
#else
  #define LOG_TB(a)
#endif
void TheButton()
{
  //Tunables
  #define GameEndCounterPlayerFactorMin 70
  #define GameEndCounterPlayerFactorMax 120
  #define ProbNoLight 0
  //Tunbles END

  //Local vars
  int GameEndCounter=random(GameEndCounterPlayerFactorMin*nbj,GameEndCounterPlayerFactorMax*nbj);
  #define Gamedelay 5
  #define LightDelay 150
  #define LightSignatureNum 1
  bool SequenceComplete=false;
  int Looser=-1;
  int SuperLooser=-1;
  bool TimeIsUp=false;
  int GameCounter=0;
  int GameCounterPrevAction=0;
  int GameSequence[nbj];
  for (int i=0; i<nbj; i++)
  {
    GameSequence[i]=-1;
  }
  bool PreviousState[nbj]={false};
  bool CurrentState[nbj];
  int SeqProgress=0;
  int WaitTime[nbj];
  for (int j=0; j<nbj; j++)
  {
    WaitTime[j]=-1;
  }
  bool EnableLights=random(0,ProbNoLight)==0;
  
  //END LOCAL VARS

  LOG_TB("================\n");
  LOG_TB("   THE BUTTON\n");
  LOG_TB("================\n");
  LOG_TB("\n");
  LOG_TB("GameEndCounter:");
  LOG_TB(GameEndCounter);
  LOG_TB("\n");
  LOG_TB("EnableLights:");
  LOG_TB(EnableLights);
  LOG_TB("\n");
  
  //Log Sequence
  LOG_TB("\n");
  LOG_TB("Game Sequence:\n");
  for (int i=0; i<nbj; i++)
  {
    LOG_TB(GameSequence[i]+1);
    LOG_TB(", ");
  }
  LOG_TB("\n");

  //Signature lumineuse
  MoveDEDUFlag(100);
  for (int j=0; j<LightSignatureNum; j++)
  {
    for (int i=0; i<nbj_max; i++)
    {
      int lf=100-10*i;
      ControlAllLights(true,lf,lf);
      delay(LightDelay);
    }
  }
  ControlAllLights(true,0,0);
  delay(25);
  TurnOffAllLights();
  ReadySound(550);
  
  do
  {
    //Move Flag To show game progress
    MoveDEDUFlag(100-100*((float)GameCounter/(float)GameEndCounter));

    //Check player input.
    for (int i=0; i<nbj; i++)
    {
      //Record current state
      CurrentState[i]=ReadPlayerInput(i);

      //Check if player has started pressing
      if (!PreviousState[i] && CurrentState[i])
      {
        //Log presser
        LOG_TB("Press:");
        LOG_TB(i+1);
        LOG_TB("\n");
        LOG_TB("Current:");
        LOG_TB(GameSequence[SeqProgress]+1);
        LOG_TB("\n");
        LOG_TB("Next:");
        if (SeqProgress==nbj-1)
        {
          LOG_TB("N/A");
        }
        else
        {
          LOG_TB(GameSequence[SeqProgress+1]+1);
        }
        LOG_TB("\n");
        LOG_TB("------------\n");
        
        //Player is pressing

        //Check if player is part of the sequence first.
        bool NotInSequence=true;
        for (int j=0; j<nbj; j++)
        {
          NotInSequence=GameSequence[j]!=i;
          if (!NotInSequence) break;
        }
        
        //If the game sequence is not defined for the current progress, define it and reset the sequence.
        if (GameSequence[SeqProgress]==-1 && NotInSequence)
        {
          LOG_TB("NEW Player in seq:");
          LOG_TB(i+1);
          LOG_TB("\n");

          if (EnableLights)
          {
            ActivateRedLight(i);
            delay(100);
            //OneUp();
          }
          
          GameSequence[SeqProgress]=i;

          //Reset the sequence
          for (int j=0; j<nbj; j++)
          {
            WaitTime[j]=-1;
          }
          SeqProgress=0;
          GameCounter=0;
          GameCounterPrevAction=0;
          TurnOffAllRedLights();

          //Log new seq
          //Log Sequence
          LOG_TB("\n");
          LOG_TB("NEW Game Sequence:\n");
          for (int j=0; j<nbj; j++)
          {
            LOG_TB(GameSequence[j]+1);
            LOG_TB(", ");
          }
          LOG_TB("\n");

          
          LOG_TB("Next:");
          if (SeqProgress==nbj-1)
          {
            LOG_TB("N/A");
          }
          else
          {
            LOG_TB(GameSequence[0]+1);
          }
          LOG_TB("\n");
          LOG_TB("------------\n");
        }
        //If the game sequence is defined and the proper player presses, make the sequence progress
        else if (GameSequence[SeqProgress]==i)
        {
          if (EnableLights)
          {
            ActivateRedLight(i);
          }
          WaitTime[i]=GameCounter-GameCounterPrevAction;
          GameCounterPrevAction=GameCounter;
          SeqProgress++;
        }
        else if (!NotInSequence)
        {
          LOG_TB("SUPER LOOSER:");
          LOG_TB(i+1);
          LOG_TB("\n");
          LOG_TB("Current was:");
          LOG_TB(GameSequence[SeqProgress]+1);
          
          //Log Sequence
          LOG_TB("\n");
          LOG_TB("Game Sequence:\n");
          for (int j=0; j<nbj; j++)
          {
            LOG_TB(GameSequence[j]+1);
            LOG_TB(", ");
          }
          LOG_TB("\n");
          
          ActivateRedLight(i);
          SuperLooser=i;
        }
        else
        {
          ActivateRedLight(i);
          Looser=i;
        }
        
        PreviousState[i]=CurrentState[i];
        break;
      }
      //Record Current into Previous
      PreviousState[i]=CurrentState[i];
    }

    
    //Increase gametimer and delay
    GameCounter++;
    delay(Gamedelay);
    
    TimeIsUp=GameCounter>GameEndCounter;
    SequenceComplete=SeqProgress==nbj;
  }while(!SequenceComplete && !TimeIsUp && Looser==-1 && SuperLooser==-1);

  delay(500);
  TurnOffAllLights();
  MoveDEDUFlag(0);
  delay(500);

  //Time Up: Longest wait=looser;
  if (TimeIsUp)
  {
    //Too slow, punish the slowest.
    LOG_TB("GAME END: TOO SLOW!\n");
    LOG_TB("GameCounter:");
    LOG_TB(GameCounter);
    LOG_TB("\n");
    
    //Was it someone's turn?
    if (GameSequence[SeqProgress]==-1)  //No one's turn
    {
      bool TheyAllLoose=SeqProgress==0;
      
      //Check if the sequence players left enough time
      int TimeRemainingAtGameEnd=GameCounter-GameCounterPrevAction;

      if (TheyAllLoose)
      {
        LOG_TB("ALL LOOSERS!\n");
        AllLoosersSoundAndLight();
        TurnOffAllLights();
      }
      else
      {
        int MaxWait=-1;
        for (int i=0; i<nbj; i++)
        {
          if (WaitTime[i]>MaxWait)
          {
            MaxWait=WaitTime[i];
            Looser=i;
          }
        }
        
        if (MaxWait>TimeRemainingAtGameEnd)
        {
          //They did not have enough time, you bastard.
          LOG_TB("This Fella did not leave enough time for the rest!\n");
          LooserSoundAndLight(Looser,false);
          SingleLooserSoundAndLight(Looser);
          TurnOffAllLights();
        }
        else
        {
          bool Loosers[nbj]={false};

          for (int i=0; i<nbj; i++)
          {
            bool NotInSequence;
            for (int j=0; j<nbj; j++)
            {
              NotInSequence=GameSequence[j]!=i;
              if (!NotInSequence) break;
            }
            Loosers[i]=NotInSequence;
          }
          
          //They had enough time
          MultiLooserSoundAndLight(Loosers, nbj);
        }
      }
    }
    else //Someone's turn
    {
      LOG_TB("WHOS A SLOWPOKE?\n");
      //First record the last players' wait time
      WaitTime[GameSequence[SeqProgress]]=GameCounter-GameCounterPrevAction;

      int MaxWait=-1;
      for (int i=0; i<nbj; i++)
      {
        if (WaitTime[i]>MaxWait)
        {
          MaxWait=WaitTime[i];
          Looser=i;
        }
      }
      //On donne la honte à celui qui a été le plus lent.
      LooserSoundAndLight(Looser,false);
      JoueurHonte=MarqueurHonte(Looser,DelaiPetiteHonte);
      //Reset des jeux qui transferent la honte.
      ResetProbHonte();
      TurnOffAllLights();
    }
  }
  else if (Looser!=-1)
  {
    LOG_TB("WHO BREAKS OUR BALLS?\n");
    //Single Looser, Breaker of sequence
    LooserSoundAndLight(Looser,false);
    SingleLooserSoundAndLight(Looser);
    TurnOffAllLights();
  }
  else if (SuperLooser!=-1)
  {
    LOG_TB("WTF REALLY?\n");
    //Single Looser, Breaker of sequence, already in the seq
    LooserSoundAndLight(SuperLooser,false);
    JoueurHonte=MarqueurHonte(SuperLooser,DelaiPetiteHonte);
    //Reset des jeux qui transferent la honte.
    ResetProbHonte();
    TurnOffAllLights();
  }
  else
  {
    LOG_TB("VICTORY!\n");
    //Seq Complete
    ActivateGreenLED(20);
    delay(500);
    OneUp();
    delay(500);
    TurnOffAllLights();
    ResetProbFFA();
    FFA();
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ENABLE_LOGGING
  #define LOG_SG(a) LOG_GAME(Game_id_SEQ,a)
#else
  #define LOG_SG(a)
#endif
void SequenceGlobale(bool DemoMode)
{
  //Tunables
  #define MaxGameCounterFailAll 1000
  #define GameLengthPlayerFactorMin 1
  #define GameLengthPlayerFactorMax 3
  #define GameLengthPlayerFactorDemo 1
  #define MaxInvalSeqMD 100
  #define MaxInvalSeqVT 400
  #define IntroNoteTime 150
  #define IntroSilenceTime 150
  #define GameNoteTimeMin 150
  #define GameSilenceTimeMin 150
  #define GameTimeDecreaseMin 5
  #define GameTimeDecreaseMax 25
  int GameNoteTime=300;
  int GameSilenceTime=300;
  int JumpMin;
  int JumpMax;
  if (DemoMode)
  {
    JumpMin=2;
    JumpMax=2;
  }
  else
  {
    JumpMin=2;
    JumpMax=4;
  }
  //Tunables END.

  //Game vars
  #define GamedelaySeq 15
  int GameCounter;
  int GameLength=DemoMode ? (nbj*GameLengthPlayerFactorDemo)+2 : random(nbj*GameLengthPlayerFactorMin+2,nbj*GameLengthPlayerFactorMax+1);
  if (GameLength%nbj==0) GameLength++;
  int GameProgressInit=random(JumpMin,JumpMax+1);
  int GameProgress=GameProgressInit;
  int ValidityThreshold=max(1,(int)GameLength/nbj);
  int ValidityMaxDelta=2;
  int Looser=-1;
  bool AllLoosers=false;
  bool SequenceComplete=false;
  int GameSequence[GameLength];
  int BaseTones[nbj_max]={261,293,329,350,392,440,494,523,587,659};
  int Tones[nbj];
  for (int i=0; i<nbj; i++)
  {
    Tones[i]=BaseTones[i];
  }
  bool NewRound=true;
  bool PreviousState[nbj]={false};
  bool CurrentState[nbj];
  int SeqProgress;
  //Game vars END
  
  LOG_SG("================\n");
  LOG_SG("SEQUENCE GLOBALE\n");
  LOG_SG("================\n");
  LOG_SG("\n");
  LOG_SG("GameLength:");
  LOG_SG(GameLength);
  LOG_SG("\n");
  LOG_SG("ValidityThreshold:");
  LOG_SG(ValidityThreshold);
  LOG_SG("\n");
  LOG_SG("ValidityMaxDelta:");
  LOG_SG(ValidityMaxDelta);
  LOG_SG("\n");
    
  //Initialize
  bool InvalidSequence;
  int NumInvalidSeq=0;
  do
  {
    int Min=1000;
    int Max=-1000;
    //Randomize sequence
    for (int i=0; i<GameLength; i++)
    {
      GameSequence[i]=random(nbj);
    }
    InvalidSequence=false;
    //Check Sequence
    for (int j=0; j<nbj; j++)
    {
      int Count=0;
      for (int i=0; i<GameLength; i++)
      {
        if (GameSequence[i]==j) Count++;
      }

      if (Count<Min) Min=Count;
      if (Count>Max) Max=Count;
      
      if (Count<ValidityThreshold)
      {
        InvalidSequence=true;
        NumInvalidSeq++;
        break;
      }
    }

    if (Max-Min>ValidityMaxDelta && !InvalidSequence)
    {
      InvalidSequence=true;
      NumInvalidSeq++;
    }

    bool LogMaxInval=false;
    if (NumInvalidSeq%MaxInvalSeqMD==MaxInvalSeqMD-1)
    {
      LogMaxInval=true;
      ValidityMaxDelta++;
    }
    if (NumInvalidSeq%MaxInvalSeqVT==MaxInvalSeqVT-1)
    {
      LogMaxInval=true;
      ValidityThreshold=max(1,ValidityThreshold-1);
    }
    if (LogMaxInval)
    {
      LOG_SG("TOO MANY INVALID!\n");
      LOG_SG("-----------------\n");
      LOG_SG("NumInvalidSeq:");
      LOG_SG(NumInvalidSeq);
      LOG_SG("\n");
      LOG_SG("GameLength:");
      LOG_SG(GameLength);
      LOG_SG("\n");
      LOG_SG("ValidityThreshold:");
      LOG_SG(ValidityThreshold);
      LOG_SG("\n");
      LOG_SG("ValidityMaxDelta:");
      LOG_SG(ValidityMaxDelta);
      LOG_SG("\n");
    }
    
    if (!InvalidSequence)
    {
      LOG_SG("Max:");
      LOG_SG(Max);
      LOG_SG("\n");
      LOG_SG("Min:");
      LOG_SG(Min);
      LOG_SG("\n");
      LOG_SG("NumInvalidSeq:");
      LOG_SG(NumInvalidSeq);
      LOG_SG("\n");
    }
    
  }while(InvalidSequence);
  
  //Log IndivCounts
  for (int j=0; j<nbj; j++)
  {
    int Count=0;
    for (int i=0; i<GameLength; i++)
    {
      if (GameSequence[i]==j) Count++;
    }
    LOG_SG("ID:");
    LOG_SG(j+1);
    LOG_SG(", Count:");
    LOG_SG(Count);
    LOG_SG("\n");
  }
  LOG_SG("\n");

/*LOGGAMEONLY.
//Log Sequence
LOG_SG("\n");
LOG_SG("Game Sequence:\n");
for (int i=0; i<GameLength; i++)
{
  LOG_SG(GameSequence[i]+1);
  LOG_SG(", ");
}
LOG_SG("\n");
SequenceGlobale(false);
*/
  if (!SkipLights)
    {
    //Light Signature
    //Run the sequence quickly, play notes and move DEDU accordingly.
    int PrevG=0;
    int PrevB=0;
    for (int i=0; i<GameLength; i++)
    {
      int CurG;
      int CurB;
      do
      {
        CurG=random(0,3);
        CurB=random(0,3);
      }while((CurG==PrevG && CurB==PrevB) || (CurG==0 && CurB==0));
      
      ActivateBlueLED(CurG*10);
      ActivateGreenLED(CurB*10);
      //void PlayNoteWithLight(int Tone_Pin, float Freq, float PlayTime, float WaitTime,int Player)
      PlayNoteWithLight(Tones[GameSequence[i]],IntroNoteTime,IntroSilenceTime,GameSequence[i]);
      PrevG=CurG;
      PrevB=CurB;
    }
    TurnOffAllLights();
    delay(700);
    
    TicTac(700,2);
    delay(700);
  }

  //Main Game Loop
  do
  {
    if (NewRound)
    {
      LOG_SG("==========\n");
      LOG_SG("NEW ROUND!\n");
      LOG_SG("==========\n");
      //Log Sequence
      LOG_SG("\n");
      LOG_SG("Game Sequence:\n");
      for (int i=0; i<GameLength; i++)
      {
        LOG_SG(GameSequence[i]+1);
        LOG_SG(", ");
      }
      LOG_SG("\n");
      
      if (GameProgress>GameProgressInit)
      {
        delay(GameNoteTime);
        TurnOffAllRedLights();
        delay(500);
        ActivateGreenLED(20);
        OneUp();
        GameNoteTime-=random(GameTimeDecreaseMin,GameTimeDecreaseMax);
        GameSilenceTime-=random(GameTimeDecreaseMin,GameTimeDecreaseMax);
        if (GameNoteTime<GameNoteTimeMin) GameNoteTime=GameNoteTimeMin;
        if (GameSilenceTime<GameSilenceTimeMin) GameSilenceTime=GameSilenceTimeMin;
        delay(500);
        DeactivateGreenLED();
        delay(500);
      }
      LOG_SG("GameProgress:");
      LOG_SG(GameProgress);
      LOG_SG("\n");
      LOG_SG("First:");
      LOG_SG(GameSequence[0]+1);
      LOG_SG("\n");
      LOG_SG("GameNoteTime:");
      LOG_SG(GameNoteTime);
      LOG_SG("\n");
      LOG_SG("GameSilenceTime:");
      LOG_SG(GameSilenceTime);
      LOG_SG("\n");
      //Demo the sequence
      for (int i=0; i<GameProgress; i++)
      {
        PlayNoteWithLight(Tones[GameSequence[i]],GameNoteTime,GameSilenceTime,GameSequence[i]);
      }
      TurnOffAllLights();
      delay(700);
      TicTac(700,2);
      NewRound=false;
      SeqProgress=0;
      GameCounter=0;
    }

    //Check Inputs
    for (int i=0; i<nbj; i++)
    {
      //Record current state
      CurrentState[i]=ReadPlayerInput(i);

      //Check if player has started pressing
      if (!PreviousState[i] && CurrentState[i])
      {

        //Log presser
        LOG_SG("Press:");
        LOG_SG(i+1);
        LOG_SG("\n");
        LOG_SG("Current:");
        LOG_SG(GameSequence[SeqProgress]+1);
        LOG_SG("\n");
        LOG_SG("Next:");
        if (SeqProgress==GameLength-1)
        {
          LOG_SG("N/A");
        }
        else
        {
          LOG_SG(GameSequence[SeqProgress+1]+1);
        }
        LOG_SG("\n");
        LOG_SG("------------\n");
        
        //Illuminate the player's LED
        ActivateRedLight(i);
        
        //Check if it is the proper player
        if (i==GameSequence[SeqProgress])
        {
          //Good! Make the sequence progress.
          tone(Tone_Pin, Tones[i], GameNoteTime);
          SeqProgress++;
          GameCounter=0;
        }
        else
        {
          Looser=i;
          //END THE SEQUENCE HERE.
        }
      }

      //Record Current into Previous
      PreviousState[i]=CurrentState[i];
    }

    //Check for new round
    if (SeqProgress==GameProgress)
    {
      //Check for Seq complete
      if (GameProgress==GameLength)
      {
        SequenceComplete=true;
      }
      else
      {
        GameProgress+=random(JumpMin,JumpMax+1);
        if (GameProgress>GameLength) GameProgress=GameLength;
        NewRound=true;
      }
    }
    
    if (GameCounter==GameNoteTime/GamedelaySeq)
    {
      TurnOffAllRedLights();
    }
    
    if (GameCounter>MaxGameCounterFailAll)
    {
      AllLoosers=true;
      Looser=-1;
      SequenceComplete=false;
    }
    delay(GamedelaySeq);
    GameCounter++;
  }while(!SequenceComplete && Looser==-1 && !AllLoosers);
  delay(200);
  TurnOffAllRedLights();
  
  delay(500);
  
  if (AllLoosers)
  {
    LOG_SG("---------------------\n");
    LOG_SG("GAME END: ALL LOOSERS\n");
    LOG_SG("---------------------\n");
    AllLoosersSoundAndLight();
    TurnOffAllLights();
  }
  
  if (Looser!=-1)
  {
    LOG_SG("---------------------\n");
    LOG_SG("GAME END:    1 LOOSER\n");
    LOG_SG("---------------------\n");
    LooserSoundAndLight(Looser,false);
    SingleLooserSoundAndLight(Looser);
    TurnOffAllLights();
  }
  
  if (SequenceComplete)
  {
    LOG_SG("---------------------\n");
    LOG_SG("GAME END:SEQ COMPLETE\n");
    LOG_SG("---------------------\n");
    ActivateGreenLED(20);
    delay(500);
    for (int i=0; i<ValidityThreshold; i++)
    {
      OneUp();
      delay(500);
    }
    TurnOffAllLights();
    ResetProbFFA();
    FFA();
  }
}

