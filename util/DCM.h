/*
  DCM.h - DCM library
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
�ӵ��� �����մϴ�. ���� ������ �ӵ���ȭ�� �䱸�ϴ� ����� �Ұ����մϴ�. 
���� �� ���̺귯���� �ټ��� ���͸� �״��� �������� ���� ������� �����ϰ��� �Ҷ�
����մϴ�. 
*/

#ifndef DCM_h
#define DCM_h

#include "Arduino.h"

#define MAX_MOTOR  8
#define USED       1
#define NOT_USE    0
#define CW         1
#define CCW        2
#define STOP       3
#define LOOSE      4

// Switch on LED on pin 13 each second 

typedef struct {
  unsigned char Pin0;
  unsigned char Pin1;
  unsigned char StatePin0;
  unsigned char StatePin1;
  unsigned char Speed;
} OpMotor;


class DCM
{
  public:
    DCM();
    int attachPins(unsigned char pin0, unsigned char pin1);
    void write(unsigned char Dir, unsigned char value);
    	  
 private:
    unsigned char _MotorIndex;
};


//extern void InputLogic();
#endif



