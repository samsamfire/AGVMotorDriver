#ifndef H_MOTOR_DRIVER
#define H_MOTOR_DRIVER

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
		Motor(int motor_addess);
		void readVelEncoder();
		void readPosEncoder();
		void readPos();

		void readVel();

		void readPosVel();
		uint16_t* readPosVelTorqueEncoder();

		void start();
		void stop();

		void writeVel(int16_t vel);
		void writePos(uint16_t pos);
		bool getState();

		bool setHdl(int s);
		uint8_t getAdress();
		


	private:

		uint16_t twist[3];
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












	


















#endif