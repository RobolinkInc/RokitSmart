#include <SmartInventor.h>

//TV Remocon Control
void setup()
{
  SmartInventor.TVRemoconUse();  // TV Remocon Use
  Serial.begin(57600);          // initialize serial communication at 57600 bits per second:
  delay(500);                    // waits 500ms
}

void loop()
{
  int keyData =  SmartInventor.TVRemoconData();  // read TV Remocon receive data => keyData

    if (keyData == KEY_U)                   // read TV Remocon receive data then 'KEY_U'
  {  
    Serial.println("Forward");           // receive data print
  }
  else if (keyData == KEY_D)              // read TV Remocon receive data then 'KEY_D'
  {
    Serial.println("Backword");          // receive data print
  }
  else if (keyData == KEY_L)              // read TV Remocon receive data then 'KEY_L'
  {
    Serial.println("Left");              // receive data print
  }
  else if (keyData == KEY_R)              // read TV Remocon receive data then 'KEY_R'
  {  
    Serial.println("Right");             // receive data print
  }
  else if (keyData == KEY_C)              // read TV Remocon receive data then 'Center'
  {
    Serial.println("Center");            // receive data print
  }
  else if (keyData == KEY_F1)             // read TV Remocon receive data then 'KEY_F1'
  {
    Serial.println("F1");                // receive data print
  }
  else if (keyData == KEY_F2)             // read TV Remocon receive data then 'KEY_F2'
  {
    Serial.println("F2");                // receive data print
  }
  else if (keyData == KEY_F3)             // read TV Remocon receive data then 'KEY_F3'
  {
    Serial.println("F3");                // receive data print
  }
  else if (keyData == KEY_F4)             // read TV Remocon receive data then 'KEY_F4'
  {
    Serial.println("F4");                // receive data print
  }
}









