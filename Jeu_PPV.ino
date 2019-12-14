#ifdef ENABLE_LOGGING
  #define LOG_PPV(a) LOG_GAME(Game_id_PPV,a)
#else
  #define LOG_PPV(a)
#endif
void PPV()
{
  
  //TUNABLES
  int WinNumPress=6;
  //END TUNABLES
  int Winner=-1;
  unsigned long Game_Timer=0;
  unsigned long PreviousTotalPressTime[nbj_max]={0};
  unsigned long PressTime[nbj_max]={0};
  unsigned long TotalPressTime;
  int NumPress[nbj_max]={0};
  bool RecordPress;
  int MinimumDiff=25;
  bool PreviousState[nbj_max]={false};
  bool CurrentState;

  WaitForAllNonActive(nbj_raw_max);

  //LUMIERES
  //Paires de lumières rouges qui avance
  ControlAllLights(false,0,0);
  for (int i=0; i<5; i++)
  {
    for (int j=0; j<10; j++)
    {
      if (j%5==i)
      {
        ActivateRedLight(j);
      }
    }
    delay(300);
    TurnOffAllRedLights();
  }
  delay(300);
  //Lumière réplique du jeu
  const int LightDelayDecrement=75;
  const int LightDelayMin=150;
  int LightDelay=LightDelayMin+WinNumPress*LightDelayDecrement;
  for (int i=0; i<WinNumPress; i++)
  {
    tone(Tone_Pin,400,20);
    TurnOnAllRedLights();
    delay(LightDelay);
    LightDelay-=LightDelayDecrement;
    tone(Tone_Pin,200,20);
    TurnOffAllRedLights();
    delay(150);
  }
  delay(500);
  ControlAllLights(false,0,0);
  delay(1000);
  ControlAllLights(true,0,0);
  ReadySound(500);
  //END LUMIERES
  
  //MAIN GAME
  do
  {
    for (int i=0; i<nbj; i++)
    {
      CurrentState=ReadPlayerInput(i);
      //Record the START PRESS TIMER on trans from LOW to HIGH
      if (!PreviousState[i] && CurrentState)
      {
        PressTime[i]=Game_Timer;
        LOG_PPV("i:");
        LOG_PPV(i);
        LOG_PPV(" PressTime[i]");
        LOG_PPV(PressTime[i]);
        LOG_PPV("\n");
        
        DeactivateRedLight(i);
      }
      //Record the END PRESS TIMER on trans from HIGH to LOW
      else if (PreviousState[i] && !CurrentState)
      {
        RecordPress=true;
        TotalPressTime=Game_Timer-PressTime[i];

        
        LOG_PPV("i:");
        LOG_PPV(i);
        LOG_PPV(" TotalPressTime:");
        LOG_PPV(TotalPressTime);
        LOG_PPV("\n");
        
        if (NumPress[i]!=0)
        {
          //Reset Sequence if this press time is greater than the previous
          if (TotalPressTime+MinimumDiff>=PreviousTotalPressTime[i])
          {
            
            LOG_PPV("i:");
            LOG_PPV(i);
            LOG_PPV(" ResetSeq:");
            LOG_PPV(TotalPressTime);
            LOG_PPV(" vs ");
            LOG_PPV(PreviousTotalPressTime[i]);
            LOG_PPV("\n");
            
            RecordPress=false;
            NumPress[i]=0;
            ActivateRedLight(i);
          }
        }
        
        if (RecordPress)
        {
          LOG_PPV("i:");
          LOG_PPV(i);
          LOG_PPV(" RecordPress:");
          LOG_PPV(NumPress[i]);
          LOG_PPV("\n");
          PreviousTotalPressTime[i]=TotalPressTime;
          NumPress[i]++;
        }
      }
      PreviousState[i]=CurrentState;
      
      //Update Winner
      if (NumPress[i]>=WinNumPress)
      {
        Winner=i;
        LOG_PPV("i:");
        LOG_PPV(i);
        LOG_PPV(" WINNER FOUND:");
        LOG_PPV(Winner);
        LOG_PPV("\n");
      }
    }
    
    //Increment GameTime
    delay(1);
    Game_Timer++;
    
  }while(Winner==-1);

  
  TurnOffAllLights();
  delay(500);

  //Identify winner
  WinnerSoundAndLight(Winner);
  UpdateWinner(Winner);

  //Reset
  delay(700);
  TurnOffAllLights();
  delay(25);
}
