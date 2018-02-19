
void TestMode()
{
  
  PlayNote(Tone_Pin,2500,200,20);
  PlayNote(Tone_Pin,1000,200,20);
  PlayNote(Tone_Pin,2500,200,20);
  PlayNote(Tone_Pin,1000,200,20);
  
  while (1)
  {
    for (int i=0; i<=nbj_raw_max;i++)
    {
      if (ReadPlayerInput(i) == HIGH)
      {
        ActivateRedLight(i);
      }
      else
      {
        DeactivateRedLight(i);
      }
    }
  }
}


void DemoMode()
{
  bool AllPressing;

  //Tone
  PlayNote(Tone_Pin,2500,200,20);
  PlayNote(Tone_Pin,1000,200,20);
  PlayNote(Tone_Pin,2500,200,20);
  PlayNote(Tone_Pin,1000,200,20);
  delay(1000);
  NombreJoueurs();
  
  for(int i=0 ; i<NbJeux;i++)
  {
    //Demo the game once
    PlayGame(i);
    
    do
    {
      AllPressing=true;
      for(int j=0 ; j<nbj ;j++)
      {
        if(ReadPlayerInput(j)==HIGH)
        {
          ActivateRedLight(i);
        }
        else
        {
          AllPressing=false;
          DeactivateRedLight(i);
        }
      }
      delay(1);
    }while(AllPressing==false);
  }
}

