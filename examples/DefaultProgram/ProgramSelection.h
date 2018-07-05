
int ProgramSelection(byte mode);
void LedProgramStart();
void SelectSound(byte direction);

int ProgramSelection(byte mode)
{
  SmartInventor.TVRemoconUse();

  DDRC = 0xff;
  PORTC = 1;

  byte selectMode = 1;
  byte selectModeEnd = 0;
  byte modeMax = 27;
  
  word sensorOffsetA0 = 300;
  word sensorOffsetA1 = 300;
  word sensorOffsetA2 = 300;

  boolean nearSensorMode = false;

  if (SmartInventor.SensorCalibration(A1) <= 300) nearSensorMode = true;

  delay(100);

//  Serial.begin(57600);

  while (selectModeEnd == 0)
  {
    int  selectLevelA0 = SmartInventor.SensorCalibration(A0);
    int  selectLevelA1 = SmartInventor.SensorCalibration(A1);
    int  selectLevelA2 = SmartInventor.SensorCalibration(A2);

    //**********************************************//
    if (nearSensorMode) sensorOffsetA1 = 0;
    //**********************************************//

    selectLevelA0 = selectLevelA0 - sensorOffsetA0;
    selectLevelA1 = selectLevelA1 - sensorOffsetA1;
    selectLevelA2 = selectLevelA2 - sensorOffsetA2;

   int keyData = SmartInventor.TVRemoconData();

    SmartInventor.PreviousMillis = millis();
    while (!SmartInventor.TimeCheckMillis(100));

    /*************Remocon & Sensor**********************************************************/


      word leftSensorValue = analogRead(A0);
      word centerSensorValue = analogRead(A1);
      word rightSensorValue = analogRead(A2);

    if (mode == 1)
    {
      selectLevelA0 = 0;
      selectLevelA1 = 0;
      selectLevelA2 = 0;
    }

    if ((leftSensorValue < selectLevelA0) || (keyData == CH1_KEY_L) || (keyData == CH2_KEY_L) || (keyData == CH3_KEY_L) || (keyData == CH4_KEY_L))
    {
      selectMode--;
      if (selectMode == 0) selectMode = modeMax;
      SmartInventor.LedPerformanceNumber(selectMode - 1);
      SelectSound(0);//leftSensor = 0;
    }

    else if ((rightSensorValue < selectLevelA2) || (keyData == CH1_KEY_R) || (keyData == CH2_KEY_R) || (keyData == CH3_KEY_R) || (keyData == CH4_KEY_R))
    {
      selectMode++;
      if (selectMode > modeMax) selectMode = 1;
      SmartInventor.LedPerformanceNumber(selectMode - 1);
      SelectSound(2); //rightSensor = 2;
    }

    else if ((centerSensorValue < selectLevelA1) || (keyData == CH1_KEY_C) || (keyData == CH2_KEY_C) || (keyData == CH3_KEY_C) || (keyData == CH4_KEY_C))
    {
      SmartInventor.LedPerformanceNumber((selectMode - 1));
      SelectSound(1); //centerSensor = 1;
      LedProgramStart();
      selectModeEnd = 1;
      delay(1000);
    }
  }

  SmartInventor.TVRemoconClose();
  return selectMode;
}

void LedProgramStart()
{
  ///////////////////////////////////////
  int led_sign = 0;
  DDRC =  0b11111111;
  while (led_sign < 8)
  {
    PORTC = ((1 << (led_sign + 1)) - 1);
    led_sign++;
    delay(100);
  }
  while (led_sign > -2)
  {
    PORTC = ((1 << (led_sign + 1)) - 1);
    led_sign--;
    delay(100);
  }
  ///////////////////////////////////////
}


void SelectSound(byte direction)
{
  SmartInventor.TVRemoconClose();
  if ((direction == 0) || (direction == 2))
  {
    SmartInventor.Buzz(1542, 20);
    SmartInventor.Buzz(2315, 16);
  }
  else if (direction == 1)
  {
    SmartInventor.Buzz(1981, 12);
    SmartInventor.Buzz(2132, 12);
    SmartInventor.Buzz(2315, 8);
  }
  SmartInventor.TVRemoconUse();
}




