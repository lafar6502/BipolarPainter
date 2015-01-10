#include "MultiAxisGearedProfileGenerator.h"

bool MultiAxisGearedProfileGenerator::StartMovingToDestination(Vect<double> dest, double maxAccel, double maxVelocity) {
	int idx = dest.MaxAbsValueIndex();
	_ratios = dest / dest[idx];
	char buf[100];
	_ratios.ToString(buf, sizeof(buf));
	printf("ratios: %s, tp: %f\n", buf, dest[idx]);
	_gen.SetTargetPosition(dest[idx]);
	_gen.SetMaxVelocity(maxVelocity);
	_gen.SetAcceleration(maxAccel);
	return _gen.PrepareMotion();
}

Vect<double> MultiAxisGearedProfileGenerator::GetCurrentPos() {
	double pos = _gen.GetCurrentPosition();
	(_ratios * pos).Print("mp");
	Vect<double> p2 = _ratios * pos;
	_ratios.Print("ratios");
	p2.Print("multed");
	printf("pos: %f\n", pos);
	return p2;
};


