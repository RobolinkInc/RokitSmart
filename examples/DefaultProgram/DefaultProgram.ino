/*==============================================================================
  - Smart Step 1 & 2  All Example
  - CubeWorks 3 Step All Example
  - Rokit Brick & Smart Simulator
  -------------------------------------------------------------------------------
  //2015-07-17 RoboLink
  //2015-09-03 firmata add (snap4 arduino)
  //2015-10-16 Servo, firmata, linetracer modify
  //2015-10-22 Smart Simulator add
  //2015-10-30 Model Bug Fix
  //2015-12-09 Servo Angle First Move Add
  //2016-01-08 Servo Angle Bug Fix
  //2016-01-12 Version Display (PowerON - Serial 9600 bps)
  //2016-03-09 Rokit firmata add (Rokit Brick)
  //2016-03-11 Rokit firmata Bug Fix(IR Remocon)
  //2016-03-14 Rokit Simulator Modify (Receive Command - Motor,LED Action)
  //2016-03-22 Rokit Model Example Modify (Servo Motors)
  //2016-07-29 Rokit Model Example Modify (1Step)
  //2016-09-24 Rokit Model Example Modify (2Step)
  -------------------------------------------------------------------------------
  - add Smart1 & Smart2
  - add Cubeworks3
  - add Rokit Brick
  - add Smart Simulator
  -------------------------------------------------------------------------------
  //Mode Select
  -------------------------------------------------------------------------------
  |--------| Program Upload Mode (Arduino sketch Upload)
  | ■□□ | (Uploaded sketch Execute : Switch 1 DOWN↓)
  | □■■ | Switch 1 : UP   ↑
  l 1 2 3  | Switch 2 : DOWN ↓
  |--------| Switch 3 : DOWN ↓
  -------------------------------------------------------------------------------
  |--------| Smart Step 1
  | □□□ |
  | ■■■ | Switch 1 : DOWN ↓
  l 1 2 3  | Switch 2 : DOWN ↓
  |--------| Switch 3 : DOWN ↓
  -------------------------------------------------------------------------------
  |--------| Smart Step 2
  | □■□ |
  | ■□■ | Switch 1 : DOWN ↓
  l 1 2 3  | Switch 2 : UP   ↑
  |--------| Switch 3 : DOWN ↓
  -------------------------------------------------------------------------------
  |--------| CubeWorks 3
  | ■■□ |
  | □□■ | Switch 1 : UP   ↑
  l 1 2 3  | Switch 2 : UP   ↑
  |--------| Switch 3 : DOWN ↓
  -------------------------------------------------------------------------------
  |--------| Smart Simulator
  | □■■ |
  | ■□□ | Switch 1 : DOWN ↑
  l 1 2 3  | Switch 2 : UP   ↑
  |--------| Switch 3 : UP   ↑
  -------------------------------------------------------------------------------
  |--------| Rokit Brick
  | ■■■ |
  | □□□ | Switch 1 : UP  ↑
  l 1 2 3  | Switch 2 : UP  ↑
  |--------| Switch 3 : UP  ↑
  -------------------------------------------------------------------------------

  ===============================================================================*/

#include <SmartInventor.h>
#include <EEPROM.h>
#include "RokitFirmata.h"
#include <Servo.h>

#include "Simulator.h"
#include "ProgramSelection.h"

//-----------------------------//

#include "RemoconCar.h"
//#include "Smart2_ServoModels.h"

//-----------------------------//


//1 step include
#include "MouseBot.h"         //1
#include "SumoBot.h"          //2
//#include "CrabBot.h"        //3
//#include "SoccerBot.h"      //4, 11 (RemoconCar 0 : SoccerBot & BugBot)
#include "Segway.h"           //5 
//#include "Trailer.h"        //6 (RemoconCar 1 : SoccerBot & BugBot)
#include "Viking.h"           //7
#include "TurretBot.h"        //8
#include "RiceBarleyBot.h"    //9
#include "GorillarBot.h"      //10
//#include "BugBot.h"         //11, 4 (RemoconCar 0 : BugBot & SoccerBot)
#include "LineTracer.h"       //12

//2 step include
//#include "Bike.h"             //1
//#include "DuneBuggy.h"        //2
#include "GripBot.h"            //3
#include "Rodeo.h"              //4
#include "UpgradeMouseBot.h"    //5
#include "HandballBot.h"        //6
//#include "UpgradeSumoBot.h"   //7
#include "ShootingBot.h"        //8
#include "MelodyBot.h"          //9
#include "LiftBot.h"            //10
#include "ServoAngleTuner.h"    //12

//CubeWorks 3 step include
//#include "CrabBot.h"          //1
//#include "Viking.h"           //2
//#include "LineTracer.h"       //3 Train
//#include "Surfing.h"          //4 Rodeo servo 1
#include "FlagGame.h"           //5
//#include "Fan.h"              //6
#include "AutoCrossBar.h"       //7
//#include "AutoCart.h"         //8
//#include "PuttingBot.h"       //9
//#include "CarrierBot.h"       //10
//#include "RobotCleaner.h"     //11
//#include "RemoconCar.h"

void setup()
{
  Serial.begin(9600);
  Serial.print("- Smart - ");
  Serial.print("ver : ");
  Serial.println(170412);

  /*
    Serial.println(EEPROM.read(10));  //SERVO1_ANGLE_ADDRESS 10
    Serial.println(EEPROM.read(11));  //SERVO2_ANGLE_ADDRESS 11
    Serial.println(EEPROM.read(12));  //SERVO3_ANGLE_ADDRESS 12
    Serial.println(EEPROM.read(13));  //SERVO4_ANGLE_ADDRESS 13
  */
  Serial.end();

  //----------------------------------------------//

  pinMode(8, INPUT_PULLUP);     //DipSw1
  pinMode(9, INPUT_PULLUP);     //DipSw2
  pinMode(10, INPUT_PULLUP);    //DipSw3
  
  //  dip1 = 8, dip2 = 9, dip3 = 10 //LOW : Switch UP , HIGH : Switch Down
  
  if ((digitalRead(8) == LOW) && (digitalRead(9) == LOW) && (digitalRead(10) == LOW)) RokitFirmata(); //Rokit Brick - dipSw 1,2, 3 UP
  if ((digitalRead(9) == LOW) && (digitalRead(10) == LOW)) Simulator(); //Simulator - dipSw 2, 3 UP

  //----------------------------------------------//

  word RangeMAX = 600;
  word RangeMIN = 400;

  boolean checkJoysticA3ToA6  = true;

  for (int i = 0 ; i < 10 ; i++)
  {
    int sen3 = analogRead(A3);
    int sen4 = analogRead(A4);
    int sen5 = analogRead(A5);
    int sen6 = analogRead(A6);
    if (!((sen3 < RangeMAX) && (sen3 > RangeMIN) && (sen4 < RangeMAX) && (sen4 > RangeMIN) && (sen5 < RangeMAX) && (sen5 > RangeMIN) && (sen6 < RangeMAX) && (sen6 > RangeMIN)))
      checkJoysticA3ToA6 = false;
    delay(10);
  }
  //----------------------------------------------//



  //*************first move - servo angle input*************//
  if (EEPROM.read(19) != 90)
  {
    EEPROM.write(10, 90); //servo1 standard position
    EEPROM.write(11, 90); //servo2 standard position
    EEPROM.write(12, 90); //servo3 standard position
    EEPROM.write(13, 90); //servo4 standard position
    EEPROM.write(19, 90); //servo angle state
  }
  //*********************************************************//
  delay(250);
}

void loop()
{
  //  dip1 = 8, dip2 = 9, dip3 = 10 //LOW : Switch UP , HIGH : Switch Down

  // if ((digitalRead(8) == LOW) && (digitalRead(9) == LOW) && (digitalRead(10) == LOW)) RokitFirmata(); //Rokit Brick - dipSw 1,2, 3 UP
  //  if ((digitalRead(9) == LOW) && (digitalRead(10) == LOW)) Simulator(); //Simulator - dipSw 2, 3 UP
  if (digitalRead(10) == LOW) RemoconCar(0);  //Remote Car - dipSw3 UP
  
  /******************************Smart step 1 ******************************************************/
  //Smart step 1 select - dipSw2 Down
  else if ((digitalRead(8) == HIGH) && (digitalRead(9) == HIGH))
  {
    byte programNumber =  ProgramSelection(0);  //sensor or remocon use
    delay(500);

    if (programNumber == 1)  MouseBot(0);
    else if (programNumber == 2)  SumoBot(0);
    else if (programNumber == 3)  MouseBot(1);    //  1 = crab
    else if (programNumber == 4)  RemoconCar(0);  // (SoccerBot & BugBot)
    else if (programNumber == 5)  Segway();
    else if (programNumber == 6)  RemoconCar(1);  //trailer
    else if (programNumber == 7)  Viking();
    else if (programNumber == 8)  TurretBot();
    else if (programNumber == 9)  RiceBarleyBot();
    //////////////////////////////////////////////////////////////////////////////
    else if (programNumber == 10)  GorillarBot();
    //////////////////////////////////////////////////////////////////////////////
    else if (programNumber == 11)  RemoconCar(0); // (SoccerBot & BugBot)
    else if (programNumber == 12)  LineTracer(0);
    else RemoconCar(0);  //RemoteCar
  }

  /********************************Smart step 2 **************************************************/
  //Smart step 2 select - dipSw2 UP
  else if ((digitalRead(8) == HIGH) && (digitalRead(9) == LOW))
  {
    byte programNumber =  ProgramSelection(1);  //remocon only use
    delay(500);

    if (programNumber == 1)  RemoconCar(2);
    else if (programNumber == 2)  RemoconCar(3);
    else if (programNumber == 3)  GripBot();
    else if (programNumber == 4)  Rodeo(0);
    //////////////////////////////////////////////////////////////////////////////
    else if (programNumber == 5)  UpgradeMouseBot();
    else if (programNumber == 6)  HandballBot();
    else if (programNumber == 7)  SumoBot(1);
    else if (programNumber == 8)  ShootingBot();
    /////////////////////////////////////////////////////////////////////////////
    else if (programNumber == 9)  MelodyBot();
    else if (programNumber == 10) LiftBot(); //no test
    else if (programNumber == 11) LineTracer(0); ////linetracer mode(grip)
    else if (programNumber == 12) ServoAngleTuner();
    else RemoconCar(0);  //RemoteCar
  }

  /********************************Cubeworks Step 3************************************************/
  //Cubeworks Step 3 select - dipSw 1, 2 UP
  else if ((digitalRead(8) == LOW ) && (digitalRead(9) == LOW))
  {
    byte programNumber =  ProgramSelection(0);  //sensor or remocon use
    delay(500);

    if (programNumber == 1)  MouseBot(1); //  1 = crab
    else if (programNumber == 2)  Viking();
    else if (programNumber == 3)  LineTracer(1); //Train
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    else if (programNumber == 4)  Rodeo(1); //Surfing();
    else if (programNumber == 5)  FlagGame();
    else if (programNumber == 6)  MouseBot(2); //Fan
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    else if (programNumber == 7)  AutoCrossBar();
    else if (programNumber == 8)  MouseBot(3); //AutoCart
    else if (programNumber == 9)  RemoconCar(4); //PuttingBot
    else if (programNumber == 10)  RemoconCar(5); //CarrierBot
    else if (programNumber == 11)  MouseBot(4);
    else RemoconCar(0);  //RemoteCar
  }
  /*****************************************************************************************/
}
