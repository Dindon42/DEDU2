#ifdef ENABLE_LOGGING
  #define LOG_TROMPE(a) LOG_GAME(Game_id_TO,a)
#else
  #define LOG_TROMPE(a)
#endif
void TrompeOeil()
{
  LOG_TROMPE("TROMPE");
  LOG_TROMPE("\n");
  
  int NumActive=-1;
  int maxIter=random(2500,4500);
  int maxIter_Sheep=2500;
  int IterVert=random(30,35);
  bool SwitchColor=false;
  bool SwitchToRed=false;
  int ToRED=IterVert+50;
  int ProbVert=4;
  bool GreenFirst=(random(ProbVert)==0);
  
  LOG_TROMPE("Game_Mode:");
  LOG_TROMPE(Game_Mode);
  LOG_TROMPE("\n");
  LOG_TROMPE("GreenFirst:");
  LOG_TROMPE(GreenFirst);
  LOG_TROMPE("\n");
  LOG_TROMPE("maxIter:");
  LOG_TROMPE(maxIter);
  LOG_TROMPE("\n");  
  LOG_TROMPE("IterVert:");
  LOG_TROMPE(IterVert);
  LOG_TROMPE("\n");  
  
  int Looser=-1;

  //Initialize Loosers Array
  int Loosers[nbj];
  for (int i=0; i<=nbj_raw;i++)
  {
    Loosers[i]=0;
  }
  
  if (GreenFirst)
  {
    //Init lights as green!
    ActivateGreenLED(random(1,5));
  }
  else
  {
    //Init lights as red!
    TurnOnAllRedLights();
  }

  for (int i=0; i<=maxIter; i++)
  {

    if (!SwitchColor && i>IterVert && GreenFirst)
    {
      SwitchColor=true;
      ActivateGreenLED(0);
      LOG_TROMPE("SWITCHING OFF GREEN");
      LOG_TROMPE("\n");  
    }

    if (!SwitchToRed && i>ToRED && GreenFirst)
    {
      SwitchToRed=true;
      TurnOnAllRedLights();
      LOG_TROMPE("SWITCHING TO RED");
      LOG_TROMPE("\n");  
    }
    
    Looser=FirstActive(nbj_raw);
    if (Looser>= 0) 
    {
      TurnOffAllRedLights();
      ActivateGreenLED(0);
      tone(Tone_Pin, 1500, 200);
      ActivateRedLight(Looser);
      Loosers[Looser]=1;
      break;
    }
    delay(1);
  }

  if (Looser>= 0)
  {
    for (int j=0; j<=maxIter_Sheep; j++)
    {
      for (int i=0; i<=nbj_raw;i++)
      {
        if (ReadPlayerInput(i) && Loosers[i]==0)
        {
          Loosers[i]=1;
          ActivateRedLight(i);
          tone(Tone_Pin, 1500, 200);
        }
      }
      delay(1);
    }
  }

  //Game End
  TurnOffAllRedLights();
  delay(250);
}