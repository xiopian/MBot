#include <Wire.h>
#include "MyMotor.h"
#include "MyBuzzer.h"
#include <MeMCore.h>
#include <TimeLib.h>

//Line follower
MeLineFollower lineFinder(PORT_2);

//Telecommande infra-rouge
MeIR irSensor;

bool bRunning = false;
bool bAvance = false;
bool bTurnLeft = false;
bool bTurnRight = false;

//Capteur ultrason
MeUltrasonicSensor ultraSensor(PORT_3);

MyBuzzer buzzer;
MyMotor motor;

//Setup
void setup() {

	//Init
	Serial.begin(9600);
	irSensor.begin();
}

//Loop
void loop() {

	/*int s = second();
	if (s == 0 || s == 10 || s == 20 || s == 30 || s == 40 || s == 50) {
		buzzer.BuzzerOn(500);
	}*/

	//Telecommande
	if (irSensor.decode())
	{
		uint32_t value = irSensor.value;
		switch (value >> 16 & 0xff) {
		case IR_BUTTON_A:
			bRunning = true;
			buzzer.BuzzerOn(500);
			break;
		case IR_BUTTON_B:
			bRunning = false;
			motor.MotorStop();
			buzzer.BuzzerOn(500);
			break;
		case IR_BUTTON_C:
			bRunning = false;
			motor.MotorStop();
			buzzer.BuzzerOn(500);
			break;
		case IR_BUTTON_D:
			break;
		case IR_BUTTON_E:
			break;
		case IR_BUTTON_F:
			break;

		case IR_BUTTON_PLUS:  //Avance
			break;
		case IR_BUTTON_MINUS: //Recule
			break;
		case IR_BUTTON_NEXT:  //Droite
			break;
		case IR_BUTTON_PREVIOUS:  //Gauche
			break;

		case IR_BUTTON_1:
			motor.MotorSpeed = 50;
			buzzer.BuzzerOn(500);
			break;
		case IR_BUTTON_2:
			motor.MotorSpeed = 70;
			buzzer.BuzzerOn(500);
			break;
		case IR_BUTTON_3:
			motor.MotorSpeed = 90;
			buzzer.BuzzerOn(500);
			break;
		case IR_BUTTON_4:
			motor.MotorSpeed = 110;
			buzzer.BuzzerOn(500);
			break;
		case IR_BUTTON_5:
			motor.MotorSpeed = 130;
			buzzer.BuzzerOn(500);
			break;
		case IR_BUTTON_6:
			motor.MotorSpeed = 150;
			buzzer.BuzzerOn(500);
			break;
		case IR_BUTTON_7:
			motor.MotorSpeed = 170;
			buzzer.BuzzerOn(500);
			break;
		case IR_BUTTON_8:
			motor.MotorSpeed = 190;
			buzzer.BuzzerOn(500);
			break;
		case IR_BUTTON_9:
			motor.MotorSpeed = 210;
			buzzer.BuzzerOn(500);
			break;
		}
	}

	//Si en marche
	if (bRunning) {

		//Capteur ligne
		int sensorState = lineFinder.readSensors();
		switch (sensorState)
		{
		case S1_IN_S2_IN:
			break;
		case S1_IN_S2_OUT:
			bAvance = false;
			bTurnRight = true;
			bTurnLeft = false;
			break;
		case S1_OUT_S2_IN:
			bAvance = false;
			bTurnRight = false;
			bTurnLeft = true;
			break;
		case S1_OUT_S2_OUT:
			bAvance = true;
			bTurnRight = false;
			bTurnLeft = false;
			break;
		}

		
		//Direction
		if (bAvance) motor.MotorAvance(motor.MotorSpeed);
		if (bTurnRight) motor.MotorTourne(DROITE, motor.MotorSpeed);
		if (bTurnLeft) motor.MotorTourne(GAUCHE, motor.MotorSpeed);
	}
}


