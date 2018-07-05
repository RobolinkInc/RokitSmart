#include <SmartInventor.h>

#define MAX_CMD_LENGTH 7
byte cmdBuff[MAX_CMD_LENGTH];
int cmdIndex = 0;
boolean checkHeader = 0;

#define DIGITAL 1
#define ANALOG  2

/***************************************************************/

void SendPacket();
void AnalogSend();
void DigitalSend();
void ReceiveSimulator();
void CommandAction();

/***************************************************************/
/*
  #define M1  1
  #define M2  2
*/

/*
  #define CW    1
  #define CCW   2
  #define STOP    3
*/

#define PORT_C   3
#define PORT_D   4

#define INPUT_PORT   1
#define OUTPUT_PORT  2

int simCommmand = 0;
int simOption   = 0;
int simValue    = 0;

/***************************************************************/




byte packet[6];
byte portC[8];
byte portD[8];
byte portA[8];

byte data0 = 0;
byte data1 = 0;
byte data2 = 0;
byte data3 = 0;


void Simulator()
{
  Serial.begin(57600);
  SmartInventor.DCMotorUse();  // DC Motor Use

  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);

  DDRC = 0x00;

  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  pinMode(18, INPUT);

  pinMode(27, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);

  while (1)
  {

    byte buttonState1 = digitalRead(8);
    byte buttonState2 = digitalRead(9);
    byte buttonState3 = digitalRead(10);

    AnalogSend();

    ReceiveSimulator();
    CommandAction();
    delay(10);

    DigitalSend();

    ReceiveSimulator();
    CommandAction();

    delay(10);

  }
}


void AnalogSend()
{

  //mode ANALOG 0x02

  for (int i = 0; i < 8; i++)
  {
    int value = analogRead(A0 + i);

    byte highValue = value >> 8;
    byte lowhValue = value & 0xff;

    data0 = ANALOG;
    data1 = i;
    data2 = lowhValue;
    data3 = highValue;

    SendPacket();
  }

}

void DigitalSend()
{
  //mode digital 0x01
  data0 = DIGITAL;

  portC[7] = digitalRead(11);
  portC[6] = digitalRead(12);
  portC[5] = digitalRead(13);
  portC[4] = digitalRead(14);
  portC[3] = digitalRead(15);
  portC[2] = digitalRead(16);
  portC[1] = digitalRead(17);
  portC[0] = digitalRead(18);

  for (int i = 0 ; i < 8; i++)
  {
    data1 += portC[0 + i] << 7 - i;
  }
  //  Serial.println(data1);
  //  data1 = 0;


  portA[7] = !digitalRead(A0);
  portA[6] = !digitalRead(A1);
  portA[5] = !digitalRead(A2);
  portA[4] = !digitalRead(A3);
  portA[3] = !digitalRead(A4);
  portA[2] = !digitalRead(A5);
  portA[1] = !digitalRead(A6);
  portA[0] = !digitalRead(A7);

  for (int i = 0 ; i < 8; i++)
  {
    data2 += portA[0 + i] << 7 - i;
  }
  //Serial.write(data2);
  //data2 = 0;


  portD[7] = !digitalRead(8);
  portD[6] = !digitalRead(9);
  portD[5] = !digitalRead(10);
  portD[4] = !digitalRead(27);
  portD[3] = !digitalRead(28);
  portD[2] = !digitalRead(29);
  portD[1] = !digitalRead(30);
  portD[0] = !digitalRead(31);

  for (int i = 0 ; i < 8; i++)
  {
    data3 += portD[0 + i] << 7 - i;
  }
  //Serial.write(data3);
  //data3 = 0;


  SendPacket();

}

void SendPacket()
{

  //START CODE
  packet[0] = 0xff;

  //header
  packet[1] = 0x88;

  packet[2] = data0;
  packet[3] = data1;
  packet[4] = data2;
  packet[5] = data3;

  Serial.write(packet, 6);

  data0 = 0;
  data1 = 0;
  data2 = 0;
  data3 = 0;
}

void ReceiveSimulator()
{
  if (Serial.available() > 0)
  {
    int input = Serial.read();

    cmdBuff[cmdIndex++] = (char)input;

    if (cmdIndex >= MAX_CMD_LENGTH)
    {
      checkHeader = 0;
      cmdIndex = 0;
    }

    else
    {
      if (cmdIndex == 1)
      {
        if (cmdBuff[0] == 0xff)
        {
          checkHeader = 1;
        }
        else
        {
          checkHeader = 0;
          cmdIndex = 0;
        }
      }

      else if (checkHeader == 1)
      {
        if (cmdIndex == 2)
        {
          if (cmdBuff[1] == 0x55)
          {
            checkHeader = 2;
          }
          else
          {
            checkHeader = 0;
            cmdIndex = 0;
          }
        }
      }
      else if (checkHeader == 2)
      {
        if (cmdIndex == 6)
        {
          /*
            Serial.write(cmdBuff[2]);
            Serial.write(cmdBuff[3]);
            Serial.write(cmdBuff[4]);
            Serial.write(cmdBuff[5]);
          */
          simCommmand = cmdBuff[2];
          simOption = cmdBuff[3];
          simValue = cmdBuff[5];

          checkHeader = 0;
          cmdIndex = 0;
        }
      }
    }
  }
}

void CommandAction()
{

  if (simCommmand > 0)
  {

    if (simCommmand == M1 || simCommmand == M2)
    {
      SmartInventor.DCMotor(simCommmand, simOption, simValue);
    }

    else if (simCommmand == PORT_C || simCommmand == PORT_D)
    {
      if (simCommmand == PORT_C)
      {
        if (simOption == INPUT_PORT)
        {
          DDRC &= ~(0b1 << simValue - 1);
          PORTC &= ~(0b1 << simValue - 1);
        }
        else if (simOption == OUTPUT_PORT)
        {
          DDRC |= (0b1 << simValue - 1);
          PORTC |= (0b1 << simValue - 1);
        }
      }

      if (simCommmand == PORT_D)
      {
        if (simOption == INPUT_PORT)
        {
          if (simValue >= 3 && simValue <= 7)
          {
            DDRD &= ~(0b1 << simValue - 1);
            PORTD |= (0b1 << simValue - 1);   //Pull-Up
            // PORTD &= ~(0b1 << simValue - 1);
          }
        }
        else if (simOption == OUTPUT_PORT)
        {
          if (simValue >= 3 && simValue <= 7)
          {
            DDRD |= (0b1 << simValue - 1);
            PORTD |= (0b1 << simValue - 1);
          }
        }
      }
    }
  }

  simCommmand = 0;
  simOption = 0;
  simValue = 0;
}

