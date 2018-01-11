void readIR()
{
  for(char s = 0; s < 8; s++)
  {
   int sum = 0;
    for(char i = 0; i < 4; i++)
    {
      sum += analogRead(irOrder[s]);
    }
    if((sum/4) > thres[s])
      irPanelVals[s] = 1;
    else
      irPanelVals[s] = 0;
  }
}


void caliberateIR()
{ lcd.clear();
  lcd.print("Give Black");

  while(!pushState())
  {  }  
  
  for(char s = 0; s < 8; s++)
  {
    int maxRead = 0;
    int minRead = 1023;
    for(char i = 0; i < 10; i++)
    {
      int reading = analogRead(irOrder[s]);
      if (reading > maxRead) maxRead = reading;
      if (reading < minRead) minRead = reading;
      delay(10);
    }
    whiteIR[s] = minRead;
  }

  lcd.clear();
  lcd.print("Give White");

  while(!pushState())
  {  }

  for(char s = 0; s < 8; s++)
  {
    int maxRead = 0;
    int minRead = 1023;
    for(char i = 0; i < 10; i++)
    {
      int reading = analogRead(irOrder[s]);
      if (reading > maxRead) maxRead = reading;
      if (reading < minRead) minRead = reading;
      delay(10);
    }
    blackIR[s] = maxRead;
  }

  for(char s = 0; s < 8; s++)
  {
    thres[s] = 0.5*(whiteIR[s] + blackIR[s]);
  }
  
  lcd.clear();
  lcd.print("IR Panel Caliberated!"); 
  delay(2000);
}
