/*------------------------------
	Main Robot Control

	
	Intended Processor: ESP8266, on NodeMCU
	source: hhtps://github.com/mendes110898/rescuebot

	Created By: Lucas Martins Mendes
	Date: 18/02/2017 11:55

------------------------------*/


//------------------------------
// ---------- Includes ----------

#include "robot.h"
#include "libInclude.h"

//-----------------------------
// ------- Lib Declaration

static WiFiClient wifi;
static ESP8266WebServer server(80);

//--------------------------------------
//---------- Variables ----------

String Robot::SSID = "";
String Robot::AP_SSID = "";
String Robot::PASSWD = "";

//-----------------------------------------------
//------- Function Definition

void Robot::init(int SerialSpeed, uint8_t leftEngine, uint8_t rightEngine) {
	//Sistem init
	debug(F("---------------------------"));
	debug(F("ESP8266 Init"));
	debug(F("Setting Up Pins and Serial"));

	Serial.begin(SerialSpeed);
	pinMode(leftEngine, 1);
	pinMode(rightEngine, 1);
	debug(F("done"));
}

void Robot::initWiFi(String Network, String Password) {
	//Wifi Startup
	debug(F("Starting WiFi"));
	WiFi.begin("","");
	debug(F("Connecting To stored Wireless network"));

	//Sets Up A acess point if unconfigured, or did not found the pre-set network
	if (connectWifi(Network,Password) == WL_CONNECTED )
	{
		//Set's up the HTTP server and starts it up
		debug(F("Connected!"));
		debug(F("Settting HTTP status server"));
		server.on("/status", statusReport);
		debug(F("Starting HTTP status server on \" /status\""));
		server.begin();
	}
	else {
		//starts Acess point
		startAP();

		//TODO: Encapsulate this in a function
		debug(F("Setting HTTP setup server"));
		debug(WiFi.softAPIP());
		debug(F("\"/setup\""));
		server.on("/setup");
		debug(F("Starting HTTP setup server"));
		server.begin();
	}
}

int Robot::connectWifi(String Network, String Password) {
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

void Robot::startAP(String SSID) {
	//TODO: AP Config, and 
	AP_SSID = SSID;
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

void Robot::setMode(uint8_t modeFlag) {
	//TODO: Implement modechange
}


//TODO: understand this
template <typename Generic>
void RobotClass::debug(Generic text) {
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

