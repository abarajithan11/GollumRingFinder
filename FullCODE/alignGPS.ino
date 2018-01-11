
float Kp = 10, Kd = 0;
int error;
int lastError = 0;
int spdLimit = 100;


void alignToAngle(int angle)
{
  error = alignErrorCalc(angle);
  turn = Kp * error + Kd* (error - lastError);

  speedR = base_speed - turn;
  speedL = base_speed + turn;

  if (speedR > spdLimit) speedR = spdLimit;
  else if (speedR < -spdLimit) speedR = -spdLimit;
  if (speedL > spdLimit) speedL = spdLimit;
  else if (speedL < -spdLimit) speedL = -spdLimit;

  lastError = error;
  motorSpeed('l', speedL);        
  motorSpeed('r', speedR);
}

void gotoGPS()
{
  readGPSAvg();
  alignToAngle(courseAngle);
}
