/*------------------------------
	Main Robot Control

	
	Intended Processor: ESP8266, on NodeMCU
	source: hhtps://github.com/mendes110898/rescuebot

	Created By: Lucas Martins Mendes
	Date: 18/02/2017 11:55

------------------------------*/


//------------------------------
// ---------- Includes ----------
#include "libInclude.h"

#include "robot.h"


//-----------------------------
// ------- Lib Declaration

static WiFiClient wifi;
static ESP8266WebServer server(80);


//-----------------------------------
// Variable Declaration
 
//-----------------------------------------------
//------- Function Definition ----------------



void Robot::init(int SerialSpeed, int leftEnginePin, int rightEnginePin) {
	// Memory allocation
	this->SSID = (char*) malloc (SSID_LEN + 1);
	this->PASSWD = (char*) malloc(PASSWD_LEN + 1);

	//Sistem init
	debug(F("---------------------------"));
	debug(F("ESP8266 Init"));
	debug(F("Setting Up Pins and Serial"));

	Serial.begin(SerialSpeed);
	pinMode(leftEnginePin, 1);
	pinMode(rightEnginePin, 1);
	
	debug(F("done"));


}

void Robot::initWiFi() {
	//Wifi Startup
	debug(F("Starting WiFi"));
	WiFi.begin("","");
	debug(F("Connecting To stored Wireless network"));

	int t0 = millis(); //Connection timeout start time
	while(!(WiFi.status() == WL_CONNECTED) && ( millis() - t0 < WIFI_TIMEOUT)) {
		debug(F("."));
		delay(300);
	}

	//Sets Up A acess point if unconfigured, or did not found the pre-set network
	if (WiFi.status() == WL_CONNECTED )
	{
		//Set's up the HTTP server and starts it up
		debug(F("Connected!"));
		//TODO: output device IP to serial
		debug(F("Settting HTTP status server"));
		//server.on("/status", std::bind(&Robot::statusReport, this));
		debug(F("Starting HTTP status server on:"));
		//TODO: output HTTP server link on serial

		server.begin();
	}
	else {
		debug(F("failed to Connect to Wireless Network, Starting AP"));
		//starts Acess point
		startAP(AP_SSID);
		debug(F("AP started"));

		//TODO: Encapsulate this in a function
		debug(F("Setting HTTP setup server"));
		debug(WiFi.softAPIP());
		debug(F("\"/setup\""));
		//server.on("/setup",std::bind(&Robot::setWiFi),this);
		debug(F("Starting HTTP setup server"));
		server.begin();
	}
}

void Robot::setWiFi (char* Network, char* Password) {
	//todo: this
}

int Robot::connectWifi (char* Network, char* Password) {
	debug(F("Setting to station mode"));

	WiFi.mode(WIFI_STA);//Set To station, aka: client mode
	
	int t_begin = millis(); //Time when the connection started, for timeout

	while (((millis() - t_begin) < WIFI_TIMEOUT) && !(WiFi.status() == WL_CONNECTED)) {
		debug(".");
		delay(WIFI_TIMEOUT/10);
	}

	return WiFi.status();
}

void Robot::statusReport() {
	//TODO: Status report via HTTP on "<IP>/status"

}

void Robot::startAP(char* SSID) {
	//TODO: AP Config, and 
	//AP_SSID = SSID;
}

//void Robot::StartHTTP(char)

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


/*
void RobotClass::connectWifi (String ssid, String pass) {
  DEBUG_WM(F("Connecting as wifi client..."));

  // check if we've got static_ip settings, if we do, use those.
  if (_sta_static_ip) {
    DEBUG_WM(F("Custom STA IP/GW/Subnet"));
    WiFi.config(_sta_static_ip, _sta_static_gw, _sta_static_sn);
    DEBUG_WM(WiFi.localIP());
  }
  //fix for auto connect racing issue
  if (WiFi.status() == WL_CONNECTED) {
    DEBUG_WM("Already connected. Bailing out.");
    return WL_CONNECTED;
  }
  //check if we have ssid and pass and force those, if not, try with last saved values
  if (ssid != "") {
    WiFi.begin(ssid.c_str(), pass.c_str());
  } else {
    if (WiFi.SSID()) {
      debug("Using last saved values, should be faster");
      //trying to fix connection in progress hanging
      ETS_UART_INTR_DISABLE();
      wifi_station_disconnect();
      ETS_UART_INTR_ENABLE();

      WiFi.begin();
    } else {
      debug("No saved credentials");
    }
}
*/



//--------------------------------------------------------

