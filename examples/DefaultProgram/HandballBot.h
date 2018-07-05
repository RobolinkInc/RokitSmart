
#include <Servo.h>
#include <EEPROM.h>

void HandballBot()
{
  SmartInventor.TVRemoconUse();
  SmartInventor.DCMotorUse();

  DDRC = 0xff;
  PORTC = 0b00111100;

  Servo servo1;
  Servo servo2;

  int sp = 50;
  int keyData;

  int deg1 = EEPROM.read(10); //SERVO1_ANGLE_ADDRESS 10
  int deg2 = EEPROM.read(11); //SERVO2_ANGLE_ADDRESS 11

  servo1.write(deg1);
  servo2.write(deg2);
//  delay(1000);

  while (1)
  {
    keyData = SmartInventor.TVRemoconData();

    if (keyData == KEY_F3)
    {
      servo1.attach(27);
      servo2.attach(28);

      servo1.write(deg1);  //Handball_SERVO1_ORIGIN
      servo2.write(deg2);  //Handball_SERVO2_ORIGIN
      delay(1000);

      servo1.detach();
      servo2.detach();
    }

    else if (keyData == KEY_F4)
    {
      servo1.attach(27);
      servo2.attach(28);

      servo1.write(deg1 + 75);              //Handball_SERVO1_MAX
      servo2.write(deg2 - 75);              //Handball_SERVO2_MIN

      delay(1000);
      servo1.detach();
      servo2.detach();
    }

    else if (keyData == KEY_C)
    {
      servo1.attach(27);
      servo2.attach(28);

      servo1.write(deg1 + 30);              //Handball_SERVO1_INIT
      servo2.write(deg2 - 30);              //Handball_SERVO2_INIT

      delay(1000);
      servo1.detach();
      servo2.detach();
    }


    if (keyData == KEY_U)
    {
      SmartInventor.DCMove(forward, sp);
    }
    else if (keyData == KEY_D)
    {
      SmartInventor.DCMove(backward, sp);
    }
    else if (keyData == KEY_L)
    {
      SmartInventor.DCMove(left, sp);
    }
    else if (keyData == KEY_R)
    {
      SmartInventor.DCMove(right, sp);
    }
    else SmartInventor.DCMove(stop, sp);

    if (keyData == KEY_F1)
    {
      sp = SmartInventor.SpeedDisplay(sp, 1);
    }
    else if (keyData == KEY_F2)
    {
      sp = SmartInventor.SpeedDisplay(sp, 0);
    }
  }

}



