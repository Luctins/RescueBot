/*------------------------------
	Main Robot Control
	
	For: Arduino UNO

	Created By: Lucas Martins Mendes
	Date: 18/02/2017 11:55

------------------------------*/

//------------------------------
// ---------- Includes ----------

//Project Defines
#include "robot.h"


//-----------------------------
// Object declaration
//-----------------------------

class Robot {
	public:
		//Variable and pins setup
		void init() {
			//Sistem init
			debug(F(BOARD_MODEL));
			debug(F("---------------------------"));
			debug(F("Hello, I'm rescuebot."));
			debug(F("Setting Up Pins and Serial"));

			Serial.begin(SERIAL_SPEED);
			
			//Pin setup
			pinMode(ENG_RGT_1, OUTPUT);
			pinMode(ENG_RGT_2, OUTPUT);
			pinMode(ENG_LFT_1, OUTPUT);
			pinMode(ENG_LFT_2, OUTPUT);

			setMode(MODE_IDLE);

			debug(F("done"));
		}

		void tankDrive (int left, int right) {
			//Tank type steering
		

			debug(F("Left"));
			debug(left);

			debug(F("Right"));
			debug(right);
		}

		void setMode(uint8_t modeFlag) {
			//TODO: Implement modechange for remote control
		}

		template <typename Generic>
		void debug(Generic text) {
			Serial.println(text);
		}

		uint8_t mode;
	private:

} robot;

//------------------------------
// ---------- Setup -----------
void setup()
{
	//Hardware init
	robot.init();
}


//------------------------------
// ---------- Loop ----------

void loop()
{


}


/*----------
	EOF
----------*/