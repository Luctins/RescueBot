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
			//negative values go backwards
			//Does nothing if idle

			if(mode == MODE_AUTO) {
				setEngine(left, ENG_LFT_1, ENG_LFT_2);
				setEngine(right, ENG_RGT_1, ENG_RGT_2);
			}
			else if(mode == MODE_IDLE);
			debug(F("tried to move when idle"));
		}


		void setMode(uint8_t modeFlag) {
			mode = modeFlag;
			debug(F("mode set to:"));
			debug(modeFlag);
		}

		template <typename Generic>
		void debug(Generic text) {
			Serial.println(text);
		}

		uint8_t mode;
	private:

		void setEngine(int value, uint8_t engine1, uint8_t engine2) {
			if(value>0) {
				analogWrite(engine1, value);
				analogWrite(engine2, 0);
			}
			else if(value<0) {
				digitalWrite(engine1, 0);
				digitalWrite(engine2, value);
			}
			else {
				digitalWrite(engine1, 0);
				digitalWrite(engine2, 0);
			}
		}


} robot;

//------------------------------
// ---------- Setup -----------
void setup()
{
	//Hardware init
	robot.init();
	robot.setMode(MODE_IDLE);

}


//------------------------------
// ---------- Loop ----------

void loop()
{
//TODO: Bot start switch with debounce


}


/*----------
	EOF
----------*/