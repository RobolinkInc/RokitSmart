/*****************************
//TurretBot Example
//2015-06-04 RoboLink
******************************/
#include <SmartInventor.h>

const int analogInPin0 = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPin1 = A1;  // Analog input pin that the potentiometer is attached to
const int analogInPin2 = A2;  // Analog input pin that the potentiometer is attached to

byte speed = 100;
word sensorOffset = 300;

word  selectLevelA0 = 0;
word  selectLevelA1 = 0;
word  selectLevelA2 = 0;

word moveTime = 6;
word stopTime = 2;
boolean toggleLED =  false;
byte countLED = 0;

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

  digitalWrite(17, HIGH);
  digitalWrite(18, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);

}

void loop()
{
  word leftSensorValue = analogRead(analogInPin0);
  word centerSensorValue = analogRead(analogInPin1);
  word rightSensorValue = analogRead(analogInPin2);

  if (rightSensorValue < selectLevelA2)
  {
    if (countLED == 2)
    {
      if (toggleLED == true)
      {
        digitalWrite(17, HIGH);
        digitalWrite(18, HIGH);
        toggleLED = false;
      }
      else
      {
        digitalWrite(17, LOW);
        digitalWrite(18, LOW);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        toggleLED = true;
      }
      countLED = 0;
    }
    else
    {
      countLED++;
    }

    SmartInventor.DCMotor(M1, CCW, speed);
    delay(moveTime);
    SmartInventor.DCMotor(M1, STOP, speed);
    delay(stopTime);

    //Led OFF
    for (int thisPin = 11; thisPin <= 18; thisPin++)   {
      digitalWrite(thisPin, LOW);
    }
  }
  else if (leftSensorValue < selectLevelA0)
  {
     if (countLED == 2)
    {
      if (toggleLED == true)
      {
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
        toggleLED = false;
      }
      else
      {
        digitalWrite(17, LOW);
        digitalWrite(18, LOW);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        toggleLED = true;
      }
      countLED = 0;
    }
    else
    {
      countLED++;
    }

    SmartInventor.DCMotor(M1, CW, speed);
    delay(moveTime);
    SmartInventor.DCMotor(M1, STOP, speed);
    delay(stopTime);

    //Led OFF
    for (int thisPin = 11; thisPin <= 18; thisPin++)   {
      digitalWrite(thisPin, LOW);
    }
  }
  else if (centerSensorValue < selectLevelA1)
  {
    digitalWrite(14, HIGH);
    digitalWrite(15, HIGH);

    SmartInventor.DCMotor(M2, CW, speed);
    SmartInventor.Buzz(913, 8);
    SmartInventor.Buzz(1160, 8);
    delay(300);
    SmartInventor.DCMotor(M2, STOP, speed);
    delay(100);

    //Led OFF
    for (int thisPin = 11; thisPin <= 18; thisPin++)   {
      digitalWrite(thisPin, LOW);
    }
  }
}
