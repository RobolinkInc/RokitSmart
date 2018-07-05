/*****************************
//RiceBarleyBot Example
//2015-06-04 RoboLink
******************************/
#include <SmartInventor.h>

const int analogInPin1 = A1;  // Analog input pin that the potentiometer is attached to
word sensorOffset = 50;
word findTime = 0;

void setup()
{
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

  delay(500);
}

void loop()
{
  word selectLevelA1 = SmartInventor.SensorCalibration(A1) - sensorOffset;
  word centerSensorValue = analogRead(analogInPin1);

  //Led OFF
  for (int thisPin = 11; thisPin <= 18; thisPin++)   {
    digitalWrite(thisPin, LOW);
  }
  byte sensor = analogRead(analogInPin1) / 200;

  byte speedMeterL = 14 - sensor;
  byte speedMeterR = 15 + sensor ;

  digitalWrite(speedMeterL, HIGH);
  digitalWrite(speedMeterR, HIGH);

  byte actionTime = random(50, 255);

  if (centerSensorValue < selectLevelA1)
  {
    findTime++;
    if (findTime > actionTime)
    {
      findTime = 0;

      SmartInventor.Buzz(1160, 8);
      SmartInventor.DCMotor(M1, CW, 100);
      SmartInventor.DCMotor(M2, CW, 100);
      delay(1000);

      SmartInventor.DCMotor(M1, CW, 60);
      SmartInventor.DCMotor(M2, CW, 60);
      delay(2000);
      SmartInventor.DCMotor(M1, CCW, 100);
      SmartInventor.DCMotor(M2, CCW, 100);
      delay(100);
      SmartInventor.DCMotor(M1, LOOSE, 100);
      SmartInventor.DCMotor(M2, LOOSE, 100);

      SmartInventor.Buzz(1160, 12);
      SmartInventor.Buzz(740, 8);
    }
  }
}











