/*
  SmartInventor.cpp - SmartInventor library
  Copyright (C) 2014 RoboLink.  All rights reserved.
*/

#include "SmartInventor.h"
//#include "Arduino.h"

byte spLight = 0b00111100;

void SmartInventorClass::TVRemoconUse() //control command
{
	remoconUseTV = 1;
		
//	irPIN = 6;
//	ChannelSW1 = 8;
//	ChannelSW2 = 9;
//	ChannelSW3 = 10;

	//64분주 - 100us 타이머
	//ir receiver
	//pinMode(irPIN, INPUT);
	DDRB &= ~0b10000;
	
	//dip sw - id set
	//pinMode(ChannelSW1, INPUT_PULLUP);
	//pinMode(ChannelSW2, INPUT_PULLUP);
	//pinMode(ChannelSW3, INPUT_PULLUP);
	
	DDRB  &= ~1100000;
	PORTB |=  1100000;
		  
	Timer2Set();
}
void SmartInventorClass::TVRemoconClose() //control command
{
	remoconUseTV = 0;
	if(dcUse == 0 || remoconUseTV == 0 || remoconUseRF == 0) TIMSK |= (0<<TOIE2);  
}
int SmartInventorClass::TVRemoconData()
{
	SmartInventor.RemoconSetChannel(); 
	return dataCode;
}

void SmartInventorClass::RemoconSetChannel()
{
	
//	RemoconChannel  = digitalRead(ChannelSW1);
//	RemoconChannel |= (digitalRead(ChannelSW2)<<1);
//	RemoconChannel = 0b11 - RemoconChannel;
	
	remoconChannel = (((~PINB) >> 5) & 0b011);
	
	if((remoconUseRF == 1) && (RFdataCode != 0))
	{
	  	Button_up = Rf_KEY_U;
		Button_down = Rf_KEY_D;
		Button_left = Rf_KEY_L;
		Button_right= Rf_KEY_R;
//		Button_center = 512;
		Button_func1 = Rf_KEY_1;
		Button_func2 = Rf_KEY_2;
		Button_func3 = Rf_KEY_3;
		Button_func4 = Rf_KEY_4;
		Button_funcr = Rf_KEY_5;
		Button_funcl = Rf_KEY_6;
	}
	
	//ch1
	else if(remoconChannel == 0b00)
	{
	  	Button_up = CH1_KEY_U;
		Button_down = CH1_KEY_D;
		Button_left = CH1_KEY_L;
		Button_right= CH1_KEY_R;
		Button_center = CH1_KEY_C;
		Button_func1 = CH1_KEY_F1;
		Button_func2 = CH1_KEY_F2;
		Button_func3 = CH1_KEY_F3;
		Button_func4 = CH1_KEY_F4;
		Button_ch1 = CH1_KEY_CH1;
		Button_ch2 = CH1_KEY_CH2;
		Button_ch3 = CH1_KEY_CH3;
		Button_ch4 = CH1_KEY_CH4;
	}
	
	//ch2
	else if(remoconChannel == 0b01)
	{
	  	Button_up = CH2_KEY_U;
		Button_down = CH2_KEY_D;
		Button_left = CH2_KEY_L;
		Button_right= CH2_KEY_R;
		Button_center = CH2_KEY_C;
		Button_func1 = CH2_KEY_F1;
		Button_func2 = CH2_KEY_F2;
		Button_func3 = CH2_KEY_F3;
		Button_func4 = CH2_KEY_F4;
		Button_ch1 = CH2_KEY_CH1;
		Button_ch2 = CH2_KEY_CH2;
		Button_ch3 = CH2_KEY_CH3;
		Button_ch4 = CH2_KEY_CH4;
	}
	
	//ch3
	else if(remoconChannel == 0b10)
	{
	  	Button_up = CH3_KEY_U;
		Button_down = CH3_KEY_D;
		Button_left = CH3_KEY_L;
		Button_right= CH3_KEY_R;
		Button_center = CH3_KEY_C;
		Button_func1 = CH3_KEY_F1;
		Button_func2 = CH3_KEY_F2;
		Button_func3 = CH3_KEY_F3;
		Button_func4 = CH3_KEY_F4;
		Button_ch1 = CH3_KEY_CH1;
		Button_ch2 = CH3_KEY_CH2;
		Button_ch3 = CH3_KEY_CH3;
		Button_ch4 = CH3_KEY_CH4;
	}
	
	//ch4
	else if(remoconChannel == 0b11)
	{
	  	Button_up = CH4_KEY_U;
		Button_down = CH4_KEY_D;
		Button_left = CH4_KEY_L;
		Button_right= CH4_KEY_R;
		Button_center = CH4_KEY_C;
		Button_func1 = CH4_KEY_F1;
		Button_func2 = CH4_KEY_F2;
		Button_func3 = CH4_KEY_F3;
		Button_func4 = CH4_KEY_F4;
		Button_ch1 = CH4_KEY_CH1;
		Button_ch2 = CH4_KEY_CH2;
		Button_ch3 = CH4_KEY_CH3;
		Button_ch4 = CH4_KEY_CH4;
	}
}

void SmartInventorClass::TVRemocon()
{
  if (TimeOutCheckEnd(220))
   {
	   dataCode = 0;
	   codeBuffer = 0;
	   dataCount = 0;
	   stateTVReceive = 0;
   }

  IR_in = !(((~PINB) >> 4) & 0b1);

  if(stateTVReceive == startReadCode)	  	//3step - DataCode check
  {  
    CheckDataCode();
  }
  
  else if(stateTVReceive == findLeadCode)	//2step - CustomCodeStart
  {
    CheckCustomCode();
  }
  
  else if(stateTVReceive == 0)	  		//1step - Lead code check
  {
    CheckLeadCode();
  }  
}

void SmartInventorClass::CheckLeadCode()
{
  if(!inputStatus)
  {
    if(IR_in == LOW)
    {
      inputStatus = 1;
      LeadPreviousMillis = millis();
    }
  }
  else
  {
    if(IR_in == HIGH)
    {
      inputStatus = 0;
      if(TimeCheckLeadcode(LeadCodetime))
      {
    	stateTVReceive = findLeadCode;    
        CodePreviousMicros = micros();
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////
void SmartInventorClass::CheckCustomCode()
{
  if(IR_in == LOW)
  {
    if(TimeCheckCode(TimeChecktime))
    {
      stateTVReceive = startReadCode;
      CodePreviousMicros = micros();
      EndPreviousMillis = millis();
      inputStatus = 1;
    }
    else
    {
    	stateTVReceive = 0;
    }
  }
}
/////////////////////////////////////////////////////////////////////
void SmartInventorClass::CheckDataCode()
{
  if(TimeCheckEnd(EndChecktime))
  {
    TimeOutPreviousMillis = millis();
    codeBuffer = 0;
    dataCount = 0;
    stateTVReceive = 0;
  }
    
  else if(inputStatus)
  {
    if(IR_in == HIGH)
    {
      CodePreviousMicros = micros();
      EndPreviousMillis = millis();
      inputStatus = 0;
    }
  }
  
  else	//!inputStatus
  {
      if(IR_in == LOW)
      { 
	if(dataCount > 15 && dataCount < 24)
	{
		codeBuffer = codeBuffer << 1;
		
	        if(TimeCheckCode(TimeCheckdatatime))	
	        {
	        	codeBuffer |= 0x01;	//data 1
		}
	        else	
	        {
	       		codeBuffer &= ~0x01;	//data 0
		}
	}
	
        dataCount++;
        inputStatus = 1;
        
        if (dataCount == 24) 
        {
        	dataCode = codeBuffer;
        }        
     }
  }
}

/////////////////////////////////////////////////////////////////////

boolean SmartInventorClass::TimeCheckCode(word interval) //micros seconds
{
  boolean time = false; 
  unsigned long currentTimes = micros();
  if(currentTimes - CodePreviousMicros > interval) 
  {
    CodePreviousMicros = currentTimes;
    time = true;
  }
  return time;
}

boolean SmartInventorClass::TimeCheckLeadcode(word interval)  //milliseconds
{
  boolean time = false; 
  unsigned long currentTimes = millis();
  if(currentTimes - LeadPreviousMillis > interval) 
  {
    LeadPreviousMillis = currentTimes;
    time = true;
  }
  return time;
}

boolean SmartInventorClass::TimeCheckEnd(word interval)  //milliseconds
{
  boolean time = false; 
  unsigned long currentTimes = millis();
  if(currentTimes - EndPreviousMillis > interval) 
  {
    EndPreviousMillis = currentTimes;
    time = true;
  }
  return time;
}

boolean SmartInventorClass::TimeOutCheckEnd(word interval)  //milliseconds
{
  boolean time = false; 
  unsigned long currentTimes = millis();
  if(currentTimes - TimeOutPreviousMillis > interval) 
  {
    TimeOutPreviousMillis = currentTimes;
    time = true;
  }
  return time;
}

ISR(TIMER2_OVF_vect)
{
 TCNT2 = 0xE7;
 if(SmartInventor.remoconUseTV == 1)	SmartInventor.TVRemocon();
 if(SmartInventor.dcUse == 1)  		SmartInventor.DCControl(); 
 if(SmartInventor.remoconUseRF == 1)	SmartInventor.RFreceive();
 /*
 if(SmartInventor.segwayUse == 1)
 {
	if(SmartInventor.tic >= 10)
	{ 
		SmartInventor.tic = 0;
		SmartInventor.SegwayGain();
	}
	else
	{
		SmartInventor.tic++;
	}
 }
 */
 SmartInventor.DCPWMCount++;
 if(SmartInventor.DCPWMCount >= 130) {SmartInventor.DCPWMCount = 0;}//최고속도는 0~100이지만 pwm 카운터는 120으로하여 모터 드라이브의 부담을 줄여주도록 한다.(최고속도는 감소함)
}

/////////////////////////////////////////////////////
/*
void SmartInventorClass::SegwayInit()
{
	segwayUse = 1;
}
void SmartInventorClass::SegwayGain()
{
		different_deviation = deviation - past_deviation;
		past_deviation = deviation;
		cumulative_error = cumulative_error + different_deviation;
		gain = (proportional*deviation) + (integral * cumulative_error) + (differental * different_deviation);
		
		if ((gain > 0) && (adc_offset_filter[adc_offset_index] < 120))
		{
			adc_offset_filter[adc_offset_index] = adc_offset + 3 + (gain / 4);
		}
		else if ((gain < 0) && (adc_offset_filter[adc_offset_index] > -120))
		{
			adc_offset_filter[adc_offset_index] = adc_offset - 3 + (gain / 4);
		}
		adc_offset_index++;
		if (adc_offset_index == 8)
		{
			adc_offset_index = 0;
		}
}
*/
/////////////////////////////////////////////////////
//dc
void SmartInventorClass::DCMove(byte direction, byte speed)
{
	if(direction == forward)
	{
		SmartInventor.DCMotor(M1,CCW,speed);
		SmartInventor.DCMotor(M2,CW,speed); 
	}
	else if(direction == backward)
	{
		SmartInventor.DCMotor(M1,CW,speed);
		SmartInventor.DCMotor(M2,CCW,speed); 
	}
	else if(direction == left)
	{
		SmartInventor.DCMotor(M1,CW,speed);
		SmartInventor.DCMotor(M2,CW,speed); 
	}
	else if(direction == right)
	{
		SmartInventor.DCMotor(M1,CCW,speed);
		SmartInventor.DCMotor(M2,CCW,speed); 
	}
	else if(direction == stop)
	{
		SmartInventor.DCMotor(M1,STOP,0);
		SmartInventor.DCMotor(M2,STOP,0); 
	}
	else if(direction == loose)
	{
		SmartInventor.DCMotor(M1,LOOSE,0);
		SmartInventor.DCMotor(M2,LOOSE,0); 
	}
}



void SmartInventorClass::DCControl()
{
	//M1	
	if((dcDirection1 == STOP) || (dcDirection1 == LOOSE))
	{
		if(dcDirection1 == STOP)	//STop	
		{
			PORTB |= 0b11;
		}
		else				//loose
		{
			PORTB &=~ 0b11;
		}
	}
	else
	{	if(DCPWMCount <= dcSpeed1 )
		{
			if(StatePinA == HIGH)
			{
				PORTB |= 0b01;
			}
			else
			{
				PORTB |= 0b10;
			}			
		}
		else
		{
			PORTB &=~ 0b11;
		}
	}
	
	//M2	
	if((dcDirection2 == STOP) || (dcDirection2 == LOOSE))
	{
		if(dcDirection2 == STOP)	//STop		
		{
			PORTB |= 0b1100;
		}
		else 				//loose
		{
			PORTB &=~0b1100;
		}
	}
	else
	{
		if(DCPWMCount <= dcSpeed2 )
		{				
			if(StatePinB == HIGH)
			{
				PORTB |= 0b0100;
			}
			else
			{
				PORTB |= 0b1000;
			}				
		}
		else
		{
			PORTB &=~0b1100;
		}
	}
	
	
	if(dcExUse == 1)
	{		
		if((dcDirection3 == STOP) || (dcDirection3 == LOOSE))
		{
			if(dcDirection3 == STOP)	
			{
				PORTD |= 0b11000;
			}
			else
			{
				PORTD &=~0b11000;
			}
		}
		else
		{
			if(DCPWMCount <= dcSpeed3 )
			{				
				if(StatePinC == HIGH)
				{
					PORTD |=0b01000;
				}
				else
				{
					PORTD |=0b10000;
				}				
			}
			else
			{
				PORTD &=~0b11000;
			}
		}		
		
		
		if((dcDirection4 == STOP) || (dcDirection4 == LOOSE))
		{
			if(dcDirection4 == STOP)	
			{
				PORTD |= 0b1100000;
			}
			else
			{
				PORTD &=~0b1100000;
			}
		}
		//else if((dcDirection4 == CW) || (dcDirection4 == CCW))
		else
		{
			if(DCPWMCount <= dcSpeed4 )
			{				
				if(StatePinD == HIGH)
				{
					PORTD |=0b1000000;
				}
				else
				{
					PORTD |=0b0100000;
				}				
			}
			else
			{
				PORTD &=~0b1100000;
			}
		}
	}
}


void SmartInventorClass::DCMotorExtension()
{
	dcExUse = 1;
	DDRD |= 0b1111000;  
}

void SmartInventorClass::DCMotorUse()
{
	dcUse = 1;
			
	DDRB |= 0b1111;
		
	Timer2Set();
}
void SmartInventorClass::DCMotorClose()
{	
	if(dcExUse == 1)
	{
		dcExUse = 0;
		PORTD &=~0b1100000;
		PORTD &=~0b11000;
	}	
	PORTB &=~0b1100;
	PORTB &=~0b11;
	
	dcUse = 0;	
	
	if(dcUse == 0 || remoconUseTV == 0 || remoconUseRF == 0) TIMSK |= (0<<TOIE2);  
	 
}
void SmartInventorClass::DCMotor(char SelectMotor, char direction, char speed)
{
	if (SelectMotor == M1)
	{
		dcDirection1 = direction;
		dcSpeed1 = speed;
		
		if(direction == CW)
		{
			StatePinA = HIGH;
		}
		else if(direction == CCW)
		{
			StatePinA = LOW;
		}
	}
	
	else if (SelectMotor == M2)
	{
		dcDirection2 = direction;
		dcSpeed2 = speed;
		
		if(direction == CW)
		{
			StatePinB = HIGH;
		}
		else if(direction == CCW)
		{
			StatePinB = LOW;
		}
	}	
	
	else if (SelectMotor == M3)
	{
		dcDirection3 = direction;
		dcSpeed3 = speed;
		
		if(direction == CW)
		{
			StatePinC = HIGH;
		}
		else if(direction == CCW)
		{
			StatePinC = LOW;
		}
	}
	
	else if (SelectMotor == M4)
	{
		dcDirection4 = direction;
		dcSpeed4 = speed;
		
		if(direction == CW)
		{
			StatePinD = HIGH;
		}
		else if(direction == CCW)
		{
			StatePinD = LOW;
		}
	}
}

/////////////////////////////////////
//sound - buzz
void SmartInventorClass::Buzz(long frequency, int tempo) 
{
	if(buzzUse == 0)
	{
		buzzUse = 1;
  		//buzzPin = 7;	
 	 	//pinMode(buzzPin,OUTPUT);
 	 	DDRD |= 0b10000000;
	}
	
	int length = 1000/tempo;  //TEMPO
	long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
	long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
	
	for (long i=0; i < numCycles; i++)
	{ // for the calculated length of time...
		
		PORTD |= 0b10000000;		
	//	digitalWrite(buzzPin,HIGH); // write the buzzer pin high to push out the diaphram
	//	delayMicroseconds(delayValue); // wait for the calculated delay value
		while(!TimeCheckBuzz(delayValue));
		
		PORTD &=~0b10000000;				
	//	digitalWrite(buzzPin,LOW); // write the buzzer pin low to pull back the diaphram
	//	delayMicroseconds(delayValue); // wait again or the calculated delay value
		while(!TimeCheckBuzz(delayValue));
	}
}

boolean SmartInventorClass::TimeCheckBuzz(word interval) //micros seconds
{
  boolean time = false; 
  unsigned long currentTimes = micros();
  if(currentTimes - PreviousBuzz >= interval) 
  {
    PreviousBuzz = currentTimes;
    time = true;
  }
  return time;
}

/////////////////////////////////////
//basic milli ,micro timer;

boolean SmartInventorClass::TimeCheckMillis(word interval)  //milliseconds
{
  boolean time = false; 
  unsigned long currentTimes = millis();
  if(currentTimes - PreviousMillis >= interval) 
  {
    PreviousMillis = currentTimes;
    time = true;
  }
  return time;
}

boolean SmartInventorClass::TimeCheckMicros(word interval) //micros seconds
{
  boolean time = false; 
  unsigned long currentTimes = micros();
  if(currentTimes - PreviousMicros >= interval) 
  {
    PreviousMicros = currentTimes;
    time = true;
  }
  return time;
}

/////////////////////////////////////
//adc sensor
unsigned int SmartInventorClass::SensorCalibration(byte pin)
{	
  ADMUX = pin - 19;
  ADCSRA =  0x86; // (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1)
    
  ADCSRA |= 0x40;
  while ((ADCSRA & 0x10) == 0x00);
  lowLevel[pin - 19] = ADC;
    
  for (int i = 0; i < 100; i++)
  {
    ADCSRA |= 0x40;
    while ((ADCSRA & 0x10) == 0x00);
    lowLevel[pin - 19] = min(ADC, lowLevel[pin - 19]);
  }  
  return lowLevel[pin-19];
}


/////////////////////////////////////
//led preformance
void SmartInventorClass::LedPerformanceNumber(unsigned char num)
{
  DDRC = 0xff;

  if(num >= 26)
  {
    PORTC = 240;
    num = num - 26;
  }
  else if(num >= 21)
  {
    PORTC = 224;
    num = num - 21;
  }
  else if(num >= 15)
  {
    PORTC = 192;
    num = num - 15;
  }
  else if(num >= 8)
  {
    PORTC = 128;
    num = num - 8;
  }
  else
  {
    PORTC = 0;
  }
  PORTC = (1 << num) | PORTC;
}

void SmartInventorClass::LedArray(unsigned char num)
{	
  DDRC = 0xff;
  PORTC = num;
}

//Bluetooth
void SmartInventorClass::RFRemoconUse(long speed)
{
	remoconUseRF = 1;
	_count = 0;
	Serial.begin(speed);
	Timer2Set();
}


void SmartInventorClass::RFRemoconClose()
{
	remoconUseRF = 0;	
	if(dcUse == 0 || remoconUseTV == 0 || remoconUseRF == 0) TIMSK |= (0<<TOIE2);  
}


void SmartInventorClass::RFreceive()
{
	word data = 0xFFFF;
	int num = Serial.available();	
	
	for(int i=0; i<num; i++)
	{		
		int input = Serial.read();	 // this is 'int' to handle -1 when no data		
	
		if(input >= 0)
		{
			_packet[_count++] = (byte)input;
			
			if(_count > 6)
			{
				_header = 0;
				_count = 0;
			}
			
			else 
			{
				if(_count == 2)
				{
					if(_packet[0] == 0xFF && _packet[1] == 0x55)
					{
						_header = 1;
					}	
				}
				
			}
						
			if(_header == 1)
			{	
				if(_count == 6)
				{
					_header = 0;
					_count = 0;
								
					if(_packet[2] == (byte)(~_packet[3]) && _packet[4] == (byte)(~_packet[5]))
					{
						data = _packet[2];
						data |= (_packet[4] << 8) & 0xFF00;
					}
				}
			}
		}
	}

	if(data == 0xFFFF)	RFdataCode -1;
	else			RFdataCode = data;	
}

int SmartInventorClass::RFRemoconData()
{
	SmartInventor.RemoconSetChannel(); 
	return RFdataCode;
}


void SmartInventorClass::Timer2Set()
{
	//timer2 set
	TIMSK &= ~(1<<TOIE2);    
	TCCR2 &= ~((1<<WGM21) | (1<<WGM20));  
	ASSR &= ~(1<<AS2);
	TIMSK &= ~(1<<OCIE2);
	//64 - 100us
	TCCR2 |= (1<<CS22);                                  
	TCCR2 &= ~((1<<CS21) | (1<<CS20));
	//timer2 on
	TIMSK |= (1<<TOIE2);  
}
/////////////////////////////////////////////////////

byte SmartInventorClass::SpeedDisplay(byte speed, byte state)
{
	//0 down
	//1 up
	if(state == 1)
	{
		if (SmartInventor.TimeCheckMillis(500))
		{
			if (speed < 90)
			{
			  speed += 20;
			  SmartInventor.Buzz(1160, 12);
			}
		}
	}
	else
	{
		if (SmartInventor.TimeCheckMillis(500))
		{
			if (speed > 30)
			{
			  speed -= 20;	
			  SmartInventor.Buzz(1160, 12);
			}
		}
	}
	
		PORTC = ((((0b00001000 << (speed/20)) & 0b11110000) | (((0b00010000 >> (speed/20))) & 0b00001111)));
	
	
	return speed;
}

/////////////////////////////////////////////////////
SmartInventorClass SmartInventor;