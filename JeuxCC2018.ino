#ifdef ENABLE_LOGGING
  #define LOG_JD(a) LOG_GAME(Game_id_JD,a)
#else
  #define LOG_JD(a)
#endif
void JeanDit()
{
  WaitForAllNonActive(nbj_raw_max);
  
  int Winner=-1;
  int Jean=random(nbj);
  bool Immunity = true;
  bool PreviousState[nbj];
  bool CurrentState[nbj];
  //À chaque fois que Jean change le DEDU d'état, laisser un temps de réaction.
  //Éliminer le dernier à changer d'état.
  //Donner un temps minimum à Jean pour faire son action.  Graduellement réduire les lumières Vert/Bleu pendant ce temps d'attente.
  
  do
  {
    for (int i=0;i<nbj;i++)
    {
      if(ReadPlayerInput(i)==HIGH) CurrentState[i]=true;
      else CurrentState[i]=false;
    }
    
    //Save current into previous.
    for (int i=0;i<nbj;i++)
    {
      PreviousState[i]=CurrentState[i];
    }
  }while(Winner==-1);

  
  TurnOffAllLights();
  delay(500);

  //Identify winner
  WinnerSoundAndLight(Winner);

  //Reset
  delay(700);
  TurnOffAllLights();
  delay(25);
}

