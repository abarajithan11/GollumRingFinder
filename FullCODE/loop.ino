void loop()
{  
  long timeCount = millis();
  
  if(taskStatus ==0)    //Starting
  {
    startCalibrate();
    selectLocation();
  }

  if(taskStatus == 1)   //Go to the target location
  {
    obsAvoid2();
    if(!(timeCount % 10000))
    {
      gotoGPS();
    }
    detectLine();
  }

  if(taskStatus ==2) //Found the boundary of target location, Display
  {
    lineFound();
  }
  if(taskStatus ==3) //Found the boundary, align perpendicular to it
  {
    lineAlign();
  }
  if(taskStatus ==4) //Print Aligned
  {
    lineAligned();
  }
  if(taskStatus ==5) //Now Rotate and search for cylindar
  {
    rotateSearch();
  }
  if(taskStatus ==6) //Cylindar found. Move towards it
  {
    wallMeet3();
  }
  if(taskStatus ==7) //Met the cylindar wall. Turn to become parallel to the wall
  {
    passToParallel();
  }
  if(taskStatus ==8) //Follow the wall
  {
    wallFollow();
  }
  if(taskStatus ==9) //Entrance found
  {
    turnInside();
  }
  if(taskStatus ==10) //Move inside
  {
    moveInside();
  }
  if(taskStatus ==11) //Pickup the ring
  {
    pickUpRing();
  }
  if(taskStatus ==12) //Moving outside
  {
    moveOutside();
    latTarget = startLat;
    longTarget = startLong;
  }
  if(taskStatus ==13) //Go to the Starting point
  {
    obsAvoid2();
    if(!(timeCount % 10000))
    {
      gotoGPS();
    }
  }
  if(taskStatus ==14) //Task over. Stop and Beep
  {
    motorBreak();
    while(1)
    {
      beep();
    }
  }

}


