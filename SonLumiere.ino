
//Activates one red light.
void ActivateRedLight(int iPlayer)
{
  digitalWrite(PlayerOutputPins[iPlayer],HIGH);
}


//Deactivates one red light.
void DeactivateRedLight(int iPlayer)
{
  digitalWrite(PlayerOutputPins[iPlayer],LOW);
}

void ActivateBlueLED(int Value)
{
  if (Value<0)
  {
    Value=0;
  }
  else if (Value>100)
  {
    Value=100;
  }
  
  analogWrite(B, Value);
}

void DeactivateBlueLED()
{
  analogWrite(B, 0);
}


void ActivateGreenLED(int Value)
{
  if (Value<0)
  {
    Value=0;
  }
  else if(Value>100)
  {
    Value=100;
  }
  
  analogWrite(G, Value);
}

void DeactivateGreenLED()
{
  analogWrite(G, 0);
}

//Turn off all the reds
void TurnOffAllRedLights()
{
  for (int i=0; i<=nbj_raw_max;i++)
  {
    DeactivateRedLight(i);
  }
}

//Turn ON all the reds
void TurnOnAllRedLights()
{
  for (int i=0; i<=nbj_raw_max;i++)
  {
    ActivateRedLight(i);
  }
}

//Turns off red light for players which did not press and those not playing.
void TurnOffNonActiveRedLights()
{
  //Deactivate Non-Active inputs
  for (int i=0; i<=nbj_raw;i++)
  {
    if (ReadPlayerInput(i)==LOW)
    {
      DeactivateRedLight(i);
    }
  }
  TurnOffNonActivePlayerRedLights();
}


void TurnOffNonActivePlayerRedLights()
{
  //Turn off non active players
  for (int i=nbj_raw+1; i<=nbj_raw_max;i++)
  {
    DeactivateRedLight(i);
  }
}

void ClignoteEtSon(int NbMax,int FreqStart, int FreqIncrease, int NbOffset)
{
  //Clignote + Son
  for (int i = 0 + NbOffset; i <= NbMax; i++)
  {
    //Light and sound for valid players.
    ActivateRedLight(i);
    Tone_Frequency = FreqStart + FreqIncrease * i;
    tone(Tone_Pin, Tone_Frequency, 50);
    delay(100);
  }
}

void PlayNote(int Tone_Pin, double Freq, double PlayTime, double WaitTime)
{
  tone(Tone_Pin, Freq, PlayTime);
  delay(PlayTime+WaitTime);
}

//Error mode to tell something is going on.
void FlashAndBuzzAllActive()
{
  int NumActive;
  int NumBuzz=10;
  bool Activate=true;
  
  NumActive = CheckAllActive(nbj_raw_max);

  ActivateGreenLED(50);
  ActivateBlueLED(50);
  
  for (int j=0; j<=NumBuzz ; j++)
  {
    for (int i=0; i<=nbj_raw_max ; i++)
    {
      if(InputState[i]==HIGH)
      {
        if (Activate == true)
        {
          ActivateRedLight(i);
        }
        else
        {
          DeactivateRedLight(i);
        }
      }
    }
    tone(Tone_Pin, 2500, 200);
    delay(150);


    if (Activate==false) Activate= true;
    else Activate = false;
    
  }


  DeactivateGreenLED();
  DeactivateBlueLED();
  
}

