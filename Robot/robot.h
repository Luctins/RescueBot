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

#include "robotClass.h"

class Robot{ 
	public:
		void Robot::init(int SerialSpeed, int leftEngine, int rightEngine);
		void Robot::initWiFi(String Network, String Password);
		int Robot::connectWifi(String Network, String Password);
		void Robot::statusReport();
		void Robot::startAP(String SSID);
		void Robot::tankDrive (int left, int right);
		void Robot::setMode(int modeFlag);
		void RobotClass::debug(Generic text);


	private:
		String SSID = "";
		String AP_SSID = "";
		String PASSWD = "";
};


#endif /* ROBOT_H */
