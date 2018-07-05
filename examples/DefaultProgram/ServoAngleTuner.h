//edit

#include<Servo.h>
#include <EEPROM.h>

//#define SERVO_ORIGIN  90

void ServoAngleTuner()
{
  Servo servo[4];

  byte deg[4] = {90, 90, 90, 90};
  int delta[4] = {0, 0, 0, 0};
  int servoSelect = 0 ;

  servo[0].attach(27);
  servo[1].attach(28);
  servo[2].attach(29);
  servo[3].attach(30);

  servo[0].write(deg[0]);
  servo[1].write(deg[1]);
  servo[2].write(deg[2]);
  servo[3].write(deg[3]);

  SmartInventor.TVRemoconUse();
  //  SmartInventor.LedArray(0b00000001);
  PORTC = 0b00000001;

  Serial.begin(9600);

  //  Serial.println("Servo0");
  //Serial.println(servoSelect);
  while (1)
  {
    int keyData = SmartInventor.TVRemoconData();

    if ((keyData == KEY_F1) || (keyData == KEY_F2) || (keyData == KEY_F3) || (keyData == KEY_F4))
    {
      if (keyData == KEY_F1)        servoSelect = 0;
      else if (keyData == KEY_F2)   servoSelect = 1;
      else if (keyData == KEY_F3)   servoSelect = 2;
      else if (keyData == KEY_F4)   servoSelect = 3;

      PORTC = 1 << servoSelect;
      Serial.println(servoSelect);
      delay(500);
    }

    if ((keyData == KEY_U) || (keyData == KEY_D))
    {
      if (keyData == KEY_U)
      {
        delta[servoSelect]++;
        if ( (deg[servoSelect] + delta[servoSelect]) >= 179) delta[servoSelect]--;
      }
      else if (keyData == KEY_D)
      {
        delta[servoSelect]--;
        if ( (deg[servoSelect] + delta[servoSelect]) <= 0) delta[servoSelect]++;
      }

      servo[servoSelect].write(deg[servoSelect] + delta[servoSelect]);

      Serial.println(deg[servoSelect] + delta[servoSelect]);
      delay(20);
    }

    else if ((keyData == KEY_L) || (keyData == KEY_R))
    {
      for (int j = 0; j < 4; j++)
      {
        delta[j] = 0;
        servo[j].write(deg[j] + delta[j]);
        //   Serial.println(deg[j] + delta[j]);
        //   delay(200);
      }
    }

    if (keyData == KEY_C)
    {
      PORTC = 0b11111111;
      delay(400);

      PORTC = 1 << servoSelect;

      for (int j = 10; j < 14; j++)
      {
        int val = deg[j - 10] + delta[j - 10];
        EEPROM.write(j, val);
//-------------------------------///
        Serial.print(val);
        Serial.print(" ");
//-------------------------------///
      }
      //     Serial.println();
    }
  }
}
