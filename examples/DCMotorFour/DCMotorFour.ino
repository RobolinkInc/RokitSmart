#include <SmartInventor.h>

// this code need "DCM" Module
// four motor use

byte speed = 60;              // motor speed
word motorDelay = 2000;       // motor delay

void setup()
{
  SmartInventor.DCMotorUse();  // DC Motor Use
  SmartInventor.DCMotorExtension();
}
void loop()
{  
  SmartInventor.DCMotor(M1,CCW,speed);    // DC Motor 1 , Direction CCW (CounterClockWise) , speed value
  SmartInventor.DCMotor(M2,CCW,speed);    // DC Motor 2 , Direction CCW (CounterClockWise) , speed value
  SmartInventor.DCMotor(M3,CCW,speed);    // DC Motor 3 , Direction CCW (CounterClockWise) , speed value
  SmartInventor.DCMotor(M4,CCW,speed);    // DC Motor 4 , Direction CCW (CounterClockWise) , speed value
  delay(motorDelay);     // wait time
  
  SmartInventor.DCMotor(M1,STOP,speed);   // DC Motor 1 , STOP (quick Stop)
  SmartInventor.DCMotor(M2,STOP,speed);   // DC Motor 1 , STOP (quick Stop)
  SmartInventor.DCMotor(M3,STOP,speed);   // DC Motor 1 , STOP (quick Stop)
  SmartInventor.DCMotor(M4,STOP,speed);   // DC Motor 1 , STOP (quick Stop)
  delay(motorDelay);    // wait time
  
  SmartInventor.DCMotor(M1,CW,speed);    // DC Motor 1 , Direction CW (CounterClockWise) , speed value
  SmartInventor.DCMotor(M2,CW,speed);    // DC Motor 2 , Direction CW (CounterClockWise) , speed value
  SmartInventor.DCMotor(M3,CW,speed);    // DC Motor 3 , Direction CW (CounterClockWise) , speed value
  SmartInventor.DCMotor(M4,CW,speed);    // DC Motor 4 , Direction CW (CounterClockWise) , speed value
  delay(motorDelay);    // wait time
  
  SmartInventor.DCMotor(M1,LOOSE,speed);    // DC Motor 2 , loose (slow Stop)
  SmartInventor.DCMotor(M2,LOOSE,speed);    // DC Motor 2 , loose (slow Stop)
  SmartInventor.DCMotor(M3,LOOSE,speed);    // DC Motor 2 , loose (slow Stop)
  SmartInventor.DCMotor(M4,LOOSE,speed);    // DC Motor 2 , loose (slow Stop)
  delay(motorDelay);    // wait time

}


