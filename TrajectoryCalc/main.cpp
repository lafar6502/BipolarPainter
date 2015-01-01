#include <stdlib.h>
#include <stdio.h>
#include "SingleAxisTrapezGenerator.h"





int main(int argc, char** argv)
{

	SingleAxisTrapezGenerator gen;
	gen.SetAcceleration(1.5);
	gen.SetMaxVelocity(20);
	gen.SetCurrentPosition(0.0);
	gen.SetDestinationPosition(-200);
	gen.PrepareTrajectory();
	int cnt = 0;
	printf("%d: pos %f, vel %f\n", cnt, (float) gen.GetCurrentPosition(), (float) gen.GetCurrentVelocity());
	while(gen.TrajectoryInProgress())
	{
		gen.SingleStep();
		cnt++;
		printf("%d: pos %f, vel %f\n", cnt, (float) gen.GetCurrentPosition(), (float) gen.GetCurrentVelocity());
	}
	return 0;
}
