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

#ifndef ROBOT_H
#define ROBOT_H

//-----------------------------------
// ---------- Defines ---------------
#define 	BOARD_MODEL 	"Arduino Uno"

//debug
//#define DEBUG_BOARDONLY
//#define DEBUG_NO_STARTBUTTON

// ----------- ID's and other defines

//Timeout values
#define NOLINE_TIMEOUT 5000 // 5s
#define TURN_TIMEOUT 5000 //For the 𝛑 rad turn, 1s
#define OBSTACLE_AVOID_TIMEOUT 5000 //For the turn around the obstacle

#define READ_WAIT 1 //ms

//compensation constant
#define DRIVE_ADJ  0 //compensation for the different engines
#define DRIVE_SPD   255 //regular drive speed

#define TURN_SPEED 200 //Speed when turning

//----------Modes
#define 	MODE_IDLE		0	  //Stand by, sensors disabled/not beiyng read
#define 	MODE_AUTO		1  	//Autonomous
//#define 	MODE_REMOTE		2	//Remote controlled by other application

//----------Color
//TODO: measure and input the values below
#define VICTIM_COLOR 1024
#define LINE_COLOR   0
//#define OBSTACLE_COLOR 0

//------------------------
//--- Code Control Defines
 /*
 comment these for removing/altering
 specific parts of the program related to it
*/

//----------- Sensors
//These are also the sensor's id's
#define 	LGT_SENSOR 1
#define 	DST_SENSOR 2

//---------- Peripherals
//#define 	RGB_LED 3
//#define 	GYRO

// --------- H bridge control
//#define 	HBRIDGE 1 //Minha ponte H bridge type
#define HBRIDGE_2 1 //L293 bridge type


//-----------------------------------------
//-----------Pin's / Serial----------------

#define STRT_BTN_PIN   12  //Start Button PIN

#define ALRM_PIN  13

#ifdef DST_SENSOR
#define DST_SNSR_TRIG_PIN   11
#define DST_SNSR_ECHO_PIN	 10
#define MIN_DIST  10 //In cm
#endif

#define 	SERIAL_SPEED	38400
//#define   BT_SERIAL_SPEED 9600

//Light/color sensors
#define 	LGT_SNSR_LFT	0
#define 	LGT_SNSR_CTR 	1
#define 	LGT_SNSR_RGT	2
#define     LGT_SNSR_FRT    3 //Frontal Light sensor

#define ADJ_PIN 4 //AnRead 4 

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

#define 	ENG_RGT_1   	4
#define 	ENG_RGT_2		2
#define 	ENG_RGT_EN	    5

#define 	ENG_LFT_1		7
#define 	ENG_LFT_2		8
#define 	ENG_LFT_EN		6

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
