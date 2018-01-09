float RelativeError(float TestValue,float TrueValue)
{
  float Score;


  
  if (TrueValue !=0)
  {
    Score = 1 - (  abs( TrueValue-TestValue )  /  ( TrueValue) );
  }
  else
  {
    Score=0;
  }

  
  if (Score < 0) Score = 0;

/*
  LOG_GENERAL("\n");
  LOG_GENERAL("\n");
  LOG_GENERAL("Test:");
  LOG_GENERAL(TestValue);
  LOG_GENERAL("\n");
  LOG_GENERAL("True:");
  LOG_GENERAL(TrueValue);
  LOG_GENERAL("\n");
  LOG_GENERAL("Score:");
  LOG_GENERAL(Score);
  LOG_GENERAL("\n");
  LOG_GENERAL("\n");
*/
  return Score;
}



