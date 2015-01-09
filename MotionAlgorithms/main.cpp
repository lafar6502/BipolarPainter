#include <iostream>
#include "ProfileGenerator.h"
#include "TrapezProfileGenerator.h"
#include <stdio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void TestTrapez()
{
	TrapezProfileGenerator p;
	p.SetTargetPosition(50);
	p.SetMaxVelocity(0.8);
	p.SetAcceleration(0.04);
	p.SetBaseVelocity(0.01);
	
	char buf[100];
	p.PrepareMotion();
	int cnt = 0;
	while(p.InMotion() && cnt++ < 100) {
		p.PrintState(buf, sizeof(buf));
		printf("%s\n", buf);
		p.NextStep();
	};
	p.PrintState(buf, sizeof(buf));
	printf("%s - STOP\n", buf);
}

int main(int argc, char** argv) {
	
	TestTrapez();
	
	return 0;
}
