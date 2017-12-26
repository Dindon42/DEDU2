
//Turn off all the reds
void TurnOffAllRedLights()
{
  for (int i=0; i<=nbj_raw_max;i++)
  {
    digitalWrite(PlayerOutputPins[i], LOW);
  }
}

//Turn ON all the reds
void TurnOnAllRedLights()
{
  for (int i=0; i<=nbj_raw_max;i++)
  {
    digitalWrite(PlayerOutputPins[i], HIGH);
  }
}

void ClignoteEtSon(int NbMax,int FreqStart, int FreqIncrease, int NbOffset)
{
  //Clignote + Son
  for (int i = 0 + NbOffset; i <= NbMax; i++)
  {
    //Light and sound for valid players.
    digitalWrite(PlayerOutputPins[i], HIGH);
    Tone_Frequency = FreqStart + FreqIncrease * i;
    tone(Tone_Pin, Tone_Frequency, 150);
    delay(150);
  }
}

void PlayNote(int Tone_Pin, double Freq, double PlayTime, double WaitTime)
{
  tone(Tone_Pin, Freq, PlayTime);
  delay(PlayTime+WaitTime);
}
