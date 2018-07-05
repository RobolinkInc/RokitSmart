#include <SmartInventor.h>
#include <Servo.h> 

byte speed = 60;               //motor speed
word motorDelay = 1500;        //motor delay

Servo myservo1;      // create servo object to control a servo1
Servo myservo2;      // create servo object to control a servo2


void setup()
{
  SmartInventor.DCMotorUse();  // DC Motor Use

  Serial.begin(57600);       // initialize serial communication at 57600 bits per second:

  myservo1.attach(27);        // attaches the servo on pin 27 to the servo object 
  myservo2.attach(28);        // attaches the servo on pin 28 to the servo object 

  myservo1.write(90);          // servo1 to go to position in 90 degrees
  myservo2.write(90);          // servo2 to go to position in 90 degrees
  delay(500);                  // waits 500ms
}

void loop()
{
  SmartInventor.DCMove(forward,speed);          // forward : m1- CCW, m2- CW ,speed
  myservo1.write(0);                            // servo1 to go to position in 0 degrees
  myservo2.write(180);                          // servo2 to go to position in 180 degrees
  Serial.println("forward");                   // motor status print
  Serial.println("Servo1: 0,  Servo2: 180");   // servo status print
  delay(motorDelay);                            // wait time

  SmartInventor.DCMove(backward,speed);         // backward : m1- CW, m2- CCW ,speed
  myservo1.write(180);                          // servo1 to go to position in 180 degrees
  myservo2.write(0);                            // servo2 to go to position in 0 degrees
  Serial.println("backward");                  // motor status print
  Serial.println("Servo1: 180,  Servo2: 0");   // servo status print
  delay(motorDelay);                            // wait time

  SmartInventor.DCMove(stop,speed);             // stop : m1- stop, m2- stop 
  myservo1.write(90);                           // servo1 to go to position in 90 degrees
  myservo2.write(90);                           // servo2 to go to position in 90 degrees
  Serial.println("stop");                      // motor status print
  Serial.println("Servo1: 90,  Servo2: 90");   // servo status print
  delay(motorDelay);                            // wait time

  SmartInventor.DCMove(left,speed);             // left : m1- CW, m2- CW, speed
  myservo1.write(0);                            // servo1 to go to position in 0 degrees
  myservo2.write(0);                            // servo2 to go to position in 0 degrees
  Serial.println("left");                      // motor status print
  Serial.println("Servo1: 0,  Servo2: 0");     // servo status print
  delay(motorDelay);                            // wait time

  SmartInventor.DCMove(right,speed);            // right : m1- CCW, m2- CCW, speed
  myservo1.write(180);                          // servo1 to go to position in 180 degrees
  myservo2.write(180);                          // servo2 to go to position in 180 degrees
  Serial.println("right");                     // motor status print
  Serial.println("Servo1: 180,  Servo2: 180"); // servo status print
  delay(motorDelay);                            // wait time

  SmartInventor.DCMove(loose,speed);            // loose : m1- loose, m2- loose
  myservo1.write(90);                           // servo1 to go to position in 90 degrees
  myservo2.write(90);                           // servo2 to go to position in 90 degrees
  Serial.println("loose");                     // motor status print
  Serial.println("Servo1: 90,  Servo2: 90");   // servo status print
  delay(motorDelay);                            // wait time
}  















