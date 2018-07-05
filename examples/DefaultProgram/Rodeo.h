
#include <Servo.h>

// 0 = ver. Smart Rodeo
// 1 = ver. CubeWorks Surfing

void Rodeo(byte mode)
{
  Servo myservo2;
  Servo myservo1;

  byte angle2 = 90;
  byte angle1 = 90;

  byte speed = 100;
  byte score = 22;
  int angleLevel = 1;

  DDRC = 0xff;

  if (mode == 0)  // Rodeo
  {
    myservo1.attach(27);
    myservo2.attach(28);
  }
  else    // Surfing
  {
    myservo2.attach(27);
  }
  
  myservo1.write(angle1);
  myservo2.write(angle2);

  while (1)
  {
   int leftSensor = analogRead(A2);
   int rightSensor =  analogRead(A0);

    if (leftSensor < rightSensor)
    {
      if (angle2 < 179) angle2 = angle2 - angleLevel;
    }
    else
    {
      if (angle2 > 0) angle2 = angle2 + angleLevel;
    }

    myservo2.write(angle2);

    //down cow
    if ((angle2 < 30) || (angle2 > 140))
    {
      if (angle2 < 30)  myservo2.write(0);
      if (angle2 > 140) myservo2.write(180);

      for (byte i = 0; i < 3; i++)
      {
        SmartInventor.Buzz(740, 2);
        delay(500);
      }

      angle2 = 90;
      angle1 = 90;
      speed = 100;
      angleLevel = 1;
      score = 22;
      /*
      //Led OFF
      for (int thisPin = 11; thisPin <= 18; thisPin++)   {
        digitalWrite(thisPin, LOW);
      }
          */
      PORTC = 0;
    }

    SmartInventor.Buzz(1160, 20);
    delay(speed);

    if (SmartInventor.TimeCheckMillis(1000))
    {
      speed = speed - 5;
      if (speed <= 0) speed = 5;

      if (speed < 30) angleLevel = 7;
      else if (speed < 50) angleLevel = 5;
      else if (speed < 70) angleLevel = 3;
      else if (speed < 80) angleLevel = 2;

      angle1 = angle1 + random(-5, 5);
      if (angle1 > 90) angle1 = 90;
      else if (angle1 < 70) angle1 = 70;

      myservo1.write(angle1);

      score ++;
      if (score > 36) score = 36;
    }

    digitalWrite(score / 2, HIGH);
  }
}
