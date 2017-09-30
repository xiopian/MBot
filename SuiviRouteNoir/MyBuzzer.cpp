// 
// 
// 

#include "MyBuzzer.h"

void MyBuzzer::BuzzerOn(uint8_t pDuration)
{
	buzzer.tone(buzzerFreq, pDuration);
}

void MyBuzzer::BuzzerOff()
{
	buzzer.noTone();
}
