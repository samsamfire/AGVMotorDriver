#include "motor_driver.h"
#
//See header file for explanations


void setDuty(float duty)
{
	if(duty==0){
		OC1R = 0;
		OC2R = 0;
	}
	else if(duty>0)
	{
		OC2R = 0; //Turn off reverse half-bridge
		OC1R = (uint16_t) limitPWM((float)MAX_PWM_DUTY*((float)duty/100));

	}
	else if(duty<0)
	{
		OC1R = 0; //Turn off forward half-bridge
		OC2R = (uint16_t) limitPWM((float)MAX_PWM_DUTY*((float)duty/100));
	}
}



uint16_t limitPWM(float val){
	if (val>MAX_PWM_DUTY_ALLOWED)
	{
		return MAX_PWM_DUTY_ALLOWED;
	}
	else if(val<-MAX_PWM_DUTY_ALLOWED)
	{
		return MAX_PWM_DUTY_ALLOWED;
	}
	else{
		return val;
	}
}	