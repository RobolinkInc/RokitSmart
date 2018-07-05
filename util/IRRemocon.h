/*
  IRRemocon.h - IR Remocon library
  Copyright (C) 2014 RoboLink.  All rights reserved.
*/

//인터럽트가 아닌 폴링방식의 IR수신 프로그램입니다.

#ifndef IRRemocon_h
#define IRRemocon_h

#include "Arduino.h"

/*
// For hunoi16 Setup
#define DIPSW1	2               
#define DIPSW2	3
#define DIPSW3  4
#define RECEIVERPIN    5   // smart servobox: 5  arduX 100 :10
*/
/////////////////////////////


#define DIPSW1	43               
#define DIPSW2	44
#define DIPSW3  45
#define RECEIVERPIN    11   // smart servobox: 5  arduX 100 :10


/////////////////////////////

#define BITREADTERM    500
#define BUTTONUPTIME   300000

#define KEY_UP	0
#define KEY_U	1
#define KEY_D	2
#define KEY_L	4
#define KEY_R	8
#define KEY_1	16
#define KEY_2	32
#define KEY_3	64
#define KEY_4	128
#define KEY_5	256
#define KEY_6	512

class IRRemocon
{
  public:
	IRRemocon();
	void update();
	unsigned int read();
	void attachCallback(void(*func)(void));
	void channelPins(unsigned char Pin0, unsigned char Pin1, unsigned char Pin2);
	void receiverPin(unsigned char Pin);
	void rokitSetup();
	void (*callback)(void);
	unsigned int _IRData;
	

  private:
    void remocon();
    unsigned char _recPin;
	unsigned char _IRIn;
	unsigned char _dipSW;
	unsigned char _IRFlag;
	unsigned char _IRIndex;
	unsigned char _IRCnt;
	signed long  _IRTimer;
    unsigned char _IRInterval;
    unsigned char _buttonUp;
	unsigned long _lastTime;
	unsigned char _dataBuffer[3];
  
    unsigned char _channelPin0, _channelPin1, _channelPin2;
};

#endif 