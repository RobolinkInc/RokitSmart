/*
  SmartInventor.h - SmartInventor library
  Copyright (C) 2014 RoboLink.  All rights reserved.
  
  TIMER2 USE
  TVREMOCON FOLLING
  
*/

#ifndef SmartInventor_h
#define SmartInventor_h
#include "Arduino.h"
#include <avr/interrupt.h>
/***********************************************************************/

//TVRemocon
#define customCodeTVremocon 0b1110000011100000

#define  CH1_KEY_U   0x80
#define  CH1_KEY_D   0x40
#define  CH1_KEY_L   0x20
#define  CH1_KEY_R   0x10
#define  CH1_KEY_C   0xF0
#define  CH1_KEY_F1  0x08
#define  CH1_KEY_F2  0x88
#define  CH1_KEY_F3  0x48
#define  CH1_KEY_F4  0xC8

#define  CH1_KEY_CH1  0x14
#define  CH1_KEY_CH2  0x15
#define  CH1_KEY_CH3  0x16 
#define  CH1_KEY_CH4  0x17


#define  CH2_KEY_U   0x8D
#define  CH2_KEY_D   0x4D
#define  CH2_KEY_L   0x2D
#define  CH2_KEY_R   0x1D
#define  CH2_KEY_C   0xFD
#define  CH2_KEY_F1  0x04
#define  CH2_KEY_F2  0x84
#define  CH2_KEY_F3  0x44
#define  CH2_KEY_F4  0xC4

#define  CH2_KEY_CH1  0xE4
#define  CH2_KEY_CH2  0xE5
#define  CH2_KEY_CH3  0xE6 
#define  CH2_KEY_CH4  0xE7

#define  CH3_KEY_U   0x83
#define  CH3_KEY_D   0x43
#define  CH3_KEY_L   0x23
#define  CH3_KEY_R   0x13
#define  CH3_KEY_C   0xF3
#define  CH3_KEY_F1  0x0C
#define  CH3_KEY_F2  0x8C
#define  CH3_KEY_F3  0x4C
#define  CH3_KEY_F4  0xCC

#define  CH3_KEY_CH1  0x64
#define  CH3_KEY_CH2  0x65
#define  CH3_KEY_CH3  0x66 
#define  CH3_KEY_CH4  0x67

#define  CH4_KEY_U   0x8B
#define  CH4_KEY_D   0x4B
#define  CH4_KEY_L   0x2B
#define  CH4_KEY_R   0x1B
#define  CH4_KEY_C   0xFB
#define  CH4_KEY_F1  0x02
#define  CH4_KEY_F2  0x82
#define  CH4_KEY_F3  0x42
#define  CH4_KEY_F4  0xC2
	
#define  CH4_KEY_CH1  0xA4
#define  CH4_KEY_CH2  0xA5
#define  CH4_KEY_CH3  0xA6 
#define  CH4_KEY_CH4  0xA7

#define  Rf_KEY_UP	0x00
#define  Rf_KEY_U	0x01
#define  Rf_KEY_D	0x02
#define  Rf_KEY_L	0x04
#define  Rf_KEY_R	0x08

#define  Rf_KEY_1	0x10
#define  Rf_KEY_2	0x20
#define  Rf_KEY_3	0x40
#define  Rf_KEY_4	0x80
#define  Rf_KEY_5	0x100
#define  Rf_KEY_6	0x200
	
#define  KEY_U       SmartInventor.Button_up
#define  KEY_D       SmartInventor.Button_down
#define  KEY_L       SmartInventor.Button_left
#define  KEY_R       SmartInventor.Button_right
#define  KEY_C       SmartInventor.Button_center
#define  KEY_F1      SmartInventor.Button_func1
#define  KEY_F2      SmartInventor.Button_func2
#define  KEY_F3      SmartInventor.Button_func3
#define  KEY_F4      SmartInventor.Button_func4
#define  KEY_CH1     SmartInventor.Button_ch1
#define  KEY_CH2     SmartInventor.Button_ch2
#define  KEY_CH3     SmartInventor.Button_ch3
#define  KEY_CH4     SmartInventor.Button_ch4
//zig-100,rokit-rc
#define  KEY_FL      SmartInventor.Button_funcl	
#define  KEY_FR      SmartInventor.Button_funcr
/***********************************************************************/
#define  RFdata	     SmartInventor.RFdataCode


//dc

#define CW		1
#define CCW		2
#define STOP		3
#define LOOSE		4

#define FORWARD		1	
#define BACKWARD	2
#define LEFT 		5
#define RIGHT 		6

#define forward		FORWARD 	
#define backward	BACKWARD	
#define stop		STOP 		
#define loose		LOOSE 		
#define left		LEFT 		
#define right		RIGHT 		

#define M1	1
#define M2	2
#define M3	3
#define M4	4


//buzz
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// Switch on LED on pin 13 each second 


#define	 LeadCodetime  	8
#define	 TimeChecktime  3000
#define	 EndChecktime  	7
#define	 TimeCheckdatatime  1500

#define  findLeadCode 1
#define  startReadCode 2


/***********************************************************************/

class SmartInventorClass
{
public:
	//TVRemocon
	void TVRemoconUse();  	//control command
	void TVRemocon();
	int TVRemoconData();
	void RemoconSetChannel();
	
	volatile unsigned char remoconUseTV;
	unsigned char dataCode;
	unsigned char remoconChannel;
			
	unsigned char Button_up;
	unsigned char Button_down;
	unsigned char Button_left;
	unsigned char Button_right;
	unsigned char Button_center;
	unsigned char Button_func1;
	unsigned char Button_func2;
	unsigned char Button_func3;
	unsigned char Button_func4;
	unsigned char Button_ch1;
	unsigned char Button_ch2;
	unsigned char Button_ch3;
	unsigned char Button_ch4;
	
	unsigned char Button_funcl;	
	unsigned char Button_funcr;
	
	void DCMotorUse();
	void DCMotorExtension();	// dcm use
	void DCMove(byte direction, byte speed);
	void DCMotor(char SelectMotor, char direction, char speed);
	void DCControl();
				
	volatile unsigned char dcExUse;		
	volatile unsigned char dcUse;
	volatile unsigned char  DCPWMCount;	
	
	//buzzer
	void Buzz(long frequency, int tempo);
	
	//basic timer
	boolean TimeCheckMicros(word interval); //micros seconds
	boolean TimeCheckMillis(word interval);  //milliseconds
 	unsigned long PreviousMillis;
 	unsigned long PreviousMicros;
 	
 	//adc sensor
	unsigned int SensorCalibration(byte pin);
	
	//led
	void LedPerformanceNumber(unsigned char num);
	void LedArray(unsigned char num);
	
	//bluetooth
	void RFRemoconUse(long speed);
	int RFRemoconData();
	void RFreceive();
	int RFdataCode;
	volatile unsigned char remoconUseRF;
	
	//off
	void RFRemoconClose();
	void TVRemoconClose();
	void DCMotorClose();
	
	//model util
	byte SpeedDisplay(byte speed, byte state);
	
	/*
	//segway
	void SegwayGain();
	void SegwayInit();
	
	volatile unsigned char segwayUse;
	volatile unsigned char adc_offset_index;
	volatile int adc_offset;
	volatile int different_deviation;
	volatile int adc_offset_filter[8];
	volatile int cumulative_error;
	volatile int proportional;
	volatile int integral;
	volatile int differental;
	volatile int past_deviation;
	volatile int gain;
	volatile int deviation;
	volatile unsigned char tic;
	*/
	
private:
	//TVRemocon
	void CheckLeadCode();
	void CheckCustomCode();
	void CheckDataCode();
	
	boolean TimeCheckCode(word interval); //micros seconds
	boolean TimeCheckLeadcode(word interval);  //milliseconds
	boolean TimeCheckEnd(word interval);  //milliseconds
	boolean TimeOutCheckEnd(word interval);  //milliseconds

	unsigned char IR_in;
	
	long CodePreviousMicros;
	long EndPreviousMillis;
	long LeadPreviousMillis; 
	long TimeOutPreviousMillis;

	unsigned char inputStatus;
	unsigned char stateTVReceive;
	unsigned char dataCount;
	unsigned char codeBuffer;
	
	//dc
	unsigned char dcDirection1;
	unsigned char dcDirection2;
	unsigned char dcDirection3;
	unsigned char dcDirection4;
		
	unsigned char dcSpeed1;
	unsigned char dcSpeed2;
	unsigned char dcSpeed3;
	unsigned char dcSpeed4;
	
	unsigned char StatePinA;
	unsigned char StatePinB;
	unsigned char StatePinC;
	unsigned char StatePinD;

 	/*********************************/
 	 	
 	//buzzer
 	boolean TimeCheckBuzz(word interval); 
 	unsigned char buzzUse;
 	unsigned char buzzPin;
 	long	PreviousBuzz;
 	
 	//adc sensor
 	unsigned int lowLevel[8];
 	
 	//bluetooth
 	byte _packet[6];
	byte _count;
	byte _header;
	
	//timer2 set
	void Timer2Set();
	
	//model util
	
};

extern SmartInventorClass SmartInventor;

#endif 