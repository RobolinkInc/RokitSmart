
#include <Servo.h>
#include <EEPROM.h>

void GripBot()
{
  Servo servo1;
  Servo servo2;

  int sp = 50;
  boolean toggle = false;

  int keyData;
  int delta1 = 0;
  int delta2 = 0;

  SmartInventor.TVRemoconUse();
  SmartInventor.DCMotorUse();

  DDRC = 0xff;
  PORTC = 0b00111100;

  int deg1 = EEPROM.read(10);//SERVO1_ANGLE_ADDRESS 10
  int deg2 = EEPROM.read(11);//SERVO2_ANGLE_ADDRESS 11

  servo1.attach(27);
  servo2.attach(28);

  servo1.write(deg1);
  servo2.write(deg2);

  /*/////////////////////////////////////////
  Serial.begin(57600);
  Serial.println(deg1);
  Serial.println(deg2);
  /////////////////////////////////////////*/

  while (1)
  {
    keyData = SmartInventor.TVRemoconData();

    if (keyData == KEY_F4)
    {
      delta2++;

      if (delta2 >= 40 ) delta2 = 40;
      servo2.write(deg2 + delta2);
      delay(10);
    }
    else if (keyData == KEY_F3)
    {
      delta2--;
      
      if ( delta2 <= -50 ) delta2 = -50;
      servo2.write(deg2 + delta2);
      delay(10);
    }
    else if (keyData == KEY_C)
    {
      if ( toggle == true) {
        servo1.write(deg1 + 20); //Grip_SERVO1_MAX
        toggle = false;
      }
      else if (toggle == false) {
        servo1.write(deg1 - 40); //Grip_SERVO1_MIN
        toggle = true;
      }
      delay(500);
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

