#ifdef ENABLE_LOGGING
  #define LOG_PATATE2(a) LOG_GENERAL(a)
#else
  #define LOG_PATATE2(a)
#endif
void Patate2()
{
  unsigned long basetime=4242;
  unsigned long maxrandtime=10242;
  unsigned long GameTimeMillis = basetime+random(maxrandtime);
  int TimeDecMin=50;
  int TimeDecMax=300;
  int ReactTimeMin=100;
  int ReactTimeMax=250;
  int InitSpread=nbj/2;
  bool ReadyToSwitch[2]={false,false};
  bool PlayerIsPressing[2]={false,false};
  unsigned long PressCounter[2]={0,0};
  const int PressRev=15;
  const int PressStall=30;
  unsigned long GameCounter=0;

  int LuckyPlayer[2];
  int DirectionNextPlayer=0;
  
  LOG_PATATE2("GameTimeMillis:");
  LOG_PATATE2(GameTimeMillis);
  LOG_PATATE2("\n");
  GameCounter=0;
  TurnOffAllLights();
  
  //Initialize direction of turn
  if(random(2)==0)
  {
     DirectionNextPlayer=1;
  }
  else
  {
    DirectionNextPlayer=-1;
  }

  if(nbj%2!=0)
  {
    if (random(2)==0)
    {
      InitSpread=InitSpread+1;
    }
  }


  //Start the players furthest apart.
  LuckyPlayer[0]=random(nbj);
  
  LOG_PATATE2("LuckyPlayer[0]:");
  LOG_PATATE2(LuckyPlayer[0]);
  LOG_PATATE2("\n");
  LOG_PATATE2("InitSpread:");
  LOG_PATATE2(InitSpread);
  LOG_PATATE2("\n");
  LOG_PATATE2("DirectionNextPlayer:");
  LOG_PATATE2(DirectionNextPlayer);
  LOG_PATATE2("\n");
  
  LuckyPlayer[1]=ProchainJoueur(LuckyPlayer[0],InitSpread,DirectionNextPlayer);

  LOG_PATATE2("LuckyPlayer[0]:");
  LOG_PATATE2(LuckyPlayer[0]);
  LOG_PATATE2("\n");
  LOG_PATATE2("LuckyPlayer[1]:");
  LOG_PATATE2(LuckyPlayer[1]);
  LOG_PATATE2("\n");
  
  //Lights/DEDU INIT Setup
  ActivateBlueLED(21);
  delay(1500);
  MoveDEDUFlag(50+DirectionNextPlayer*25);
  delay(500);
  for(int i=0; i<=1 ; i++)
  {
    ActivateRedLight(LuckyPlayer[i]);
  }

  do
  {
    for (int i=0 ; i<=1 ; i++)
    {
      /*
      LOG_PATATE2("Current Player:");
      LOG_PATATE2(LuckyPlayer[i]);
      LOG_PATATE2("\n");
      LOG_PATATE2("PlayerIsPressing:");
      LOG_PATATE2(PlayerIsPressing[i]);
      LOG_PATATE2("\n");
      LOG_PATATE2("ReadyToSwitch:");
      LOG_PATATE2(ReadyToSwitch[i]);
      LOG_PATATE2("\n");
      LOG_PATATE2("PressCounter:");
      LOG_PATATE2(PressCounter[i]);
      LOG_PATATE2("\n");
      */
      
      //Monitor initial transition to LOW
      if(ReadPlayerInput(LuckyPlayer[i])==LOW && ReadyToSwitch[i]==false)
      {
        LOG_PATATE2("Change ReadyToSwitch");
        LOG_PATATE2("\n");
        ReadyToSwitch[i]=true;
      }
      
      //Monitor subsequent transition to HIGH
      if(ReadPlayerInput(LuckyPlayer[i])==HIGH && ReadyToSwitch[i]==true && PlayerIsPressing[i]==false)
      {
        LOG_PATATE2("Change PlayerIsPressing");
        LOG_PATATE2("\n");
        PlayerIsPressing[i]=true;
      }

      
      
      //Player releases.  Check counter to know in which direction to go.
      if (PlayerIsPressing[i]==true)
      {
        LOG_PATATE2("I have started Pressing");
        LOG_PATATE2("\n");
        //HIGH, Keep counting
        if(ReadPlayerInput(LuckyPlayer[i])==HIGH)
        {
          LOG_PATATE2("I keep Pressing");
          LOG_PATATE2("\n");
          PressCounter[i]++;
        }
        //LOW, Take Action
        else
        {
          LOG_PATATE2("I Released!!");
          LOG_PATATE2("\n");
          LOG_PATATE2("SwitchingPlayer!!");
          LOG_PATATE2("\n");
          LOG_PATATE2("Current Player:");
          LOG_PATATE2(LuckyPlayer[i]);
          LOG_PATATE2("\n");
          LOG_PATATE2("DirectionNextPlayer:");
          LOG_PATATE2(DirectionNextPlayer);
          LOG_PATATE2("\n");
          LOG_PATATE2("PressCounter:");
          LOG_PATATE2(PressCounter[i]);
          LOG_PATATE2("\n");
          //NORMAL DIRECTION
          if (PressCounter[i]<PressRev)
          {
            LOG_PATATE2("NORMAL DIR!");
            LOG_PATATE2("\n");
            DeactivateRedLight(LuckyPlayer[i]);
            LuckyPlayer[i]+=DirectionNextPlayer;
          }
          //REV DIR
          else if (PressCounter[i]>=PressRev && PressCounter[i] < PressStall)
          {
            LOG_PATATE2("REV DIR!");
            LOG_PATATE2("\n");
            DeactivateRedLight(LuckyPlayer[i]);
            LuckyPlayer[i]-=DirectionNextPlayer;
          }
          else
          {
            //STALL ON PLAYER, TOO LONG PRESS
            LOG_PATATE2("STALL");
            LOG_PATATE2("\n");
          }
          
          //Reset Counters and player ID
          ReadyToSwitch[i]=false;
          PlayerIsPressing[i]=false;
          PressCounter[i]=0;
          
          //WRAP AROUND?
          if (LuckyPlayer[i]>nbj_raw)
          {
            LuckyPlayer[i]=0;
          }
          else if (LuckyPlayer[i] < 0)
          {
            LuckyPlayer[i]=nbj_raw;
          }

          LOG_PATATE2("New Player:");
          LOG_PATATE2(LuckyPlayer[i]);
          LOG_PATATE2("\n");
          
          //Deactivate my Light;
          ActivateRedLight(LuckyPlayer[i]);
        }
      }
    }
    delay(1);
  }while(LuckyPlayer[0] != LuckyPlayer[1]);

  //BOTH SAME: PLAYER FOUND.
  LOG_PATATE2("GAME OVER");
  LOG_PATATE2("\n");
}
