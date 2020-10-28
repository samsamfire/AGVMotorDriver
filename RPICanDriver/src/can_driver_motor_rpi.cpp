#include "can_driver_rpi.h"



Motor::Motor(int socket_hdl, int motor_address){
	//Add constructor stuff
	this->address = motor_address;
	this->s = socket_hdl;
}

void Motor::readPos(){
	//Add some filtering to get right motor
	read(s, &frame, sizeof(frame));
	pos = (frame.data[1] << 8) + frame.data[0];
}

void Motor::readVel(){
	//Add some filtering to get right motor
	read(s, &frame, sizeof(frame));
	vel = (frame.data[1] << 8) + frame.data[0];
}

void Motor::readPosEncoder(){
	//Add some filtering to get right motor
	read(s, &frame, sizeof(frame));
	pos_encoder = (frame.data[1] << 8) + frame.data[0];
}

void Motor::readVelEncoder(){
	//Add some filtering to get right motor
	read(s, &frame, sizeof(frame));
	vel_encoder = (frame.data[1] << 8) + frame.data[0];
}

void Motor::readPosVelEncoder(){

	read(s, &frame, sizeof(frame));
	pos_encoder = (frame.data[1] << 8) + frame.data[0];
	vel_encoder = (frame.data[3] << 8) + frame.data[2];

}

void Motor::start(){
	frame.can_id = (address << 7) | START_ID;
	frame.can_dlc = 0;
	write(s, &frame, sizeof(frame));
}


void Motor::stop(){
	frame.can_id = (address << 7) | STOP_ID;
	frame.can_dlc = 0;
	write(s, &frame, sizeof(frame));
}

void Motor::writeVel(int16_t vel){
	frame.can_id = (address << 7) | SET_VEL_ID ;
	frame.can_dlc = 2;
	frame.data[0] = vel & 0xFF;
	frame.data[1] = vel >> 8;
	write(s,&frame,sizeof(frame));

}


void Motor::writePos(uint16_t pos){

	frame.can_id = (address << 7) | SET_POS_ID ;
	frame.can_dlc = 2;
	frame.data[0] = vel & 0xFF;
	frame.data[1] = vel >> 8;
	write(s,&frame,sizeof(frame));


}