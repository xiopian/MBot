// 
// 
// 

#include "MyMotor.h"

//MeDCMotor MyMotor::motorG
//{
//	return MeDCMotor(M1);
//}
//
//MeDCMotor MyMotor::motorD()
//{
//	return MeDCMotor(M2);
//}


void MyMotor::MotorAvance(uint8_t pSpeed)
{
	motorG.run(-pSpeed);
	motorD.run(pSpeed);
}

void MyMotor::MotorRecule(uint8_t pSpeed)
{
	motorG.run(pSpeed);
	motorD.run(-pSpeed);
}

void MyMotor::MotorTourne(Tourne pSens, uint8_t pSpeed)
{
	if (pSens == GAUCHE) {
		motorG.run(pSpeed);
		motorD.run(pSpeed);
	}
	if (pSens == DROITE) {
		motorG.run(-pSpeed);
		motorD.run(-pSpeed);
	}
}

void MyMotor::MotorStop()
{
	motorG.stop();
	motorD.stop();
}


