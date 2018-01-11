bool abc = 0;
void lcdGPS()
{
  if(abc)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(latNow,8);
    lcd.setCursor(0,1);
    lcd.print(longNow,8);
  }
  if(!abc)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(alignErrorCalc(courseAngle));
    lcd.setCursor(5,0);
    lcd.print(nSats);
    lcd.setCursor(0,1);
    lcd.print(distanceTo);
  }
  abc = !abc;
}

int targetNo = -1;

void selectLocation()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Select Loc");
  delay(1000);

  for(char i = 0 ; i < 3; i++)
  {

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(arrLats[i],8);
    lcd.setCursor(0,1);
    lcd.print(arrLongs[i],8);

    lcd.setCursor(15,0);
    lcd.print(i);

    for (char j = 0; j < 80; j++)
    {
      if(pushState()) break;
      delay(50);
    }
  

    if(pushState())
    {
      delay(500);
      if(pushState())
      {
        latTarget = arrLats[i];
        longTarget = arrLongs[i];
        targetNo = i;
        lcd.clear();
        lcd.print("Loc 1 Chosen");
        lcd.setCursor(4,0);
        lcd.print(i+1);
        delay(2000);
        return;
      }
      continue;
    }
    if(i == 2) i = -1;
  }
  
}

void startCalibrate()
{
  lcd.clear();
  lcd.print("Gollum Starts....");
  delay(3000);
  lcd.clear();
  lcd.print("Skip Calibrate?");

  for (char j = 0; j < 150; j++)
  {
    if(pushState()) return;
    delay(50);
  }  
  caliberateIR();
}

void setTarget()
{
  if(pushState())
  {
    delay(500);
    if(pushState())
    {
      delay(1000);
      readGPSAvg();
      
      latTarget = latNow;
      longTarget = longNow;
      
      lcd.clear();
      lcd.print("Target Set");
      
      analogWrite(13, 150);
      delay(500);
      analogWrite(13, 0);
    }
  }
  
}

void displayGPSInfo()
{
  readGPSAvg();
  
  Serial.print(F("Location: ")); 
  Serial.print(latNow,8);
  Serial.print(F(","));
  Serial.println(longNow,8);
  Serial.print("Sats: ");
  Serial.println(nSats);

  Serial.print(F("Course: ")); 
  Serial.println(courseAngle);

  Serial.print(F("Distance To: ")); 
  Serial.println(distanceTo);
  
  Serial.println();

}

void obsServoDirn(char dirn)
{
  if (dirn == 'F')
  {
    servoLObs.write(slFwd);
    servoRObs.write(srFwd);
  }
  else if (dirn == 'O')
  {
    servoLObs.write(slObs);
    servoRObs.write(srObs);
  }
}
