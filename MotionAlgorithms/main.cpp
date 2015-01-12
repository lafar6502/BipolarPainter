#include <iostream>
#include "ProfileGenerator.h"
#include "TrapezProfileGenerator.h"
#include "MultiAxisGearedProfileGenerator.h"
#include <stdio.h>
#include "Vect.h"
#include <math.h>
#include "ParametricTest.h"


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



void TestParametricStepping()
{
	double res = 0.002;
	CirclePrm cp;
	cp.r = 50;
	double t = 0;
	parametricCurve crv = pcircle;
	double funVal[2];
	long funInt[2];
	long prevFunInt[2];
	long difz[2];
	
	memset(difz, 0, sizeof(difz));
	crv(t, &cp, funVal);
	roundCoords(funVal, sizeof(funVal) / sizeof(double), prevFunInt);
	int step = 1;
	while(t < 1) {
		crv(t, &cp, funVal);
		roundCoords(funVal, sizeof(funVal) / sizeof(double), funInt);
		for (int i=0; i<2; i++) {
			difz[i] = funInt[i] - prevFunInt[i];
			if (abs(difz[i]) > 1) {
				printf("RESOLUTION too low: %d, %f\n", i, difz[i]);
				return;
			}
		}
		printf("%d. %f\t->\t%d, %d\n", step, t, difz[0], difz[1]);
		memcpy(prevFunInt, funInt, sizeof(funInt));
		t+= res;
		step++;
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

void circleParametric(double t, double r, double* vals) {
	vals[1] = r * sin(t);
	vals[0] = r * cos(t);
};





void TestRasterization()
{
	double r = 50;
	double res = 0.025;
	double prev[2], cur[2];
	circleParametric(0, r, cur);
	memcpy(prev, cur, sizeof(prev));
	double t = 0;
	int n = 0;
	char buf[50];
	while(t < 2*3.14159) {
		circleParametric(t, r, cur);
		int p1 = (int) trunc(prev[0]);
		int p2 = (int) trunc(cur[0]);
		int dirx = p2 - p1;
		p1 = (int) trunc(prev[1]);
		p2 = (int) trunc(cur[1]);
		int diry = p2 - p1;
		printf("%d: [%d, %d\n", n, dirx, diry);
		memcpy(prev, cur, sizeof(prev));
		t += res;	
		n++;
	}
	
	
}






int main(int argc, char** argv) {
	TestParametricStepping();
	return 0;
	TestRasterization();
	return 0;
	TestMultiAxisTrapez();
	return 0;
	TestVect();
	return 0;
	TestTrapez();
	
	return 0;
}
