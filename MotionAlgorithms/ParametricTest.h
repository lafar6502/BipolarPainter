#ifndef _PTHIN_32342
#define _PTHIN_32342

typedef void (*parametricCurve)(double t, void* state, double* values);

typedef struct 
{
	double r;
} CirclePrm;



void pcircle(double t, void* state, double* values);

void roundCoords(double* coords, int len, long* rounded);




#endif

