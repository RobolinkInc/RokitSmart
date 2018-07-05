/*****************************
//GorillarBot Example
//2015-06-04 RoboLink
******************************/
#include <SmartInventor.h>

const int analogInPin0 = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPin2 = A2;  // Analog input pin that the potentiometer is attached to

word sensorOffset = 50;

byte speed = 100;
byte leftMotorStop = 0;
byte rightMotorStop = 0;
byte motorDirection = STOP;
byte Rush = 0;
int keyData = 0;

void setup()
{
  SmartInventor.TVRemoconUse();
  SmartInventor.DCMotorUse();
  SmartInventor.RFRemoconUse(57600);
  delay(100);
}

void loop()
{
  if(RFdata != 0)   keyData =  SmartInventor.RFRemoconData();
  else              keyData =  SmartInventor.TVRemoconData();

  if (keyData == KEY_C)   
  {
    Rush = 1; 
  }

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

  word leftSensorValue = analogRead(analogInPin0);         
  word rightSensorValue = analogRead(analogInPin2);  

  word  selectLevelA0 = SmartInventor.SensorCalibration(A0) - sensorOffset;
  word  selectLevelA2 = SmartInventor.SensorCalibration(A2) - sensorOffset;

  if(leftSensorValue < selectLevelA0)  rightMotorStop = 1;
  if(rightSensorValue < selectLevelA2)  leftMotorStop = 1; 

  if(Rush == true)
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















