/*------------------------------
	Robot header

	Header Containing:
		Defines,
		Macros

	Created By: Lucas Martins Mendes
	Date: 18/02/2017 12:45

------------------------------*/

//TODO: Define pins

#ifndef ROBOT_H
#define ROBOT_H

//Defines---------------
#define 	BOARD_MODEL 	"Arduino Uno"

#define   STRT_BTN   13  //Start Button PIN

//Serial
#define 	SERIAL_SPEED	9600
//#define   BT_SERIAL_SPEED 9600



//Sensor ID's
#define 	LGT_SENSOR		1
#define 	DST_SENSOR		2

//Light/color sensors
#define 	SNSR_LGT_CTR 	8
#define 	SNSR_LGT_LFT	6
#define 	SNSR_LGT_RGT	4
#define   SNSR_LGT_FRNT  4

//Modes
#define 	MODE_IDLE		0	  //Stand by, sensors disabled/not beiyng read
#define 	MODE_AUTO		1  	//Autonomous
//#define 	MODE_REMOTE		2	//Remote controlled by other application

//Action ID's
#define ACTION_IDLE 0
#define ACTION_MOVE 1
#define ACTION_ALERT 2

/* Control Defines,
 comment these for removing/altering
 specific parts of the program related to it */
  
//DO NOT DEFINE BOTH OF THOSE, ALWAYS KEEP ONLY ONE ACTIVE
//#define 	HBRIDGE 1 //Minha ponte H bridge type
#define HBRIDGE_2 1 //L293 bridge type

//Peripherals
//#define 	RGB_LED
//#define 	GYRO

#ifdef HBRIDGE_2
#ifdef HBRIDGE
#error "Do not define 2 Hbridge's at the same time"
#endif
#endif

#ifndef HBRIDGE_2
#ifndef HBRIDGE
#error "Please define one Hbridge"
#endif
#endif

//Pins

//H bridge, 1 is forward, 2 is reverse
#ifdef HBRIDGE_2

#define 	ENG_RGT_1		1
#define 	ENG_RGT_2		2
#define 	ENG_RGT_EN	3

#define 	ENG_LFT_1		4
#define 	ENG_LFT_2		5
#define 	ENG_LFT_EN	6

#endif

#ifdef HBRIDGE

#define 	ENG_RGT_1		3
#define 	ENG_RGT_2		5

#define 	ENG_LFT_1		7
#define 	ENG_LFT_2		9

#endif

//Led RGB
#ifdef 		RGB_LED
#define 	RGB_LED_PIN
#endif

//GYRO
#ifdef 		GYRO
#define 	GYRO_PIN
#endif

//-----------------------------------------------
#endif /* ROBOT_H */
