
void TestMode()
{
  LOG_GENERAL("==============\n");
  LOG_GENERAL("   TEST MODE  \n");
  LOG_GENERAL("==============\n");
  MoveDEDUFlag(10);
  SonTestMode();
  MoveDEDUFlag(0);
  int NumAct=0;
  int PrevNumAct=0;
  bool DeduFlag=false;
  while (1)
  {
    NumAct=IlluminateActiveExtinguishNonActive(nbj_raw_max);
    delay(1);
    if (NumAct<5)
    {
      ActivateGreenLED(20);
      ActivateBlueLED(0);
    }
    else
    {
      ActivateGreenLED(0);
      ActivateBlueLED(20);
    }
    PrevNumAct=NumAct;
  }
}


void DemoMode(bool AllModes)
{
  bool GoToNext;
  int NumActOut;
  unsigned long Counter;
  int IndivDelay=2;
  int DelayGame=25;
  unsigned const long CounterPlaySame=2500/DelayGame;
  bool PrevInputState[nbj_max]={false};
  bool Player1Controls=true;
  int MaxP=nbj;
  int GameDelay=1000;

  if (Player1Controls)
  {
    MaxP=1;
  }

  LOG_GENERAL("==============\n");
  LOG_GENERAL("= DEMO MODE  =\n");
  LOG_GENERAL("==============\n");
  //Tone
  SonTestMode();

  delay(GameDelay);
  for (int i=0; i<NbJeux-1;i++)
  {
    //If the game mode is 0, play games that have non-0 Prob
    //If the game mode is non-0, play games that did not exist in previous mode.
    //If AllModes, Demo all modes.
    if (
      (Game_Mode==Game_Mode_Original && ProbIndivJeux[i]!=0) ||
      (Game_Mode>Game_Mode_Original && GameProb[i][Game_Mode]!=0 && GameProb[i][Game_Mode-1]==0 && ProbIndivJeux[i]!=0) ||
       AllModes && ProbIndivJeux[i]!=0)
    {
      LOG_GENERAL("JEU:");
      LogGameName(i,true);
      if (!SkipGame)
      {
        do
        {
          WaitForAllNonActive(nbj_raw);
          delay(GameDelay);
          
          //Demo the game once
          PlayGame(i,true);

          WaitForAllNonActive(nbj_raw);
          delay(120);
          
          Counter=0;
          do
          {
            Counter++;
            GoToNext=false;
            for (int j=0; j<MaxP ;j++)
            {
              if (ReadPlayerInput(j))
              {
                if (!PrevInputState[j])
                {
                  Counter=0;
                  LOG_GENERAL("TOGGLE:");
                  LOG_GENERAL(j);
                  LOG_GENERAL("\n");
                  LOG_GENERAL("ReadPlayerInput(j):");
                  LOG_GENERAL(ReadPlayerInput(j));
                  LOG_GENERAL("\n");
                  LOG_GENERAL("PrevInputState[j]:");
                  LOG_GENERAL(PrevInputState[j]);
                  LOG_GENERAL("\n");
                  
                  PrevInputState[j]=true;
                  ToggleOutput(j);
                }
              }
              else
              {
                PrevInputState[j]=false;
              }
              delay(IndivDelay);
            }
            delay(DelayGame);
            
            NumActOut=CheckAllActiveOutputs(nbj_raw);
            
            if (NumActOut==MaxP)
            {
              GoToNext=true;
            }
            
          }while(GoToNext==false && Counter<CounterPlaySame);
          
          delay(500);
          TurnOffAllLights();
          delay(250);
          
        }while(GoToNext==false);
      }
      else
      {
        SimulateGame(i);
      }
    }
  }
  LOG_GENERAL("==============\n");
  LOG_GENERAL("=  DEMO FIN  =\n");
  LOG_GENERAL("==============\n");
}

void EndlessMusicMode()
{
  do
  {
    int r;
    LOG_GENERAL("\n");
    LOG_GENERAL("MUSIC MODE");
    LOG_GENERAL("\n");
    if (SelectedSong==-1)
    {
      LOG_GENERAL("Random Song:");
      r=random(NombreChansons);
    }
    else
    {
      LOG_GENERAL("Selected Song:");
      r=SelectedSong;
    }
    LOG_GENERAL(r);
    LOG_GENERAL("\n");
    JoueChanson(r, 1, MusicRandFactVit, MusicModeLumiere);
    delay(2500);
  }while(1);
}

void PlayExclusiveGame()
{
  do
  {
    LOG_GENERAL("\n");
    LOG_GENERAL("EXCLUSIVE MODE");
    LOG_GENERAL("\n");
    #ifdef ENABLE_LOGGING
      ActiveGameLogging[ExclusiveGame_ID]=true;
    #endif
    PrepareGame(ExclusiveGame_ID);
    PlayGame(ExclusiveGame_ID,ExclusiveGame_DemoMode);
    delay(ExclusiveGameDelay);
  }while(1);
}

