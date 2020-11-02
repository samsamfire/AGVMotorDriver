#ifndef PID_APP
#define PID_APP
#include "app.h"
#include "PID.h"



typedef enum
{
	PID_APP_STATE_INIT=0,


} PID_APP_STATES;

//This contains the essential data during app operation
typedef struct
{
	
	
	
} PID_APP_DATA;






void PID_APP_Init();
void PID_APP_Tasks();



extern PID_APP_DATA pappData;












#endif