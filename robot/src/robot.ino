/*------------------------------
	Main Robot Control

	For: Arduino UNO

	Created and  developed by:
		Lucas Martins Mendes,
		Jaqueline Ribeiro

	18/02/2017 11:55
------------------------------*/

//------------------------------
// ---------- Includes ----------
//Lib's
#include "Ultrasonic.h"

//Project Defines
#include "robot.h"

//-----------------------------
// Object declaration
//-----------------------------
#ifdef DST_SENSOR
Ultrasonic ultrasonic(DST_SNSR_TRIG_PIN, DST_SNSR_ECHO_PIN);
#endif

//Classe Robô
class Robot {
	public:

		//Variable and pins setup
		void init() {
			//Sistem init
			debug(BOARD_MODEL);
			debug(F("---------------------------\n Hello, I'm rescuebot. \nSetting Up Pins and Serial"));

			Serial.begin(SERIAL_SPEED);

			//Pin setup -----------------------

			#ifndef DEBUG_NO_STARTBUTTON
			pinMode(STRT_BTN_PIN, INPUT);
			#endif

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
			#ifdef DST_SENSOR
			pinMode(DST_SNSR_ECHO_PIN, INPUT);
			pinMode(DST_SNSR_TRIG_PIN, OUTPUT);
			#endif

			#ifndef DEBUG_NO_STARTBUTTON
			setMode(MODE_IDLE);
			#else
			setMode(MODE_AUTO);
			#endif

			debug(F("init done"));
		}

		#ifdef HBRIDGE
		void tankDrive (int left, int right) {
			//Tank type steering
			//negative values go backwards
			setEngine(left, ENG_LFT_1, ENG_LFT_2);
			setEngine(right, ENG_RGT_1, ENG_RGT_2);
			debug(F("l:"));
			debug(left);
			debug(F("r:"));
			debug(right);
		}
		#endif

		#ifdef HBRIDGE_2
		void tankDrive (int left, int right) {
			//Tank type steering
			//negative values go backwards
			setEngine(left, ENG_LFT_EN);
			setEngine(right, ENG_RGT_EN);
			debug(F("l:"));
			debug(left);
			debug(F("r:"));
			debug(right);
		}
		#endif

		int readSensors(uint8_t sensorId, uint8_t sensorPin) {
			int sensorValue;

			switch(sensorId) {
				#ifdef LGT_SENSOR
				case LGT_SENSOR:
				 	sensorValue = analogRead(sensorPin);
					debug(F("read Light sensor"));
					debug(sensorPin);
					debug(F("value:"));
					debug(sensorValue);

				break;
				#endif

				#ifdef DST_SENSOR
				case DST_SENSOR:
					long distance;
					//uint16_t microsec;
					//microsec = ultrasonic.timing();
					//distance = ultrasonic.convert(microsec, Ultrasonic::CM);
					distance = ultrasonic.Ranging(CM);
					sensorValue = round(distance);
					debug(F("Read Light Sensor, Value:"));
					debug(distance);
				break;
				#endif

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

		void notify(uint8_t state) {
			digitalWrite(ALRM_PIN, state);
		}

		uint8_t mode;
		uint16_t t0Turn;

		// ---------- Flags
		bool	flagReadingSensors = 1; //is sensor data being read or not?
		bool	flagIsTurning = 0; //for the 𝛑 rad turn
		bool	flagVictimFound = 0;
		bool	flagIsCounting = 0; //timeout countdown flag
		bool	flagObstacleFound = 0;


	private:
		//PCB H bridge
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
		#endif
		//L298 H bridge
		#ifdef HBRIDGE_2
		void setEngine(int value, uint8_t engine) {
			if(value >= 0) {
				analogWrite(engine, value);
				if(engine == ENG_LFT_EN) {
					digitalWrite(ENG_LFT_1, 0);
					digitalWrite(ENG_LFT_2, 1);
				}
				if(engine == ENG_RGT_EN) {
					digitalWrite(ENG_RGT_1, 0);
					digitalWrite(ENG_RGT_2, 1);
				}
			}
			else {
				analogWrite(engine, -value);
				if(engine == ENG_LFT_EN) {
					digitalWrite(ENG_LFT_1, 1);
					digitalWrite(ENG_LFT_2, 0);
				}
				if(engine == ENG_RGT_EN) {
					digitalWrite(ENG_RGT_1, 1);
					digitalWrite(ENG_RGT_2, 0);
				}
			}

		}
		#endif

};

//-----------------------------
//-- Object declaration and global variables  -------

static Robot robot;

//------------------------------
// ---------- Setup ------------
void setup()
{
	//Hardware init
	robot.init();
	#ifndef DEBUG_NO_STARTBUTTON
	robot.setMode(MODE_IDLE);
	#endif
}


//------------------------------
// ---------- Loop ----------
void loop()
{
	//Global variables
	int right;
	int left;
	int center;
	int front;
	int setpoint = DRIVE_ADJ;
	int distance;
	//int turnangle = 0;

	switch(robot.mode) {
		case MODE_AUTO:

			//normal operation
			if (robot.flagReadingSensors) {
				right = robot.readSensors(LGT_SENSOR,LGT_SNSR_RGT);
				delay(READ_WAIT);
 				left = robot.readSensors(LGT_SENSOR,LGT_SNSR_LFT);
				delay(READ_WAIT);
				center = robot.readSensors(LGT_SENSOR,LGT_SNSR_CTR);
				delay(READ_WAIT);
				front = robot.readSensors(LGT_SENSOR,LGT_SNSR_FRT);
				#ifdef DST_SENSOR
				distance = robot.readSensors(DST_SENSOR,0);
				#endif
			}

			//Noline detection
			if(right >= LINE_COLOR && left >= LINE_COLOR && center >= LINE_COLOR && !robot.flagIsCounting) {
				robot.flagIsCounting = 1;
				robot.t0Turn = millis();
			}

			//timeout for the noline countdown
			if (robot.flagIsCounting && ((millis() - robot.t0Turn) >= NOLINE_TIMEOUT) ) {
				robot.flagIsTurning = 1;
				robot.flagIsCounting = 0;
				robot.flagReadingSensors = 0;
				robot.t0Turn = millis();
			}

			#ifdef  DST_SENSOR
			//distance sensor trigged
			if (distance <= MIN_DIST ) {
				robot.flagObstacleFound = 1;
				robot.flagReadingSensors = 0;
				robot.t0Turn = millis();
			}
			#endif

			#ifdef LGT_SENSOR
			if (front >= VICTIM_COLOR) {
				robot.flagReadingSensors = 0;
				robot.flagVictimFound = 1;
				robot.setMode(MODE_IDLE);
				robot.tankDrive(0,0);
				robot.notify(1);
			}
			#endif

			//normal operation
			if(!robot.flagIsTurning && !robot.flagObstacleFound)
				robot.tankDrive(DRIVE_SPD - (left - (1024 - right))/8 - setpoint ,
					 							DRIVE_SPD - (right +  (1024 - left))/8 - setpoint);

			//for the 𝛑 rad turn
			else if (robot.flagIsTurning) {
				robot.tankDrive(-TURN_SPEED,TURN_SPEED);
			}

			//Obstacle avoid
			if(robot.flagObstacleFound) {
				//TODO: this method
				//robot.tankDrive(TURN_SPEED*sin(turnangle), -TURN_SPEED*sin(turnangle));
				//turnangle = (millis() - robot.t0Turn)* M_PI/OBSTACLE_AVOID_TIMEOUT;
			}

			//obstacle avoid timeout
			if(robot.flagObstacleFound && ((millis() - robot.t0Turn) > OBSTACLE_AVOID_TIMEOUT) ) {
					robot.flagObstacleFound = 0;
					robot.flagReadingSensors = 0;
			}

		break;

		case MODE_IDLE :
			/*
			if (millis() % 1001 == 0) {
				robot.debug(F("Waiting"));
			}
			*/
			#ifndef DEBUG_NO_STARTBUTTON
			if(digitalRead(STRT_BTN_PIN) == 1) {
				delay(3000); //Start delay
				robot.setMode(MODE_AUTO);
			}
			#else
				robot.setMode(MODE_AUTO);
			#endif
		break;

		default:
			robot.debug(F("What?, How did you end up in here?"));
		break;
	}
}
/*----------
	EOF
----------*/
