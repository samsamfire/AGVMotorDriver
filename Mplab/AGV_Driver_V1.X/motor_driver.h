
#ifndef H_MOTOR_DRIVER
#define H_MOTOR_DRIVER

#include "mcc_generated_files/system.h"
/*Fonctions utiles pour faire fonctionner le moteur*/



#define QEI_SPEED_CONSTANT
#define QEI_ANGLE_CONSTANT

/*Output compare module is used for generating PWM signal
Timer2 is the time base and the period is determined by the PR2 register
The duty cycle is then determined by OCR2 (if OCR2 = PR2 then duty cycle is 100% and if OCR2 = 0 then duty cycle is 0%)
Hence we can define the maximum pwm value*/

#define MAX_PWM_DUTY 0x7FFF
#define MAX_PWM_DUTY_ALLOWED 26000 //Around 80% of max pwm



/*Cette fonction prend en entrée un angle et met le moteur à l'angle désiré*/

void setAngle(float *angle);


/*Controls duty cycle in %
Negative is anticlockwise and positive is clockwise*/

void setDuty(float duty);




void setSpeed(float *speed);


/*idem mais permet de controler le couple*/

void setTorque(float *torque);


float limitPWM(float val);
































#endif