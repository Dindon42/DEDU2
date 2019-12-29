
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
  #define GameLengthPlayerFactorMax 2
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
  int GameLength=DemoMode ? (nbj*GameLengthPlayerFactorDemo)+2 : random((nbj*GameLengthPlayerFactorMin)+2,(nbj*GameLengthPlayerFactorMax)-2);
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

