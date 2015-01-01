#include <stdlib.h>
#include <stdio.h>
#include "SingleAxisTrapezGenerator.h"
#include "IntSingleAxisTrapezGenerator.h"


void TestTrapez1();
void TestTrapez2();


int main(int argc, char** argv)
{
	TestTrapez2();

	return 0;
}


void TestTrapez1()
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
}

void TestTrapez2()
{
	IntSingleAxisTrapezGenerator gen;
	gen.SetAcceleration(1);
	gen.SetMaxVelocity(20);
	gen.SetCurrentPosition(0);
	gen.SetTargetPosition(2000);
	gen.PrepareTrajectory();
	printf("%d: pos %d, vel %d\n", gen.GetStepCount(), gen.GetCurrentPosition(), gen.GetCurrentVelocity());
	while(gen.MotionInProgress())
	{
		gen.NextStep();
		printf("%d: pos %ld, vel %d\n", gen.GetStepCount(), gen.GetCurrentPosition(), gen.GetCurrentVelocity());
	}
}
