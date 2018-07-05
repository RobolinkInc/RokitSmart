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

이 라이브러리는 DCmotor를 내부 인터럽트라는 예외적인 방법으로 제어합니다.
최대 8개의 DCmotor를 사용할 수 있지만 헤더 파일의 'MAX_MOTOR값을 변경하면
더 많은 모터들을 제어할 수 있습니다. 
다만 아두이노의 밀리세컨트 시스템을 깨지 않기 위해 100Hz의 낮은 PWM으로 모터의
속도를 제어합니다. 따라서 정밀한 속도변화를 요구하는 제어는 불가능합니다. 
따라서 이 라이브러리는 다수의 모터를 그다지 정밀하지 않은 방법으로 제어하고자 할때
사용합니다. 
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



