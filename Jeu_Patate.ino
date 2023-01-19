#ifdef ENABLE_LOGGING
  #define LOG_PATATE(a) LOG_GAME(Game_id_PC,a)
#else
  #define LOG_PATATE(a)
#endif
void PatateChaude(bool SimpleControls)
{
  unsigned long basetime=5242;
  unsigned long maxrandtime=12242;
  unsigned long GameTimeMillis=basetime+random(maxrandtime);
  unsigned long GameCounter=0;
  unsigned long PressCounter=0;
  int TimeDecMin=42;
  int TimeDecMax=242;
  bool ReadyToSwitch=false;
  int ReactTimeMin=84;
  int ReactTimeMax=2420;
  unsigned long GameCounterPenalite[nbj];
  bool PlayerIsPressing=false;
  bool PreviousState[nbj];
  for (int i=0; i<nbj; i++)
  {
    GameCounterPenalite[i]=0;
    PreviousState[i]=false;
  }
  #define PenaliteIncrPatate 2000;
  #define Patate_PressRev 150
  #define Patate_PressStall 300

  LOG_PATATE("GameTimeMillis:");
  LOG_PATATE(GameTimeMillis);
  LOG_PATATE("\n");
  GameCounter=0;
  TurnOffAllLights();
  //Lights Setup
  ActivateBlueLED(21);
  delay(1200);

  int LuckyPlayer=random(nbj);
  int NextPlayer;

  
  if (random(2)==0)
  {
     NextPlayer=1;
  }
  else
  {
    NextPlayer=-1;
  }


  MoveDEDUFlag(((float)GameTimeMillis/(float)(basetime+maxrandtime)*random(50,75)));
  delay(500);
  ActivateRedLight(LuckyPlayer);
  
  do
  {
    //Monitor spammers
    for (int i=0; i<nbj; i++)
    {
      if (ReadPlayerInput(i) && !PreviousState[i] && i!=LuckyPlayer)
      {
        GameCounterPenalite[i]=GameCounter+PenaliteIncrPatate;
        
        LOG_PATATE("Penalite Joueur:");
        LOG_PATATE(i);
        LOG_PATATE("\n");
        LOG_PATATE("GameCounterPenalite[i]:");
        LOG_PATATE(GameCounterPenalite[i]);
        LOG_PATATE("\n");
      }
    }
    
    if (!ReadPlayerInput(LuckyPlayer) && GameCounter>GameCounterPenalite[LuckyPlayer])
    {
      ReadyToSwitch=true;
    }
    
    if (ReadPlayerInput(LuckyPlayer) && ReadyToSwitch && !PlayerIsPressing)
    {
      LOG_PATATE("Change PlayerIsPressing");
      LOG_PATATE("\n");
      PlayerIsPressing=true;
    }


      //CHECK RELEASE
    if (PlayerIsPressing==true)
    {
      LOG_PATATE("I have started Pressing");
      LOG_PATATE("\n");
      //HIGH, Keep counting
      if (ReadPlayerInput(LuckyPlayer))
      {
        LOG_PATATE("I keep Pressing");
        LOG_PATATE("\n");
        PressCounter++;
      }
      else
      {
        LOG_PATATE("SwitchingPlayer!!");
        LOG_PATATE("\n");
        LOG_PATATE("GameTimeMillisIN:");
        LOG_PATATE(GameTimeMillis);
        LOG_PATATE("\n");
        LOG_PATATE("GameCounter:");
        LOG_PATATE(GameCounter);
        LOG_PATATE("\n");
        LOG_PATATE("PressCounter:");
        LOG_PATATE(PressCounter);
        LOG_PATATE("\n");
        //NORMAL DIRECTION
        if (PressCounter<Patate_PressRev || SimpleControls)
        {
          LOG_PATATE("NORMAL DIR!");
          LOG_PATATE("\n");
          DeactivateRedLight(LuckyPlayer);
          LuckyPlayer+=NextPlayer;
          tone(Tone_Pin, 800, 15);
        }
        //REV DIR
        else if (PressCounter>= Patate_PressRev && PressCounter<Patate_PressStall)
        {
          LOG_PATATE("REV DIR!");
          LOG_PATATE("\n");
          DeactivateRedLight(LuckyPlayer);
          LuckyPlayer-=NextPlayer;
          tone(Tone_Pin, 1200, 15);
        }
        else
        {
          //STALL ON PLAYER, TOO LONG PRESS
          LOG_PATATE("STALL");
          LOG_PATATE("\n");
          tone(Tone_Pin, 300, 150);
        }
        
        LOG_PATATE("REDUCING TIME!!");
        LOG_PATATE("\n");
        GameTimeMillis-=(random(TimeDecMin,TimeDecMax));
  
        //AddTimeToAllowReaction
        if (GameTimeMillis-GameCounter<ReactTimeMin)
        {
          LOG_PATATE("\n");
          LOG_PATATE("GIVING MORE TIME!!");
          LOG_PATATE("\n");
          GameTimeMillis+=(random(ReactTimeMin,ReactTimeMax));
        }
        
        LOG_PATATE("GameTimeMillisAFTER:");
        LOG_PATATE(GameTimeMillis);
        LOG_PATATE("\n");

        //Correct New LuckyPlayer
        LuckyPlayer=WrapAround(LuckyPlayer);
        //Activate new lucky Player
        ActivateRedLight(LuckyPlayer);
        ReadyToSwitch=false;
        PlayerIsPressing=false;
        PressCounter=0;
      }
    }
    
    //Side-switching function
    if (random(10000)>9996)
    {
      LOG_PATATE("SwitchingSIDE!!");
      LOG_PATATE("\n");
      
      if (NextPlayer == 1)
      {
        NextPlayer=-1;
        //Decrease Flag
        MoveDEDUFlag(random(ServoAnglePercent()));
      }
      else
      {
        NextPlayer=1;
        //IncreaseFlag
        MoveDEDUFlag(random(ServoAnglePercent(),100));
      }
    }

    for (int i=0; i<nbj; i++)
    {
      PreviousState[i]=ReadPlayerInput(i);
    }
    delay(1);
    GameCounter++;
  }while(GameCounter<GameTimeMillis);

  ActivateBlueLED(5);
  
  for (int i=1; i<=80; i++)
  {
    Tone_Frequency=2000 - 20 * i;
    tone(Tone_Pin, Tone_Frequency);
    delay(10);
  }
  noTone(Tone_Pin);
  
  //Identify the Looser
  for (int e=1; e<=4; e++) {
    ActivateRedLight(LuckyPlayer);
    delay(500);
    DeactivateRedLight(LuckyPlayer);
    delay(500);
  }

  TurnOffAllLights();
  MoveDEDUFlag(0);
  delay(1200);
}

