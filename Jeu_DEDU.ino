//Debut DEDU
void DEDU()
{
  float myRand1=random(280,400)/100;
  int myRand2=random(25,32);
  
  JoueChanson(0,myRand1,false, true);
  
  for (int e=1; e<=myRand2; e++) {

    MoveDEDUFlag(100-random(20));

    TurnOnAllRedLights();
    delay(60 + random(200));
    TurnOffAllRedLights();

    ActivateBlueLED(80);
    delay(60 + random(200));
    DeactivateBlueLED();

    ActivateGreenLED(80);
    delay(60 + random(200));
    DeactivateGreenLED();
  }


  DeactivateBlueLED();
  DeactivateGreenLED();
  TurnOffAllRedLights();
  MoveDEDUFlag(0);
  delay(500);
}