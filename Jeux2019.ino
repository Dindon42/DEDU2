
#ifdef ENABLE_LOGGING
  #define LOG_SG(a) LOG_GAME(Game_id_Seq,a)
#else
  #define LOG_SG(a)
#endif
void SequenceGlobale(bool DemoMode)
{
  //Tunables
  #define MaxGameCounterFailAll 1000
  #define GameLengthPlayerFactorMin 2
  #define GameLengthPlayerFactorMax 4
  #define GameLengthPlayerFactorDemo 1
  #define IntroNoteTime 150
  #define IntroSilenceTime 150
  int GameNoteTime=300;
  int GameSilenceTime=300;
  int GameTimeDecrease=5;
  if(DemoMode)
  {
    #define JumpMin 1
    #define JumpMax 1
  }
  else
  {
    #define JumpMin 1
    #define JumpMax 4
  }
  //Tunables END.

  //Game vars
  #define Gamedelay 15
  int GameCounter;
  int GameLengthBaseNum=(int)nbj/2;
  int GameLength=DemoMode ? GameLengthBaseNum+(nbj*GameLengthPlayerFactorDemo) : random(nbj*GameLengthPlayerFactorMin,nbj*GameLengthPlayerFactorMax);
  if(GameLength%nbj<GameLengthBaseNum) GameLength+=GameLengthBaseNum;
  int GameProgressInit=DemoMode ? 1 : random(JumpMin,JumpMax);
  int GameProgress=GameProgressInit;
  int ValidityThreshold=max(1,(int)GameLength / nbj);
  int ValidityMaxDelta=2;
  int Looser=-1;
  int GameSequence[GameLength];
  int Tones[nbj];
  int BaseTones[nbj_max]={261,293,329,350,392,440,494,523,587,659};
  for(int i=0; i<nbj; i++)
  {
    Tones[i]=BaseTones[i];
  }
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

  //Log Sequence
  LOG_SG("\n");
  LOG_SG("Game Sequence:\n");
  for(int i=0; i<GameLength; i++)
  {
    LOG_SG(GameSequence[i]+1);
    LOG_SG(", ");
  }
  LOG_SG("\n");
  
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

  //Main Game Loop
  bool NewRound=true;
  bool AllLoosers=false;
  bool SequenceComplete=false;
  bool PreviousState[nbj]={false};
  bool CurrentState[nbj];
  int SeqProgress;
  do
  {
    if(NewRound)
    {
      if(GameProgress>GameProgressInit)
      {
        delay(GameNoteTime);
        TurnOffAllRedLights();
        delay(500);
        ActivateGreenLED(20);
        OneUp();
        GameNoteTime-=GameTimeDecrease;
        GameSilenceTime-=GameTimeDecrease;
        delay(500);
        DeactivateGreenLED();
        TicTac(700,2);
      }
      LOG_SG("NEW ROUND!\n");
      LOG_SG("GameProgress:");
      LOG_SG(GameProgress);
      LOG_SG("\n");
      //Demo the sequence
      for(int i=0; i<GameProgress; i++)
      {
        PlayNoteWithLight(Tones[GameSequence[i]],GameNoteTime,GameSilenceTime,GameSequence[i]);
      }
      TurnOffAllLights();
      delay(500);
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
        LOG_SG(i);
        LOG_SG("\n");
        LOG_SG("GameSequence[SeqProgress]:");
        LOG_SG(GameSequence[SeqProgress]);
        LOG_SG("\n");
        
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
        if(GameProgress>GameLength) GameProgress==GameLength;
        NewRound=true;
      }
    }
    
    if(GameCounter==GameNoteTime/Gamedelay)
    {
      TurnOffAllRedLights();
    }
    
    if(GameCounter>MaxGameCounterFailAll)
    {
      AllLoosers=true;
      Looser=-1;
      SequenceComplete=false;
    }
    delay(Gamedelay);
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
  }
  
  if(Looser!=-1)
  {
    LOG_SG("---------------------\n");
    LOG_SG("GAME END:    1 LOOSER\n");
    LOG_SG("---------------------\n");
  }
  
  if(SequenceComplete)
  {
    LOG_SG("---------------------\n");
    LOG_SG("GAME END:SEQ COMPLETE\n");
    LOG_SG("---------------------\n");
  }
}

