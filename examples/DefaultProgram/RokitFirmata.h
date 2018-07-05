#include <Servo.h>
#include <SmartInventor.h>
//#include <CLCD.h>

#define SEVENSENSOR ((~PINC) & 0b11111111)
#define SERIAL_BAUDRATE     57600

#define DCMOTOR               0x01
#define DIGITAL_READ          0x02
#define DIGITAL_WRITE         0x03
#define SET_SERVO             0x04
#define ANALOG_READ           0x05
#define ANALOG_WRITE          0x06
#define SEVENSENSOR_READ      0x07
#define DIPSWITCH_READ        0x08
#define IRREMOCON_READ        0x09
#define BUZZER                0x0A
#define STREAM_ON             0x0B
#define STREAM_OFF            0x0C

#define READY                 0xE0
#define OFF                   0xD0

byte pinVal = 0;
byte outVal = 0;
byte outVal2 = 0;
long analogPin = 0;
int  inpVal = 0;
int  inChar;
char buf[10] = {};
byte recvBytes[5] = {0};
byte bufferBytes[20][6];
int cnt = 0;
int col = 0;
int follow = 0;
long exMillis = 0;
boolean isReceiving = false;
boolean isReady = true;
boolean isStreaming = true;
int header = 0;
byte exInByte = 0;

Servo servo[10];

void serialRead();

void RokitFirmata() {
  Serial.begin(SERIAL_BAUDRATE);
  SmartInventor.TVRemoconUse();
  SmartInventor.DCMotorUse();
  DDRC = 0x00;

  for (int j = 0; j < 20; j++)
  {
    bufferBytes[j][5] = OFF;
  }


  while (1)
  {
    serialRead();

    if (isReady == true)
    {
      switch (bufferBytes[follow][1])
      {
        case DCMOTOR:
          {
            SmartInventor.DCMotor(bufferBytes[follow][2], bufferBytes[follow][3], bufferBytes[follow][4]);
            break;
          }
        case SET_SERVO:
          {
            if (bufferBytes[follow][3] >= 179) bufferBytes[follow][3] = 179;
            else if (bufferBytes[follow][3] <= 0) bufferBytes[follow][3] = 0;
            servo[bufferBytes[follow][2] - 22].attach( bufferBytes[follow][2]);
            servo[ bufferBytes[follow][2] - 22].write( bufferBytes[follow][3]);
            break;
          }
        case DIGITAL_WRITE:
          {
            pinMode( bufferBytes[follow][2], OUTPUT);
            digitalWrite( bufferBytes[follow][2],  bufferBytes[follow][3]);
            break;
          }
        case ANALOG_WRITE:
          {
            pinMode( bufferBytes[follow][2], OUTPUT);
            analogWrite( bufferBytes[follow][2],  bufferBytes[follow][3]);
            break;
          }
        case DIGITAL_READ:
          {
            pinMode( bufferBytes[follow][2] , INPUT_PULLUP);
            break;
          }
        case SEVENSENSOR_READ:
          {
            DDRC = 0x00;
            break;
          }
        case BUZZER:
          {
            int pitch = ((int)(bufferBytes[follow][3]) << 8) | bufferBytes[follow][2];
            int noteDuration = 1000 / bufferBytes[follow][4];
            // tone(7, pitch, noteDuration);
            break;
          }
        case STREAM_ON:
          {
            isStreaming = true;
            break;
          }

        case STREAM_OFF:
          {
            isStreaming = false;
            break;
          }
      }
      bufferBytes[follow][5] = OFF;

      follow++;
      if (follow >= 20) follow = 0;
      if (bufferBytes[follow][5] == OFF) isReady = false;  else isReady = true;
    }
    else
    {
      for (int j = 0; j < 20; j++)  {
        if (bufferBytes[j][5] == READY) {
          isReady = true;
          follow = j;
          break;
        }
      }
    }

    if ((millis() - exMillis) >= 10 )
    {
      if (analogPin <= 7)
      {
        int val = analogRead(analogPin);
        long sendVal = (analogPin << 16) | val;
        if (isStreaming == true) Serial.println(sendVal);
      }
      else if (analogPin == 8)
      {
        int dVal =  (((PIND & 0b01111100) >> 2) << 8) | ((PINB & 0b11100000) | ((PINA & 0b11111000) >> 3));
        long sendDval = (analogPin << 16) | dVal;       // pin 27 is virtual input pin
        if (isStreaming == true) Serial.println(sendDval);
      }
      else if (analogPin == 9)
      {
        int dirPin = (((DDRD & 0b01111100) >> 2) << 8) | ((DDRB & 0b11100000) | ((DDRA & 0b11111000) >> 3));
        long sendDirVal = (analogPin << 16) | dirPin;
        if (isStreaming == true) Serial.println(sendDirVal);
      }
      else if (analogPin == 10)
      {
        byte sVal = ~SEVENSENSOR;
        int IRValue =  SmartInventor.TVRemoconData();
        long sendExVal = (analogPin << 16) | ((( IRValue << 8) | sVal) & 0xFFFF);   // pin 28 is vitrual input pin
        if (isStreaming == true) Serial.println(sendExVal);
      }
      analogPin++;
      if (analogPin >= 11) analogPin = 0;
      exMillis = millis();
    }
  }
}
void serialRead() {

  while (Serial.available()) {

    byte inByte = (byte)Serial.read();
    //CLCD.print(inByte, HEX);
    if (isReceiving == true)
    {
      recvBytes[cnt] =  inByte;
      //CLCD.print(recvBytes[cnt]);
      cnt++;

      if (recvBytes[0] < cnt)
      {
        isReady = true; isReceiving = false; cnt = 0;
        for (int j = 0; j < 5; j++)
        {
          bufferBytes[col][j] = recvBytes[j];
        }
        bufferBytes[col][5] = READY; col++;
        if (col >= 20) col = 0;
      }
    }
    if ((inByte == 0xFF) && (exInByte == 0xFF)) {
      isReceiving = true;
      exInByte = 0;
    }
    else {
      exInByte = inByte;
    }
  }
}


