
#include <Servo.h>
#include <EEPROM.h>

void LiftBot()
{
  SmartInventor.DCMotorUse();
  SmartInventor.TVRemoconUse();

  DDRC = 0xff;
  PORTC = 0b00111100;

  byte speedMeterL = 13;
  byte speedMeterR = 16;

  Servo servo1;
  Servo servo2;

  int sp = 50;
  int keyData;
  
  int delta1 = 0;
  int delta2 = 0;

  int deg1 = EEPROM.read(10); //SERVO1_ANGLE_ADDRESS 10
  int deg2 = EEPROM.read(11); //SERVO2_ANGLE_ADDRESS 11

  servo1.attach(27);
  servo2.attach(28);

  servo1.write(deg1);
  servo2.write(deg2);


  /*
  Serial.println(deg1);
  Serial.println(deg2);
  */

  while (1)
  {
    keyData = SmartInventor.TVRemoconData();

    if (keyData == KEY_F3)
    {
      delta1--;
      delta2++;

      if ( delta2 > 60 /*SERVO1_MIN*/)
      {
        delta1++;
        delta2--;
      }

      servo1.write(deg1 + delta1);
      servo2.write(deg2 + delta2);
/*
      Serial.print(delta1);
      Serial.print("\t");
      Serial.print(delta2);
      Serial.print("\t");

      Serial.print(deg1 + delta1);
      Serial.print("\t");
      Serial.println(deg2 + delta2);
*/
      delay(20);
    }

    else if (keyData == KEY_F4)
    {
      delta1++;
      delta2--;

      if ( delta1 > 5)
      {
        delta1--;
        delta2++;
      }

      servo1.write(deg1 + delta1);
      servo2.write(deg2 + delta2);
/*
      Serial.print(delta1);
      Serial.print("\t");
      Serial.print(delta2);
      Serial.print("\t");

      Serial.print(deg1 + delta1);
      Serial.print("\t");
      Serial.println(deg2 + delta2);
*/
      delay(20);
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


