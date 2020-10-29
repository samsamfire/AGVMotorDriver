#include "AGV_Driver.h"



//Maybe create a twits message to interface with ROS ?



/*This function reads velocity info from encoder of all 4 drivers and computes 
actual dx, dy, dyaw via inverse kinematics*/

void AGV::readVel(double vel[3]){

	uint16_t *state[3];
	for (int i = 0; i < 4; ++i)
	{
		if(m[i].getState() == true){
			state[i] = m[i].readPosVelTorqueEncoder();
			printf("Read positio,velocity,torque : %i %i %i\r\n",state[i][0],state[i][1],state[i][2]);
		}
		
	}


}


void AGV::writeVel( double vel[3] ){
	//Cinematic model:

	this->vel[0] = vel[0];
	this->vel[1] = vel[1];
	this->vel[2] = vel[2];

	double Vx = vel[0];
	double Vy = vel[1];
	double Vz = vel[2];

	int16_t m_v[4];

	//https://www.fh-dortmund.de/roehrig/papers/roehrigCCTA17.pdf

	// double J[4][3] = {
	// 	{1.0,-1.0,-(La+Lb)},
	// 	{1.0,1.0,La+Lb},
	// 	{1.0,-1.0,-(La+Lb)},
	// 	{1.0,1.0,(La+Lb)}
	// };

	
//Check signs by testing

	m_v[0] = (1/Rr)*(Vx-Vy-(La+Lb))*F;
	m_v[1] = -(1/Rr)*(Vx+Vy+(La+Lb))*F;
	m_v[2] = (1/Rr)*(Vx-Vy-(La+Lb))*F;
	m_v[3] = -(1/Rr)*(Vx+Vy+(La+Lb))*F;

	for (int i = 0; i < 4; ++i)
	{
		//Check if motor is activated
		if(m[i].getState() == 1){
			printf("Sending speed of %i to motor %i\r\n",m_v[i],i);
			m[i].writeVel((int16_t)m_v[i]);
		}
		else{
			printf("Error motor %i is not on\r\n",i );
		}
		
	}


}

/*Start each motor of the agv*/
/*Bus needs to be opened before calling this function*/

void AGV::start(){
	for (int i = 0; i < 4; ++i)
	{
		if(m[i].getAdress() != -1){
			m[i].start();
		}
	}

}


/*Stop each motor of the agv*/
/*Bus needs to be opened before calling this function*/


void AGV::stop(){

	for (int i = 0; i < 4; ++i)
	{
		if(m[i].getAdress() != -1){
			m[i].stop();
		}
	}

}


/*Start CAN bus on device*/

bool AGV::openBus(int bitrate){

	/*TODO
    -Add a dummy read or write to check if connexion is working 
    -Check the address of all connected devices*/

    //Code from waveshare demo https://www.waveshare.com/wiki/RS485_CAN_HAT

	char buff[100];
	
	/*Should remove the sudo */
	sprintf(buff,"sudo ip link set can0 type can bitrate %i",bitrate);
	system(buff);
    system("sudo ifconfig can0 up");

    printf("Initialized can at bitrate %i \r\n",bitrate);

    
    for (int i = 0; i < 4; ++i)
    {
    	//1.Create socket
    	s[i] = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    	if (s[i] < 0) {
	        perror("socket PF_CAN failed");
	        return 1;
    	}

    	 //2.Specify can0 device
	    strcpy(ifr[i].ifr_name, "can0");
	    ret[i] = ioctl(s[i], SIOCGIFINDEX, &ifr[i]);
	    if (ret[i] < 0) {
	        perror("ioctl failed");
        	return 1;
        }


        //3.Bind the socket to can0
	    addr[i].can_family = AF_CAN;
	    addr[i].can_ifindex = ifr[i].ifr_ifindex;
	    ret[i] = bind(s[i], (struct sockaddr *)&addr[i], sizeof(addr[0]));
	    if (ret[i] < 0) {
	        perror("bind failed");
	        return 1;
	    }

	    //4.Define receive rules
	    rfilter[i].can_id = (m[i].getAdress() << 7); //Ids begging with correct address
    	rfilter[i].can_mask = (m[i].getAdress() << 7);//All lower bits are don't cares
    	setsockopt(s[i], SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter[0]));
	

		//5.Give to motors socket handle

		m[i].setHdl(s[i]);

	}

    return 0;
}

/*Close CAN bus*/

bool AGV::closeBus(){

	//Shutdown can and socket
	for (int i = 0; i < 4; ++i)
	{
		close(s[i]);
	}
	
	system("sudo ifconfig can0 down");

	printf("Shut down can0\n");

	return 0;

}



