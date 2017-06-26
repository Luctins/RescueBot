//test file
#define 	ENG_RGT_1 	4
#define 	ENG_RGT_2	2	
#define 	ENG_RGT_EN	5

#define 	ENG_LFT_1	7
#define 	ENG_LFT_2	8
#define 	ENG_LFT_EN	6

void setup () {
	pinMode(ENG_RGT_1, OUTPUT);
	pinMode(ENG_RGT_2, OUTPUT);
	pinMode(ENG_LFT_1, OUTPUT);
	pinMode(ENG_LFT_2, OUTPUT);

	//using the L293 IC bridge
	pinMode(ENG_RGT_EN, OUTPUT);
	pinMode(ENG_LFT_EN, OUTPUT);

}

void loop () {
digitalWrite(ENG_RGT_1, 1);
digitalWrite(ENG_RGT_2, 0);
analogWrite(ENG_RGT_EN, 255);
digitalWrite(ENG_LFT_1, 1);
digitalWrite(ENG_LFT_2, 0);
analogWrite(ENG_LFT_EN,255);
delay(5000);
digitalWrite(ENG_RGT_1, 1);
digitalWrite(ENG_RGT_2, 0);
analogWrite(ENG_RGT_EN, 0);
digitalWrite(ENG_LFT_1, 1);
digitalWrite(ENG_LFT_2, 0);
analogWrite(ENG_LFT_EN, 255);
delay(3000);

}
