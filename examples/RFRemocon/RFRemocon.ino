#include <SmartInventor.h>

//RF Remocon Control

int keyData = 0;

void setup()
{
  SmartInventor.RFRemoconUse(57600);  //RF Remocon Use - communication at 57600 bits per second

  //□ □ □ □ □ □ □ □
  //11,12,13,14,15,16,17,18
  //Led All Output Set
  for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
    pinMode(thisPin, OUTPUT);  
  } 
  //Led All OFF
  for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
    digitalWrite(thisPin, LOW);  
  } 
}

void loop()
{
  keyData =  SmartInventor.RFRemoconData();

  if (keyData == KEY_U)                          // read RF Remocon receive data then 'KEY_U'
  {
    //Led All OFF
    for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
      digitalWrite(thisPin, LOW);  
    } 
    // ■ □ □ □ □ □ □ □
    // 11,12,13,14,15,16,17,18
    digitalWrite(11,HIGH);                        // LED ON digital pin 11             
  }  
  else if (keyData == KEY_D)                      // read RF Remocon receive data then 'KEY_D'
  {
    //Led All OFF
    for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
      digitalWrite(thisPin, LOW);  
    } 
    // □ ■ □ □ □ □ □ □
    // 11,12,13,14,15,16,17,18
    digitalWrite(12,HIGH);                        // LED ON digital pin 12  
  }
  else if (keyData == KEY_L)                       // read RF Remocon receive data then 'KEY_L'
  {
    //Led All OFF
    for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
      digitalWrite(thisPin, LOW);  
    } 
    // □ □ ■ □ □ □ □ □
    // 11,12,13,14,15,16,17,18
    digitalWrite(13,HIGH);                         // LED ON digital pin 13   
  }
  else if (keyData == KEY_R)                       // read RF Remocon receive data then 'KEY_R'
  {
    //Led All OFF
    for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
      digitalWrite(thisPin, LOW);  
    } 
    // □ □ □ ■ □ □ □ □
    // 11,12,13,14,15,16,17,18
    digitalWrite(14,HIGH);                          // LED ON digital pin 14   
  }
}

