/*****************************
//Line Tracer Example
//2015-06-04 RoboLink
******************************/
#include <SmartInventor.h>
#include <Servo.h> 

void ProgramingLoop();
void LineSensorTest();

void LineRun(byte speed);
void LeftTurn(byte speed);
void RightTurn(byte speed);
void TurnBack(byte speed);
void breakTime(word time);

#define Sensor ((~PINC) & 0b11111111)
#define S000        0b00000000
#define S101        0b00011000
#define S102        0b00011100
#define S103        0b00111000
#define S104        0b00000100
#define S105        0b00100000  
#define S106        0b00000110
#define S107        0b01100000
#define S108        0b00000010
#define S109        0b01000000
#define S110        0b00000001
#define S111        0b10000000

#define OPEN   110    
#define CLOSE   10

int dipSw1 = 8;
int dipSw2 = 9;
int dipSw3 = 10;

byte maxProgram = 27;
byte programCount = 0;
byte lineMemory[30];

word sensorOffset = 300;
int keyData = 0;

word speed = 80;


Servo myservo1;
  
void setup()
{
  SmartInventor.TVRemoconUse();
  SmartInventor.DCMotorUse();

  pinMode(dipSw1, INPUT_PULLUP);
  pinMode(dipSw2, INPUT_PULLUP);
 
  myservo1.attach(27);
  myservo1.write(OPEN);
  delay(1000);
 
  LineSensorTest();
}

void loop()
{
  SmartInventor.DCMove(STOP,0);  //not use speed value

  ProgramingLoop();
  
  myservo1.write(OPEN);
  delay(500);

  int runningProgram = 0;
  while(runningProgram < programCount)
  {

    runningProgram++;
    Serial.println(lineMemory[runningProgram]);

    if(lineMemory[runningProgram] == 1)  LineRun(speed);		//forward
    else if(lineMemory[runningProgram] == 2)  RightTurn(speed);	//turn right
    else if(lineMemory[runningProgram] == 3)  LeftTurn(speed);	//turn left
    else if(lineMemory[runningProgram] == 4)  TurnBack(speed);	//turn back

    else if(lineMemory[runningProgram] == 5) 
    { 
      myservo1.write(OPEN); 
      delay(500);
    }  //arm open
    else if(lineMemory[runningProgram] == 6) 
    { 
      myservo1.write(CLOSE);  
      delay(500);
    }  //arm close

    while(!SmartInventor.TimeCheckMillis(500));
  }
}


void LineRun(byte speed)
{
  SmartInventor.Buzz(1160,12); 

  byte buttonState1 = digitalRead(dipSw1);
  byte buttonState2 = digitalRead(dipSw2);

  //dip s/w speed control
  if((buttonState1 == HIGH)  && (buttonState2 == HIGH))  speed = 70;
  if((buttonState1 == LOW)  && (buttonState2 == HIGH))  speed = 80;
  if((buttonState1 == HIGH)  && (buttonState2 == LOW))  speed = 90;
  if((buttonState1 == LOW)  && (buttonState2 == LOW))  speed = 100; 
  
  int speed0 = speed;
  int speed1 = speed * 0.6; //0.6
  int speed2 = speed * 0.4;  //0.4
  int speed3 = speed * 0.2;  //0.2

    int speedM1 = 0;
  int speedM2 = 0;

  int directionM1 = 0;
  int directionM2 = 0;

  //Led Input
  for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
    pinMode(thisPin, INPUT);  
  } 
  
  SmartInventor.PreviousMillis = millis();
  while(SmartInventor.TimeCheckMillis(200))
  {
    SmartInventor.DCMotor(M1,CCW,speed0);
    SmartInventor.DCMotor(M2,CW,speed0); 
  }
  
//  while(!(Sensor == 0b11111111))
  while(((~Sensor) & 0b10000000) && ((~Sensor) & 0b00000001))
  {
    if (Sensor == S102)       {      directionM1= CCW;      directionM2 = CW ;      speedM1 = speed1 ;       speedM2 = speed0;    }//s102
    else if (Sensor == S104)  {      directionM1= CCW;      directionM2 = CW ;      speedM1 = speed2 ;       speedM2 = speed0;    }//s104
    else if (Sensor == S106)  {      directionM1= CCW;      directionM2 = CW ;      speedM1 = speed3 ;       speedM2 = speed0;    }//s106
    else if (Sensor == S108)  {      directionM1= CCW;      directionM2 = CW ;      speedM1 = speed3 ;       speedM2 = speed0;    }//s108
    else if (Sensor == S110)  {      directionM1= CW;       directionM2 = CW ;      speedM1 = speed0 ;       speedM2 = speed0;    }//s110

    else if (Sensor == S103)  {      directionM1= CCW;      directionM2 = CW ;      speedM1 = speed0 ;       speedM2 = speed1;    }//s103
    else if (Sensor == S105)  {      directionM1= CCW;      directionM2 = CW ;      speedM1 = speed0 ;       speedM2 = speed2;    }//s105
    else if (Sensor == S107)  {      directionM1= CCW;      directionM2 = CW ;      speedM1 = speed0 ;       speedM2 = speed3;    }//s107
    else if (Sensor == S109)  {      directionM1= CCW;      directionM2 = CW ;      speedM1 = speed0 ;       speedM2 = speed3;    }//s109
    else if (Sensor == S111)  {      directionM1= CCW;      directionM2 = CCW ;      speedM1 = speed0 ;       speedM2 = speed0;    }//s111

    else    {      directionM1= CCW;      directionM2 = CW ;      speedM1 = speed0 ;       speedM2 = speed0;    }//s101

    SmartInventor.DCMotor(M1,directionM1,speedM1);
    SmartInventor.DCMotor(M2,directionM2,speedM2); 
  }

  SmartInventor.PreviousMillis = millis();
  while(!SmartInventor.TimeCheckMillis(200));

  SmartInventor.DCMove(STOP,0);  //not use speed value
}

void LeftTurn(byte speed)
{
  LineRun(speed);
  SmartInventor.DCMove(left,speed); 
  while(1)
  {
    if(Sensor & 0b00000001)   break;
  }
  SmartInventor.DCMove(left,speed/2); 
  while(1)
  {
    //  if(Sensor & 0b00000100)   break;
    if(Sensor & 0b00011000)   break;
  }
  SmartInventor.DCMove(STOP,0);  //not use speed value
}

void RightTurn(byte speed)
{
  LineRun(speed);

  SmartInventor.DCMove(right,speed); 
  while(1)
  {
    if(Sensor & 0b10000000)   break;
  }
  SmartInventor.DCMove(right,speed/2); 
  while(1)
  {	
    // if(Sensor & 0b00100000)       break;
    if(Sensor & 0b00011000)   break;
  }
  SmartInventor.DCMove(STOP,0);  //not use speed value
}

void TurnBack(byte speed)
{
  LineRun(speed);

  SmartInventor.DCMove(left,speed); 
  while(1)
  {
    if(Sensor & 0b00000001)   break;
  }

  SmartInventor.DCMove(left,speed/2); 
  while(1)
  {	
    //  if(Sensor & 0b00000100)   break;
    if(Sensor & 0b00011000)   break;
  }
  SmartInventor.DCMove(STOP,0);  //not use speed value

  delay(500);

  SmartInventor.DCMove(left,speed); 
  while(1)
  {
    if(Sensor & 0b00000001)   break;
  }

  SmartInventor.DCMove(left,speed/2); 
  while(1)
  {
    //  if(Sensor & 0b00000100)   break;
    if(Sensor & 0b00011000)   break;
  }
  SmartInventor.DCMove(STOP,0);  //not use speed value
}

void breakTime(word time)
{
  while(!SmartInventor.TimeCheckMillis(time));
  //  delay(time);
}

void ProgramingLoop()
{
  byte programingEnd = 0;
  SmartInventor.LedPerformanceNumber(programCount);


  while (!programingEnd)
  {

    word  selectLevelA0 = SmartInventor.SensorCalibration(A0) - sensorOffset;
    word  selectLevelA1 = SmartInventor.SensorCalibration(A1) - sensorOffset;
    word  selectLevelA2 = SmartInventor.SensorCalibration(A2) - sensorOffset;

    word leftSensorValue = analogRead(A0);       
    word centerSensorValue = analogRead(A1);       
    word rightSensorValue = analogRead(A2);  

    //  Serial.print(centerSensorValue);
    //  Serial.print(" - ");
    // Serial.println(selectLevelA1);

    //□ □ □ □ □ □ □ □
    //11,12,13,14,15,16,17,18

    if(RFdata != 0)   keyData =  SmartInventor.RFRemoconData();
    else              keyData =  SmartInventor.TVRemoconData();


    //Led Output
    for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
      pinMode(thisPin, OUTPUT);  
    } 
    SmartInventor.LedPerformanceNumber(programCount);

    if( SmartInventor.TimeCheckMillis(800))
    {
      if(((leftSensorValue < selectLevelA0) && (rightSensorValue < selectLevelA2)) || (keyData == KEY_U)) //forward
      {
        if (programCount < maxProgram)  programCount++;
        lineMemory[programCount] = 1;
        SmartInventor.LedPerformanceNumber(programCount);
        SmartInventor.Buzz(740,12); 
      }

      else if(((leftSensorValue < selectLevelA0) && (centerSensorValue < selectLevelA1)) || (keyData == KEY_F3)) //delete
      {
        lineMemory[programCount] = 0;
        if (programCount > 0)  programCount--;
        SmartInventor.LedPerformanceNumber(programCount);
        SmartInventor.Buzz(1207,12); 
      }

      else if(((centerSensorValue < selectLevelA1) && (rightSensorValue < selectLevelA2)) || (keyData == KEY_D))  //tuen back
      {
        if (programCount < maxProgram)  programCount++;
        lineMemory[programCount] = 4;
        SmartInventor.LedPerformanceNumber(programCount);
        SmartInventor.Buzz(1465,12); 
      }

      else if(((rightSensorValue < selectLevelA2)) || (keyData == KEY_R))   //right turn
      {
        if (programCount < maxProgram)  programCount++;
        lineMemory[programCount] = 2;
        SmartInventor.LedPerformanceNumber(programCount);
        SmartInventor.Buzz(913,12); 
      }

      else if((leftSensorValue < selectLevelA0) || (keyData == KEY_L))  //left turn
      {
        if (programCount < maxProgram)  programCount++;
        lineMemory[programCount] = 3;
        SmartInventor.LedPerformanceNumber(programCount);
        SmartInventor.Buzz(1160,12); 
      }

      else if((centerSensorValue < selectLevelA1) || (keyData == KEY_C))  //start
      {
        programingEnd = 1;

        SmartInventor.Buzz(1981,12); 
        SmartInventor.Buzz(2132,12); 
        SmartInventor.Buzz(2315,12);  
        delay(500);
      }

        if(keyData == KEY_F1)  //OPEN
        {
          if (programCount < maxProgram)  programCount++;
          lineMemory[programCount] = 5;
          SmartInventor.LedPerformanceNumber(programCount);
          SmartInventor.Buzz(2132,12); 
        }

        else if(keyData == KEY_F2)  //CLOSE
        {
          if (programCount < maxProgram)  programCount++;
          lineMemory[programCount] = 6;
          SmartInventor.LedPerformanceNumber(programCount);
          SmartInventor.Buzz(2315,12); 
        }   
    }
  }
}

void LineSensorTest()
{
  unsigned char end = 1;

  //□ □ □ □ □ □ □ □
  //11,12,13,14,15,16,17,18
  //Led Input
  for (int thisPin = 11; thisPin <= 18; thisPin++)   {   
    pinMode(thisPin, INPUT);  
  } 

  while (end == 1)
  {
   if(RFdata != 0)   keyData =  SmartInventor.RFRemoconData();
    else              keyData =  SmartInventor.TVRemoconData();

    word  selectLevelA1 = SmartInventor.SensorCalibration(A1) - sensorOffset;
    word centerSensorValue = analogRead(A1);  
    if ((centerSensorValue < selectLevelA1) || (keyData == KEY_C))
    {
      if(SmartInventor.TimeCheckMillis(800) == true)
      {
        end = 0;
        SmartInventor.Buzz(740,8);
        SmartInventor.Buzz(1160,8);
      }
    }		
  }
}

