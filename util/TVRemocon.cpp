/*
  TVRemocon.cpp - TVRemocon library
  Copyright (C) 2014 RoboLink.  All rights reserved.
*/

#include "Arduino.h"
#include "TVRemocon.h"

unsigned long _recvData = 0;
unsigned char _key = 0;
unsigned int _CID = 0;
unsigned long _lastTime = 0;
unsigned long _limitTime = 0;
unsigned char _exSwitchID = 0xff;



IRrecv _irrecv(RECV_PIN);
decode_results _results;

TVRemoconClass::TVRemoconClass()
{
	_up = CH1_KEY_U;
	_down = CH1_KEY_D;
	_left = CH1_KEY_L;
	_right = CH1_KEY_R;
	_center = CH1_KEY_C;
	_func1 = CH1_KEY_F1;
	_func2 = CH1_KEY_F2;
	_func3 = CH1_KEY_F3;
	_func4 = CH1_KEY_F4;
	_ch1 = CH1_KEY_CH1;
	_ch2 = CH1_KEY_CH2;
	_ch3 = CH1_KEY_CH3;
	_ch4 = CH1_KEY_CH4;
}

void TVRemoconClass::begin()
{
	pinMode(ARDUX_SW1, INPUT_PULLUP);
	pinMode(ARDUX_SW2, INPUT_PULLUP);
		
	_irrecv.enableIRIn(); 
}

unsigned char TVRemoconClass::receive()
{
   unsigned long _pastTime = 0;
   unsigned long now = millis();
   unsigned char temp = 0;
   
   _pastTime = now - _lastTime;  

   _limitTime = _limitTime + _pastTime;
   if (_limitTime >= LIMIT_TIME) 
   {
     _key = BUTTON_UP;
   }     
           
   if (_irrecv.decode(&_results))
   {
     SWCheck();
	 
	 _limitTime = 0;
     _recvData = _results.value;
     _CID = (_recvData & 0xffff0000) >> 16;
     temp = (_recvData & 0x0000ff00) >> 8;
     if(temp != BUTTON_DOWN) _key = temp;
    
     _irrecv.resume(); 
   }
      
  _lastTime = now;

  return _key;
}


void TVRemoconClass::SWCheck()
{
	unsigned char switchID = 0;
	
	switchID = digitalRead(ARDUX_SW1) + (digitalRead(ARDUX_SW2) << 1);
	
	if(_exSwitchID != switchID)
	{
		if( switchID == 3)
		{
			_up = CH1_KEY_U;
			_down = CH1_KEY_D;
			_left = CH1_KEY_L;
			_right= CH1_KEY_R;
			_center = CH1_KEY_C;
			_func1 = CH1_KEY_F1;
			_func2 = CH1_KEY_F2;
			_func3 = CH1_KEY_F3;
			_func4 = CH1_KEY_F4;
			_ch1 = CH1_KEY_CH1;
			_ch2 = CH1_KEY_CH2;
			_ch3 = CH1_KEY_CH3;
			_ch4 = CH1_KEY_CH4;
		}
		else if(switchID == 2)
        {
		    _up = CH2_KEY_U;
			_down = CH2_KEY_D;
			_left = CH2_KEY_L;
			_right = CH2_KEY_R;
			_center = CH2_KEY_C;
			_func1 = CH2_KEY_F1;
			_func2 = CH2_KEY_F2;
			_func3 = CH2_KEY_F3;
			_func4 = CH2_KEY_F4;
			_ch1 = CH2_KEY_CH1;
			_ch2 = CH2_KEY_CH2;
			_ch3 = CH2_KEY_CH3;
			_ch4 = CH2_KEY_CH4;
				
        }
        else if(switchID == 1)
        {
		    _up = CH3_KEY_U;
			_down = CH3_KEY_D;
			_left = CH3_KEY_L;
			_right = CH3_KEY_R;
			_center = CH3_KEY_C;
			_func1 = CH3_KEY_F1;
			_func2 = CH3_KEY_F2;
			_func3 = CH3_KEY_F3;
			_func4 = CH3_KEY_F4;
			_ch1 = CH3_KEY_CH1;
			_ch2 = CH3_KEY_CH2;
			_ch3 = CH3_KEY_CH3;
			_ch4 = CH3_KEY_CH4;
        }
        else if(switchID == 0)
        {
		    _up = CH4_KEY_U;
			_down = CH4_KEY_D;
			_left = CH4_KEY_L;
			_right = CH4_KEY_R;
			_center = CH4_KEY_C;
			_func1 = CH4_KEY_F1;
			_func2 = CH4_KEY_F2;
			_func3 = CH4_KEY_F3;
			_func4 = CH4_KEY_F4;
			_ch1 = CH4_KEY_CH1;
			_ch2 = CH4_KEY_CH2;
			_ch3 = CH4_KEY_CH3;
			_ch4 = CH4_KEY_CH4;
			
        }	
		
		_exSwitchID = switchID; 
	}
	
}


unsigned int TVRemoconClass::customCode()
{
	return _CID;
}


 TVRemoconClass TVRemocon;
