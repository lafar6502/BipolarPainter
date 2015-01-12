#include "ParametricTest.h"
#include <math.h>
#include <stdio.h>
#include <string.h>



void pcircle(double t, void* state, double* values)
{
	CirclePrm *cp = (CirclePrm*) state;
	values[0] = cp->r * cos(t * 2 * M_PI) - cp->r;
	values[1] = cp->r * sin(t * 2 * M_PI);
};

void roundCoords(double* coords, int len, long* rounded) {
	for(int i=0; i<len; i++) {
		rounded[i] = lround(coords[i]);
	}
};






