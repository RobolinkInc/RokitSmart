/*
  IRRemocon.cpp - IRRemocon library
  Copyright (C) 2014 RoboLink.  All rights reserved.
*/

#include "Arduino.h"
#include "IRRemocon.h"

unsigned char temp = 0;

IRRemocon::IRRemocon()
{  
	_IRCnt = 0; _IRIndex = 0; _IRInterval = 0;
	_buttonUp = 0; _IRTimer = 0;
}

void IRRemocon::remocon()
{
    unsigned long pastTime = 0;   
	unsigned long now = micros();
    unsigned char sPin0, sPin1, sPin2;
	unsigned char dipSW = 0;
    
		
	pastTime = now - _lastTime;
	
	if(pastTime >= BITREADTERM)
	{
	    
		_IRIn = digitalRead(_recPin);
	    
		sPin0 = digitalRead(_channelPin0);
	    sPin1 = digitalRead(_channelPin1);
	    sPin2 = digitalRead(_channelPin2);
				
		dipSW = (~(sPin0 | (sPin1 << 1) | (sPin2 << 2))) & 0b00000111;
		// 스위치ID와 리모컨 수신값은 역수이며 하위 3비트 이외에는 0으로 만든다.

        if (_IRTimer > 0) {_IRTimer = _IRTimer - pastTime;  }  //일정시간이 지나면 버튼업으로 간주
		if (_IRTimer <= 0) _IRData = 0;
		
		
		if (_IRIn == 0)              
	    {
			_IRFlag = 1;            
	    }
	
	    if (_IRIndex < 3)                           //3바이트를 읽어들임. 
	    {
		    _dataBuffer[_IRIndex] |= _IRFlag << _IRCnt;  // 비트를 읽어들인다. 
		    _IRFlag = 0;
	    }

	    else if (_IRIndex >= 3)             //3바이트를 다 읽어들이면 패킷에서 데이타를 추출함 
    	{
	    						
	//		if (_dataBuffer[0]  == ((dipSW << 4) | 0b101))    //수신한 데이터의 ID가 제어기의 DIP_sw설정과 동일한가(하위 3비트(0b101)은 startbits임)
	//	    {
			   _IRData = (_dataBuffer[1] + (_dataBuffer[2] << 8));  
               _IRTimer = BUTTONUPTIME; 
	  //		}
           
				    
            _dataBuffer[0] = 0;
	 	    _dataBuffer[1] = 0;
	        _dataBuffer[2] = 0;
			
	    
	    }
	
      // ir input start
	   if ((_IRIn == 0) && (_IRIndex == 3))             //초기화
	   {
	       _IRCnt = 0; _IRIndex = 0; _IRInterval = 0;
		   
          
	   }

        _IRInterval++;

		if(_IRInterval >= 3)
		{
			_IRInterval = 0;

            _IRCnt++;
	
	        if (_IRCnt >= 8)
	        {
	    	    _IRCnt = 0;
			
		        if (_IRIndex < 3)
		        {
			        _IRIndex++;           //8비트가 되면 인덱스를 1증가시켜 다음 바이트 읽을 준비 
			    }
	        }
		}

         // ir timer
		
        (*callback)();

		_lastTime = now;	    
    }

}

void IRRemocon::attachCallback(void(*func)())
{
	callback = func;
}

void IRRemocon::update()
{
   remocon();
}


unsigned int IRRemocon::read()
{
   return _IRData;
}

void IRRemocon::channelPins(unsigned char Pin0, unsigned char Pin1, unsigned char Pin2)
{

	_channelPin0 = Pin0;
	_channelPin1 = Pin1;
	_channelPin2 = Pin2;
	
	pinMode(Pin0, INPUT);
	pinMode(Pin1, INPUT);
	pinMode(Pin2, INPUT);

	digitalWrite(Pin0, HIGH);
	digitalWrite(Pin1, HIGH);
	digitalWrite(Pin2, HIGH);
}


void IRRemocon::receiverPin(unsigned char Pin)
{
	_recPin = Pin;
	pinMode(Pin, INPUT);
	digitalWrite(Pin, HIGH);
}

void IRRemocon::rokitSetup()
{
    channelPins(DIPSW1, DIPSW2, DIPSW3);
	receiverPin(RECEIVERPIN);
}