#ifndef H_CAN_DRIVER_RPI
#define H_CAN_DRIVER_RPI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>





class MotorCAN
{

	public:
		void MotorCan();
		int init();
		int getSpeed();
		int startConnection(int bitrate);
		int stopConnection();
		int on();
		int off();

		int startMotors();
		int stopMotors();
		
		int setMode();
		int getMode();
		int getState(); //On or off of each motor

		void setAddresses(int fl, int fr, int br, int bl); //-1 ifdon't care 


	private:
		int ret;
	    int s, nbytes;
	    struct sockaddr_can addr;
	    struct ifreq ifr;
	    struct can_frame frame;

	    int motor_addresses[4]; //Sens trigo : front left, front right, back right, back left

	    
	
};









	


















#endif