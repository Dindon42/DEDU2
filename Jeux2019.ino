
#ifdef ENABLE_LOGGING
  #define LOG_SG(a) LOG_GAME(Game_id_Seq,a)
#else
  #define LOG_SG(a)
#endif
void SequenceGlobale(bool DemoMode)
{
  //Tunables
  #define GameLengthPlayerFactorMin 2
  #define GameLengthPlayerFactorMax 3
  #define GameLengthPlayerFactorDemo 1
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
  #define Gamedelay 5
  int GameLength=DemoMode ? 2+(nbj*GameLengthPlayerFactorDemo) : random(nbj*GameLengthPlayerFactorMin,nbj*GameLengthPlayerFactorMax);
  int GameProgress=DemoMode ? 1 : random(JumpMin,JumpMax);
  int ValidityThreshold=max(1,(int)GameLength / nbj);
  int Looser=-1;
  int GameSequence[GameLength];
  int NumInvalidSeq=0;
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
    
  //Initialize
  bool InvalidSequence;
  do
  {
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
      if(Count<ValidityThreshold)
      {
        InvalidSequence=true;
        NumInvalidSeq++;
        break;
      }
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
  
  LOG_SG("NumInvalidSeq:");
  LOG_SG(NumInvalidSeq);
  LOG_SG("\n");
  
  //Light Signature
  
  
  do
  {
    ToggleOutput(0);
    delay(500);
    delay(Gamedelay);
  }while(1);
}

