/*------------------------------
	Robot header

	Header Containing:
		pin defines,
    id's,
    and
		macros.

	Created By:
    Lucas Martins Mendes,
    Jaqueline Ribeiro

	Date: 18/02/2017 12:45

------------------------------*/

//TODO: Define pins

#ifndef ROBOT_H
#define ROBOT_H

//-----------------------------------
// ---------- Defines ---------------


// ----------- ID's and other defines
#define 	BOARD_MODEL 	"Arduino Uno"

//Timeout values
#define NOLINE_TIMEOUT 3000 // 3s
#define TURN_TIMEOUT 1000 //For the 𝛑 rad turn, 1s

#define OBSTACLE_AVOID_TIMEOUT 2000

#define DRIVE_ADJ  0 //compensation for the different engines

#define TURN_SPEED 200 //Speed when turning

//Sensor ID's
#define 	LGT_SENSOR		1
#define 	DST_SENSOR		2

//Modes
#define 	MODE_IDLE		0	  //Stand by, sensors disabled/not beiyng read
#define 	MODE_AUTO		1  	//Autonomous
//#define 	MODE_REMOTE		2	//Remote controlled by other application

//Color
//TODO: measure and input the values below
#define VICTIM_COLOR 0
#define LINE_COLOR   0
#define OBSTACLE_COLOR 0

//Control Defines
 /*comment these for removing/altering
 specific parts of the program related to it */

//#define 	HBRIDGE 1 //Minha ponte H bridge type
#define HBRIDGE_2 1 //L293 bridge type

//Other sensors
//#define 	RGB_LED
//#define 	GYRO

//-----------------------------------------
//-----------Pin's / Serial----------------

#define STRT_BTN_PIN   13  //Start Button PIN

#define ALRM_PIN  12

#ifdef DST_SENSOR
#define DST_SNSR_TRIG_PIN 0
#define DST_SNSR_ECHO_PIN	 0
#define MIN_DIST  10 //In mm
#endif

#define 	SERIAL_SPEED	9600
//#define   BT_SERIAL_SPEED 9600

//Light/color sensors
#define 	LGT_SNSR_CTR 	0
#define 	LGT_SNSR_LFT	1
#define 	LGT_SNSR_RGT	2
#define   LGT_SNSR_FRT 3 //Frontal Light sensor

//H bridge set-up and verification
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
