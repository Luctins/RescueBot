/*------------------------------
	Robot header
	
	Header Containing:
		Defines,
		Macros,
		Class Predeclarations ,
		and functions definitions; 
	
	Created By: Lucas Martins Mendes
	Date: 18/02/2017 12:45

------------------------------*/

#ifndef ROBOT_H
#define ROBOT_H

//Defines---------------

//WiFi
#define 	AP_SSID			"RoboAoResgate"	//Wireless Network Name for local AP
#define 	SSID_LEN		16 				//Maximium Wireless network name length
#define 	PASSWD_LEN 		16 				//Maximium Wireless network password length
#define 	WIFI_TIMEOUT	2000			//Timeout for connecting to wifi, in msec
 
//Pins and Serial
#define 	ENGINE_LEFT		9		//Left engine pin
#define 	ENGINE_RIGHT	11		//Right engine pin
#define 	SERIAL_SPEED	9600	//9600 bauds

//Flags
#define 	MODE_STANDBY	0	//Stand by
#define 	MODE_REMOTE		1	//Remote controlled by other application


//----------------------------------------------------


//---------------------------------------
// Class Predeclaration


class Robot {
	private:
		template<typename Generic>
		void debug(Generic text); 	//Reports What the program is doing via the serial
		char *SSID; 				//SSID storage pointer
		char *PASSWD;				//PASSWD storage pointer
	public:
		//Init
		void init(int SerialSpeed, int leftEngine, int rightEngine); 	//Main setup
		void initWiFi();					//WiFi Setup, tries stored network first, then turns AP on if nothing found
		void setWiFi(char* Network, char* Password);
		int connectWifi(char* Network, char* Password);
		void statusReport();
		void startAP(char* SSID);
		void tankDrive (int left, int right);
		void setMode(int modeFlag);
		
};

//-----------------------------------------------

#endif /* ROBOT_H */
