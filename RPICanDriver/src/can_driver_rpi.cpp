#include "can_driver_rpi.h"
//#include <iostream>
#include <string>
#include "stdio.h"
#include "can_message.h"

using namespace std;
//Constructor
void MotorCAN::MotorCan(){

	//Create a motor can object

}

int MotorCAN::startConnection(int bitrate){

	char buff[100];
	memset(&frame, 0, sizeof(struct can_frame));

	sprintf(buff,"sudo ip link set can0 type can %i",bitrate);
	system(buff);
    system("sudo ifconfig can0 up");

    printf("Initialized can at bitrate %i \r\n",bitrate);

    //1.Create socket
    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (s < 0) {
        perror("socket PF_CAN failed");
        return 1;
    }
    
    //2.Specify can0 device
    strcpy(ifr.ifr_name, "can0");
    ret = ioctl(s, SIOCGIFINDEX, &ifr);
    if (ret < 0) {
        perror("ioctl failed");
        return 1;
    }
    
    //3.Bind the socket to can0
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    ret = bind(s, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        perror("bind failed");
        return 1;
    }

    return 0;

    /*TODO
    -Add a dummy read or write to check if connexion is working 
    -Check the address of all connected devices*/
}

int MotorCAN::stopConnection(){

	//Shutdown can and socket
	close(s);
	system("sudo ifconfig can0 down");

	printf("Shut down can0\n");

	return 0;
}



int MotorCAN::startMotors(){
	//Send command to start each motor
	int i;

	for(i=0;i<4;i++){

		//Construct CAN frame
		frame.can_id = (motor_addresses[i]<<7)|START_ID;
		frame.can_dlc = 1;
		frame.data[0] = 55;

		if (motor_addresses[i] != -1)
		{
			printf("Starting motor %i at address %i \r\n",i,motor_addresses[i]);
			write(s, &frame, sizeof(frame));
		}


	}


	return 0;
}

int MotorCAN::stopMotors(){

	int i=0;

	for(i=0;i<4;i++){
		//Construct CAN frame
		frame.can_id = (motor_addresses[i]<<7)|STOP_ID;
		frame.can_dlc = 1;
		frame.data[0] = 66;
		if (motor_addresses[i] != -1)
		{
			printf("Stoping motor %i at address %i \r\n",i,motor_addresses[i]);
			write(s, &frame, sizeof(frame));
		}

	}

	return 0;
}



void MotorCAN::setAddresses(int fl, int fr, int br, int bl){
	//Set the address of each motor
	motor_addresses[0] = fl;
	motor_addresses[1] = fr;
	motor_addresses[2] = br;
	motor_addresses[3] = bl;
}







int main(int argc, char const *argv[])
{
	/* code */
	MotorCAN m_can;
	m_can.startConnection(500000);

	m_can.setAddresses(1, 2, 3, 4);
	m_can.startMotors();
	m_can.stopMotors();



	return 0;
}