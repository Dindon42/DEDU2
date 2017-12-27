float RelativeError(float TestValue,float TrueValue)
{
  float Score;
  Score = 1 - (  abs( TrueValue-TestValue )  /  ( 1+TrueValue) );
  if (Score < 0) Score = 0;

  return Score;
}



