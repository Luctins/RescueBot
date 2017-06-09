/*------------------------------
	Main Robot Control

	For: Arduino UNO

	Created By:
		Jaqueline Ribeiro,
		Lucas Martins Mendes

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
			pinMode(STRT_BTN, INPUT);
			pinMode(ENG_RGT_1, OUTPUT);
			pinMode(ENG_RGT_2, OUTPUT);
			pinMode(ENG_LFT_1, OUTPUT);
			pinMode(ENG_LFT_2, OUTPUT);


			//if using the protoboard H bridge
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

		#elif HBRIDGE_2
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
			/*The color sensors return value is to be interpreted like so:
			will be read like:
			the left one is zero,
			the middle one is 512 and,
			the right one is 1204. */
			int sensorValue = 0; //Placeholder
			//TODO: read sensors here

			return sensorValue;
		}

		void setMode(uint8_t modeFlag) {
			mode = modeFlag;
			debug(F("mode set to:"));
			debug(modeFlag);
		}

		//
		template <typename Generic>
		void debug(Generic text) {
			Serial.println(text);
		}

		uint8_t mode;
		uint16_t time;

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

} robot;

/*
//Classe de controle
class Controller {
	public:

	//Basicamente uma função "init" da classe
  Controller(int _kP, int _setpoint) {
    kP = _kP;
		setPoint = _setpoint;
  }

//Adiciona nova amostra
  void addNewSample(double _sample){
    sample = _sample;
  }

  int compute() {
    // Implementação PID
    error = setPoint - sample; //Calcula erro
    //float deltaTime = (millis() - lastProcess) / 1000.0; //computa delta de tempo
    //lastProcess = millis();
    P = error * kP;
    return P;
  }
	private:
		int error;
		int sample; //Amostra
		int kP; //Ganho do controlador
		float P; //valor de saída do controlador

		int setPoint; //ponto objetivo
		//long lastProcess;
		//Quanto tempo passou
		//desde a ultima vez que o sistema computou os valores
};

Controller controller(CNTR_GAIN, CNTR_STPT);
*/

//------------------------------
// ---------- Setup -----------

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
	//namespace robot;
	int right;
	int left;
	int center;
	int victim;

	switch(robot.mode) {
		case MODE_AUTO:
			//controller.addNewSample(robot.computeSensorAvg());
			//int compensation = controller.compute();
			right = robot.readSensors(LGT_SENSOR,SNSR_LGT_RGT);
 			left = robot.readSensors(LGT_SENSOR,SNSR_LGT_LFT);
 			center = robot.readSensors(LGT_SENSOR,SNSR_LGT_CTR);
			//center /= 1.5;
			robot.tankDrive(center+right,center+left); //depois explico exatamente como isso funciona
			//             |
			//             |
			//             |
			//             |
			//------------------------------
			//

			victim = robot.readSensors(LGT_SENSOR,SNSR_LGT_FRNT);

		break;

		case MODE_IDLE :
			/*
			if (millis() % 1001 == 0) {
				robot.debug(F("Waiting"));
			}
			*/
			if(digitalRead(STRT_BTN) == 1) {
				delay(50); //Button Debounce
				while (digitalRead(STRT_BTN) == 1); //wait for button to be released
				robot.setMode(MODE_AUTO);
				}
		break;

		default:
			robot.debug(F("What?, How did you end up in here?"));
		break;
	}
}
/*----------
	EOF
----------*/
