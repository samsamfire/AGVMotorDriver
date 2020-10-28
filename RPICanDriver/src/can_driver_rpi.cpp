#include "can_driver_rpi.h"
//#include <iostream>



/*TODO
-Add security to switch off motors if connection is lost
*/




//Constructor
MotorCAN::MotorCAN(){
	int i;
	//Create a motor can object
	memset(&frame, 0, sizeof(struct can_frame));

	//All motors are off to begin with 

	for (i = 0; i < 4; ++i)
	{
		motors_state[i] = false;
	}

}

int MotorCAN::startConnection(int bitrate){

	char buff[100];
	

	sprintf(buff,"sudo ip link set can0 type can bitrate %i",bitrate);
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
			//should check for ack
			motors_state[i] = true;
			printf("Starting motor %s at address %i \r\n",motor_names[i],i);
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
			//Should check for ack
			motors_state[i]=false;
			printf("Stoping motor %s at address %i \r\n",motor_names[i],i);
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

int MotorCAN::setVel(uint8_t motor_num, int16_t vel){

	frame.can_id = (motor_addresses[motor_num]<<7)|SET_VEL_ID;
	frame.can_dlc = 2;
	frame.data[0] = vel & 0xFF;
	frame.data[1] = vel >> 8;

	nbytes = write(s, &frame, sizeof(frame)); 
    if(nbytes != sizeof(frame)) {
        printf("Send Error frame[0]!\r\n");
        //system("sudo ifconfig can0 down");
        return 1;
    }

	return 0;

}

int MotorCAN::getHdl(){

	return s;
}
















int main(int argc, char const *argv[])
{
	/* code */
	int s;
	MotorCAN m_can;
	m_can.startConnection(500000);
	s=m_can.getHdl();
	Motor m1(s,5);
	m1.start();

	m1.writeVel(20);



	//m_can.setAddresses(1, 2, 3, 4);
	//m_can.startMotors();
	//m_can.stopMotors();

	m_can.stopConnection();



	return 0;
}