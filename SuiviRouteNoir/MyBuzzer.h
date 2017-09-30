// MyBuzzer.h

#ifndef _MYBUZZER_h
#define _MYBUZZER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <MeBuzzer.h>
#else
#include "WProgram.h"
#endif

class MyBuzzer {

public:
	void BuzzerOn(uint8_t pDuration);
	void BuzzerOff();

private:
	MeBuzzer buzzer;
	uint8_t buzzerFreq = 500;
};

#endif

