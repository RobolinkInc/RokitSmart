/*****************************
//SumoBot Example
//2015-06-04 RoboLink
******************************/
#include <SmartInventor.h>
byte speed = 50;
word  BackTime = 0;
word  TurnTime = 0;

void setup()
{
  //□ □ □ □ □ □ □ □
  //11,12,13,14,15,16,17,18
  //BOTTOM SENSOR USE
  pinMode(11, INPUT);
  pinMode(18, INPUT);
  SmartInventor.DCMotorUse();

  SmartInventor.DCMove(forward, speed);
}
void loop()
{
  BackTime++;
  TurnTime++;
  if (BackTime >= 200) BackTime = 100;
  if (TurnTime >= 500) TurnTime = 100;

  if (digitalRead(11) == LOW)
  {
    SmartInventor.DCMove(backward, speed);
    SmartInventor.Buzz(1160, 12);
    delay(100 + BackTime);
    SmartInventor.DCMove(right, speed);
    delay(100 + TurnTime);
    SmartInventor.DCMove(forward, speed);
  }

  else if (digitalRead(18) == LOW)
  {
    SmartInventor.DCMove(backward, speed);
    SmartInventor.Buzz(1160, 12);
    delay(100 + BackTime);
    SmartInventor.DCMove(left, speed);
    delay(100 + TurnTime);
    SmartInventor.DCMove(forward, speed);
  }

}



