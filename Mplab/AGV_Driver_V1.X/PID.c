#include "PID.h"





void update_pid(PID *pid){

	//Calculate PID output
    

    pid->error = (float) *(pid->input)/1000 - (float)*(pid->feedback);

    pid->iterm += (float)pid->Ki*T*pid->error;
    pid->dterm = pid->Kd*(pid->prev_error-pid->error)/T;

    if(pid->iterm > pid->antiWindup){
        pid->iterm = pid->antiWindup;
    }
    else if(pid->iterm < -pid->antiWindup){
        pid->iterm = -pid->antiWindup;
    }

	pid->output =(float) pid->Kp*pid->error + pid->iterm + pid->dterm;
   // pid->output = 10000;
	//Convert This value into pwm for motor
	if(pid->output < 0){
            pid->output_pwm = (float) (pid->output - 8.5)/0.46; //Calculated from excel spreadsheet and divided by 1000

        }
    else if(pid->output >0){
        pid->output_pwm = (float) (pid->output + 8.5)/0.46; //Calculated from excel spreadsheet and divided by 1000

    }

    else{

        pid->output_pwm = 0;
    }

    pid->prev_error = pid->error;
    
	


}