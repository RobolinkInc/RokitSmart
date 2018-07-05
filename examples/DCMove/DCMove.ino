#include <SmartInventor.h>

// DCMove : two motror unison control

byte speed = 60;               // motor speed
word motorDelay = 1000;        // motor delay

void setup()
{
  SmartInventor.DCMotorUse();  // DC Motor Use
  Serial.begin(57600);        // initialize serial communication at 57600 bits per second:
}

void loop()
{
  SmartInventor.DCMove(forward,speed);  // forward : m1- CCW, m2- CW ,speed
  Serial.println("forward");           // motor status print
  delay(motorDelay);                    // wait time

  SmartInventor.DCMove(backward,speed);  // backward : m1- CW, m2- CCW ,speed
  Serial.println("backward");           // motor status print
  delay(motorDelay);                     // wait time

  SmartInventor.DCMove(stop,speed);     // stop : m1- stop, m2- stop 
  Serial.println("stop");              // motor status print
  delay(motorDelay);                    // wait time            

  SmartInventor.DCMove(left,speed);     // left : m1- CW, m2- CW, speed
  Serial.println("left");              // motor status print 
  delay(motorDelay);                    // wait time

  SmartInventor.DCMove(right,speed);    // right : m1- CCW, m2- CCW, speed
  Serial.println("right");            // motor status print
  delay(motorDelay);                    // wait time

  SmartInventor.DCMove(loose,speed);    // loose : m1- loose, m2- loose
  Serial.println("loose");             // motor status print
  delay(motorDelay);                    // wait time
}





