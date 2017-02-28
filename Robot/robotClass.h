/*------------------------------
	RobotClass header
	
	Header Containing:
		Defines,
		Macros,
		Class Predeclarations ,
		and functions definitions; 
	
	Created By: Lucas Martins Mendes
	Date: 18/02/2017 12:45

------------------------------*/

#ifndef ROBOTCLASS_H
#define ROBOTCLASS_H


//Defines---------------

//WiFi
#define 	SSID_HOST 		"RoboAoResgate" 	//Nome da rede wifi quando em modo host
#define 	PASSWORD_HOST 	"aabbccddee" 	//Senha da rede
#define 	SSID_LEN		16 		//Maximium Wireless network name length
#define 	PASSWD_LEN 		16 		//Maximium Wireless network password length
#define 	WIFI_TIMEOUT	2000	//Timeout for connecting to wifi, in msec
 
//Pins and Serial
#define 	ENGINE_LEFT		9		//Left engine pin
#define 	ENGINE_RIGHT	11		//Right engine pin
#define 	SERIAL_SPEED	9600	//9600 bauds

//Flags
#define 	MODE_STANDBY	0	//Stand by
#define 	MODE_REMOTE		1	//Remote controlled by other application


#endif /* ROBOTCLASS_H */



//---------------------------

