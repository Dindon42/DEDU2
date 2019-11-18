#ifdef ENABLE_LOGGING
  #define LOG_AR2(a) LOG_GAME(Game_id_AR2,a)
#else
  #define LOG_AR2(a)
#endif
void AR2()
{
  if(nbj<=5) return;
  //MAX NUMASSIGNMENTS NE PEUT PAS ÊTRE PLUS GRAND QUE LA GRANDEUR DE ARRAY EQUIPES-nbj.
  #define AR2_NumAssignments 18
  //LUMIERES
  if(!SkipLights)
  {
    MaxRandom(10,true);
  }
  //END LUMIERES

  //Inputs Mappings
  //0 to 9 -> LED 1 à 10
  //10, 11, 12, 13 -> BUZZER 1, 2, 3, 4
  //14, 15 -> LED G 1, 2
  //16, 17 -> LED B 1, 2
  //DEDU (Condition de victoire) + DEDUMASTER
  bool OutputArray[AR2_NumAssignments]={false};
  bool InputArray[AR2_NumAssignments]={false};
  int InputMapping[AR2_NumAssignments];
  bool PreviousState[nbj]={false};
  int WinCondition=-1;
  //Setting all input mappings to -1
  for(int i=0; i<AR2_NumAssignments; i++)
  {
    InputMapping[i]=-1;
  }
  LOG_AR2("=--=--=\n");
  LOG_AR2("=-AR2-=\n");
  LOG_AR2("=--=--=\n");
  int LightMapping[4] = {0,6,15,24};
  int ToneMapping[8]={261,293,329,350,392,440,494,523};
  
  //Assignations des états initiaux
  //Diviser les joueurs actifs en 2
  //Assigner les états initiaux
  //Diviser les joueurs non-actifs en 2
  //Assigner les états initiaux
  AllocateTwoTeams(nbj);
  for(int i=0; i<nbj; i++)
  {
    OutputArray[i]=Equipes[i]==1;
  }

  AllocateTwoTeams(AR2_NumAssignments-nbj);
  for(int i=nbj; i<AR2_NumAssignments; i++)
  {
    OutputArray[i]=Equipes[i-nbj]==1;
  }
  //Print des états initiaux
  LOG_AR2("Initial states\n");
  for(int i=0; i<AR2_NumAssignments ; i++)
  {
    LOG_AR2("i: ");
    LOG_AR2(i);
    LOG_AR2("  State: ")
    LOG_AR2(OutputArray[i]);
    LOG_AR2("\n");
  }
  
  //Assign Random Mapping to each player
  int PosAssigned=0;
  LOG_AR2("Assigning Player Mappings\n")
  for(int i=0; i<AR2_NumAssignments; i++)
  {
    LOG_AR2("Assigning Player: ")
    LOG_AR2(i);
    LOG_AR2("\n");
    do
    {
      bool NumAlreadyAllocated=false;
      int r=random(AR2_NumAssignments);
      LOG_AR2("Wanting to assign mapping: ")
      LOG_AR2(r);
      LOG_AR2("\n");
      for(int j=0; j<i; j++)
      {
        if(InputMapping[j]==r)
        {
          LOG_AR2("Mapping already assigned to player: ")
          LOG_AR2(j);
          LOG_AR2("\n");
          NumAlreadyAllocated=true;
          break;
        }
      }
  
      if(NumAlreadyAllocated==false)
      {
        LOG_AR2("Mapping not already assigned.\nAssigning it to player: ")
        LOG_AR2(i);
        LOG_AR2("\n");
        InputMapping[i]=r;
      }
    }while(InputMapping[i]==-1);
  }

  
  //Print des Mappings
  LOG_AR2("Input Mapping\n");
  for(int i=0; i<AR2_NumAssignments ; i++)
  {
    LOG_AR2("i: ");
    LOG_AR2(i);
    LOG_AR2("  NewMapping: ")
    LOG_AR2(InputMapping[i]);
    LOG_AR2("\n");
  }

  
  
  do
  {
    /*
    //Activate lights
    for(int i=0; i<4 ; i++)
    {
      ActivateBlueLED(LightMapping[i]);
      delay(1000);
    }
    for(int i=0; i<4 ; i++)
    {
      ActivateGreenLED(LightMapping[i]);
      delay(1000);
    }
    for(int i=3; i>=0 ; i--)
    {
      ActivateBlueLED(LightMapping[i]);
      delay(1000);
    }
    for(int i=3; i>=0 ; i--)
    {
      ActivateGreenLED(LightMapping[i]);
      delay(1000);
    }
    */

    /*
    //Activate tone.
    for(int i=0; i<8; i++)
    {
      PlayNote(ToneMapping[i],500,0);
    }
    for(int i=7; i>=0; i--)
    {
      PlayNote(ToneMapping[i],500,0);
    }
    */
  }while(abs(SumPlayerOutput(OutputArray, nbj)-WinCondition)!=1);

  //Identify the Looser based on wincondition
  //Do something to it.
  
}

int SumPlayerOutput(bool OutputArray[], int ArrSize)
{
  int Sum=0;
  for(int i=0; i<ArrSize; i++)
  {
    if(OutputArray[i]) Sum++;
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
  #define GameEndCounterPlayerFactorMin 50
  #define GameEndCounterPlayerFactorMax 90
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
  for(int i=0; i<nbj; i++)
  {
    GameSequence[i]=-1;
  }
  bool PreviousState[nbj]={false};
  bool CurrentState[nbj];
  int SeqProgress=0;
  int WaitTime[nbj];
  for(int j=0; j<nbj; j++)
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
  for(int i=0; i<nbj; i++)
  {
    LOG_TB(GameSequence[i]+1);
    LOG_TB(", ");
  }
  LOG_TB("\n");

  //Signature lumineuse
  MoveDEDUFlag(100);
  for (int j=0; j<LightSignatureNum; j++)
  {
    for(int i=0; i<nbj_max; i++)
    {
      int lf = 100-10*i;
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
    for(int i=0; i<nbj; i++)
    {
      //Record current state
      CurrentState[i]=ReadPlayerInput(i)==HIGH? true:false;

      //Check if player has started pressing
      if(!PreviousState[i] && CurrentState[i])
      {
        //Log presser
        LOG_TB("Press:");
        LOG_TB(i+1);
        LOG_TB("\n");
        LOG_TB("Current:");
        LOG_TB(GameSequence[SeqProgress]+1);
        LOG_TB("\n");
        LOG_TB("Next:");
        if(SeqProgress==nbj-1)
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
        for(int j=0; j<nbj; j++)
        {
          NotInSequence=GameSequence[j]!=i;
          if(!NotInSequence) break;
        }
        
        //If the game sequence is not defined for the current progress, define it and reset the sequence.
        if(GameSequence[SeqProgress]==-1 && NotInSequence)
        {
          LOG_TB("NEW Player in seq:");
          LOG_TB(i+1);
          LOG_TB("\n");

          if(EnableLights)
          {
            ActivateRedLight(i);
            delay(100);
            //OneUp();
          }
          
          GameSequence[SeqProgress]=i;

          //Reset the sequence
          for(int j=0; j<nbj; j++)
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
          for(int j=0; j<nbj; j++)
          {
            LOG_TB(GameSequence[j]+1);
            LOG_TB(", ");
          }
          LOG_TB("\n");

          
          LOG_TB("Next:");
          if(SeqProgress==nbj-1)
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
        else if(GameSequence[SeqProgress]==i)
        {
          if(EnableLights)
          {
            ActivateRedLight(i);
          }
          WaitTime[i]=GameCounter-GameCounterPrevAction;
          GameCounterPrevAction=GameCounter;
          SeqProgress++;
        }
        else if(!NotInSequence)
        {
          LOG_TB("SUPER LOOSER:");
          LOG_TB(i+1);
          LOG_TB("\n");
          LOG_TB("Current was:");
          LOG_TB(GameSequence[SeqProgress]+1);
          
          //Log Sequence
          LOG_TB("\n");
          LOG_TB("Game Sequence:\n");
          for(int j=0; j<nbj; j++)
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

  //Time Up: Longest wait = looser;
  if(TimeIsUp)
  {
    //Too slow, punish the slowest.
    LOG_TB("GAME END: TOO SLOW!\n");
    LOG_TB("GameCounter:");
    LOG_TB(GameCounter);
    LOG_TB("\n");
    
    //Was it someone's turn?
    if(GameSequence[SeqProgress]==-1)  //No one's turn
    {
      bool TheyAllLoose=SeqProgress==0;
      
      //Check if the sequence players left enough time
      int TimeRemainingAtGameEnd=GameCounter-GameCounterPrevAction;

      if(TheyAllLoose)
      {
        LOG_TB("ALL LOOSERS!\n");
        AllLoosersSoundAndLight();
        TurnOffAllLights();
      }
      else
      {
        int MaxWait=-1;
        for(int i=0; i<nbj; i++)
        {
          if(WaitTime[i]>MaxWait)
          {
            MaxWait=WaitTime[i];
            Looser=i;
          }
        }
        
        if(MaxWait>TimeRemainingAtGameEnd)
        {
          //They did not have enough time, you bastard.
          LOG_TB("This Fella did not leave enough time for the rest!\n");
          LooserSoundAndLight(Looser,false);
          SingleLooserSoundAndLight(Looser);
          TurnOffAllLights();
        }
        else
        {
          bool Loosers[nbj_max]={false};

          for(int i=0; i<nbj; i++)
          {
            bool NotInSequence;
            for(int j=0; j<nbj; j++)
            {
              NotInSequence=GameSequence[j]!=i;
              if(!NotInSequence) break;
            }
            Loosers[i]=NotInSequence;
          }
          
          //They had enough time
          MultiLooserSoundAndLight(Loosers);
        }
      }
    }
    else //Someone's turn
    {
      LOG_TB("WHOS A SLOWPOKE?\n");
      //First record the last players' wait time
      WaitTime[GameSequence[SeqProgress]]=GameCounter-GameCounterPrevAction;

      int MaxWait=-1;
      for(int i=0; i<nbj; i++)
      {
        if(WaitTime[i]>MaxWait)
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
  else if(Looser!=-1)
  {
    LOG_TB("WHO BREAKS OUR BALLS?\n");
    //Single Looser, Breaker of sequence
    LooserSoundAndLight(Looser,false);
    SingleLooserSoundAndLight(Looser);
    TurnOffAllLights();
  }
  else if(SuperLooser!=-1)
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
  #define LOG_SG(a) LOG_GAME(Game_id_Seq,a)
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
  if(DemoMode)
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
  if(GameLength%nbj==0) GameLength++;
  int GameProgressInit=random(JumpMin,JumpMax+1);
  int GameProgress=GameProgressInit;
  int ValidityThreshold=max(1,(int)GameLength / nbj);
  int ValidityMaxDelta=2;
  int Looser=-1;
  bool AllLoosers=false;
  bool SequenceComplete=false;
  int GameSequence[GameLength];
  int BaseTones[nbj_max]={261,293,329,350,392,440,494,523,587,659};
  int Tones[nbj];
  for(int i=0; i<nbj; i++)
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
    for(int i=0; i<GameLength; i++)
    {
      GameSequence[i]=random(nbj);
    }
    InvalidSequence=false;
    //Check Sequence
    for(int j=0; j<nbj; j++)
    {
      int Count=0;
      for(int i=0; i<GameLength; i++)
      {
        if(GameSequence[i]==j) Count++;
      }

      if(Count<Min) Min=Count;
      if(Count>Max) Max=Count;
      
      if(Count<ValidityThreshold)
      {
        InvalidSequence=true;
        NumInvalidSeq++;
        break;
      }
    }

    if(Max-Min>ValidityMaxDelta && !InvalidSequence)
    {
      InvalidSequence=true;
      NumInvalidSeq++;
    }

    bool LogMaxInval=false;
    if(NumInvalidSeq%MaxInvalSeqMD==MaxInvalSeqMD-1)
    {
      LogMaxInval=true;
      ValidityMaxDelta++;
    }
    if(NumInvalidSeq%MaxInvalSeqVT==MaxInvalSeqVT-1)
    {
      LogMaxInval=true;
      ValidityThreshold=max(1,ValidityThreshold-1);
    }
    if(LogMaxInval)
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
    
    if(!InvalidSequence)
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
  for(int j=0; j<nbj; j++)
  {
    int Count=0;
    for(int i=0; i<GameLength; i++)
    {
      if(GameSequence[i]==j) Count++;
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
for(int i=0; i<GameLength; i++)
{
  LOG_SG(GameSequence[i]+1);
  LOG_SG(", ");
}
LOG_SG("\n");
SequenceGlobale(false);
*/
  if(!SkipLights)
    {
    //Light Signature
    //Run the sequence quickly, play notes and move DEDU accordingly.
    int PrevG=0;
    int PrevB=0;
    for(int i=0; i<GameLength; i++)
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
    if(NewRound)
    {
      LOG_SG("==========\n");
      LOG_SG("NEW ROUND!\n");
      LOG_SG("==========\n");
      //Log Sequence
      LOG_SG("\n");
      LOG_SG("Game Sequence:\n");
      for(int i=0; i<GameLength; i++)
      {
        LOG_SG(GameSequence[i]+1);
        LOG_SG(", ");
      }
      LOG_SG("\n");
      
      if(GameProgress>GameProgressInit)
      {
        delay(GameNoteTime);
        TurnOffAllRedLights();
        delay(500);
        ActivateGreenLED(20);
        OneUp();
        GameNoteTime-=random(GameTimeDecreaseMin,GameTimeDecreaseMax);
        GameSilenceTime-=random(GameTimeDecreaseMin,GameTimeDecreaseMax);
        if(GameNoteTime<GameNoteTimeMin) GameNoteTime=GameNoteTimeMin;
        if(GameSilenceTime<GameSilenceTimeMin) GameSilenceTime=GameSilenceTimeMin;
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
      for(int i=0; i<GameProgress; i++)
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
    for(int i=0; i<nbj; i++)
    {
      //Record current state
      CurrentState[i]=ReadPlayerInput(i)==HIGH? true:false;

      //Check if player has started pressing
      if(!PreviousState[i] && CurrentState[i])
      {

        //Log presser
        LOG_SG("Press:");
        LOG_SG(i+1);
        LOG_SG("\n");
        LOG_SG("Current:");
        LOG_SG(GameSequence[SeqProgress]+1);
        LOG_SG("\n");
        LOG_SG("Next:");
        if(SeqProgress==GameLength-1)
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
        if(i==GameSequence[SeqProgress])
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
    if(SeqProgress==GameProgress)
    {
      //Check for Seq complete
      if(GameProgress==GameLength)
      {
        SequenceComplete=true;
      }
      else
      {
        GameProgress+=random(JumpMin,JumpMax+1);
        if(GameProgress>GameLength) GameProgress=GameLength;
        NewRound=true;
      }
    }
    
    if(GameCounter==GameNoteTime/GamedelaySeq)
    {
      TurnOffAllRedLights();
    }
    
    if(GameCounter>MaxGameCounterFailAll)
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
  
  if(AllLoosers)
  {
    LOG_SG("---------------------\n");
    LOG_SG("GAME END: ALL LOOSERS\n");
    LOG_SG("---------------------\n");
    AllLoosersSoundAndLight();
    TurnOffAllLights();
  }
  
  if(Looser!=-1)
  {
    LOG_SG("---------------------\n");
    LOG_SG("GAME END:    1 LOOSER\n");
    LOG_SG("---------------------\n");
    LooserSoundAndLight(Looser,false);
    SingleLooserSoundAndLight(Looser);
    TurnOffAllLights();
  }
  
  if(SequenceComplete)
  {
    LOG_SG("---------------------\n");
    LOG_SG("GAME END:SEQ COMPLETE\n");
    LOG_SG("---------------------\n");
    ActivateGreenLED(20);
    delay(500);
    for(int i=0; i<ValidityThreshold; i++)
    {
      OneUp();
      delay(500);
    }
    TurnOffAllLights();
    ResetProbFFA();
    FFA();
  }
}

