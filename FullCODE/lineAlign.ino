#define rotSpeed 120

int lineLost()
{
  drive(-150);
  delay(50);
  motorBreak();
  return -1;
}

int lineLost1()
{
  lcd.clear();
  lcd.print("Line Lost");
  
  long t1 = millis();
  while(1)
  {

    readIR();
    
    char sensDet = 0;
    for(char s = 0; s < 8; s++)
    {
      if (irPanelVals[s]) sensDet++;
    }
    if(sensDet >= 2)
    {
      return 1;
    }
    drive(-120);
    delay(50);
    motorBreak();
    delay(100);
  }
  lcd.clear();
  lcd.print("LINE Found Again");
  delay(2000);
}

int lineAlign()
{
  while(!(irPanelVals[0] && irPanelVals[1] && irPanelVals[2] && irPanelVals[3] && irPanelVals[4] && irPanelVals[6] && irPanelVals[7])) 
  {
    readIR();
    printIR();
    
    if(lineFrom == 'l')
    {
      rotate(rotSpeed);
      delay(100);
      motorBreak();

      lcd.clear();
      lcd.print("Rotating");
    }
    else if (lineFrom == 'r')
    {
      rotate(-rotSpeed);
      delay(100);
      motorBreak();

      lcd.clear();
      lcd.print("Rotating");
    }

  }
  taskStatus = 4;
  return 1;
}

void lineAligned()
{
    lcd.clear();
    lcd.print("LINE ALIGNED");
    motorBreak();
    analogWrite(13, 150);
    delay(500);
    analogWrite(13, 0);
    delay(500);
    analogWrite(13, 150);
    delay(500);
    analogWrite(13, 0);
    delay(500);

    rotateSearch();
}


