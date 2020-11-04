#include "PID.h"





void update_pid(PID *pid){

	//Calculate PID output
    float error = 0;

    error = (float) *(pid->input)/1000 - *(pid->feedback);

    pid->iterm += pid->Ki*T*error;

    if(pid->iterm > pid->antiWindup){
        pid->iterm = pid->antiWindup;
    }
    else if(pid->iterm < -pid->antiWindup){
        pid->iterm = -pid->antiWindup;
    }

	pid->output =(float) pid->Kp*error + pid->iterm;
   // pid->output = 10000;
	//Convert This value into pwm for motor
	if(pid->output <= 0){
            pid->output_pwm = (float) (pid->output - 8.5)/0.46; //Calculated from excel spreadsheet and divided by 1000

        }
    else{
        pid->output_pwm = (float) (pid->output + 8.5)/0.46; //Calculated from excel spreadsheet and divided by 1000

    }
    //pid->output_pwm = 35;
	


}