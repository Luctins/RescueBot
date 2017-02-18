/*------------------------------
	Main Robot Control
	
	Intended Processor: ESP8266, on NodeMCU
	

		Any defines must be on header files

	Created By: Lucas Martins Mendes
	Date: 18/02/2017 11:55

------------------------------*/


//------------------------------
// ---------- Includes ----------

//Libraries
#include "Arduino.h"

#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>


//User
#include "text.hpp"
#include "robot.h"

//------------------------------
//---------- Class Definition ----------



// Class declaration
extern class RobotClass
{
	public:
		void debug (void * message) {
			Serial.print(*message);
		}

		bool move (int left, int right) {
			//right and left values are in
			//TODO: define movement method (speed, time or angle)

		}

	private:
		//initialization messages
		const char greeting [] = "------------------";
		const char bothello [] = "---------- ESP8266 Based Bot ----------";
		

		const char slavemode [] = "Set to Slave Mode"; 

		//Notifications
		const char modeChange [] = "Setting to Wireless client mode";
		const char connecting [] = "Connecting to Wireless network";
		const char  connected = "Connected!";

};