
#include <Servo.h>

// 0 = mouse
// 1 = crab
// 2 = Fan
// 3 = AutoCart
// 4 = robotcleaner

void MouseBot(byte mode)
{
//  delay(500);

  SmartInventor.DCMotorUse();

  byte speed = 50;
  word sensorOffset = 50;

  word  selectLevelA0 = SmartInventor.SensorCalibration(A0) - sensorOffset;
  word  selectLevelA1 = SmartInventor.SensorCalibration(A1) - sensorOffset;
  word  selectLevelA2 = SmartInventor.SensorCalibration(A2) - sensorOffset;

  DDRC = 0xff;

  Servo myservo1;
  myservo1.attach(27);
  myservo1.write(90);


  int interval = 1000;
  unsigned long oldTime = millis();
  byte angle = 90;

  if (mode == 2) //fan
  {
    SmartInventor.DCMotor(M1, CCW, speed);
    SmartInventor.DCMotor(M2, CW, speed);
  }

  while (1)
  {
    word leftSensorValue = analogRead(A0);
    word centerSensorValue = analogRead(A1);
    word rightSensorValue = analogRead(A2);

    if (leftSensorValue < selectLevelA0)
    {
      PORTC = 0b00010001; //left
      SmartInventor.Buzz(740, 12);

      if ((mode == 0) || (mode == 4))  //mouse //robotcleaner
      {
        SmartInventor.DCMove(right, speed);
      }
      else if (mode == 1) //crab
      {
        SmartInventor.DCMove(forward, speed);
      }
      else if (mode == 2) //fan
      {
        myservo1.write(45);
      }
      else if (mode == 3)  //AutoCart
      {
        SmartInventor.DCMove(left, speed);
      }
    }

    else if (rightSensorValue < selectLevelA2)
    {
      PORTC = 0b10000100;//rightEye
      SmartInventor.Buzz(1160, 12);

      if ((mode == 0) || (mode == 4))  //mouse //robotcleaner
      {
        SmartInventor.DCMove(left, speed);
      }
      else if (mode == 1) //crab
      {
        SmartInventor.DCMove(backward, speed);
      }
      else if (mode == 2) //fan
      {
        myservo1.write(135);
      }
      else if (mode == 3)  //AutoCart
      {
        SmartInventor.DCMove(right, speed);
      }
    }

    else if (centerSensorValue < selectLevelA1)
    {
      if ((mode == 0) || (mode == 4))  //mouse //robotcleaner
      {
        PORTC = 0b01000010;  //defaultEye
        SmartInventor.Buzz(913, 12);
        SmartInventor.DCMove(left, speed);
      }
      else if (mode == 1) //crab
      {
        PORTC = 0b00010001; //left
        SmartInventor.Buzz(913, 12);
        SmartInventor.DCMove(forward, speed);
        delay(100);
        SmartInventor.DCMove(backward, speed);
        delay(100);
        PORTC = 0b10000100;//rightEye
        SmartInventor.Buzz(913, 12);
        SmartInventor.DCMove(forward, speed);
        delay(100);
        SmartInventor.DCMove(backward, speed);
        delay(100);
      }
      else if (mode == 2) //fan
      {
        PORTC = 0b01000010;  //defaultEye
        myservo1.write(90);
      }
      else if (mode == 3)  //AutoCart
      {
        PORTC = 0b01000010;  //defaultEye
        SmartInventor.Buzz(913, 12);
        SmartInventor.DCMove(forward, speed);
      }
    }
    else
    {
      PORTC = 0b01000010;  //defaultEye

      if ((mode == 0) || (mode == 4)) //mouse //robotcleaner
      {
        SmartInventor.DCMove(forward, speed);

        if (oldTime + interval < millis())
        {
          if (angle == 120)
          {
            myservo1.write(angle);
            angle = 60;
            oldTime = millis();
          }
          else
          {
            myservo1.write(angle);
            angle = 120;
            oldTime = millis();
          }
        }
      }
      else if ((mode == 1) || (mode == 3)) //crab //cart
      {
        SmartInventor.DCMove(loose, 0);
      }
    }
  }
}



