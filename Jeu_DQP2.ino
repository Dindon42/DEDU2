void DQP2()
{
  int const NumIter_same=10;
  int const ScoreTol=3;
  
  int sum[nbj_raw_max];
  int Looser=-1;
  int LooserCount=0;
  bool looserfound=false;
  //Init Setup: Mauve comme DQP1
  ActivateBlueLED(100);
  TurnOnAllRedLights();

  int NumActiveOutputs=-1;
  
  do
  {
    ReadInputToggleOutput(nbj_raw);
    delay(random(5,30));

    
    LooserCount=0;
    looserfound=false;
    for (int i=0;i<=nbj_raw;i++)
    {
      if (ReadPlayerInput(i) || ReadPlayerOutput(i))
      {
        LooserCount++;
        Looser=i;
      }
    }
    
    if (LooserCount==1)
    {
      looserfound=true;
    }
    else if (LooserCount==0)
    {
      TurnOnAllRedLights();
      delay(20);
    }
  }while(!looserfound);



  //SCORE
  ActivateBlueLED(10);
  TurnOffNonActivePlayerRedLights();

  

  for (int i=1; i<=80; i++)
  {
    Tone_Frequency=2000 - 20 * i;
    tone(Tone_Pin, Tone_Frequency);
    delay(10);
  }
  noTone(Tone_Pin);

  //Identify the Loosers
  for (int e=1; e<=4; e++) {
    
    ActivateRedLight(Looser);
    
    delay(500);


    DeactivateRedLight(Looser);
    
    delay(500);
  }
  DeactivateBlueLED();
}

