//edit 

void RiceBarleyBot()
{
  SmartInventor.DCMotorUse();

  DDRC = 0xff;
  PORTC = 0;
  
  byte sensorOffset = 50;
  word selectLevelA1 = SmartInventor.SensorCalibration(A1) - sensorOffset;

  while (1)
  {
    word centerSensorValue = analogRead(A1);

    PORTC = 0;
    byte sensor = centerSensorValue / 200;
    byte speedMeterL = 14 - sensor;
    byte speedMeterR = 15 + sensor;

    digitalWrite(speedMeterL, HIGH);
    digitalWrite(speedMeterR, HIGH);

    if (2 > sensor)
    {
      SmartInventor.Buzz(1160, 8);
      SmartInventor.DCMove(left, 100);
      delay(1000);
      SmartInventor.DCMove(left, 60);
      delay(2000);
      SmartInventor.DCMove(right, 100);
      delay(100);
      SmartInventor.DCMove(LOOSE, 100);
      SmartInventor.Buzz(1160, 12);
      SmartInventor.Buzz(740, 8);
    }
  }
}

