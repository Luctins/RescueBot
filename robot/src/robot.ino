/*------------------------------
	Main Robot Control

	For: Arduino UNO

	Created By:
		Lucas Martins Mendes

	18/02/2017 11:55

------------------------------*/

//------------------------------
// ---------- Includes ----------

//Project Defines
#include "robot.h"

//-----------------------------
// Object declaration
//-----------------------------

//Classe Robô
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

			//Pin setup -----------------------
			pinMode(STRT_BTN_PIN, INPUT);
			pinMode(ALRM_PIN, OUTPUT);
			pinMode(ENG_RGT_1, OUTPUT);
			pinMode(ENG_RGT_2, OUTPUT);
			pinMode(ENG_LFT_1, OUTPUT);
			pinMode(ENG_LFT_2, OUTPUT);

			//if using the L293 IC bridge
			#ifdef HBRIDGE_2
			pinMode(ENG_RGT_EN, OUTPUT);
			pinMode(ENG_LFT_EN, OUTPUT);
			#endif

			//Sensors
			//TODO: Set up sensors here

			setMode(MODE_IDLE);

			debug(F("done"));
		}

		#ifdef HBRIDGE
		void tankDrive (int left, int right) {
			//Tank type steering
			//negative values go backwards
			//Does nothing if idle
			if(mode == MODE_AUTO) {
				setEngine(left, ENG_LFT_1, ENG_LFT_2);
				setEngine(right, ENG_RGT_1, ENG_RGT_2);
			}
			else if(mode == MODE_IDLE)
			debug(F("tried to move idle"));
		}
		#endif

		#ifdef HBRIDGE_2
		void tankDrive (int left, int right) {
			//Tank type steering
			//negative values go backwards
			//Does nothing if idle
			if(mode == MODE_AUTO) {
				setEngine(left, ENG_LFT_EN);
				setEngine(right, ENG_RGT_EN);
			}
			else if(mode == MODE_IDLE) { debug(F("tried to move idle")); }
		}
		#endif

		int readSensors(uint8_t sensorId, uint8_t sensorPin) {
			int sensorValue;

			switch(sensorId) {
				case LGT_SENSOR:
				 	sensorValue = analogRead(sensorPin);
					debug(F("read Light sensor n°"));
					debug(sensorPin);
					debug(F("Value:"));
					debug(sensorValue);
				break;

				case DST_SENSOR:
					//TODO: read light sensor here
				break;

				default:
					debug(F("Invalid sensor ID"));
				break;
			}
			return sensorValue;
		}

		void setMode(uint8_t modeFlag) {
			mode = modeFlag;
			debug(F("mode set to:"));
			debug(modeFlag);
		}

		//Debug messages go to the serial
		template <typename Generic>
		void debug(Generic text) {
			Serial.println(text);
		}

		uint8_t mode;
		uint16_t t0Turn;

		//Flags
		bool flagReadingSensors = 1; //is sensor data beying read or not?
		bool flagIsTurning = 0; //for the 𝛑 rad turn
		bool flagVictimFound = 0;
		bool flagIsCouting = 0; //timeout countdown flag


	private:

		#ifdef HBRIDGE
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
		#elif HBRIDGE_2
		void setEngine(int value, uint8_t engine) {
			if(value>0) {
				analogWrite(engine, value);
			}
			else if(value<0) {
				digitalWrite(engine, value);
			}
			else {
				digitalWrite(engine, 0);
			}

		}
		#endif

};

/*
//classe PID
class PID {
public:

  int error;
  int sample;
  //int lastSample;
  int kP, kI, kD;
  int P, I, D;
  int pid;

  int setPoint;
  //int lastProcess; //Time of last process

  PID(int _kP, int _kI, int _kD, int setpoint){
    kP = _kP;
    kI = _kI;
    kD = _kD;
  }

  void addNewSample(int _sample){
    sample = _sample;
  }

  void setSetPoint(int _setPoint){
    setPoint = _setPoint;
  }

  double process() {
    error = setPoint - sample;
    //float deltaTime = (millis() - lastProcess) / 1000.0;
    //lastProcess = millis();

    //P
    P = error * kP;

    //I
    I = I + (error * kI) * deltaTime;

    //D
    D = (lastSample - sample) * kD / deltaTime;
    lastSample = sample;

    // Soma tudo
    pid = P + I + D;

    return pid;
  }
};
*/

//-----------------------------
//-- Object declaration and global variables  -------

//PID pid(1,0,0,0);
static Robot robot;

const int base_speed = 3*1024/4;

//------------------------------
// ---------- Setup ------------

void setup()
{
	//Hardware init
	robot.init();
	robot.setMode(MODE_IDLE);
	//int setpoint = CNTR_STPT;
}


//------------------------------
// ---------- Loop ----------

void loop()
{
	//Global variables
	//namespace robot;
	int right;
	int left;
	int center;
	int victim;
	int setpoint = 0;

	switch(robot.mode) {
		case MODE_AUTO:
			//controller.addNewSample(robot.computeSensorAvg());
			//int compensation = controller.compute();
			right = robot.readSensors(LGT_SENSOR,LGT_SNSR_RGT);
 			left = robot.readSensors(LGT_SENSOR,LGT_SNSR_LFT);
 			center = robot.readSensors(LGT_SENSOR,LGT_SNSR_CTR);
			victim = robot.readSensors(LGT_SENSOR,LGT_SNSR_FRT);

			//checks the frontal sensor for the victim
			if(victim>=VICTIM_COLOR) {
				robot.flagVictimFound = 1;
				robot.setMode(MODE_IDLE);
			}

			if(right >= LINE_COLOR && left >= LINE_COLOR && center >= LINE_COLOR) {
				robot.flagIsCouting = 1;
				robot.t0Turn = millis();
			}

			if (robot.flagIsCouting && (millis() - robot.t0Turn >= NOLINE_TIMEOUT)) {
				robot.flagIsTurning = 1;
				robot.flagReadingSensors = 0;
				robot.t0Turn = millis();
			}

			if(!robot.flagIsTurning)
			robot.tankDrive(setpoint+center-right,setpoint+center-left);
		break;

		case MODE_IDLE :
			/*
			if (millis() % 1001 == 0) {
				robot.debug(F("Waiting"));
			}
			*/
			if(digitalRead(STRT_BTN_PIN) == 1) {
				delay(50); //Button Debounce
				while (digitalRead(STRT_BTN_PIN) == 1); //wait for button to be released
				robot.setMode(MODE_AUTO);
				}
		break;

		default:
			robot.debug(F("What?, How did you end up in here?"));
		break;
	}

	if(robot.flagVictimFound == 1) {
		digitalWrite(ALRM_PIN, 1);
	}

}
/*----------
	EOF
----------*/
