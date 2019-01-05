//delay function to work in interrupts
//takes in a time in milliseconds
void timer(int period)
{
  int start = millis();
  //do nothing until the required milliseconds have elapsed
  //assume unaffected by rollover :/
  while(millis() - start < period);
}

