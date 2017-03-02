/*------------------------------
	Main Robot Control
	
	Intended Processor: ESP8266, on NodeMCU

	Created By: Lucas Martins Mendes
	Date: 18/02/2017 11:55

------------------------------*/


//------------------------------
// ---------- Includes ----------
#include <Arduino.h>

#include "libInclude.h"


//User
#include "robot.h"

//------------------------
//Object declaration

Robot robot;

//------------------------------
// ---------- Setup -----------
void setup()
{
	//Hardware init
	robot.init(SERIAL_SPEED,ENGINE_LEFT,ENGINE_RIGHT);
	//robot.initWiFi();

}


//------------------------------
// ---------- Loop ----------

void loop()
{
	

}


/*----------
	EOF
----------*/