
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
      if (digitalRead(InPinStart+InPinInterval*i) == HIGH)
      {
        digitalWrite(OutPinStart+OutPinInterval*i, HIGH);
      }
      else
      {
        digitalWrite(OutPinStart+OutPinInterval*i, LOW);
      }
    }
  }
}
