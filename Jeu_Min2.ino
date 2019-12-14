#ifdef ENABLE_LOGGING
  #define LOG_MIN2(a) LOG_GAME(Game_id_MIN2,a)
#else
  #define LOG_MIN2(a)
#endif
void MIN2()
{
  #define ExtraRoundsFor2Players false
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

    if(!ExtraRoundsFor2Players)
    {
      TwoWinners=ActivePlayers==2;
      LOG_MIN2("TwoWinners: ");
      LOG_MIN2(TwoWinners);
      LOG_MIN2("\n");
    }
    
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
