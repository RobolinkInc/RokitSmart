#include <SmartInventor.h>

// DCMotor :  single motror control

byte speed = 60;              // motor speed
word motorDelay = 1000;       // motor delay

void setup()
{
  SmartInventor.DCMotorUse();  // DC Motor Use
  Serial.begin(57600);        // initialize serial communication at 57600 bits per second:
}

void loop()
{
  SmartInventor.DCMotor(M1,CCW,speed);    // DC Motor 1 , Direction CCW (CounterClockWise) , speed value
  Serial.println("M1 : CCW");            // Input motor value print
  delay(motorDelay);                      // wait time

  SmartInventor.DCMotor(M2,CCW,speed);    // DC Motor 2 , Direction CCW (CounterClockWise) , speed value
  Serial.println("M2 : CCW");            // Input motor value print
  delay(motorDelay);                      // wait time  

  SmartInventor.DCMotor(M1,STOP,speed);   // DC Motor 1 , STOP
  Serial.println("M1 : STOP");           // Input motor value print
  delay(motorDelay);                      // wait time

  SmartInventor.DCMotor(M2,STOP,speed);   // DC Motor 2 , STOP
  Serial.println("M2 : STOP");           // Input motor value print
  delay(motorDelay);                      // wait time

  SmartInventor.DCMotor(M2,CW,speed);     // DC Motor 2 , Direction CW (ClockWise) , speed value
  Serial.println("M2 : CW");             // Input motor value print
  delay(motorDelay);                      // wait time

  SmartInventor.DCMotor(M1,CW,speed);    // DC Motor 1 , Direction CW (ClockWise) , speed value
  Serial.println("M1 : CW");            // Input motor value print
  delay(motorDelay);                      // wait time

  SmartInventor.DCMotor(M1,stop,speed);  // DC Motor 1 , STOP (quick Stop)
  SmartInventor.DCMotor(M2,stop,speed);  // DC Motor 2 , STOP (quick Stop)
  Serial.println("M1 : STOP");          // Input motor value print
  Serial.println("M2 : STOP");          // Input motor value print
  delay(motorDelay);                      // wait time

  SmartInventor.DCMotor(M1,CCW,speed);  // DC Motor 1 , Direction CCW (CounterClockWise) , speed value
  SmartInventor.DCMotor(M2,CW,speed);   // DC Motor 2 , Direction CW (CounterClockWise) , speed value
  Serial.println("M1 : CCW");          // Input motor value print
  Serial.println("M2 : CW");           // Input motor value print
  delay(motorDelay);                      // wait time

  SmartInventor.DCMotor(M1,CW,speed);    // DC Motor 1 , Direction CW (CounterClockWise) , speed value
  SmartInventor.DCMotor(M2,CCW,speed);   // DC Motor 2 , Direction CCW (CounterClockWise) , speed value
  Serial.println("M1 : CW");            // Input motor value print
  Serial.println("M2 : CW");            // Input motor value print
  delay(motorDelay);                      // wait time

  SmartInventor.DCMotor(M1,loose,speed);  // DC Motor 1 , loose (slow Stop)
  SmartInventor.DCMotor(M2,loose,speed);  // DC Motor 2 , loose (slow Stop)
  Serial.println("M1 : loose");          // Input motor value print
  Serial.println("M2 : loose");          // Input motor value print
  delay(motorDelay);                      // wait time
}









