/*****************************
//MouseBot Example
//2015-06-04 RoboLink
******************************/
#include <SmartInventor.h>

byte  speed = 50;

//   selectLevelA0 = 600;
//   selectLevelA1 = 400;
//   selectLevelA2 = 600;

word sensorOffset = 50;

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

  Serial.begin(57600);
}

void loop ()
{
  word leftSensorValue = analogRead(A0);
  word centerSensorValue = analogRead(A1);
  word rightSensorValue = analogRead(A2);

  if (leftSensorValue < selectLevelA0)
  {
    //Led OFF
    for (int thisPin = 11; thisPin <= 18; thisPin++)   {
      digitalWrite(thisPin, LOW);
    }
    digitalWrite(11, HIGH);
    digitalWrite(15, HIGH);

    SmartInventor.Buzz(740, 12);

    SmartInventor.DCMove(right, speed);
  }

  else if (rightSensorValue < selectLevelA2)
  {
    //Led OFF
    for (int thisPin = 11; thisPin <= 18; thisPin++)   {
      digitalWrite(thisPin, LOW);
    }
    digitalWrite(13, HIGH);
    digitalWrite(18, HIGH);

    SmartInventor.Buzz(1160, 12);

    SmartInventor.DCMove(left, speed);
  }

  else if (centerSensorValue < selectLevelA1)
  {
    //Led OFF
    for (int thisPin = 11; thisPin <= 18; thisPin++)   {
      digitalWrite(thisPin, LOW);
    }
    digitalWrite(12, HIGH);
    digitalWrite(17, HIGH);

    SmartInventor.Buzz(913, 12);

    SmartInventor.DCMove(left, speed);
  }

  else
  {
    //Led OFF
    for (int thisPin = 11; thisPin <= 18; thisPin++)   {
      digitalWrite(thisPin, LOW);
    }
    digitalWrite(12, HIGH);
    digitalWrite(17, HIGH);

    SmartInventor.DCMove(forward, speed);
  }
}
