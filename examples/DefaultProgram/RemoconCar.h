//#include <SmartInventor.h>
#include <Servo.h>

// 0 = remocon,soccer,bug
// 1 = trailer
// 2 = bike
// 3 = dunebuggy
// 4 = puttingBot
// 5 = CarrierBot

void RemoconCar(byte mode)
{
  SmartInventor.TVRemoconUse();
  SmartInventor.RFRemoconUse(57600);// Serial.begin(57600) Inclusion
  SmartInventor.DCMotorUse();

  byte leftCurveAngle  = 40;
  byte rightCurveAngle = 140;
  byte forwardAngle = 90;

  if (mode == 3) //dunebuggy
  {
    leftCurveAngle  = 60;
    rightCurveAngle = 150;
  }

  Servo myservo1;
  myservo1.attach(27);
  myservo1.write(forwardAngle);

  DDRC = 0xff;
  PORTC = 0b00111100;

  byte speed = 50;
  int keyData = 0;

  delay(100);

  while (1)
  {
    if (RFdata != 0)  keyData =  SmartInventor.RFRemoconData();
    else              keyData =  SmartInventor.TVRemoconData();

    if (keyData == KEY_U)
    {
      myservo1.write(forwardAngle);
      SmartInventor.DCMove(forward, speed);
    }
    else if (keyData == KEY_D)
    {
      myservo1.write(forwardAngle);
      SmartInventor.DCMove(backward, speed);
    }
    else if (keyData == KEY_L)
    {
      if ((mode == 2) || (mode == 3)) //bike & dunebuggy
      {
        myservo1.write(leftCurveAngle);
        SmartInventor.DCMove(forward, speed);
      }
      else if (mode == 1) //1 = trailer
      {
        SmartInventor.DCMotor(M1, LOOSE, speed);
        SmartInventor.DCMotor(M2, CW, speed);
      }
      else  //remocon
      {
        SmartInventor.DCMove(left, speed);
      }
    }
    else if (keyData == KEY_R)
    {
      if ((mode == 2) || (mode == 3)) //bike & dunebuggy
      {
        myservo1.write(rightCurveAngle);
        SmartInventor.DCMove(forward, speed);
      }
      else if (mode == 1) //1 = trailer
      {
        SmartInventor.DCMotor(M1, CCW, speed);
        SmartInventor.DCMotor(M2, LOOSE, speed);
      }
      else  //remocon
      {
        SmartInventor.DCMove(right, speed);
      }
    }
    else
    {
      SmartInventor.DCMove(LOOSE, 0); //not use speed value
    }


    if (keyData == KEY_F1)
    {
      speed = SmartInventor.SpeedDisplay(speed, 1);
    }
    else if (keyData == KEY_F2)
    {
      speed = SmartInventor.SpeedDisplay(speed, 0);
    }

    if (mode == 4)  //puttingBot
    {
      if (keyData == KEY_C) //Shot
      {
        myservo1.write(170);
        delay(500);
        myservo1.write(60);
        delay(1000);
        myservo1.write(110);
      }
    }
    if (mode == 5)  //puttingBot
    {
      if (keyData == KEY_F3) //angle up
      {
        if (SmartInventor.TimeCheckMillis(10))
        {
          if (forwardAngle < 179) forwardAngle += 1;
          myservo1.write(forwardAngle);
        }
      }

      else if (keyData == KEY_F4) //angle down
      {
        if (SmartInventor.TimeCheckMillis(10))
        {
          if (forwardAngle > 0) forwardAngle -= 1;
          myservo1.write(forwardAngle);
        }
      }
    }

  }
}
