void DQP2()
{
  
  //Init Setup: Mauve comme DQP
  ActivateBlueLED(100);
  TurnOnAllRedLights();

  int NumActiveOutputs=-1;
  
  do
  {
    ReadInputToggleOutput(nbj_raw);
    delay(25);
    NumActiveOutputs = CheckAllActiveOutputs(nbj_raw);
  }while(NumActiveOutputs!=1);

  //EndAll lights
  DeactivateGreenLED();
  DeactivateBlueLED();
  TurnOffAllRedLights();
  delay(2000);

  DQP2();
}

void Maj()
{
  
  //Init Setup: Mauve comme DQP
  ActivateBlueLED(100);
  TurnOnAllRedLights();

  int NumActiveOutputs=-1;
  
  do
  {
    ReadInputToggleOutput(nbj_raw);
    delay(25);
    NumActiveOutputs = CheckAllActiveOutputs(nbj_raw);
  }while(NumActiveOutputs!=1);

  //EndAll lights
  DeactivateGreenLED();
  DeactivateBlueLED();
  TurnOffAllRedLights();
  delay(2000);

  DQP2();
}

