
#include <Servo.h>

void UpgradeMouseBot()
{
  SmartInventor.DCMotorUse();
  
  byte speed = 40;
  Servo myservo1;
  myservo1.attach(27);
  myservo1.write(90);
  byte led;  
  DDRC = 0xff;
  delay(500);

  while (1)
  {
    int leftSensorValue = analogRead(A0);
    int centerSensorValue = analogRead(A1);
    int rightSensorValue = analogRead(A2);

    if (leftSensorValue < 400 || centerSensorValue < 400 || rightSensorValue < 400 )
    {
      SmartInventor.DCMove(stop, speed);

      myservo1.write(60);
      delay(500);

      if (leftSensorValue < 400)
      {
        myservo1.write(120);
        delay(500);
        
        if (rightSensorValue < 400)
        {
          SmartInventor.DCMove(backward, speed);
          myservo1.write(90);
          delay(1000);
          SmartInventor.DCMove(left, speed);
          delay(500);
        }
        else
        {
          SmartInventor.DCMove(right, speed);
          myservo1.write(90);
          delay(300);
        }
      }
      else
      {
        SmartInventor.DCMove(left, speed);
        myservo1.write(90);
        delay(300);
      }
    }
    else
    {
      SmartInventor.DCMove(forward, speed);

      if (SmartInventor.TimeCheckMillis(300))
      {
        SmartInventor.Buzz(1160, 12);
        
        PORTC = ((0b10000000 >> led) | (0b00000001 << led));
        led++;
        if (led == 4) led = 0;
      }
    }
  }
}


