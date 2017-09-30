#include <MeMCore.h>
#include <SoftwareSerial.h>

//Capteur ultrason
MeUltrasonicSensor ultraSensor(PORT_3);


//Moteur
MeDCMotor motor(M1);
uint8_t motorSpeed = 110;

//Matrice
MeLEDMatrix ledMx(PORT_2);

MeRGBLed led(PORT_1);

//LED
MeRGBLed rgbled(7, 2);
uint8_t led1 = 1;
uint8_t led2 = 2;
cRGB colorBlack;
cRGB colorWhite;
cRGB colorRed;
cRGB colorBlue;
cRGB colorGreen;
cRGB colorYellow;
cRGB colorViolet;
cRGB colorOrange;
enum {
	CLIGNOTTE_STOP,
	CLIGNOTTE_1,
	CLIGNOTTE_2
};
uint8_t clignoteMode = CLIGNOTTE_STOP;

//Switch
MeLimitSwitch switchRoue(PORT_4, SLOT1);
MeLimitSwitch switchDmde(PORT_4, SLOT2);
uint8_t intDmde = 0;

//Buzzer
MeBuzzer buzzer;
uint8_t buzzerFreq = 500;

//Setup
void setup() {

	//Init
	Serial.begin(9600);
	initColors();

	led.setColor(1, colorBlack.r, colorBlack.g, colorBlack.b);
	led.show();
	
	//Matrice
	ledMx.clearScreen();
	ledMx.setBrightness(6);
	ledMx.setColorIndex(1);
	matrixDrawFace();	

	//Reset LED
	ledSetColor(1, colorBlue);
	ledSetColor(2, colorBlue);
}

bool bStarted = false;
bool bSwitch = false;

//Loop
void loop() {
	
	//Si demande
	if (!bStarted & !switchDmde.touched()) {
		intDmde++;
		//ledMx.drawStr(0, 7, intDmde);
	}

	//Si pas demarré et sensor
	if (!bStarted && sensorGetDist() < 10) {

		//Depart
		bStarted = true;
		bSwitch = false;
	
		//Couleur
		ledSetColor(1, colorGreen);
		ledSetColor(2, colorGreen);

		//Matrice
		ledMx.drawStr(0, 7, "OK");

		//Buzzer
		//buzzerOn(500);

		//Marche moteur
		motor.run(-70);
	}

	//Si départ
	if (bStarted) {

		//Début du tour
		if (!switchRoue.touched()) {
			bSwitch = true;
		}

		//Fin du tour
		if (bSwitch && switchRoue.touched()) {

			//Arret moteur
			motor.stop();
			bStarted = false;
			bSwitch = false;

			//Buzzer
			//buzzerOn(500);

			//Reset LED
			ledSetColor(1, colorBlue);
			ledSetColor(2, colorBlue);

			//Matrice
			matrixDrawFace();
		}
	}

}

//******************************************** LED

//Initialisation des couleurs
void initColors() {

	colorBlack.r = 0;
	colorBlack.g = 0;
	colorBlack.b = 0;

	colorWhite.r = 255;
	colorWhite.g = 255;
	colorWhite.b = 255;

	colorRed.r = 255;
	colorRed.g = 0;
	colorRed.b = 0;

	colorBlue.r = 0;
	colorBlue.g = 38;
	colorBlue.b = 255;

	colorGreen.r = 0;
	colorGreen.g = 255;
	colorGreen.b = 33;

	colorYellow.r = 255;
	colorYellow.g = 216;
	colorYellow.b = 0;

	colorOrange.r = 255;
	colorOrange.g = 106;
	colorOrange.b = 0;

	colorViolet.r = 178;
	colorViolet.g = 0;
	colorViolet.b = 255;
}

//Applique une couleur à une led
//LED = 1 ou 2
void ledSetColor(int pLedNum, cRGB pRGB) {
	rgbled.setColor(pLedNum, pRGB.r, pRGB.g, pRGB.b);
	rgbled.show();
}

//Allume les 2 LED
void ledColor(cRGB pRGB) {
	rgbled.setColor(1, pRGB.r, pRGB.g, pRGB.b);
	rgbled.show();
	rgbled.setColor(2, pRGB.r, pRGB.g, pRGB.b);
	rgbled.show();
}

//Etteind les 2 LED
void ledStop() {
	rgbled.setColor(1, colorBlack.r, colorBlack.g, colorBlack.b);
	rgbled.show();
	rgbled.setColor(2, colorBlack.r, colorBlack.g, colorBlack.b);
	rgbled.show();
}

//Clignottement LED Blanc/Rouge/Bleu
int intLED = 0;
int intLEDFreqMs = 3;
void ledClignotte() {

	switch (clignoteMode) {
	case CLIGNOTTE_STOP:
		return;
	case CLIGNOTTE_1:
		if (intLED == 0)ledColor(colorWhite);
		if (intLED == (1 * intLEDFreqMs))ledColor(colorRed);
		if (intLED == (2 * intLEDFreqMs))ledColor(colorBlue);
		if (intLED == (3 * intLEDFreqMs))intLED = -1;
		break;
	case CLIGNOTTE_2:
		if (intLED == 0)ledColor(colorViolet);
		if (intLED == (1 * intLEDFreqMs))ledColor(colorOrange);
		if (intLED == (2 * intLEDFreqMs))ledColor(colorGreen);
		if (intLED == (3 * intLEDFreqMs))intLED = -1;
		break;
	}
	intLED++;
}

//******************************************** BUZZER

//Active buzzer
void buzzerOn(uint8_t pDuration) {
	buzzer.tone(buzzerFreq, pDuration);
}

//Désactive buzzer
void buzzerOff() {
	buzzer.noTone();
}

//******************************************** MATRIX

void matrixDrawFace() {
	uint8_t i1[16] = { 0,0,96,96,0,2,9,13,9,2,0,96,96,0,0,0 };
	ledMx.drawBitmap(0, 0, 16, i1);
}



//******************************************** CAPTEUR ULTRASON

//Renvoi la distance en cm
int sensorGetDist() {
	return ultraSensor.distanceCm();
}

