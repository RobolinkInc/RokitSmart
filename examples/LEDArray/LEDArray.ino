#include <SmartInventor.h>
word delayTime = 1500;      //LED change time

// LED position
// □ □ □ □ □ □ □ □
// 11,12,13,14,15,16,17,18

void setup()
{
  // initialize serial communication at 57600 bits per second:
  Serial.begin(57600);
}

void loop()
{
 // ■ ■ ■ ■ ■ ■ ■ ■
 // 11,12,13,14,15,16,17,18
  SmartInventor.LedArray(0b11111111);  // bynary Input : 0b11111111 , hex Input : 0xff, decimal Input : 255;
  Serial.println("0b11111111");       // Input value print
  delay(delayTime);                    // wait time

 // □ □ □ □ □ □ □ ■
 // 11,12,13,14,15,16,17,18
  SmartInventor.LedArray(0b00000001);  // bynary Input : 0b00000001 , hex Input : 0x01, decimal Input : 1;
  Serial.println("0b00000001");       // Input value print
  delay(delayTime);                    // wait time

 // ■ □ □ □ □ □ □ ■
 // 11,12,13,14,15,16,17,18
  SmartInventor.LedArray(0b10000001);  // bynary Input : 0b10000001 , hex Input : 0x81, decimal Input : 129;
  Serial.println("0b10000001");       // Input value print
  delay(delayTime);                    // wait time

 // ■ □ □ ■ ■ □ □ ■
 // 11,12,13,14,15,16,17,18
  SmartInventor.LedArray(0b10011001);  // bynary Input : 0b10011001 , hex Input : 0x99, decimal Input : 153;
  Serial.println("0b10011001");       // Input value print
  delay(delayTime);                    // wait time
}




