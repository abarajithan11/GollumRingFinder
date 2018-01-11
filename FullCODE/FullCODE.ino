//Author: Aba
//Group : 5



#include <TinyGPS++.h>
#include <HMC5883L_Simple.h>
#include <Wire.h>
#include <ArduinoSort.h>
#include <LiquidCrystal.h>
#include <NewPing.h> 
#include <Servo.h>

int base_speed = 180;
char taskStatus = 0;

#define lineLostDelay 100
#define halfCircleTimes 25
#define rotDelay  18

#define obsMaxDist        50
#define obsFMaxDist       50
#define obsLRMaxDist      40
#define obsMinDist        15

#define wallMaxDist       50
#define wallSetDist       10
#define wallStopDist      5
#define wallSharpTurn     20

#define push 44

//**************************************Motor Pins
#define lEn1 9    //Gray (A)
#define linB1 33    //Black b1
#define linF1 31    //White b2

#define lEn2 10   //Orange (A)
#define linF2 37    //Red  f1
#define linB2 35    //Brown f2-


#define rEn1 11   //Blue (B)
#define rinB1 30      //Red f1
#define rinF1 32    //Brown f2

#define rEn2 12   //Purple (B)
#define rinB2 36    //Yellow b1
#define rinF2 34    //Orange b2

//************************************** LCD Pins

 #define lcdRS 39
 #define lcdE 41
 #define lcd4 43
 #define lcd5 42
 #define lcd6 47
 #define lcd7 49
 #define lcdV0 6

 //********************************LINE code

unsigned char irOrder [] = {A1,A7,A6,A5,A4,A0,A3,A2};//{A2,A3, A0,A4,A5,A6,A7,A1}; 
int thres[] = {0,0,0,0,0,0,0,0};
int whiteIR[] = {0,0,0,0,0,0,0,0};
int blackIR[] = {0,0,0,0,0,0,0,0};
int irPanelVals[8];


//********************Newvar
float courseAngle;
float distanceTo;
float alignError;

float latTarget =0;
float longTarget=0;

float startLat = 6.7981586, startLong = 79.898995;

float arrLats[] = {6.7979896,6.7981908,6.7983168};
float arrLongs[] = {79.8989044,79.8991586,79.8989861};


int nSats = 0;

#define nMinSats 3
#define compassN 3
#define compassK 1
#define gpsN 5
#define gpsK 3

float latNow, longNow;

//***************************************Ultrasonic Pins
// * Wall Front
#define trigWallLF 24 //
#define echoWallLF 22
// * Wall back
#define trigWallLB 26
#define echoWallLB 28

// * Obstracle Right
#define trigObsR 8 
#define echoObsR 7
// * Obstracle Left
#define trigObsL A13 
#define echoObsL A14
// * Obstracle Front
#define trigObsF 14
#define echoObsF 15

//************************************Obs Servo Pins & Vals

#define servoRObsPin 45
#define servoLObsPin 46
#define srFwd 26
#define srObs 2
#define slFwd 78
#define slObs 105

//Sonar Readings
int wallLFcm, wallLBcm, obsRcm, obsLcm, obsFcm;

NewPing sonarObsR(trigObsR, echoObsR, obsLRMaxDist);
NewPing sonarObsL(trigObsL, echoObsL, obsLRMaxDist);
NewPing sonarObsF(trigObsF, echoObsF, obsFMaxDist);

NewPing sonarWallLF(trigWallLF, echoWallLF, wallMaxDist);
NewPing sonarWallLB(trigWallLB, echoWallLB, wallMaxDist);

//Drive Variables
char obsDirn;
bool isObsTooClose;
bool isObsFound = false;

//Obs Servos
Servo servoRObs;
Servo servoLObs;


//Drive Variables
int turn, speedL, speedR;

//GPS
TinyGPSPlus gps;


float targetAngle;

HMC5883L_Simple   Compass;
//Compass align
float heading = 0;
int headPIDerror;
int headLastError = 0;

//LCD
LiquidCrystal lcd(lcdRS, lcdE, lcd4, lcd5, lcd6, lcd7);

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(linF1, OUTPUT);
  pinMode(linB1, OUTPUT);
  pinMode(lEn1, OUTPUT);
  pinMode(rinF1, OUTPUT);
  pinMode(rinB1, OUTPUT);
  pinMode(rEn1, OUTPUT);

  pinMode(linF2, OUTPUT);
  pinMode(linB2, OUTPUT);
  pinMode(lEn2, OUTPUT);
  pinMode(rinF2, OUTPUT);
  pinMode(rinB2, OUTPUT);
  pinMode(rEn2, OUTPUT);


  //Set Initial speed
  speedL = speedR = base_speed;

    //Init Compass
  Wire.begin();

  Compass.SetDeclination(-2, 11, 'W');                //Magnetic Declination in Uni Grounds
  Compass.SetSamplingMode(COMPASS_SINGLE);            //Single Measurement mode
  Compass.SetScale(COMPASS_SCALE_130);                //scale is 130. If noise, increase
  Compass.SetOrientation(COMPASS_HORIZONTAL_X_NORTH); // y on silkscreen = North -> 0


  servoRObs.attach(servoRObsPin);
  servoLObs.attach(servoLObsPin);

  
  lcd.begin(16, 2);
  analogWrite(lcdV0,120); // Set LCD Contrast
}

bool pushState()
{
  if (!digitalRead(push))
  {
    delay(50);
    if (!digitalRead(push))
      return 1;
    else
      return 0;
  }
  else return 0;
}


