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
  bool ReadyToSwitch[2]={false,false};
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

  LOG_PATATE2("DirectionNextPlayer:");
  LOG_PATATE2(DirectionNextPlayer);
  LOG_PATATE2("\n");

  //Start the players furthest apart.
  LuckyPlayer[0]=random(nbj);
  LuckyPlayer[1]=ProchainJoueur(LuckyPlayer[0],nbj/2,DirectionNextPlayer);

  LOG_PATATE2("LuckyPlayer[0]:");
  LOG_PATATE2(LuckyPlayer[0]);
  LOG_PATATE2("\n");
  LOG_PATATE2("LuckyPlayer[1]:");
  LOG_PATATE2(LuckyPlayer[1]);
  LOG_PATATE2("\n");
  
  //Lights/DEDU INIT Setup
  ActivateBlueLED(21);
  delay(1500);
  MoveDEDUFlag(((float)GameTimeMillis/(float)(basetime+maxrandtime)*random(50,75)));
  delay(500);
  for(int i=0; i<=1 ; i++)
  {
    ActivateRedLight(LuckyPlayer[i]);
  }
  

  
  
}
