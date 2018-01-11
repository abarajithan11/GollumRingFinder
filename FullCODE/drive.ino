#define fLTune 0.83
#define bLTune 1
#define rRTune 1

void drive(int motor_speed)
{
  motorSpeed('l', motor_speed);
  motorSpeed('r', motor_speed);
}

void motorSpeed(char side, int motor_speed) 
{
  int newSpeed;
  if (side == 'l') 
  {
    newSpeed = fLTune*motor_speed;
    if(newSpeed >255) newSpeed = 255;
    if (motor_speed > 0) 
    {
      digitalWrite(linB1, LOW);   digitalWrite(linB2, LOW);
      digitalWrite(linF1, HIGH);    digitalWrite(linF2, HIGH);
      analogWrite(lEn1, newSpeed); analogWrite(lEn2, newSpeed);
    }
    else 
    {
      digitalWrite(linB1, HIGH);    digitalWrite(linB2, HIGH);
      digitalWrite(linF1, LOW);   digitalWrite(linF2, LOW);
      analogWrite(lEn1, -newSpeed);analogWrite(lEn2, -newSpeed);
    }
  }
  else 
  {
    if (motor_speed > 0) 
    {
      digitalWrite(rinF1, HIGH);    digitalWrite(rinF2, HIGH);
      digitalWrite(rinB1, LOW);   digitalWrite(rinB2, LOW);
      analogWrite(rEn1, motor_speed); analogWrite(rEn2, motor_speed);
    }
    else {
      digitalWrite(rinF1, LOW);   digitalWrite(rinF2, LOW);
      digitalWrite(rinB1, HIGH);    digitalWrite(rinB2, HIGH);
      analogWrite(rEn1, -motor_speed);  analogWrite(rEn2, -motor_speed);
    }
  }
}




void motorBreak() 
{
  digitalWrite(rinF1, HIGH);
  digitalWrite(rinB1, HIGH);
  analogWrite(rEn1, 0);
  digitalWrite(linB1, HIGH);
  digitalWrite(linF1, HIGH);
  analogWrite(lEn1, 0);

  digitalWrite(rinF2, HIGH);
  digitalWrite(rinB2, HIGH);
  analogWrite(rEn2, 0);
  digitalWrite(linB2, HIGH);
  digitalWrite(linF2, HIGH);
  analogWrite(lEn2, 0);
}

void motorRevBreak() 
{
    highBreak();
    motorSpeed('l', -150);
    motorSpeed('r', -150);
    delay(70);
    highBreak();

}

void highBreak()
{
  digitalWrite(rinF1, HIGH);
  digitalWrite(rinB1, HIGH);
  analogWrite(rEn1, 200);
  digitalWrite(linB1, HIGH);
  digitalWrite(linF1, HIGH);
  analogWrite(lEn1, 200);

  digitalWrite(rinF2, HIGH);
  digitalWrite(rinB2, HIGH);
  analogWrite(rEn2, 200);
  digitalWrite(linB2, HIGH);
  digitalWrite(linF2, HIGH);
  analogWrite(lEn2, 200);
}

void rotate(int motor_speed)      //Positve -> anticlockwise
{
  motorSpeed('r', rRTune*motor_speed);
  motorSpeed('l', -motor_speed);
}

