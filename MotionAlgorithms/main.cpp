#include <iostream>
#include "ProfileGenerator.h"
#include "TrapezProfileGenerator.h"
#include "MultiAxisGearedProfileGenerator.h"
#include <stdio.h>
#include "Vect.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void TestTrapez()
{
	TrapezProfileGenerator p;
	p.SetCurrentPosition(200);
	p.SetTargetPosition(100);
	p.SetMaxVelocity(0.99);
	p.SetAcceleration(0.04);
	p.SetBaseVelocity(0.01);
	
	char buf[100];
	if (!p.PrepareMotion()) {
		printf("Invalid motion parameters");
		return;
	}
	int cnt = 0;
	while(p.InMotion() && cnt++ < 200) {
		p.PrintState(buf, sizeof(buf));
		printf("%s\n", buf);
		p.NextStep();
	};
	p.PrintState(buf, sizeof(buf));
	printf("%s - STOP\n", buf);
}

void TestMultiAxisTrapez() {
	MultiAxisGearedProfileGenerator p(3);
	char buf[100];
	
	Vect<double> dest(10, 300, -40);
	if (!p.StartMovingToDestination(dest, 0.02, 0.8)) {
		printf("Motion error\n");
		return;
	}
	int cnt = 0;
	while(p.InMotion() && cnt++ < 500) {
		Vect<double> pos = p.GetCurrentPos();
		pos.ToString(buf, sizeof(buf));
		printf("%s\n", buf);
		p.NextStep();
	}
	
}

void TestVect()
{
	char buf[100];
	
	Vect<double> v(1.0, 2.0);
	double d1 = v[0];
	printf("x: %f, y: %f, len: %f\n", v[0], v[1], v.GetAbsLength());
	v.ToString(buf, 100);
	printf("%s\n", buf);
	v += Vect<double>(2.0, 1.0);
	printf("x: %f, y: %f, len: %f\n", v[0], v[1], v.GetAbsLength());
	v.ToString(buf, 100);
	printf("%s\n", buf);
	v *= 2;
	printf("x: %f, y: %f, len: %f\n", v[0], v[1], v.GetAbsLength());
	v.ToString(buf, 100);
	printf("%s\n", buf);
	v = v - v;
	printf("x: %f, y: %f, len: %f\n", v[0], v[1], v.GetAbsLength());
	v.ToString(buf, 100);
	printf("%s\n", buf);
}

int main(int argc, char** argv) {
	
	TestMultiAxisTrapez();
	return 0;
	TestVect();
	return 0;
	TestTrapez();
	
	return 0;
}
