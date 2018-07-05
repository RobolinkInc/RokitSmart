

void TurretBot()
{
//  delay(500);
  SmartInventor.DCMotorUse();
  
  DDRC = 0xff;
  PORTC = 0b11011011;
  
  byte speed = 100;
  word sensorOffset = 300;
  
  word  selectLevelA0 = SmartInventor.SensorCalibration(A0) - sensorOffset;
  word  selectLevelA1 = SmartInventor.SensorCalibration(A1) - sensorOffset;
  word  selectLevelA2 = SmartInventor.SensorCalibration(A2) - sensorOffset;
  
  byte moveTime = 6;
  byte stopTime = 2;
  boolean toggleLED =  false;
  byte countLED = 0;
  
  while (1)
  {
    word leftSensorValue = analogRead(A0);
    word centerSensorValue = analogRead(A1);
    word rightSensorValue = analogRead(A2);

    if (rightSensorValue < selectLevelA2)
    {
      if (countLED == 2)
      {
        if (toggleLED == true)
        {
          PORTC = 0b11000000;
          toggleLED = false;
        }
        else
        {         
          PORTC = 0;
          toggleLED = true;
        }
        countLED = 0;
      }
      else
      {
        countLED++;
      }

      SmartInventor.DCMotor(M1, CCW, speed);
      delay(moveTime);
      SmartInventor.DCMotor(M1, STOP, speed);
      delay(stopTime);
     
      PORTC = 0;
    }
    else if (leftSensorValue < selectLevelA0)
    {
      if (countLED == 2)
      {
        if (toggleLED == true)
        {
          PORTC = 0b00000011;
          toggleLED = false;
        }
        else
        {       
          PORTC = 0;
          toggleLED = true;
        }
        countLED = 0;
      }
      else
      {
        countLED++;
      }

      SmartInventor.DCMotor(M1, CW, speed);
      delay(moveTime);
      SmartInventor.DCMotor(M1, STOP, speed);
      delay(stopTime);
   
      PORTC = 0;

    }
    else if (centerSensorValue < selectLevelA1)
    {

      PORTC = 0b00011000;

      SmartInventor.DCMotor(M2, CW, speed);
      SmartInventor.Buzz(913, 8);
      SmartInventor.Buzz(1160, 8);
      delay(300);
      SmartInventor.DCMotor(M2, STOP, speed);
      delay(100);
     
      PORTC = 0;
    }
  }
}
