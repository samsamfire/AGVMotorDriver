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
#include <stdint.h>

//#include <string>

#include "can_message.h"




class Motor
{
	public:
		Motor(int socket_handle,int motor_addess);
		void readVelEncoder();
		void readPosEncoder();
		void readPos(); 
		void readVel();
		void readPosVel();
		void readPosVelEncoder();
		void start();
		void stop();

		void writeVel(int16_t vel);
		void writePos(uint16_t pos);
		bool getState();
		


	private:
		int16_t vel;
		int16_t pos;
		bool state; //On or Off
		uint8_t mode; // pos 1, vel 2, torque 3...
		int16_t vel_encoder;
		int16_t pos_encoder;
		bool error; //1 for yes 0 for no
		uint8_t connection_state;
		uint8_t address;
		//CAN variables
		uint8_t update_rate_can;//Rate at which info is sent from pic default 50Hz
		struct can_frame frame;
		uint8_t nbytes;
		int s; //Socket Handle 

		//PID parameters to add


		//std::string name;

};





class MotorCAN
{

	public:
		MotorCAN();
		int init();
		int getSpeed();

		int setVel(uint8_t motor_num, int16_t vel);

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
		int getHdl();


	private:
		int ret;
	    int s, nbytes;
	    struct sockaddr_can addr;
	    struct ifreq ifr;
	    struct can_frame frame;

	    bool motors_state[4];
	    int motor_addresses[4]; //Sens trigo : front left, front right, back right, back left
	    char * motor_names[4] = {"front left","front right","back right","back left"};
	    
};









	


















#endif