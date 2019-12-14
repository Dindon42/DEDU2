
#ifdef ENABLE_LOGGING
  #define LOG_PATATE2(a) LOG_GAME(Game_id_PC2,a)
#else
  #define LOG_PATATE2(a)
#endif
void Patate2()
{
  
  unsigned long basetime=12242;
  unsigned long maxrandtime=4242;
  unsigned long GameTimeMillis=basetime+random(maxrandtime);
  unsigned long GameCounter=0;
  int InitSpread=nbj/2;
  bool ReadyToSwitch[2]={false,false};
  bool PlayerIsPressing[2]={false,false};
  unsigned long PressCounter[2]={0,0};
  int LuckyPlayer[2];
  int DirectionNextPlayer[2]={0,0};
  int ProbOppDir=3;
  unsigned long MinChangeCounter=3500;
  unsigned long ChangeCounter=0;

  #define PenaliteIncrPatate2 2000;
  unsigned long GameCounterPenalite[nbj];
  bool PreviousState[nbj];
  for (int i=0; i<nbj; i++)
  {
    GameCounterPenalite[i]=0;
    PreviousState[i]=false;
  }

  //Positions of DEDU for different configs.
  int BothPlus=80;
  int OppDir1=60;
  int OppDir2=40;
  int BothMinus=20;
  int DEDUPosition=0;
  
  
  TurnOffAllLights();
  
  //Initialize direction of turn
  if (random(2)==0)
  {
     DirectionNextPlayer[0]=1;
     DirectionNextPlayer[1]=1;
     DEDUPosition=BothPlus;
  }
  else
  {
    DirectionNextPlayer[0]=-1;
    DirectionNextPlayer[1]=-1;
    DEDUPosition=BothMinus;
  }

  if (nbj%2!=0)
  {
    if (random(2)==0)
    {
      InitSpread=InitSpread+1;
    }
  }


  //Start the players furthest apart.
  LuckyPlayer[0]=random(nbj);
  LuckyPlayer[1]=ProchainJoueur(LuckyPlayer[0],InitSpread,DirectionNextPlayer[0]);
  
  LOG_PATATE2("\n");
  LOG_PATATE2("PATATE2");
  LOG_PATATE2("\n");
  LOG_PATATE2("\n");
  LOG_PATATE2("GameTimeMillis:");
  LOG_PATATE2(GameTimeMillis);
  LOG_PATATE2("\n");
  LOG_PATATE2("InitSpread:");
  LOG_PATATE2(InitSpread);
  LOG_PATATE2("\n");
  LOG_PATATE2("DirectionNextPlayer[0]:");
  LOG_PATATE2(DirectionNextPlayer[0]);
  LOG_PATATE2("\n");
  LOG_PATATE2("DirectionNextPlayer[1]:");
  LOG_PATATE2(DirectionNextPlayer[1]);
  LOG_PATATE2("\n");
  LOG_PATATE2("LuckyPlayer[0]:");
  LOG_PATATE2(LuckyPlayer[0]);
  LOG_PATATE2("\n");
  LOG_PATATE2("LuckyPlayer[1]:");
  LOG_PATATE2(LuckyPlayer[1]);
  LOG_PATATE2("\n");
  
  //Lights/DEDU INIT Setup
  ActivateBlueLED(21);
  delay(1200);
  MoveDEDUFlag(DEDUPosition);
  delay(500);
  for (int i=0; i<=1; i++)
  {
    ActivateRedLight(LuckyPlayer[i]);
  }

  do
  {
    //Monitor spammers
    for (int i=0; i<nbj; i++)
    {
      bool PP=ReadPlayerInput(i);
      if (PP && !PreviousState[i] && i!=LuckyPlayer[0] && i!=LuckyPlayer[1])
      {
        GameCounterPenalite[i]=GameCounter+PenaliteIncrPatate2;
        
        LOG_PATATE2("Penalite Joueur:");
        LOG_PATATE2(i);
        LOG_PATATE2("\n");
        LOG_PATATE2("GameCounterPenalite[i]:");
        LOG_PATATE2(GameCounterPenalite[i]);
        LOG_PATATE2("\n");
      }
      PreviousState[i]=PP;
    }
    
    ChangeCounter++;
    GameCounter++;
    for (int i=0; i<=1; i++)
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
      if (!ReadPlayerInput(LuckyPlayer[i]) && !ReadyToSwitch[i] && GameCounter>GameCounterPenalite[LuckyPlayer[i]])
      {
        LOG_PATATE2("Change ReadyToSwitch");
        LOG_PATATE2("\n");
        ReadyToSwitch[i]=true;
      }
      
      //Monitor subsequent transition to HIGH
      if (ReadPlayerInput(LuckyPlayer[i]) && ReadyToSwitch[i] && !PlayerIsPressing[i])
      {
        LOG_PATATE2("Change PlayerIsPressing");
        LOG_PATATE2("\n");
        PlayerIsPressing[i]=true;
      }
      
      //Player releases.  Check counter to know in which direction to go.
      if (PlayerIsPressing[i])
      {
        LOG_PATATE2("I have started Pressing");
        LOG_PATATE2("\n");
        //HIGH, Keep counting
        if (ReadPlayerInput(LuckyPlayer[i]))
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
          LOG_PATATE2(DirectionNextPlayer[i]);
          LOG_PATATE2("\n");
          LOG_PATATE2("PressCounter:");
          LOG_PATATE2(PressCounter[i]);
          LOG_PATATE2("\n");
          //NORMAL DIRECTION
          if (PressCounter[i]<Patate_PressRev)
          {
            LOG_PATATE2("NORMAL DIR!");
            LOG_PATATE2("\n");
            DeactivateRedLight(LuckyPlayer[i]);
            LuckyPlayer[i]+=DirectionNextPlayer[i];
            tone(Tone_Pin, 800, 15);
          }
          //REV DIR
          else if (PressCounter[i]>=Patate_PressRev && PressCounter[i]<Patate_PressStall)
          {
            LOG_PATATE2("REV DIR!");
            LOG_PATATE2("\n");
            DeactivateRedLight(LuckyPlayer[i]);
            LuckyPlayer[i]-=DirectionNextPlayer[i];
            tone(Tone_Pin, 1200, 15);
          }
          else
          {
            //STALL ON PLAYER, TOO LONG PRESS
            LOG_PATATE2("STALL");
            LOG_PATATE2("\n");
            tone(Tone_Pin, 200+LuckyPlayer[i]*25, 150);
          }
          
          //Reset Counters and player ID
          ReadyToSwitch[i]=false;
          PlayerIsPressing[i]=false;
          PressCounter[i]=0;
          
          LuckyPlayer[i]=WrapAround(LuckyPlayer[i]);

          LOG_PATATE2("New Player:");
          LOG_PATATE2(LuckyPlayer[i]);
          LOG_PATATE2("\n");
          
          //Activate new light;
          ActivateRedLight(LuckyPlayer[i]);
        }
      }
      delay(1);
      
      //Check Win condition between players.
      if (LuckyPlayer[0] == LuckyPlayer[1])
      {
        break;
      }
    }

    //Check change DIR
    if (random(10000)>9995 &&  ChangeCounter>MinChangeCounter)
    {
      
      LOG_PATATE2("GameCounter:");
      LOG_PATATE2(GameCounter);
      LOG_PATATE2("\n");
      LOG_PATATE2("SwitchingSIDE!!");
      LOG_PATATE2("\n");
      
      ChangeCounter=0;
      
      //MAIN DIRECTION
      if (DirectionNextPlayer[0] == 1)
      {
        DirectionNextPlayer[0]=-1;
      }
      else
      {
        DirectionNextPlayer[0]=1;
      }

      //Second Direction
      if (random(ProbOppDir)==0)
      {
        LOG_PATATE2("Opp Directions!!");
        LOG_PATATE2("\n");
        DirectionNextPlayer[1]=-DirectionNextPlayer[0];
      }
      else
      {
        LOG_PATATE2("Same Direction");
        LOG_PATATE2("\n");
        DirectionNextPlayer[1]=DirectionNextPlayer[0];
      }

      //Directions
      if (DirectionNextPlayer[0] == 1 && DirectionNextPlayer[1]==1)
      {
        DEDUPosition=BothPlus;
      }
      else if (DirectionNextPlayer[0] == 1 && DirectionNextPlayer[1]==-1)
      {
        DEDUPosition=OppDir1;
      }
      else if (DirectionNextPlayer[0] == -1 && DirectionNextPlayer[1]==1)
      {
        DEDUPosition=OppDir2;
      }
      else
      {
        DirectionNextPlayer[0]=-1;
        DirectionNextPlayer[1]=-1;
        DEDUPosition=BothMinus;
      }
      MoveDEDUFlag(DEDUPosition);
    }
  }while((LuckyPlayer[0]!=LuckyPlayer[1]) && (GameCounter<GameTimeMillis));

  //Both LED on same player OR Game Timeout.
  LOG_PATATE2("GAME OVER");
  LOG_PATATE2("\n");
  
  //Loose Stage
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
    ActivateRedLight(LuckyPlayer[0]);
    ActivateRedLight(LuckyPlayer[1]);
    delay(500);
    DeactivateRedLight(LuckyPlayer[0]);
    DeactivateRedLight(LuckyPlayer[1]);
    delay(500);
  }

  //FIN  
  TurnOffAllLights();
  MoveDEDUFlag(0);
  delay(1200);
}
