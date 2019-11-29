//Sets or Resets the player red LED based on iState.
void SetRedLight(int iPlayer, bool iOnState)
{
  if (iOnState) ActivateRedLight(iPlayer);
  else DeactivateRedLight(iPlayer);
}

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
  else if (Value>100)
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
    if (!ReadPlayerInput(i))
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
  if (NbMax+NbOffset>9)
  {
    NbMax=9;
    NbOffset=0;
  }
  //Clignote + Son
  for (int i=0; i<=NbMax; i++)
  {
    //Light and sound for valid players.
    ActivateRedLight(i);
    ActivateRedLight(i+NbOffset);
    Tone_Frequency=FreqStart + FreqIncrease * i;
    tone(Tone_Pin, Tone_Frequency, 50);
    delay(100);
  }
  
  delay(500);
  TurnOffAllRedLights();
  delay(500);
}

void PlayNote(float Freq, float PlayTime, float WaitTime)
{
  tone(Tone_Pin, Freq, PlayTime);
  delay(PlayTime+WaitTime);
}

void PlayNoteWithLight(float Freq, float PlayTime, float WaitTime,int Player)
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
  
  NumActive=CheckAllActive(nbj_raw_max);

  ActivateGreenLED(50);
  ActivateBlueLED(50);
  
  for (int j=0; j<=NumBuzz; j++)
  {
    for (int i=0; i<=nbj_raw_max; i++)
    {
      if (InputState[i])
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
    Buzz();
    delay(150);


    if (Activate==false) Activate= true;
    else Activate=false;
    
  }


  DeactivateGreenLED();
  DeactivateBlueLED();
  
}

void Buzz()
{
  tone(Tone_Pin, 2500, 200);
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
  for (int i=0; i<=nbj_raw; i++)
  {
    if (Equipes[i]==Team)
    {
      ActivateRedLight(i);
    }
  }
}

void IncrementDEDUFlag(float PercTravelIncrement)
{
  MoveDEDUFlag(ServoAnglePercent()+PercTravelIncrement);
}

//0->100
void MoveDEDUFlag(float PercTravel)
{
  if (PercTravel<0)
  {
    PercTravel=0;
  }
  else if (PercTravel>100)
  {
    PercTravel=100;
  }
  
  int MinPos=Servo_LowPos;
  int MaxPos=Servo_HighPos;
  int Delta=MaxPos-MinPos;
  Servo_BrasDEDU.write(MinPos + (PercTravel/100)*Delta);
}

int ServoAngle()
{
  return Servo_BrasDEDU.read();
}


//0->100
float ServoAnglePercent()
{
  float MinPos=Servo_LowPos;
  float MaxPos=Servo_HighPos;

  float Percent=((float)Servo_BrasDEDU.read()-MinPos)/(MaxPos-MinPos);
  return Percent*100;
}


void ReadySound(int SoundTime)
{
  tone(Tone_Pin, 1700,SoundTime);
  delay(2*SoundTime);
  tone(Tone_Pin, 1700,SoundTime);
  delay(2*SoundTime);
  tone(Tone_Pin, 2820,SoundTime*1.5);
  delay(SoundTime*1.5);
}

void WinnerSound()
{
  for (int i=1; i<=120; i++)
  {
    Tone_Frequency=500 + 30 * i;
    tone(Tone_Pin, Tone_Frequency, 3);
    delay(3);
  }
  noTone(Tone_Pin);
  delay (500);
}

void OneUp()
{
  tone(Tone_Pin,1319,125);
  delay(130);
  tone(Tone_Pin,1568,125);
  delay(130);
  tone(Tone_Pin,2637,125);
  delay(130);
  tone(Tone_Pin,2093,125);
  delay(130);
  tone(Tone_Pin,2349,125);
  delay(130);
  tone(Tone_Pin,3136,125);
  delay(125);
  noTone(Tone_Pin);
}

void MultiLooserSoundAndLight(bool Loosers[nbj_max])
{
  ActivateBlueLED(10);
  
  for (int j=0; j<nbj_max;j++)
  {
    if (Loosers[j]) ActivateRedLight(j);
  }
  
  for (int i=0; i<80; i++)
  {
    Tone_Frequency=2000 - 20 * i;
    tone(Tone_Pin, Tone_Frequency);
    delay(10);
  }
  noTone(Tone_Pin);

  //Identify the Loosers
  for (int e=1; e<=4; e++)
  {
    for (int j=0; j<nbj_max;j++)
    {
      if (Loosers[j]) ActivateRedLight(j);
    }
    delay(500);
    for (int j=0; j<nbj_max;j++)
    {
      if (Loosers[j]) DeactivateRedLight(j);
    }
    delay(500);
  }
  
  TurnOffAllRedLights();
  DeactivateBlueLED();
}

void SingleLooserSoundAndLight(int iPlayer)
{
  ActivateBlueLED(10);
  ActivateRedLight(iPlayer);
  for (int i=0; i<80; i++)
  {
    Tone_Frequency=2000 - 20 * i;
    tone(Tone_Pin, Tone_Frequency);
    delay(10);
  }
  noTone(Tone_Pin);

  //Identify the Looser
  for (int e=1; e<=4; e++)
  {
    ActivateRedLight(iPlayer);
    delay(500);
    DeactivateRedLight(iPlayer);
    delay(500);
  }
  
  TurnOffAllRedLights();
  DeactivateBlueLED();
}

void LooserSoundAndLight(int iPlayer, bool extratoggles)
{
  for (int i=0; i<2; i++)
  {
    ActivateRedLight(iPlayer);
    tone(Tone_Pin,500,500);
    delay(500);
    DeactivateRedLight(iPlayer);
    delay(500);
  }

  if (extratoggles)
  {
    for (int i=0; i<2; i++)
    {
      ActivateRedLight(iPlayer);
      delay(500);
      DeactivateRedLight(iPlayer);
      delay(500);
    }
  }
}

void AllLoosersSoundAndLight()
{
  ActivateBlueLED(20);
    
  //Sound for Loosers.
  for (int i=0; i<4; i++)
  {
    tone(Tone_Pin,800,700);
    DeactivateBlueLED();
    TurnOnAllRedLights();
    delay(800);
    TurnOffAllRedLights();
    ActivateBlueLED(20);
    delay(800);
  }
  
  TurnOffAllLights();
}

void MultipleWinnerSoundAndLight(bool ActivePlayers[])
{
  TurnOffAllLights();
  for(int i=0; i<sizeof(ActivePlayers); i++)
  {
    if(ActivePlayers[i]) ActivateRedLight(i);
  }
  
  for (int j=0; j<2; j++)
  {
    WinnerSound();
    delay(350);
    TurnOffAllRedLights();
    ActivateGreenLED(100);
    delay(350);
    for(int i=0; i<sizeof(ActivePlayers); i++)
    {
      if(ActivePlayers[i]) ActivateRedLight(i);
    }
    ActivateGreenLED(0);
  }
  TurnOffAllLights();
}

void WinnerSoundAndLight(int iPlayer)
{
  ActivateGreenLED(0);
  ActivateRedLight(iPlayer);
  for (int i=0; i<2; i++)
  {
    WinnerSound();
    delay(350);
    DeactivateRedLight(iPlayer);
    ActivateGreenLED(100);
    delay(350);
    ActivateRedLight(iPlayer);
    ActivateGreenLED(0);
  }
}

void SonTestMode()
{
  PlayNote(2500,200,20);
  PlayNote(1000,200,20);
  PlayNote(2500,200,20);
  PlayNote(1000,200,20);
}

void TicTac(int SilenceTime, int Repeats)
{
  if (Repeats<0) Repeats=1;
  for (int i=0; i<Repeats; i++)
  {
    tone(Tone_Pin,250,10);
    delay(SilenceTime);
    tone(Tone_Pin,700,10);
    delay(SilenceTime);
  }
}

void MaxRandom(int NumTimes, bool AllOff)
{
  MoveDEDUFlag(random(0,101));
  do
  {
    for (int i=0;i<10; i++)
    {
      if (random(2)==0)
      {
        ActivateRedLight(i);
      }
      else
      {
        DeactivateRedLight(i);
      }
    }
    IncrementDEDUFlag(random(21)-10);
    tone(Tone_Pin,random(50,1800),random(20,100));
    ActivateBlueLED(random(0,100));
    ActivateGreenLED(random(0,100));
    delay(200);
  }while(NumTimes-->=0);

  if (AllOff)
  {
    ControlAllLights(false,0,0);
    MoveDEDUFlag(0);
  }
}

