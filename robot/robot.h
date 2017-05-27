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


//1 is forward, 2 is reverse
//Pins and Serial
#define 	ENG_RGT_1		3
#define 	ENG_RGT_2		5

#define 	ENG_LFT_1		9
#define 	ENG_LFT_2		11

#define 	SERIAL_SPEED	9600	//9600 baud/s

//Flags
#define 	MODE_IDLE		0	//Stand by, sensors disabled/not beiyng read
#define 	MODE_AUTO		1  	//Autonomous
//#define 	MODE_REMOTE		2	//Remote controlled by other application

//Comment this lines to remove the code related to the RGB LED/Gyro
#define 	RGB_LED			
#define 	GYRO 

#ifdef RGB_LED

#define 	RGB_LED_PIN		3

#endif

#ifdef 		GYRO

#define 	GYRO_PIN

#endif

//-----------------------------------------------


#endif /* ROBOT_H */
