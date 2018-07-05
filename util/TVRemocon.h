/*
  TVRemocon.h - TVRemocon library
  Copyright (C) 2014 RoboLink.  All rights reserved.
*/
#ifndef TVRemocon_h
#define TVRemocon_h

#include "IRremoteTV.h"

// For hunoi16 Setup

#if defined(__AVR_ATmega128__) 
#define  RECV_PIN    8
#define  ARDUX_SW1  43
#define  ARDUX_SW2  44
#else 
#define  RECV_PIN    10
#define  ARDUX_SW1   3
#define  ARDUX_SW2   4
#endif

#define  BUTTON_UP   0x00
#define  BUTTON_DOWN 0xFF
#define  LIMIT_TIME  200


#define  CH1_KEY_CH1  0x14
#define  CH1_KEY_CH2  0x15
#define  CH1_KEY_CH3  0x16 
#define  CH1_KEY_CH4  0x17

#define  CH2_KEY_CH1  0xE4
#define  CH2_KEY_CH2  0xE5
#define  CH2_KEY_CH3  0xE6 
#define  CH2_KEY_CH4  0xE7

#define  CH3_KEY_CH1  0x64
#define  CH3_KEY_CH2  0x65
#define  CH3_KEY_CH3  0x66 
#define  CH3_KEY_CH4  0x67

#define  CH4_KEY_CH1  0xA4
#define  CH4_KEY_CH2  0xA5
#define  CH4_KEY_CH3  0xA6 
#define  CH4_KEY_CH4  0xA7


#define  CH1_KEY_U   0x80
#define  CH1_KEY_D   0x40
#define  CH1_KEY_L   0x20
#define  CH1_KEY_R   0x10
#define  CH1_KEY_C   0xF0
#define  CH1_KEY_F1  0x08
#define  CH1_KEY_F2  0x88
#define  CH1_KEY_F3  0x48
#define  CH1_KEY_F4  0xC8

#define  CH2_KEY_U   0x8D
#define  CH2_KEY_D   0x4D
#define  CH2_KEY_L   0x2D
#define  CH2_KEY_R   0x1D
#define  CH2_KEY_C   0xFD
#define  CH2_KEY_F1  0x04
#define  CH2_KEY_F2  0x84
#define  CH2_KEY_F3  0x44
#define  CH2_KEY_F4  0xC4

#define  CH3_KEY_U   0x83
#define  CH3_KEY_D   0x43
#define  CH3_KEY_L   0x23
#define  CH3_KEY_R   0x13
#define  CH3_KEY_C   0xF3
#define  CH3_KEY_F1  0x0C
#define  CH3_KEY_F2  0x8C
#define  CH3_KEY_F3  0x4C
#define  CH3_KEY_F4  0xCC

#define  CH4_KEY_U   0x8B
#define  CH4_KEY_D   0x4B
#define  CH4_KEY_L   0x2B
#define  CH4_KEY_R   0x1B
#define  CH4_KEY_C   0xFB
#define  CH4_KEY_F1  0x02
#define  CH4_KEY_F2  0x82
#define  CH4_KEY_F3  0x42
#define  CH4_KEY_F4  0xC2

#define  KEY_U       TVRemocon._up
#define  KEY_D       TVRemocon._down
#define  KEY_L       TVRemocon._left
#define  KEY_R       TVRemocon._right
#define  KEY_C       TVRemocon._center
#define  KEY_F1      TVRemocon._func1
#define  KEY_F2      TVRemocon._func2
#define  KEY_F3      TVRemocon._func3
#define  KEY_F4      TVRemocon._func4
#define  KEY_CH1     TVRemocon._ch1
#define  KEY_CH2     TVRemocon._ch2
#define  KEY_CH3     TVRemocon._ch3
#define  KEY_CH4     TVRemocon._ch4

class TVRemoconClass
{
  public:
	TVRemoconClass(void);
	void begin(void);
	unsigned char receive(void);
	unsigned int customCode(void);
	
	unsigned char _up;
	unsigned char _down;
	unsigned char _left;
	unsigned char _right;
	unsigned char _center;
	unsigned char _func1;
	unsigned char _func2;
	unsigned char _func3;
	unsigned char _func4;
	unsigned char _ch1;
	unsigned char _ch2;
	unsigned char _ch3;
	unsigned char _ch4;

  private:
    void SWCheck(void);
	
    
};

extern TVRemoconClass TVRemocon;

#endif 