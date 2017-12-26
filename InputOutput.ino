//Reads all input pins, if HIGH, activate the OUTPUT. If at least one is active, return TRUE
bool ReadInputActivateOutput(int NbInputs)
{
  bool AtLeastOneHIGH=false;
  
  for (int i=0; i<=NbInputs ; i++)
  {
    if (ReadPlayerInput(i)==HIGH)
    {
      //Activate the output
      ActivateRedLight(i);
      AtLeastOneHIGH = true;
    }
  }
  return AtLeastOneHIGH;
}

//Returns HIGH or LOW
int ReadPlayerInput(int iPlayer)
{
  return digitalRead(PlayerInputPins[iPlayer]);
}

//Return first active player.  -1 is default if none active.  Player 1 is 0.
int FirstActive(int NbInputs)
{
  for (int i=0; i<=NbInputs ; i++)
  {
    if (ReadPlayerInput(i)==HIGH)
    {
      return i;
    }
  }
  return -1;
}

//Returns the number of active inputs.  0 is default if none.
int CheckAllActive(int NbInputs)
{
  int NumActive=0;
  for (int i=0; i<=NbInputs ; i++)
  {
    //Store in global input array
    InputState[i]=ReadPlayerInput(i);
    if (InputState[i]==HIGH)
    {
      NumActive++;
    }
  }
  return NumActive;
}

//Waits for all inputs to be non-active or MAX ITER, in which case, error mode.
void WaitForAllNonActive(int NbInputs)
{
  int max_iter = 60;
  int count = 0;
  
  do
  {
    count++;
    delay(15);
  }while(CheckAllActive(nbj_raw) !=0 && count<=max_iter);
  
  if(count >=max_iter)
  {
    FlashAndBuzzAllActive();
    WaitForAllNonActive(NbInputs);
  }

  TurnOffAllRedLights();
  
}

