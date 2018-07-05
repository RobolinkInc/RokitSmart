
#include <Servo.h>

// 0 = smobot
// 1 = upgrade smobot

#define PUNCH1_ANGLE_A 0
#define PUNCH1_ANGLE_B 119

#define PUNCH2_ANGLE_A 179
#define PUNCH2_ANGLE_B 120

byte punchFlag;

void SumoBot(byte mode)
{
  Servo myservo1;
  Servo myservo2;
  
  SmartInventor.DCMotorUse();
  
  //□ □ □ □ □ □ □ □
  //11,12,13,14,15,16,17,18
  //BOTTOM SENSOR USE
  DDRC = 0b01111110;
  
  myservo1.attach(27);
  myservo2.attach(28);

  myservo1.write(PUNCH1_ANGLE_A);
  myservo2.write(PUNCH2_ANGLE_B);

  byte speed = 50;
  byte direction = 0;

  unsigned int  BackTime = 0;
  unsigned int  TurnTime = 0;

  SmartInventor.DCMove(forward, speed);

  while (1)
  {
    BackTime++;
    TurnTime++;
    if (BackTime >= 200) BackTime = 100;
    if (TurnTime >= 500) TurnTime = 100;

    if (mode == 1)
    {
      if (SmartInventor.TimeCheckMillis(500))
      {
        if (punchFlag == 1)
        {
          myservo1.write(PUNCH1_ANGLE_A); //PUNCH1_ANGLE_A 0
          myservo2.write(PUNCH2_ANGLE_B); //PUNCH2_ANGLE_B 120
          punchFlag = 0;
        }
        else
        {
          myservo1.write(PUNCH1_ANGLE_B); //PUNCH1_ANGLE_B 119
          myservo2.write(PUNCH2_ANGLE_A); //PUNCH2_ANGLE_A 179
          punchFlag = 1;
        }
      }
    }

    if ((digitalRead(11) == LOW) || (digitalRead(18) == LOW))
    {
      if (digitalRead(11) == LOW)  direction = right;
      if (digitalRead(18) == LOW)  direction = left;

      SmartInventor.DCMove(backward, speed);
      SmartInventor.Buzz(1160, 12);
      delay(100 + BackTime);
      SmartInventor.DCMove(direction, speed);
      delay(100 + TurnTime);
      SmartInventor.DCMove(forward, speed);
    }

    if (mode == 1)
    {
      if (SmartInventor.TimeCheckMillis(500))
      {
        if (punchFlag == 1)
        {
          myservo1.write(PUNCH1_ANGLE_A); //PUNCH1_ANGLE_A 0
          myservo2.write(PUNCH2_ANGLE_B); //PUNCH2_ANGLE_B 120
          punchFlag = 0;
        }
        else
        {
          myservo1.write(PUNCH1_ANGLE_B); //PUNCH1_ANGLE_B 119
          myservo2.write(PUNCH2_ANGLE_A); //PUNCH2_ANGLE_A 179
          punchFlag = 1;
        }
      }
    }
  }
}


