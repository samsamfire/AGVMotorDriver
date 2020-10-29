#include "Motor_Driver_DSPIC33.h"



Motor::Motor(int motor_address){
	//Add constructor stuff
	this->address = motor_address;
	
}

bool Motor::getState(){

	return state;
}

bool Motor::setHdl(int s){

	this->s=s;
	return true;
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

	/*Todo perform checks*/
	state = 1;
}


void Motor::stop(){
	frame.can_id = (address << 7) | STOP_ID;
	frame.can_dlc = 0;
	write(s, &frame, sizeof(frame));

	state = 0;
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

uint8_t Motor::getAdress(){

	return address;
}