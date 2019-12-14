
#ifdef ENABLE_LOGGING
  #define LOG_PQR(a) LOG_GAME(Game_id_PQR,a)
#else
  #define LOG_PQR(a)
#endif
void PQR()
{
  unsigned long GameCounter=0;
  unsigned long GreenCounter=0;
  bool InitialGreenComplete=false;
  int GreenTransMax=500;
  int ReacTime;
  int ReacTimeMin=542;
  int ReacTimeMax=1542;
  int Winner=-1;
  int PercB;
  int PercG;
  int MinB=1;
  int MinG=5;
  int LightIntB=3;
  int LightIntG=42;
  int NumActive;
  int PrevNumActive=-1;
  int WinCondition=-1;
  bool PreviousState[nbj_max];
  int PlayersInGame[nbj_max]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  int StateChanges[nbj_max]={0};
  int ChangeThr=3;
  int PlayersActive;
  bool TriggerEndGame=false;

  LOG_PQR("PREMIER QUI RELACHE\n");
  
  //Init Based on number of players
  for (int i=0; i<=nbj_raw ;i++)
  {
    PlayersInGame[i]=1;
  }

  LOG_PQR("PlayersInGame!\n");
  for (int i=0; i<=nbj_raw_max ;i++)
  {
    LOG_PQR("i:");
    LOG_PQR(i);
    LOG_PQR("  ");
    LOG_PQR(PlayersInGame[i]);
    LOG_PQR("\n");
  }

  ActivateGreenLED(MinG);
  ActivateBlueLED(MinB);
  
  do
  {
    if (!InitialGreenComplete)
    {
      PercG=((float)GreenCounter/(float)GreenTransMax)*LightIntG;
      PercB=((float)GreenCounter/(float)GreenTransMax)*LightIntB;
      if (PercG<MinG) PercG=MinG;
      if (PercB<MinB) PercB=MinB;
      ActivateGreenLED(PercG);
      ActivateBlueLED(PercB);
    }
    if (GreenCounter>GreenTransMax && !InitialGreenComplete)
    {
      LOG_PQR("GreenTransComplete\n");
      LOG_PQR("GameCounter:");
      LOG_PQR(GameCounter);
      LOG_PQR("\n");
      InitialGreenComplete=true;
      GameCounter=0;
      LOG_PQR("GameCounter:");
      LOG_PQR(GameCounter);
      LOG_PQR("\n");
    }

    //Record States to compare win condition.
    for (int i=0;i<nbj;i++)
    {
      PreviousState[i]=InputState[i];
    }

    
    ActivateGreenLED(PercG);
    ActivateBlueLED(PercB);
    
    NumActive=0;
    for (int i=0; i<=nbj_raw ;i++)
    {
      if (PlayersInGame[i]==1)
      {
        if (ReadPlayerInput(i))
        {
          NumActive++;
          ActivateRedLight(i);
          InputState[i]=true;
          OutputState[i]=true;
        }
        else
        {
          DeactivateRedLight(i);
          InputState[i]=false;
          OutputState[i]=false;
        }
      }
      
      if (PreviousState[i]!=InputState[i])
      {
        StateChanges[i]++;
      }
      
      if (StateChanges[i]>ChangeThr && !TriggerEndGame)
      {
        LOG_PQR("You're OUT\n");
        PlayersInGame[i]=0;
        DeactivateRedLight(i);
        StateChanges[i]=0;
      }
    }

    //Check if everyone is a spammer.
    if (!TriggerEndGame)
    {
      PlayersActive=0;
      for (int i=0; i<=nbj_raw ;i++)
      {
        if (PlayersInGame[i]==1)
        {
          PlayersActive++;
        }
      }
      
      //Reset Counts if everyone is a dumbass.
      if (PlayersActive==0)
      {
        LOG_PQR("RESET EVERYONE\n");
        for (int i=0; i<=nbj_raw ;i++)
        {
          PlayersInGame[i]=1;
          StateChanges[i]=0;
        }
      }
    }
    
    if (NumActive==WinCondition && TriggerEndGame)
    {
      for (int i=0;i<nbj;i++)
      {
        if (PreviousState[i] && !InputState[i] && PlayersInGame[i]==1)
        {
          Winner=i;
          break;
        }
      }
    }
    else if (!TriggerEndGame)
    {
      if (NumActive==0)
      {
        //LOG_PQR("ResetGameCounter\n");
        GameCounter=0;
      }
      if (NumActive>=1 && NumActive!=PrevNumActive)
      {
        LOG_PQR("WinCondition Change\n");
        WinCondition=NumActive-1;
        LOG_PQR("WinCondition:");
        LOG_PQR(WinCondition);
        LOG_PQR("\n");
        PrevNumActive=NumActive;
        GameCounter=0;
        
        ReacTime=random(ReacTimeMin,ReacTimeMax);
        LOG_PQR("ReacTime:");
        LOG_PQR(ReacTime);
        LOG_PQR("\n");
      }
      
      if (GameCounter>ReacTime && NumActive>=1)
      {
        //Cancel Non-Pressing players
        for (int i=0; i<=nbj_raw ;i++)
        {
          if (!InputState[i])
          {
            PlayersInGame[i]=0;
          }
        }
        
        LOG_PQR("TRIGGER END!\n");
        LOG_PQR("PlayersInGame!\n");
        for (int i=0; i<=nbj_raw_max ;i++)
        {
          LOG_PQR("i:");
          LOG_PQR(i);
          LOG_PQR("  ");
          LOG_PQR(PlayersInGame[i]);
          LOG_PQR("\n");
        }
        
        TriggerEndGame=true;
        PercG=0;
        PercB=0;
      }
    }
    GameCounter++;
    if (!InitialGreenComplete)
    {
      GreenCounter++;
    }
    if (GameCounter>90000)
    {
      LOG_PQR("ResetGameCounter\n");
      GameCounter=0;
    }
  delay(1);
  }while(Winner==-1);

  delay(500);

  TurnOffAllLights();

  //Identify winner
  WinnerSoundAndLight(Winner);
  UpdateWinner(Winner);
  delay(700);
  TurnOffAllLights();
  delay(25);
}

