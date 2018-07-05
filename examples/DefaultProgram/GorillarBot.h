
void GorillarBot()
{
  SmartInventor.TVRemoconUse();
  SmartInventor.DCMotorUse();
  SmartInventor.RFRemoconUse(57600);

  word sensorOffset = 50;

  byte speed = 100;
  byte leftMotorStop,rightMotorStop,Rush;
  
  byte motorDirection = STOP;
  int keyData;

//  delay(500);

  while(1)
  {
    if(RFdata != 0)   keyData =  SmartInventor.RFRemoconData();
    else              keyData =  SmartInventor.TVRemoconData();

    if (keyData == KEY_C)      Rush = 1; 

    else if (keyData == KEY_U)
    {
      motorDirection = forward;

      rightMotorStop = 0; 
      leftMotorStop = 0;

      SmartInventor.DCMove(motorDirection,speed);
      Rush = 0;
    }

    else if (keyData == KEY_L)
    {
      motorDirection = left;

      rightMotorStop = 0; 
      leftMotorStop = 0;

      SmartInventor.DCMove(motorDirection,speed);
      Rush = 0;
    }
    else if (keyData == KEY_R)
    {
      motorDirection = right;

      rightMotorStop = 0; 
      leftMotorStop = 0;

      SmartInventor.DCMove(motorDirection,speed);
      Rush = 0;
    }
    else if (keyData == KEY_D)
    {
      motorDirection = backward;

      rightMotorStop = 0; 
      leftMotorStop = 0;

      SmartInventor.DCMove(motorDirection,speed);
      Rush = 0;
    }
    else	
    {
      motorDirection = stop;  
    }

    word leftSensorValue = analogRead(A0);         
    word rightSensorValue = analogRead(A2);  

    word  selectLevelA0 = SmartInventor.SensorCalibration(A0) - sensorOffset;
    word  selectLevelA2 = SmartInventor.SensorCalibration(A2) - sensorOffset;

    if(leftSensorValue < selectLevelA0)  rightMotorStop = 1;
    if(rightSensorValue < selectLevelA2)  leftMotorStop = 1; 

    if(Rush)
    {
      if((!leftMotorStop) && (rightMotorStop))
      {
        SmartInventor.DCMotor(M1,stop,speed);
        SmartInventor.DCMotor(M2,CW,speed); 
      }
      else if((leftMotorStop) && (!rightMotorStop))
      {
        SmartInventor.DCMotor(M1,CCW,speed);
        SmartInventor.DCMotor(M2,stop,speed); 
      }  
      else if((!leftMotorStop) && (!rightMotorStop))
      {
        SmartInventor.DCMove(forward,speed);
        rightMotorStop = 0; 
        leftMotorStop = 0;
      }
      else if((leftMotorStop) && (rightMotorStop))
      {
        motorDirection = stop;
        SmartInventor.DCMove(motorDirection,speed);
        delay(5);
        rightMotorStop = 0; 
        leftMotorStop = 0;
        motorDirection = forward;	
        SmartInventor.DCMove(motorDirection,speed);
        delay(5);
      }
    }
    
    else if(Rush == false)
    {
      SmartInventor.DCMove(motorDirection,speed);
    }
  }
}







