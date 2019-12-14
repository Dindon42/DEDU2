void MIN()
{
  int Sum0=0;
  int Sum1=0;
  bool allloosers;
  bool noloosers=false;
  int DeclaredLoosers[nbj_max];
  int LightDelay=800;
  for (int i=0; i<=nbj_raw_max;i++)
  {
    DeclaredLoosers[i]=0;
  }
  
  ActivateGreenLED(100);
  TurnOnAllRedLights();
  
  int RandTimer=8+random(7);

  float TimeInterval=900;
  float TimeDelta;
  
  for (int i=0;i<RandTimer;i++)
  {
    tone(Tone_Pin,250,10);
    delay(400);
    ActivateGreenLED(50);
    tone(Tone_Pin,700,10);
    delay(TimeInterval);
    ActivateGreenLED(100);

    TimeInterval-=(float)(random(300,900)/RandTimer);
  }
  TurnOffAllRedLights();
  DeactivateGreenLED();
  delay(500);
  CheckAllActive(nbj_raw);
  delay(500);

  for (int i=0; i<=nbj_raw; i++)
  {
    if (InputState[i])
      Sum1++;
    else
      Sum0++;
  }

  //ALL LOSERS
  if (Sum0==0||Sum1==0)
  {
    for (int i=0; i<=nbj_raw;i++)
    {
      DeclaredLoosers[i]=1;
    }
    allloosers=true;
  }
  else if (Sum0>Sum1) // Low Looses
  {
    for (int i=0; i<=nbj_raw;i++)
    {
      if (!InputState[i])
      {
        DeclaredLoosers[i]=1;
      }
    }
    allloosers=false;
  }
  else if (Sum1>Sum0)//HIGH Looses
  {
    for (int i=0; i<=nbj_raw;i++)
    {
      if (InputState[i])
        DeclaredLoosers[i]=1;
    }
    allloosers=false;
  }
  else//NoLoosers, start over.
  {
    ActivateGreenLED(100);
    OneUp();
    for (int i=0; i<4; i++)
    {
      DeactivateGreenLED();
      delay(LightDelay);
      ActivateGreenLED(100);
      delay(LightDelay);
    }
    
    TurnOffAllLights();
    noloosers=true;
  }

  if (!noloosers && !allloosers)
  {
    ActivateGreenLED(20);
    
    OneUp();
    //Sound for winners.
    for (int i=0; i<4; i++)
    {
      for (int i=0; i<=nbj_raw;i++)
      {
        if (DeclaredLoosers[i]==0)
          ActivateRedLight(i);
      }
      DeactivateGreenLED();
      delay(LightDelay);
      for (int i=0; i<=nbj_raw;i++)
      {
        if (DeclaredLoosers[i]==0)
          DeactivateRedLight(i);
      }
      ActivateGreenLED(20);
      delay(LightDelay);
    }
  }
  else if (!noloosers && allloosers)
  {
    AllLoosersSoundAndLight();
  }
  TurnOffAllLights();
}


