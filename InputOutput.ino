//Reads all input pins, if HIGH, activate the OUTPUT. If at least one is active, return TRUE
bool ReadInputActivateOutput(int NbInputs)
{
  int val=0;
  bool AtLeastOneHIGH=false;
  
  for (int i=0; i<=NbInputs ; i++)
  {
    val=digitalRead(PlayerInputPins[i]);
    if (val==HIGH)
    {
      //Activate the output
      digitalWrite(PlayerOutputPins[i],HIGH);
      AtLeastOneHIGH = true;
    }
  }
  return AtLeastOneHIGH;
}

int FirstActive(int NbInputs)
{
  int val=0;

  for (int i=0; i<=NbInputs ; i++)
  {
    val=digitalRead(PlayerInputPins[i]);
    if (val==HIGH)
    {
      return i;
    }
  }
  return -1;
}

//Returns the number of active inputs.
int CheckAllActive(int NbInputs)
{
  int NumActive=0;
  Serial.println(NumActive);
  for (int i=0; i<=NbInputs ; i++)
  {
    val=digitalRead(PlayerInputPins[i]);
    InputState[i]=val;
    if (val==HIGH)
    {
      NumActive++;
    }
  }
  return NumActive;
}

