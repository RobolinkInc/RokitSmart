#include <SmartInventor.h>
#include <Servo.h> 

Servo myservo;    // create servo object to control a servo 
int pos = 0;      // variable to store the servo position 

void setup()
{
  myservo.attach(27);  // attaches the servo on pin 27 to the servo object 
}

void loop()
{
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }

  SmartInventor.Buzz(NOTE_C4,12);    // note Play C4 , Duration 12 (1/12sec)

  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  SmartInventor.Buzz(NOTE_F5,12);    // note Play F5 , Duration 12 (1/12sec)
}







