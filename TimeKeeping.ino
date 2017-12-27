unsigned long TakeTime()
{
  TimeStart=millis();
  return TimeStart;
}

unsigned long TimeDiffSeconds()
{
  return (millis()-TimeStart)/1000;
} 

unsigned long TimeDiff()
{
  return (millis()-TimeStart);
} 
