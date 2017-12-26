unsigned long TakeTime()
{
  TimeStart=millis();
  return TimeStart;
}

unsigned long TimeDiff()
{
  return (millis()-TimeStart)/1000;
}
  
