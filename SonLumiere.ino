
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

void PlayNote(int Tone_Pin, float Freq, float PlayTime, float WaitTime)
{
  tone(Tone_Pin, Freq, PlayTime);
  delay(PlayTime+WaitTime);
}

void PlayNoteWithLight(int Tone_Pin, float Freq, float PlayTime, float WaitTime,int Player)
{
  ActivateRedLight(Player);
  tone(Tone_Pin, Freq, PlayTime);
  delay(PlayTime);
  DeactivateRedLight(Player);
  delay(WaitTime);
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

void TurnOffAllLights()
{
  TurnOffAllRedLights();
  DeactivateGreenLED();
  DeactivateBlueLED();
}


void TurnOnAllLights()
{
  TurnOnAllRedLights();
  ActivateGreenLED(100);
  ActivateBlueLED(100);
}

void ControlAllLights(bool RedState, int BlueLevel, int GreenLevel)
{
  if (BlueLevel>100) BlueLevel=100;
  if (BlueLevel<0) BlueLevel=0;
  if (GreenLevel>100) GreenLevel=100;
  if (GreenLevel<0) GreenLevel=0;

  if (RedState) TurnOnAllRedLights();
  else TurnOffAllRedLights();
  
  ActivateGreenLED(GreenLevel);
  ActivateBlueLED(BlueLevel);
}

void IlluminateTeamRedLights(int Team)
{
  for(int i=0 ; i<=nbj_raw ; i++)
  {
    if(Equipes[i]==Team)
    {
      ActivateRedLight(i);
    }
  }
}


//0->100
void MoveDEDUFlag(float PercTravel)
{
  if (PercTravel < 0)
  {
    PercTravel=0;
  }
  else if (PercTravel > 100)
  {
    PercTravel=100;
  }
  
  int MinPos=Servo_LowPos;
  int MaxPos=Servo_HighPos;
  int Delta=MaxPos-MinPos;
  myservo.write(MinPos + (PercTravel/100)*Delta);
}

int ServoAngle()
{
  return myservo.read();
}


//0->100
float ServoAnglePercent()
{
  float MinPos=Servo_LowPos;
  float MaxPos=Servo_HighPos;

  float Percent = ((float)myservo.read()-MinPos)/(MaxPos-MinPos);
  return Percent*100;
}






