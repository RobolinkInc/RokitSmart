/*****************************
//CrabBot Example
//2015-06-04 RoboLink
******************************/
#include <SmartInventor.h>

byte speed = 80;
word sensorOffset = 50;  //sensitive control

int leftEye = 0;
int defaultEye = 1;
int rightEye = 2;

word  selectLevelA0 = 0;
word  selectLevelA1 = 0;
word  selectLevelA2 = 0;

void setup()
{
  delay(500);
  
  SmartInventor.DCMotorUse();
  selectLevelA0 = SmartInventor.SensorCalibration(A0) - sensorOffset;
  selectLevelA1 = SmartInventor.SensorCalibration(A1) - sensorOffset;
  selectLevelA2 = SmartInventor.SensorCalibration(A2) - sensorOffset;
}

void loop()
{
  word leftSensorValue = analogRead(A0);       
  word centerSensorValue = analogRead(A1);       
  word rightSensorValue = analogRead(A2);  

  if(leftSensorValue < selectLevelA0)
  {
    LedPerformanceEye(leftEye);
    SmartInventor.Buzz(740,12); 
    SmartInventor.DCMove(backward,speed);
  }
  else if(rightSensorValue < selectLevelA2)
  {
    LedPerformanceEye(rightEye);
    SmartInventor.Buzz(1160,12); 
    SmartInventor.DCMove(forward,speed);
  }
  else if(centerSensorValue < selectLevelA1)
  {
    LedPerformanceEye(leftEye);
    SmartInventor.Buzz(913,12); 
    SmartInventor.DCMove(forward,speed);
    delay(100);
    SmartInventor.DCMove(backward,speed);
    delay(100);

    LedPerformanceEye(rightEye);
    SmartInventor.Buzz(913,12); 
    SmartInventor.DCMove(forward,speed);
    delay(100);
    SmartInventor.DCMove(backward,speed);
    delay(100);
  }
  else
  {
    LedPerformanceEye(defaultEye);
    SmartInventor.DCMove(loose,0);
  }
}



void LedPerformanceEye(byte position)
{
  //□ □ □ □ □ □ □ □
  //11,12,13,14,15,16,17,18

  //Led Output
  for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
    pinMode(thisPin, OUTPUT);  
  } 

  if (position == 0)  //leftEye
  {
    //Led OFF
    for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
      digitalWrite(thisPin, LOW);  
    }
    digitalWrite(11, HIGH);
    digitalWrite(15, HIGH);

  }
  else if(position == 1)  //defaultEye
  {
    //Led OFF
    for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
      digitalWrite(thisPin, LOW);  
    }
    digitalWrite(12, HIGH);
    digitalWrite(17, HIGH);

  }
  else if (position == 2)  //rightEye
  {
    //Led OFF
    for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
      digitalWrite(thisPin, LOW);  
    }
    digitalWrite(13, HIGH);
    digitalWrite(18, HIGH);
  }
}






















