#define rotSpeed 120

void obsAvoid2()
{
  obsServoDirn('O');
  
  int dist = 0;
  long timeStart = millis();
    while (dist = sonarObsF.ping_cm())
    {
      if (dist < obsMinDist) motorRevBreak();
      motorBreak();      
      if(!sonarObsF.convert_cm(sonarObsF.ping_median(5,obsFMaxDist))) break;

      isObsFound = true;
      rotate(-rotSpeed);
      Serial.println("F");
      delay(100);
    }
    while (dist = sonarObsR.ping_cm())
    {
      if (dist < obsMinDist) motorRevBreak();
      motorBreak();
      
      if(!sonarObsR.convert_cm(sonarObsR.ping_median(5,obsLRMaxDist))) break;

      isObsFound = true;
      rotate(rotSpeed);
      Serial.println("R");

      delay(100);
    }
    while (dist = sonarObsL.ping_cm())
    {
      if (dist < obsMinDist) motorRevBreak();
      motorBreak();
      
      if(!sonarObsL.convert_cm(sonarObsL.ping_median(5,obsLRMaxDist))) break;

      isObsFound = true;
      rotate(-rotSpeed);
      Serial.println("L");

      delay(100);
    }
    if(isObsFound)
    {
      drive(base_speed);
      delay(1500);
      isObsFound = false;
    }

    //Simulate GPS
    delay(400);
    drive(base_speed);
    
    //gotoGPS();
}
