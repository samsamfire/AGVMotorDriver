/*main for testing AGV controller*/


#include "AGV_Driver.h"



double vel[3] = {0.3,0,0};

int main(int argc, char const *argv[])
{
	//Initialize agv robot object
	AGV agv_robot(5,6,-1,-1);

	//Start CAN bus at 500000
	agv_robot.openBus(500000);

	//Start each driver 
	agv_robot.start();

	//Send a speed command
	//agv_robot.writeVel(vel);

	while(1){

	agv_robot.writeVel(vel);
	usleep(1000000);

	}


	




	//Don't forget to turn off robot drivers

	agv_robot.stop();

	//And close bus

	agv_robot.closeBus();

	return 0;
}