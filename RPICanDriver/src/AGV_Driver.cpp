#include "AGV_Driver.h"



//Maybe create a twits message to interface with ROS ?


void AGV::writeVel( double vel[3] ){
	//Cinematic model:

	int16_t Vx = vel[0];
	int16_t Vy = vel[1];
	int16_t Vz = vel[2];

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

void AGV::start(){
	for (int i = 0; i < 4; ++i)
	{
		m[i].start();
	}


}

void AGV::stop(){

	for (int i = 0; i < 4; ++i)
	{
		m[i].stop();
	}

}