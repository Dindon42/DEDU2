
#ifdef ENABLE_LOGGING
  #define LOG_TOURVIC(a) LOG_GAME(Game_id_TV,a)
#else
  #define LOG_TOURVIC(a)
#endif
void TourVic()
{
  int LightDelay=5+random(nbj);
  int LightDelayIncrement=1;
  int LightDelayIncrementProb=4;
  int LightDelayIncrementIncrementProb=12;
  int CurrentCounter=0;
  int LastPlayer=random(nbj);
  int CurrentPlayer=0;
  int DirectionNextPlayer=0;
  int Winner=-1;
  bool ReadyToPress=false;
  bool PlayerIsPressing=false;
  bool ReadytoIncreaseIncrement=false;
  bool IgnorePresses=false;
  bool PlayerHasWon=false;
  int SpamCheckDelay=125;

  if (random(2)==0)
  {
    DirectionNextPlayer=1;
  }
  else
  {
    DirectionNextPlayer=-1;
  }
  CurrentPlayer=WrapAround(LastPlayer+DirectionNextPlayer);
  
  LOG_TOURVIC("CurrentPlayer:");
  LOG_TOURVIC(CurrentPlayer);
  LOG_TOURVIC("\n");
  LOG_TOURVIC("LastPlayer:");
  LOG_TOURVIC(LastPlayer);
  LOG_TOURVIC("\n");
  LOG_TOURVIC("DirectionNextPlayer:");
  LOG_TOURVIC(DirectionNextPlayer);
  LOG_TOURVIC("\n");
  
  //Tout vert pour commencer+Une Lumière
  ActivateRedLight(CurrentPlayer);
  ActivateGreenLED(20);
  
  //Spin the wheel!
  do
  {
    //For the active player, monitor the transitions.  
    //1: ToLow
    //2: ToHigh
    //3: ToLow
    //If this happens during the time the player is active, Good, you are the winner.
    
    /*
    LOG_TOURVIC("CurrentPlayer:");
    LOG_TOURVIC(CurrentPlayer);
    LOG_TOURVIC("\n");
    LOG_TOURVIC("ReadyToPress:");
    LOG_TOURVIC(ReadyToPress);
    LOG_TOURVIC("\n");
    LOG_TOURVIC("PlayerIsPressing:");
    LOG_TOURVIC(PlayerIsPressing);
    LOG_TOURVIC("\n");
    */
    //Monitor initial transition to LOW
    if (!ReadPlayerInput(CurrentPlayer) && !ReadyToPress && !IgnorePresses)
    {
      LOG_TOURVIC("Changing RTP!");
      LOG_TOURVIC("\n");
      ReadyToPress=true;
    }
    
    //Monitor subsequent transition to HIGH
    if (ReadPlayerInput(CurrentPlayer) && ReadyToPress && !PlayerIsPressing && !IgnorePresses)
    {
      LOG_TOURVIC("Changing PIP!")
      LOG_TOURVIC("\n");
      PlayerIsPressing=true;
    }
    
    //Monitor subsequent transition to LOW
    if (!ReadPlayerInput(CurrentPlayer) && PlayerIsPressing && !IgnorePresses)
    {
      LOG_TOURVIC("Player SAFE!")
      LOG_TOURVIC("\n");
      //YOU ARE SAFE.
      IgnorePresses=true;
      PlayerHasWon=true;
      CurrentCounter-=SpamCheckDelay;
    }
    
    delay(1);

    //Check if current player has won and is pressing again.  If so, make him loose.
    if (PlayerHasWon && ReadPlayerInput(CurrentPlayer))
    {
      LOG_TOURVIC("Player LOOSES!")
      LOG_TOURVIC("\n");
      PlayerHasWon=false;
    }
    
    //Enougn time on this guy...  Switch
    if (CurrentCounter>LightDelay)
    {
      if (PlayerHasWon)
      {
        Winner=CurrentPlayer;
      }
      else
      {
        CurrentCounter=0;
        ReadyToPress=false;
        PlayerIsPressing=false;
        IgnorePresses=false;
        PlayerHasWon=false;
        
        
        //If we reach the last guy, increment lightdelay
        if (CurrentPlayer==LastPlayer)
        {
          if(random(LightDelayIncrementProb)==0)
          {
            LightDelay+=LightDelayIncrement;
            LOG_TOURVIC("Increasing LightDelay:")
            LOG_TOURVIC(LightDelay);
            LOG_TOURVIC("\n");
          }
          
          if (ReadytoIncreaseIncrement)
          {
            if (random(LightDelayIncrementIncrementProb)==0)
            {
              LightDelayIncrement++;
              LOG_TOURVIC("Increasing Increment:")
              LOG_TOURVIC(LightDelayIncrement);
              LOG_TOURVIC("\n");
            }
            ReadytoIncreaseIncrement=false;
          }
          else
          {
            ReadytoIncreaseIncrement=true;
          }
        }
        
        delay(1);
        
        DeactivateRedLight(CurrentPlayer);
        tone(Tone_Pin, 3500, 3);
        
        //Find the next player
        CurrentPlayer=WrapAround(CurrentPlayer+DirectionNextPlayer);
        ActivateRedLight(CurrentPlayer);
      }
    }
    CurrentCounter++;
    delay(1);
  }while(Winner==-1);

  WinnerSoundAndLight(Winner);
  UpdateWinner(Winner);
  //Low intensity
  delay(700);
  TurnOffAllLights();
  delay(25);
}

