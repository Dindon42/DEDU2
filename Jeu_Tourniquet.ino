
#ifdef ENABLE_LOGGING
  #define LOG_TOURNIQUET(a) LOG_GAME(Game_id_TH,a)
#else
  #define LOG_TOURNIQUET(a)
#endif
void Tourniquet()
{
  int LightDelay=3;
  int LightDelayIncrement=1;
  int CurrentCounter=0;
  int LastPlayer=random(nbj);
  int CurrentPlayer=0;
  int DirectionNextPlayer=0;
  bool PlayersState[nbj_max]={true,true,true,true,true,true,true,true,true,true};
  int NumActivePlayers=nbj;
  int Looser=-1;
  bool ReadyToPress=false;
  bool PlayerIsPressing=false;
  bool ReadytoIncreaseIncrement=false;
  bool IgnorePresses=false;
  int IncrementProb=3;

  if (random(2)==0)
  {
    DirectionNextPlayer=1;
  }
  else
  {
    DirectionNextPlayer=-1;
  }
  CurrentPlayer=WrapAround(LastPlayer+DirectionNextPlayer);
  
  //Tout bleu pour commencer+Une Lumière
  ActivateRedLight(CurrentPlayer);
  ActivateBlueLED(20);
  
  //Spin the wheel!
  do
  {
    //For the active player, monitor the transitions.  
    //1: ToLow
    //2: ToHigh
    //3: ToLow
    //If this happens during the time the player is active, Good, you are not the looser.
    LOG_TOURNIQUET("CurrentPlayer:");
    LOG_TOURNIQUET(CurrentPlayer);
    LOG_TOURNIQUET("\n");
    LOG_TOURNIQUET("ReadyToPress:");
    LOG_TOURNIQUET(ReadyToPress);
    LOG_TOURNIQUET("\n");
    LOG_TOURNIQUET("PlayerIsPressing:");
    LOG_TOURNIQUET(PlayerIsPressing);
    LOG_TOURNIQUET("\n");
    //Monitor initial transition to LOW
    
    if (!ReadPlayerInput(CurrentPlayer) && !ReadyToPress && !IgnorePresses)
    {
      LOG_TOURNIQUET("Changing RTP!");
      LOG_TOURNIQUET("\n");
      ReadyToPress=true;
    }
    
    //Monitor subsequent transition to HIGH
    if (ReadPlayerInput(CurrentPlayer) && ReadyToPress && !PlayerIsPressing && !IgnorePresses)
    {
      LOG_TOURNIQUET("Changing PIP!")
      LOG_TOURNIQUET("\n");
      PlayerIsPressing=true;
    }
    
    //Monitor subsequent transition to LOW
    if (!ReadPlayerInput(CurrentPlayer) && PlayerIsPressing && !IgnorePresses)
    {
      LOG_TOURNIQUET("Player SAFE!")
      LOG_TOURNIQUET("\n");
      //YOU ARE SAFE.
      if (PlayersState[CurrentPlayer])
      {
        NumActivePlayers--;
        PlayersState[CurrentPlayer]=false;
        IgnorePresses=true;

        //Change Last Player if Current Player
        if (CurrentPlayer==LastPlayer)
        {
          LOG_TOURNIQUET("Player was last and is now safe!")
          LOG_TOURNIQUET("\n");
          LOG_TOURNIQUET("Changing LAST PLAYER to:")
          do
          {
            LastPlayer=WrapAround(LastPlayer+DirectionNextPlayer);
          }while(PlayersState[LastPlayer]==false);
          LOG_TOURNIQUET(LastPlayer);
          LOG_TOURNIQUET("\n");
        }
      }
    }
    
    delay(1);
    
    //Find spammers and bring them back in the game.
    for (int i=0; i<=nbj_raw; i++)
    {
      if (!PlayersState[i] && ReadPlayerInput(i))
      {
        LOG_TOURNIQUET("SPAM PLAYER:");
        LOG_TOURNIQUET(i);
        LOG_TOURNIQUET("\n");
        
        PlayersState[i]=true;
        NumActivePlayers++;
        DeactivateRedLight(i);
      }
    }
    
    delay(1);

    if (NumActivePlayers<=1) 
    {
      break;
    }
    
    //Enougn time on this guy...  Switch
    if (CurrentCounter>LightDelay)
    {
      
      CurrentCounter=0;
      ReadyToPress=false;
      PlayerIsPressing=false;
      IgnorePresses=false;
      
      //If we reach the last guy, increment lightdelay
      if (CurrentPlayer==LastPlayer)
      {
        LightDelay+=LightDelayIncrement;
        LOG_TOURNIQUET("Increasing LightDelay:")
        LOG_TOURNIQUET(LightDelay);
        LOG_TOURNIQUET("\n");
        
        if (ReadytoIncreaseIncrement==true)
        {
          if (random(IncrementProb)==0)
          {
            LightDelayIncrement++;
            LOG_TOURNIQUET("Increasing Increment:")
            LOG_TOURNIQUET(LightDelayIncrement);
            LOG_TOURNIQUET("\n");
          }
          ReadytoIncreaseIncrement=false;
        }
        else
        {
          ReadytoIncreaseIncrement=true;
        }
      }
      
      delay(1);
      //Keep winners lights active, Deactivate my light if im still in this game.
      if (PlayersState[CurrentPlayer]==true)
      {
        DeactivateRedLight(CurrentPlayer);
      }
      
      tone(Tone_Pin, 3500, 3);
      //Find an active player
      do
      {
        CurrentPlayer=WrapAround(CurrentPlayer+DirectionNextPlayer);
      }while(!PlayersState[CurrentPlayer]);
      
      ActivateRedLight(CurrentPlayer);
      
    }
    
    CurrentCounter++;
    delay(1);
  }while(NumActivePlayers>1);

  for (int i=0; i<=nbj_raw; i++)
  {
    if (PlayersState[i])
    {
      Looser=i;
    }
  }

  //Low intensity
  delay(700);
  TurnOffAllLights();

  LooserSoundAndLight(Looser,false);
  JoueurHonte=MarqueurHonte(Looser,DelaiPetiteHonte);
}


