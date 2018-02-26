
void TestMode()
{
  LOG_GENERAL("TEST MODE\n");
  SonTestMode();
  
  while (1)
  {
    IlluminateActiveExtinguishNonActive(nbj_raw_max);
    delay(1);
  }
}


void DemoMode(bool AllModes)
{
  bool GoToNext;
  int NumActOut;
  unsigned long Counter;
  int IndivDelay=2;
  int DelayGame=25;
  unsigned const long CounterPlaySame=3000/DelayGame;
  int PrevInputState[nbj_max]={LOW};

  LOG_GENERAL("DEMO MODE\n");
  //Tone
  SonTestMode();

  delay(1000);
  for(int i=0 ; i<NbJeux;i++)
  {
    //If the game is in the mode or all modes  Also so check for delta between modes (i.e.) For Mode 1, check only games not in mode 0.
    //{  
      do
      {
        WaitForAllNonActive(nbj_raw);
        delay(250);
        //Demo the game once
        PlayGame(i);
  
        Counter=0;
        do
        {
          Counter++;
          GoToNext=false;
          for(int j=0 ; j<nbj ;j++)
          {
            if(ReadPlayerInput(j)==HIGH)
            {
              if(PrevInputState[j]==LOW)
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
                
                PrevInputState[j]=HIGH;
                ToggleOutput(j);
              }
            }
            else
            {
              PrevInputState[j]=LOW;
            }
            delay(IndivDelay);
          }
          delay(DelayGame);
          NumActOut=CheckAllActiveOutputs(nbj_raw);
          if(NumActOut==nbj)
          {
            GoToNext=true;
          }
          
        }while(GoToNext==false && Counter<CounterPlaySame);
        
        delay(500);
        TurnOffAllLights();
        delay(250);
        
      }while(GoToNext==false);
    //}
  }
}

