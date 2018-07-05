/*****************************
//Viking Example
//2015-06-04 RoboLink
******************************/
#include <SmartInventor.h>

const byte s3 = 3;
const byte s2 = 2;
const byte s1 = 1;

unsigned char speed = 100;
unsigned char nowSensor = 0;
unsigned char oldSensor = 0;

unsigned char shipDirectiion = 0;

unsigned char shipSpeed = 0;
unsigned char sucessCount = 0;
unsigned char speedCheck = 100;

unsigned char MoveSpeed = 15;
unsigned char maxMoveSpeed = 30;
unsigned char maxShipSpeed = 15;
unsigned char speedControl = 3;

word  selectLevelA0 = 0;
word  selectLevelA1 = 0;
word  selectLevelA2 = 0;

word  sensorOffset = 100;

void setup()
{
  delay(500);

  //□ □ □ □ □ □ □ □
  //11,12,13,14,15,16,17,18
  //Led Output
  for (int thisPin = 11; thisPin <= 18; thisPin++)   {
    pinMode(thisPin, OUTPUT);
  }

  //Led OFF
  for (int thisPin = 11; thisPin <= 18; thisPin++)   {
    digitalWrite(thisPin, LOW);
  }

  SmartInventor.DCMotorUse();

  selectLevelA0 = SmartInventor.SensorCalibration(A0) - sensorOffset;
  selectLevelA1 = SmartInventor.SensorCalibration(A1) - sensorOffset;
  selectLevelA2 = SmartInventor.SensorCalibration(A2) - sensorOffset;

  if (F_CPU == 16000000UL)
  {
    MoveSpeed = 15;
    maxMoveSpeed = 30;
    maxShipSpeed = 1; //stop delay
    speedControl = 3;
  }
  else if (F_CPU == 7372800UL)
  {
    MoveSpeed = 15;
    maxMoveSpeed = 35;
    maxShipSpeed = 2; //stop delay
    speedControl = 2;
  }
}

void loop()
{
  /******************SensorCheck**************************************/
   word leftSensorValue = analogRead(A0);
  word centerSensorValue = analogRead(A1);
  word rightSensorValue = analogRead(A2);

  if (leftSensorValue < selectLevelA0)
  {
    oldSensor = nowSensor;
    nowSensor = s1;
    LedOff();
    digitalWrite(11, HIGH);
  }

  if (rightSensorValue < selectLevelA2)
  {
    oldSensor = nowSensor;
    nowSensor = s3;
    LedOff();
    digitalWrite(18, HIGH);
  }

  if (centerSensorValue < selectLevelA1)
  {
    oldSensor = nowSensor;
    nowSensor = s2;
    LedOff();
    digitalWrite(14, HIGH);
    digitalWrite(15, HIGH);
  }
 /*******************************************************************/
  CompareSensor();
  SucessCountCheck();

  /*******************************************************************/

  if (SmartInventor.TimeCheckMillis(900))
  {
    MoveSpeed = 15;
    sucessCount = 0;
    shipSpeed = 0;
    shipDirectiion = 0;
  }

  /*******************************************************************/
  if (shipDirectiion == 1)
  {
    SmartInventor.DCMotor(M1, CW, speed);
    StopDelayShip();
  }

  else if (shipDirectiion == 2)
  {
    SmartInventor.DCMotor(M1, CCW, speed);
    StopDelayShip();
  }

  else  SmartInventor.DCMotor(M1, STOP, speed);

  /*******************************************************************/
}


/*******************************************************************/
void CompareSensor()
{
  //sensor difference check
  if (nowSensor != oldSensor)
  {
    if ((oldSensor == s1) || (nowSensor == s2) || (nowSensor == s3))
    {
      shipDirectiion = 1;
      ComparePass();
    }
    else if ((oldSensor == s2) || (nowSensor == s1))
    {
      shipDirectiion = 2;
      ComparePass();
    }
    else if ((oldSensor == s2) || (nowSensor == s3))
    {
      shipDirectiion = 1;
      ComparePass();
    }
    else if ((oldSensor == s3) || (nowSensor == s1) || (nowSensor == s2))
    {
      shipDirectiion = 2;
      ComparePass();
    }
  }
}

/*******************************************************************/
void SucessCountCheck()
{
   //count check - success
  if (sucessCount > 100)
  {
    sucessCount = 0;
    SmartInventor.Buzz(NOTE_C5, 6);
    SmartInventor.Buzz(NOTE_E5, 6);
    SmartInventor.Buzz(NOTE_G5, 6);
  }
}

/*******************************************************************/
void ComparePass()
{
  if (!SmartInventor.TimeCheckMillis(speedCheck)) shipSpeed = maxShipSpeed;
  else shipSpeed = 0;

  oldSensor = nowSensor;
  sucessCount++;
  MoveSpeed ++;
}

/*******************************************************************/
void StopDelayShip()
{
  if (MoveSpeed > maxMoveSpeed) MoveSpeed = maxMoveSpeed;
  delay(MoveSpeed / speedControl);
  SmartInventor.DCMotor(M1, STOP, speed);
  delay(shipSpeed);
}

/*******************************************************************/
void LedOff()
{
  //Led OFF
  for (int thisPin = 11; thisPin <= 18; thisPin++)   {
    digitalWrite(thisPin, LOW);
  }
}
