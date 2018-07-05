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

�� ���̺귯���� DCmotor�� ���� ���ͷ�Ʈ��� �������� ������� �����մϴ�.
�ִ� 8���� DCmotor�� ����� �� ������ ��� ������ 'MAX_MOTOR���� �����ϸ�
�� ���� ���͵��� ������ �� �ֽ��ϴ�. 
�ٸ� �Ƶ��̳��� �и�����Ʈ �ý����� ���� �ʱ� ���� 100Hz�� ���� PWM���� ������
�ӵ��� �����մϴ�. ���� ������ ���ӵ��� ����� �Ұ����մϴ�. 
���� �� ���̺귯���� �ټ��� ���͸� �״��� �������� ���� ������� �����ϰ��� �Ҷ�
����մϴ�. 

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

