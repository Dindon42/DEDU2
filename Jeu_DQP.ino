//Dernier qui pèse
void DQP()
{
  int z;
  int Perdant=-1;

  //init lights as purple
  ActivateBlueLED(100);
  TurnOnAllRedLights();
  
  z=nbj;

  do
  {
    z=z-ReadInputDeactivateOutputIfActive(nbj_raw);
  }while (z!=1);
  Perdant=FirstActiveOutput(nbj_raw);

  TurnOffNonActivePlayerRedLights();
  
  SingleLooserSoundAndLight(Perdant);
  
  delay(500);
}