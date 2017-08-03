/*------------------------------
	Main Robot Control

	For: Arduino UNO

	Created By:
		Henrique Ternes Moresco
		Jaqueline de Souza Ribeiro
		Lucas Martins Mendes
		Maria Aparecida Muniz
		Mateus Reibintz Willemann


	18/02/2017 11:55

------------------------------*/

//------------------------------
// ---------- Includes ----------
//Lib's
#include "Arduino.h"
//#include "/home/luctins/repositorios/rescuebot/lib/Ultrasonic/Ultrasonic.h"
#include "Ultrasonic.h"

//Project Defines
#include "robot.h"

//-----------------------------
// Object declaration
//-----------------------------
Ultrasonic ultrasonic(DST_SNSR_TRIG_PIN, DST_SNSR_ECHO_PIN);

//Classe Robô
class Robot {
	public:

		//Variable and pins setup
		void init() {
			//Sistem init
			debug(F(BOARD_MODEL));
			//F( 123);
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
			#ifdef LGT_SENSOR
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
					debug(F("Read distance Sensor, Value:"));
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

		//usado para ajustar o valor base do PWM no 1º carrinho
		/*int readAdjustValue() {
			int value;
			value = analogRead(ADJ_PIN);
			return value;
		}*/

		uint8_t mode;
		uint16_t t0Turn;

		// ---------- Flags
		bool	flagReadingSensors = 1; //is sensor data being read or not?
		bool	flagIsTurning = 0; //for the 𝛑 rad turn
		bool	flagVictimFound = 0;
		bool	flagIsCouting = 0; // <any> timeout countdown flag
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
					digitalWrite(ENG_LFT_1, 1);
					digitalWrite(ENG_LFT_2, 0);
				}
				if(engine == ENG_RGT_EN) {
					digitalWrite(ENG_RGT_1, 1);
					digitalWrite(ENG_RGT_2, 0);
				}
			}
			else {
				analogWrite(engine, -value);
				if(engine == ENG_LFT_EN) {
					digitalWrite(ENG_LFT_1, 0);
					digitalWrite(ENG_LFT_2, 1);
				}
				if(engine == ENG_RGT_EN) {
					digitalWrite(ENG_RGT_1, 0);
					digitalWrite(ENG_RGT_2, 1);
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
}


//------------------------------
// ---------- Loop ----------
void loop()
{
	//Global variables

	//For the 3 sensor layout
	/*int right;
	int left;
	int center;
	int front;
	int setpoint = DRIVE_ADJ;
	//int turnangle = 0;*/

  int right_r;
  int right;
  int left;
  int left_l;
  int distance;

	switch(robot.mode) {
		case MODE_AUTO:

			//setpoint = robot.readAdjustValue()/4;
			//normal operation
			if (robot.flagReadingSensors) {
        delay(READ_WAIT);
        right_r = robot.readSensors(LGT_SENSOR,LGT_SNSR_RGT_R);
        delay(READ_WAIT);
        right = robot.readSensors(LGT_SENSOR,LGT_SNSR_RGT);
        delay(READ_WAIT);
        left = robot.readSensors(LGT_SENSOR,LGT_SNSR_LFT);
        delay(READ_WAIT);
        left_l = robot.readSensors(LGT_SENSOR,LGT_SNSR_LFT_L);
        //(READ_WAIT);
				#ifdef DST_SENSOR
       distance = robot.readSensors(DST_SENSOR,0);
        #endif

			}

			#ifdef  DST_SENSOR
			//distance sensor trigged
			if (distance < MIN_DIST) {
        robot.tankDrive(0,0);
        robot.notify(1);

				robot.flagObstacleFound = 1;
				robot.flagReadingSensors = 0;
				//robot.tankDrive(0,0);
			}
			#endif

			//frontal sensor
			/*#ifdef LGT_SENSOR_FRT
			if (front >= VICTIM_COLOR) {
				//robot.flagObstacleFound = 1;
				robot.flagReadingSensors = 0;
				robot.flagVictimFound = 1;
				robot.setMode(MODE_IDLE);
				robot.tankDrive(0,0);
			}
			#endif*/

			//normal operation
			if(robot.flagReadingSensors) {
         /*if (right > LINE_COLOR) {
          robot.tankDrive(DRIVE_SPD, 0);
        }
        else if (left > LINE_COLOR) {
          robot.tankDrive(0 ,DRIVE_SPD);
        }
        else*/ if (right_r > LINE_COLOR) {
          robot.tankDrive(DRIVE_SPD, -DRIVE_SPD );
        }
        else if (left_l > LINE_COLOR) {
          robot.tankDrive(-DRIVE_SPD ,DRIVE_SPD);
        }
        else { robot.tankDrive(DRIVE_SPD, DRIVE_SPD); }
        delay(50);

				    /*robot.tankDrive(DRIVE_SPD - (right/4 - left/3),
								DRIVE_SPD - (left/4 - right/3));
          */

       }

			//Obstacle avoid
			if(robot.flagObstacleFound) {
        robot.tankDrive(0,0);

				robot.tankDrive(0,0);
				delay(2000);
				robot.tankDrive(150,-150);
				delay(1500);
				robot.tankDrive(150,150);
				delay(2500);
				robot.tankDrive(-150,150);
				delay(1500);
				robot.tankDrive(150,150);
				delay(5000);
				robot.tankDrive(-150,150);
				delay(1000);
				robot.tankDrive(150,150);
       robot.notify(0);
       robot.flagReadingSensors = 1;
       robot.flagObstacleFound = 0;
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
				delay(3000); //start delay
				//while (digitalRead(STRT_BTN_PIN) == 1); //wait for button to be released
				pinMode(ALRM_PIN, 0);
				robot.setMode(MODE_AUTO);
			}
			#else
				robot.setMode(MODE_AUTO);
			#endif

			robot.tankDrive(0,0);
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
