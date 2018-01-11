char cylColor = ' ';

void rotateSearch()
{
  for (char i = 0; i < halfCircleTimes; i++)
  {
    rotate(200);
    delay(60);
    motorBreak();
    delay(50);
  }

  //Now it faces the left of the line

  for (char i = 0; i < 2*halfCircleTimes; i++)
  {
    rotate(-200);
    delay(60);
    motorBreak();

    if(sonarObsF.convert_cm(sonarObsF.ping_median(5,400)))
   {
    taskStatus = 6;
    beep();
    return;
   }
    
  }

    for (char i = 0; i < 2*halfCircleTimes; i++)
  {
    rotate(100);
    delay(100);
    motorBreak();
    delay(50);

    if(sonarObsF.convert_cm(sonarObsF.ping_median(5,400)))
   {
    taskStatus = 6;
    return;
   }
    
  }
}

void beep()
{
  analogWrite(13, 150);
  delay(500);
  analogWrite(13,0);
  delay(500);
}

void rotStop()
{
  rotate(200);
  delay(rotDelay);
  motorBreak();
  delay(50);
}

