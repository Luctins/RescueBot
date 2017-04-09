/*------------------------------
	Main Robot Control
	
	ESP8266, NodeMCU

	Created By: Lucas Martins Mendes
	Date: 18/02/2017 11:55

------------------------------*/

//------------------------------
// ---------- Includes ----------

#include <Arduino.h>
#include <SPI.h>
#include <ESP8266WiFi.h>

/*
#include <WiFiClientSecure.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiType.h>
#include <WiFiUdp.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiScan.h>
#include <WiFiClient.h>

#include <ESP8266WiFiMulti.h>
#include <WiFiServer.h>
#include <ESP8266WiFiSTA.h>
*/

//needed for WiFiMananger
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include "lib/WiFiMananger.h"

//Project Defines
#include "robot.h"




//-----------------------------
// Object declaration
//-----------------------------

WiFiClient wifi;
ESP8266WebServer statusServer(80);

class Robot {
	public:
		// Memory allocation
		void Robot::init(int SerialSpeed, int leftEnginePin, int rightEnginePin) {
			//Robot::SSID = (char*) malloc (SSID_LEN + 1); 	//Allocates Memory for the SSID
			//Robot::PASSWD = (char*) malloc(PASSWD_LEN + 1); // Same as above, bu tofr the password

			//Sistem init
			debug(F("---------------------------\n \t\t HELLO!"));
			debug(F("ESP8266 Init"));
			debug(F("Setting Up Pins and Serial"));

			Serial.begin(SerialSpeed);
			pinMode(leftEnginePin, OUTPUT);
			pinMode(rightEnginePin, OUTPUT);

			debug(F("done"));
		}

		void Robot::initWiFi() {
		//Wifi Startup
			debug(F("Creating WiFiManager"));
			WiFiManager wifiManager;
			debug(F("OK"));


			debug(F("Starting WiFi, at:"));
			debug(F(AP_SSID));

			//Blocking loop for wireless configuration
		    if (!wifiManager.startConfigPortal(AP_SSID)) {
    		  	debug(F("failed to connect and hit timeout, resetting"));
		      	delay(3000);

     		 	//reset and try again, or maybe put it to deep sleep
     		 	
     		 	//TODO: maybe remove this?
     	 		ESP.reset();
    	  		delay(5000);
	    	}	

    		//if you get here you have connected to the WiFi
    		debug(F("Connected!"));

			debug(F("Settting HTTP status server"));
			statusServer.on("/botStatus", std::bind(&Robot::statusReport, this));
			debug(F("Starting HTTP status server on:"));
			debug(F("<IP HERE>"));
			//TODO: output HTTP server link on serial

			server.begin();
		
		}


		void Robot::statusReport() {
			//TODO: Status report via HTTP on "<IP>/status"

		}

		void Robot::tankDrive (int left, int right) {
			//Tank type steering
			analogWrite(ENGINE_LEFT, left);
			analogWrite(ENGINE_RIGHT, right);

			debug(F("Left"));
			debug(left);

			debug(F("Right"));
			debug(right);
		}

		void Robot::setMode(int modeFlag) {
			//TODO: Implement modechange for remote control
		}

		template <typename Generic>
		void Robot::debug(Generic text) {
			Serial.println(text);
		}
	private:
	
}

//------------------------
//Object declaration

Robot robot;

//------------------------------
// ---------- Setup -----------
void setup()
{
	//Hardware init
	robot.init(SERIAL_SPEED,ENGINE_LEFT,ENGINE_RIGHT);
	robot.initWiFi();
	robot.
}


//------------------------------
// ---------- Loop ----------

void loop()
{
	

}


/*----------
	EOF
----------*/