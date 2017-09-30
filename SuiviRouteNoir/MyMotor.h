// MyMotor.h

#ifndef _MYMOTOR_h
#define _MYMOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <MeDCMotor.h>
#else
#include "WProgram.h"
#endif

enum Tourne {
	GAUCHE,
	DROITE
};

class MyMotor {



public:
	void MotorAvance(uint8_t pSpeed);
	void MotorRecule(uint8_t pSpeed);
	void MotorTourne(Tourne pSens, uint8_t pSpeed);
	void MotorStop();
	uint8_t MotorSpeed = 50;

private:
	//Moteurs 1 (gauche) et 2 (droit)
	MeDCMotor motorG = MeDCMotor(M1);
	MeDCMotor motorD = MeDCMotor(M2);
	
};

#endif

