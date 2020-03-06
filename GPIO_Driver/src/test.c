#include "GPIO.h"
void main(void)
{
	GPIO_Pin_t testpin;
	testpin.pin=GPIO_PIN_0;
	testpin.mode=GPIO_MODE_OUTPUT_PUSH_PULL;
	testpin.speed=GPIO_OUTPUT_SPEED_10MHz;

	GPIO_Init(PORTA,&testpin);
	//GPIO_Pin_Lock(PORTA,&testpin);
	while(1);
}
