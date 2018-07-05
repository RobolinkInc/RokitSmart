//edit

#include <Servo.h>

void FlagGame()
{
  // delay(500);

  byte speed = 50;
  boolean success = 0;
  word sensorOffset = 50;

  SmartInventor.DCMotorUse();

  word selectLevelA0 = SmartInventor.SensorCalibration(A0) - sensorOffset;
  word selectLevelA2 = SmartInventor.SensorCalibration(A2) - sensorOffset;

  while (1)
  {
    if ( SmartInventor.TimeCheckMillis(3000))
    {
      byte mode = random(1, 4);

      if (mode == 1)
      {
        SmartInventor.DCMotor(M1, CW, speed);
      }
      else if (mode == 2)
      {
        SmartInventor.DCMotor(M2, CCW, speed);

      }
      else if (mode == 3)
      {
        SmartInventor.DCMotor(M1, CW, speed);
        SmartInventor.DCMotor(M2, CCW, speed);
      }

      delay(500);
      SmartInventor.DCMotor(M1, STOP, speed);
      SmartInventor.DCMotor(M2, STOP, speed);


      while (!SmartInventor.TimeCheckMillis(1000) && success == false)
      {
        word leftSensorValue = analogRead(A0);
        word rightSensorValue = analogRead(A2);

        if (leftSensorValue < selectLevelA0 && rightSensorValue < selectLevelA2 && mode == 3)
        {
          success = true;
        }
        if (leftSensorValue < selectLevelA0 && mode == 1)
        {
          success = true;
        }
        if (rightSensorValue < selectLevelA2 && mode == 2)
        {
          success = true;
        }

        if ( success == true)
        {
          SmartInventor.Buzz(1981, 12);
          SmartInventor.Buzz(2132, 12);
        }
      }

      if (mode == 1)
      {
        SmartInventor.DCMotor(M1, CCW, speed);
      }
      else if (mode == 2)
      {
        SmartInventor.DCMotor(M2, CW, speed);
      }
      else if (mode == 3)
      {
        SmartInventor.DCMotor(M1, CCW, speed);
        SmartInventor.DCMotor(M2, CW, speed);
      }

      delay(350);
      SmartInventor.DCMotor(M1, STOP, speed);
      SmartInventor.DCMotor(M2, STOP, speed);

      success = false;
    }
  }
}


