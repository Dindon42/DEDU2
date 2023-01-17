#ifdef ENABLE_LOGGING
  #define LOG_PQP(a) LOG_GAME(Game_id_PQP,a)
#else
  #define LOG_PQP(a)
#endif
void PQP()
{
  int Winner=-1;
  int r=random(5);
  int r2=random(2,100);
  
  LOG_PQP("r:");
  LOG_PQP(r);
  LOG_PQP("\n");
  LOG_PQP("r2:");
  LOG_PQP(r2);
  LOG_PQP("\n");

  //Init lights as GREEN.
  //Random Low intensity green from time to time.
  if (r == 4) 
  {
    ActivateGreenLED(1);
  }
  else 
  {
    ActivateGreenLED(r2);
  }
  
  do 
  {
    Winner=FirstActive(nbj_raw);
  }while (Winner == -1);

  WinnerSoundAndLight(Winner);
  UpdateWinner(Winner);
  delay(200);
}