#ifdef ENABLE_LOGGING
  #define LOG_RANDOM(a) LOG_GAME(Game_id_AR,a)
#else
  #define LOG_RANDOM(a)
#endif
void AllRandom()
{
  int Wincondition;
  int NewAssignment[nbj_max]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  bool NumAlreadyAllocated=false;
  int PosAssigned=0;
  bool PreviousState[nbj_max]={false};
  bool LightState[nbj_max]={false};
  int OutputSum;
  int Looser=-1;
  int DEDUmaster=-1;
  int DEDUmasterProb=2;
  int DEDUmasterChangeProb=4;
  int DEDUmasterPressCounter=0;
  int DEDUmasterNextChange=random(1,DEDUmasterChangeProb);
  bool Toggle;
  long RandomProb=30000;
  long RandomProbThr=29900;
  #define AR_GraceTime 4242
  #define AR_GAMEDELAY 5
  int GameTimer=0;
  bool GraceTimeOver=false;

  LOG_RANDOM("ALLRANDOM\n");
  
  //InitialSetup CYAN
  TurnOffAllLights();
  
  ActivateBlueLED(10);
  ActivateGreenLED(22);

  if (random(DEDUmasterProb)==0)
  {
    DEDUmaster=random(nbj);
    LOG_RANDOM("DEDUmasterNextChange:");
    LOG_RANDOM(DEDUmasterNextChange);
    LOG_RANDOM("\n");
    RandomProbThr=29950;
  }
  LOG_RANDOM("DEDUMASTER:");
  LOG_RANDOM(DEDUmaster);
  LOG_RANDOM("\n");
  LOG_RANDOM("RandomProbThr:");
  LOG_RANDOM(RandomProbThr);
  LOG_RANDOM("\n");
  
  //Initial Lights setup: 50/50 Lit vs Not Lit
  AllocateTwoTeams(nbj);

  LOG_RANDOM("New Assignments\n");
  //Fill Random Array
  for(int i=0 ; i<nbj; i++)
  {
    do
    {
     NumAlreadyAllocated=false;
     
     int r=random(nbj_max);
     
     for (int j=0; j<i; j++)
     {
      if (NewAssignment[j]==r)
      {
        NumAlreadyAllocated=true;
        break;
      }
     }
     if (!NumAlreadyAllocated)
     {
      NewAssignment[i]=r;
     }
    }while(NewAssignment[i]==-1);

    //Initial light state
    if (Equipes[i]==0)
    {
      ActivateRedLight(NewAssignment[i]);
      LightState[i]=true;
    }
    LOG_RANDOM("ID: ");
    LOG_RANDOM(i);
    LOG_RANDOM(" Light: ");
    LOG_RANDOM(NewAssignment[i]);
    LOG_RANDOM(" InitState: ");
    LOG_RANDOM(LightState[i]);
    LOG_RANDOM("\n");
  }
  
  delay(800);
  if (random(2)==0)
  {
    Wincondition=1;
    MoveDEDUFlag(0);
  }
  else
  {
    Wincondition=nbj-1;
    MoveDEDUFlag(100);
  }
  delay(800);
  ReadySound(500);

  //Main game.
  do
  {
    //Change win condition randomly regardless of DEDUMASTER
    if (random(RandomProb)>RandomProbThr)
    {
      LOG_RANDOM("Changing WinCond:");
      if (random(2)==0)
      {
        LOG_RANDOM("LOW");
        Wincondition=1;
        MoveDEDUFlag(0);
      }
      else
      {
        LOG_RANDOM("HIGH");
        Wincondition=nbj-1;
        MoveDEDUFlag(100);
      }
      LOG_RANDOM("\n");
    }
    
    OutputSum=0;
    for (int i=0; i<=nbj_raw; i++)
    {
      Toggle=false;
      //IF PLAYER IS HIGH AND PREV IS LOW, Toggle his light
      if (ReadPlayerInput(i) && !PreviousState[i])
      {
        Toggle=true;
        LightState[i]=ToggleOutput(NewAssignment[i]);
      }
      PreviousState[i]=ReadPlayerInput(i);
      OutputSum+=LightState[i];

      if (i==DEDUmaster && Toggle)
      {
        LOG_RANDOM("DEDUmasterPressCounter:");
        LOG_RANDOM(DEDUmasterPressCounter);
        LOG_RANDOM("\n");
        if (DEDUmasterPressCounter==DEDUmasterNextChange)
        {
          LOG_RANDOM("Change FLAG:");
          LOG_RANDOM("\n");
          if (Wincondition==1)
          {
            Wincondition=nbj-1;
            MoveDEDUFlag(100);
          }
          else
          {
            Wincondition=1;
            MoveDEDUFlag(0);
          }
          DEDUmasterNextChange=random(0,DEDUmasterChangeProb);
          DEDUmasterPressCounter=0;
          LOG_RANDOM("DEDUmasterPressCounter:");
          LOG_RANDOM(DEDUmasterPressCounter);
          LOG_RANDOM("\n");
          LOG_RANDOM("DEDUmasterNextChange:");
          LOG_RANDOM(DEDUmasterNextChange);
          LOG_RANDOM("\n");
        }
        else
        {
          DEDUmasterPressCounter++;
        }
      }
    }

    //Win Condition
    if (OutputSum == Wincondition && GraceTimeOver)
    {
      if (Wincondition==1)
      {
        for (int i=0; i<=nbj_raw; i++)
        {
          if (LightState[i])
          {
            Looser=i;
            break;
          }
        }
      }
      else
      {
        for (int i=0; i<=nbj_raw; i++)
        {
          if (!LightState[i])
          {
            Looser=i;
            break;
          }
        }
      }
    }
    
    delay(AR_GAMEDELAY);
    if (!GraceTimeOver)
    {
      GameTimer+=AR_GAMEDELAY;
      if (GameTimer>AR_GraceTime)
      {
        GraceTimeOver=true;
        LOG_RANDOM("GraceTimeOver\n");
      }
    }
  }while(Looser==-1);


  
  for (int i=1; i<=80; i++)
  {
    Tone_Frequency=2000 - 20 * i;
    tone(Tone_Pin, Tone_Frequency);
    delay(10);
  }
  noTone(Tone_Pin);
  delay(700);

  TurnOffAllRedLights();
  ActivateGreenLED(5);
  ActivateBlueLED(5);

  delay(700);
  
  //Identify the Looser
  for (int e=1; e<=4; e++) {
    ActivateRedLight(Looser);
    delay(500);
    DeactivateRedLight(Looser);
    delay(500);
  }
  MoveDEDUFlag(0);
  TurnOffAllLights();
}




