#ifndef H_PID
#define H_PID

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>



#define T 0.005 //5 ms interrupts



typedef struct 
{
	float output;
	float output_pwm;

	int16_t *input;

	float Kp;
	float Kd;
	float Ki;

	float prev_value;
	float prev_error;

	float iterm;
	float antiWindup;

	float* feedback;
	
} PID;





void update_pid(PID * pid);





























#endif