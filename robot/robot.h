/*------------------------------
	Robot header

	Header Containing:
		Defines,
		Macros

	Created By: Lucas Martins Mendes
	Date: 18/02/2017 12:45

------------------------------*/

#ifndef ROBOT_H
#define ROBOT_H

//Defines---------------

#define 	BOARD_MODEL 	"Arduino Uno"

//TODO: Define pins for every thing

//Control Defines, comment these for removing/altering specific parts of the program related to it

//DO NOT DEFINE BOTH OF THOSE, ALWAYS KEEP ONLY ONE ACTIVE
//#define 	HBRIDGE 1
#define NO_HBRIDGE 1

//#define 	RGB_LED
//#define 	GYRO


//Pins and Serial

//H bridge, 1 is forward, 2 is reverse
#ifdef NO_HBRIDGE

#define 	ENG_RGT_1		1
#define 	ENG_RGT_2		2
#define 	ENG_RGT_EN		3

#define 	ENG_LFT_1		4
#define 	ENG_LFT_2		5
#define 	ENG_LFT_EN		6

#elif HBRIDGE

#define 	ENG_RGT_1		3
#define 	ENG_RGT_2		5

#define 	ENG_LFT_1		7
#define 	ENG_LFT_2		9

#endif

//Sensors

//Light/color sensors
#define 	SNSR_LGT_CTR  	8
#define 	SNSR_LGT_LFT	6
#define 	SNSR_LGT_RGT	4
#define   SNSR_FRN

//Serial
#define 	SERIAL_SPEED	9600	//9600 baud/s

//Modes
#define 	MODE_IDLE		0	//Stand by, sensors disabled/not beiyng read
#define 	MODE_AUTO		1  	//Autonomous
//#define 	MODE_REMOTE		2	//Remote controlled by other application

//Actions


#ifdef 		RGB_LED
#define 	RGB_LED_PIN		3
#endif

#ifdef 		GYRO
#define 	GYRO_PIN
#endif

//-----------------------------------------------


#endif /* ROBOT_H */
