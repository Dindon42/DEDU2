#ifdef ENABLE_LOGGING
  #define LOG_PB(a) LOG_GAME(Game_id_PB,a)
#else
  #define LOG_PB(a)
#endif
void PressBattle()
{
  //TUNABLES
  #define GAME_TIME_MIN 2542
  #define GAME_TIME_MAX 4542
  //END TUNABLES
  #define SOUND_TIME 500
  #define GAME_DELAY 5
  int Winner=-1;
  int Game_Time=(random(GAME_TIME_MIN,GAME_TIME_MAX)/GAME_DELAY);
  unsigned long Game_Timer=0;
  int ClicCount[nbj_max]={0};
  bool PreviousState[nbj_max]={false};
  int FlagPerc=100;
  bool PlayersTied;
  int PlayerState[nbj_max]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  int MaxClic;
  int NumPlayersMaxClic;
  int PotentialWinner;
  
  LOG_PB("PRESS BATTLE!\n");
  LOG_PB("Game_Time:");
  LOG_PB(Game_Time);
  LOG_PB("\n");
  
  WaitForAllNonActive(nbj_raw_max);
  
  //LIGHT SETUP
  MoveDEDUFlag(0);
  delay(200);
  int NumLights=random(10,12);
  int FlagIncrement=100/(float)NumLights;
  for (int i=0; i<NumLights; i++)
  {
    tone(Tone_Pin,400,20);
    TurnOnAllRedLights();
    delay(random(75,100));
    IncrementDEDUFlag(FlagIncrement);
    TurnOffAllRedLights();
    delay(random(50,125));
  }
  MoveDEDUFlag(FlagPerc);
  ReadySound(SOUND_TIME);
  //LIGHT SETUP END

  
  //Prepare
  for (int i=0; i<nbj; i++)
  {
    PlayerState[i]=0;
  }

  //MAIN GAME
  do
  {
    if (Game_Timer<Game_Time)
    {
      Game_Timer++;
      FlagPerc=(float)(Game_Time-Game_Timer)/(float)Game_Time*100; 
    }
    else
    {
      FlagPerc=0;
    }
    MoveDEDUFlag(FlagPerc);

    for (int i=0; i<nbj; i++)
    {
      if (!PreviousState[i] && ReadPlayerInput(i))
      {
        ClicCount[i]++;
        LOG_PB("i:");
        LOG_PB(i);
        LOG_PB("  count:");
        LOG_PB(ClicCount[i]);
        LOG_PB("\n");
      }
      PreviousState[i]=ReadPlayerInput(i);
    }

    //Check who's in front
    PlayersTied=false;
    MaxClic=0;
    NumPlayersMaxClic=0;
    PotentialWinner=-1;
    //First Check What's the max number of clics.
    for (int i=0; i<nbj; i++)
    {
      if (ClicCount[i]>MaxClic)
      {
        MaxClic=ClicCount[i];
      }
    }
    //Then identify players that have the max cliccount.
    for (int i=0; i<nbj; i++)
    {
      if (ClicCount[i]==MaxClic)
      {
        if (PotentialWinner!=-1)
        {
          PlayersTied=true;
        }
        PotentialWinner=i;
        ActivateRedLight(i);
      }
      else
      {
        DeactivateRedLight(i);
      }
    }
    
    //Check Win Condition if Game Timer is greater than Game_Time and no ties and a potential winner;
    if (Game_Timer>=Game_Time && !PlayersTied && PotentialWinner!=-1)
    {
      Winner=PotentialWinner;
    }
    
    delay(GAME_DELAY);
  }while(Winner==-1);
  
  //WINNER
  delay(500);

  TurnOffAllLights();

  //Identify winner
  WinnerSoundAndLight(Winner);
  UpdateWinner(Winner);
  
  //Reset
  delay(700);
  MoveDEDUFlag(0);
  TurnOffAllLights();
  delay(25);
}

