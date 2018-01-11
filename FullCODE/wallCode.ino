float wError;
float wLastError = 0;
float wKp = 5, wKd = 3;
int goInDelay = 1500;
int goOutDelay = 1800;

void wallFollow()
{  
  if(cylColor == 'B')
  {
    obsFcm = sonarObsF.convert_cm(sonarObsF.ping_median(5,400));
    if(obsFcm) //White Cylindar found
    motorBreak();
    //***********************************************************************
  }


  
  wallLFcm = sonarWallLF.convert_cm(sonarWallLF.ping_median(5,wallMaxDist));
  delay(33);
  wallLBcm = sonarWallLB.convert_cm(sonarWallLB.ping_median(5,wallMaxDist));
  delay(33);

  Serial.println(wallLFcm);
  Serial.println(wallLBcm);

  if(wallLBcm && (wallLFcm > 30 || !wallLFcm))
  {
    motorRevBreak();
    delay(1000);

    lcd.clear();
    lcd.print("HOLE FOUND");

    
    turnInside();
    return;
  }
  
  if (!wallLFcm  || !wallLBcm)
  { 
    motorBreak();
    goto endOfLoop;
  }

  wError = (wallSetDist - wallLFcm) + 0.9* float(wallLBcm - wallLFcm);  
  turn = wKp * wError + wKd * (wError - wLastError);  

  speedR = base_speed + turn;
  speedL = base_speed - turn;

  if (speedR > 200) speedR = 200;
  else if (speedR < -200) speedR = -200;
  if (speedL > 200) speedL = 200;
  else if (speedL < -200) speedL = -200;

  wLastError = wError;

  motorSpeed('l', speedL);        
  motorSpeed('r', speedR);
  //Serial.println(turn);

  endOfLoop: 
  ;
}
void wallMeet3() //Finall WallMeet
{
  if((sonarObsR.convert_cm(sonarObsR.ping_median(5,obsLRMaxDist))) || (sonarObsF.convert_cm(sonarObsF.ping_median(5,obsFMaxDist))) || (sonarObsL.convert_cm(sonarObsL.ping_median(5,obsLRMaxDist))))
  {
    motorRevBreak();
    while(!(sonarWallLF.convert_cm(sonarWallLF.ping_median(5,wallMaxDist)) && sonarWallLB.convert_cm(sonarWallLB.ping_median(5,wallMaxDist))))
    {
      rotate(rotSpeed);
      delay(33);
    }
    
    motorBreak();
    delay(1000);
    
    if (!sonarObsF.convert_cm(sonarObsF.ping_median(5,obsFMaxDist)) && !sonarObsL.convert_cm(sonarObsL.ping_median(5,obsLRMaxDist)))
    if (sonarWallLF.convert_cm(sonarWallLF.ping_median(5,wallMaxDist)) && sonarWallLB.convert_cm(sonarWallLB.ping_median(5,wallMaxDist)))
    taskStatus =7;

    lcd.clear();
    lcd.print("Got wall");
  }
}

void passToParallel()
{
  while((abs(sonarWallLB.convert_cm(sonarWallLB.ping_median(5,wallMaxDist))- sonarWallLF.convert_cm(sonarWallLF.ping_median(5,wallMaxDist))))>3)
  {
    rotate(rotSpeed);
    delay(rotDelay);
    motorBreak();
    delay(50);
  }
  lcd.clear();
  lcd.print("Now Parallel");
  
  taskStatus = 8;
}

#define insideFwdDelay 1300
#define insideRotTimes 95

void turnInside()
{

  Serial.print("turning");
  drive(50);
  delay(insideFwdDelay);
  motorBreak();
  
  for(int i = 0; i < insideRotTimes; i++)
  {
    rotStop();
    taskStatus  = 10;
  }
  
}

void moveInside()
{
  drive(base_speed/2);
  delay(goInDelay);
  taskStatus  = 11;
}

void moveOutside()
{
  drive(-base_speed/2);
  delay(goOutDelay);
  taskStatus  = 13;
}

