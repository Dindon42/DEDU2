
#ifdef ENABLE_LOGGING
  #define LOG_ED(a) LOG_GAME(Game_id_Seq,a)
#else
  #define LOG_ED(a)
#endif
void SequenceGlobale(bool DemoMode)
{
  //Tunables
  #define GameLengthPlayerFactorMin 3
  #define GameLengthPlayerFactorMax 4
  #define JumpMin 1
  #define JumpMax 4
  //Tunables END.

  //Local vars
  #define GAMEDELAY 5
  #define GameLengthPlayerFactorDemo 1
  int GameLength=DemoMode ? nbj*GameLengthPlayerFactorDemo : random(nbj*GameLengthPlayerFactorMin,nbj*GameLengthPlayerFactorMax);
  int GameProgress=DemoMode ? 1 : random(JumpMin,JumpMax);
  int Looser=-1;
  //Local vars END
  
  do
  {
    ToggleOutput(0);
    delay(500);
    delay(GAMEDELAY);
  }while(1);
}

