//test file
#define 	ENG_RGT_1 	7
#define 	ENG_RGT_2	4	
#define 	ENG_RGT_EN	5

#define 	ENG_LFT_1	8
#define 	ENG_LFT_2	12
#define 	ENG_LFT_EN	6

void setup () {

  Serial.begin(9600);
	pinMode(ENG_RGT_1, OUTPUT);
	pinMode(ENG_RGT_2, OUTPUT);
	pinMode(ENG_LFT_1, OUTPUT);
	pinMode(ENG_LFT_2, OUTPUT);

	//using the L293 IC bridge
	pinMode(ENG_RGT_EN, OUTPUT);
	pinMode(ENG_LFT_EN, OUTPUT);

}

void loop () {
  int spt;
//spt = analogRead(4)/4 - 128;
Serial.println(spt);
digitalWrite(ENG_RGT_1, 1);
digitalWrite(ENG_RGT_2, 0);
analogWrite(ENG_RGT_EN,255);
digitalWrite(ENG_LFT_1, 1);
digitalWrite(ENG_LFT_2, 0);
analogWrite(ENG_LFT_EN,255);


}
