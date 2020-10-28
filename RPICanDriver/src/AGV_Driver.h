#ifndef  H_AGV_DRIVER
#define H_AGV_DRIVER

#include "can_driver_rpi.h"

#define Rr 10 //Rayon de la roue
#define Z 70 //Rapport de reduction
#define La 0.2//Demie longueur
#define Lb 0.3 //Demie largeur
/*Facteur d'aggrandissment pour ne pas perdre trop d'informations
Lors de l'envoie des vitesses, il faudra prendre ca en compte dans le micro
Cela suppose que les vitesses sont contenus entre -30m/s et +30m/s(largement le cas)
*/
#define F 1000 






/*Driver for controlling the hole AGV*/

/*The AGV accepts controls such as x velocity, y velocity, z velocity
As well as x and y and yaw positions*/



class AGV
{
public:

	AGV(); //fl fr br bl;
	AGV(int ad_fl, int ad_fr, int ad_br, int ad_bl, int s): 
	m{Motor(s,ad_fl),Motor(s,ad_fr),Motor(s,ad_br),Motor(s,ad_bl)}{};

	void setMode();
	void writePos();

	void writeVel(double vel[3]);

	void start();
	void stop();



	//


private:
	//Declare the 4 motor drivers

	Motor m[4];




	
};




























#endif