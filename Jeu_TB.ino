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
  #define TB_Gamedelay 5
  #define TB_LightDelay 150
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
      delay(TB_LightDelay);
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
    delay(TB_Gamedelay);
    
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

