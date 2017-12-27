void TLMPareil()
{
  //Init Setup: Mix cyan et Rose
  ActivateGreenLED(15);
  ActivateBlueLED(5);
  
  for (int i=0 ; i<nbj_raw ; i++)
  {
    if (i%2==0)
    {
     ActivateRedLight(i); 
    }
  }

  do
  {
    ReadInputToggleOutput(nbj_raw);
    delay(250);
    Serial.print(CheckAllActiveOutputs(nbj_raw));
  }while(CheckAllActiveOutputs(nbj_raw)==0 || CheckAllActiveOutputs(nbj_raw)==nbj);

  //EndAll lights
  DeactivateGreenLED();
  DeactivateBlueLED();
  TurnOffAllRedLights();
  delay(2000);

  TLMPareil();
}

