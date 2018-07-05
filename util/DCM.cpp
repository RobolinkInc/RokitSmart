/*
  DCM.cpp - DCM library
  Copyright (C) 2014 RoboLink.  All rights reserved.
 
This library control DCmotors using the exceptional way that is based on the internal interrupt.
You can use at most eight DC motor, 
but if you modify 'MAX_MOTOR' value of the headerfile,you can control more motors. 
This library control the speed of motor in the low PWM of 100Hz 
for continuing milisecond based system of Arduino.
therefore it is impossible to control motor precisly in the low speed. 
but this library is of benefit to controlling many motors by a rough speed control method.

이 라이브러리는 DCmotor를 내부 인터럽트라는 예외적인 방법으로 제어합니다.
최대 8개의 DCmotor를 사용할 수 있지만 헤더 파일의 'MAX_MOTOR값을 변경하면
더 많은 모터들을 제어할 수 있습니다. 
다만 아두이노의 밀리세컨트 시스템을 깨지 않기 위해 100Hz의 낮은 PWM으로 모터의
속도를 제어합니다. 따라서 정밀한 저속도의 제어는 불가능합니다. 
따라서 이 라이브러리는 다수의 모터를 그다지 정밀하지 않은 방법으로 제어하고자 할때
사용합니다. 

*/


#include "Arduino.h"
#include "MsTimer2.h"
#include "DCM.h"

unsigned char MotorCount = 0;
unsigned char PWMCount = 0;
boolean IsTimerActive = false; 
static OpMotor _Motor[MAX_MOTOR];

//void InputLogic();

void InputLogic()
{
    unsigned char i = 0;
    
	for (i = 0; i < MotorCount; i++)
	{
		if(_Motor[i].Speed >= PWMCount) 
		{
			digitalWrite(_Motor[i].Pin0, _Motor[i].StatePin0);
			digitalWrite(_Motor[i].Pin1, _Motor[i].StatePin1);
     	}
		else
		{	
			digitalWrite(_Motor[i].Pin0, LOW);
			digitalWrite(_Motor[i].Pin1, LOW);
        }
		
	}
    
	PWMCount++;
	if(PWMCount >= 10) {PWMCount = 0; }
}


DCM::DCM()
{
    _MotorIndex = MotorCount;
	
	MotorCount++;
    if(MotorCount >= MAX_MOTOR) MotorCount = MAX_MOTOR;
}

int DCM::attachPins(unsigned char pin0, unsigned char pin1)
{
   	   
   _Motor[_MotorIndex].Pin0 = pin0;
   _Motor[_MotorIndex].Pin1 = pin1;
   _Motor[_MotorIndex].StatePin0 = LOW;
   _Motor[_MotorIndex].StatePin1 = LOW;
   _Motor[_MotorIndex].Speed = 0;
        
   pinMode(pin0, OUTPUT);
   pinMode(pin1, OUTPUT);

   if(IsTimerActive == false)
   {
	   MsTimer2::set(1, InputLogic); // 1ms period
       MsTimer2::start();

	   IsTimerActive = true;
   }
   
   return _MotorIndex;
}

void DCM::write(unsigned char Dir, unsigned char value)
{
	if(Dir == CW) {_Motor[_MotorIndex].StatePin0 = HIGH; _Motor[_MotorIndex].StatePin1 = LOW; }
	else if(Dir == CCW)  {_Motor[_MotorIndex].StatePin0 = LOW; _Motor[_MotorIndex].StatePin1 = HIGH; }
	else if(Dir == STOP) {_Motor[_MotorIndex].StatePin0 = HIGH; _Motor[_MotorIndex].StatePin1 = HIGH; }
	else {_Motor[_MotorIndex].StatePin0 = LOW; _Motor[_MotorIndex].StatePin1 = LOW; }
	
    _Motor[_MotorIndex].Speed = value;   
}

