void readCompassAvg()                       //Gets 11-median 5-avegerage of compass readings  ExecTime = 850 ms
{
  float headingArr[compassN] = {0};
  float headTemp = 0;
  for(int i = 0; i < compassN; i++)
  {
    headTemp = Compass.GetHeadingDegrees();
    if (headTemp > 180) headTemp  = headTemp - 360; 
    
    headingArr[i] = headTemp;                //Degrees [0,360]
  }

  heading = getMedian(headingArr, compassN,compassK);          //Median
  if (heading > 180) heading  = heading - 360;                 //Degrees [-180,180]
  heading = round(heading);

Serial.print("Heading: "); Serial.println(heading);
//  lcd.clear();
//  lcd.print(heading);
}


void readGPSAvg()                               //Gets the median of 11 non zero location values and the average number of sattelites. ExecTime = 850 ms
{
  float latArray[gpsN] = {0};
  float longArray[gpsN] = {0};
  int totSats = 0;

  int i = 0;
  while(i < gpsN)
  {
    while (Serial1.available() > 0)
      if (gps.encode(Serial1.read()))
      {        
        totSats += gps.satellites.value();
        latArray[i] = gps.location.lat();
        longArray[i] = gps.location.lng();
        if(gps.location.isValid() && (gps.satellites.value() > nMinSats)) i++;         //Until location becomes valid, lat and long are written on same position in array
      }
      delay(10);
  }

  latNow = getMedian(latArray, gpsN,  gpsK);
  longNow = getMedian(longArray, gpsN,  gpsK);
  nSats = totSats/gpsN;
  
  courseAngle = round(TinyGPSPlus::courseTo(latNow, longNow, latTarget, longTarget));
  if (courseAngle > 180) courseAngle -= 360;
  
  distanceTo = TinyGPSPlus::distanceBetween(latNow, longNow, latTarget, longTarget);  
    
  if (millis() > 5000 && gps.charsProcessed() < 10)               //If GPS not detected after 5 seconds
  {
    Serial.println(F("No GPS detected"));
    while(true);
  }
  lcdGPS();
}



//void readGPS()                               //Gets the median of 11 non zero location values and the average number of sattelites. ExecTime = 850 ms
//{
//  while (Serial1.available() > 0)
//      if (gps.encode(Serial1.read()))
//      {        
//        nSats = gps.satellites.value();
//        latNow = gps.location.lat();
//        longNow = gps.location.lng();
//      }
//  
//  courseAngle = round(TinyGPSPlus::courseTo(latNow, longNow, latTarget, longTarget));
//  if (courseAngle > 180) courseAngle -= 360;
//  
//  distanceTo = TinyGPSPlus::distanceBetween(latNow, longNow, latTarget, longTarget);  
//    
//  if (millis() > 5000 && gps.charsProcessed() < 10)               //If GPS not detected after 5 seconds
//  {
//    Serial.println(F("No GPS detected"));
//    while(true);
//  }
//  lcdGPS();
//}
