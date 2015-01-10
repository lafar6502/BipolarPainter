#include "MultiAxisTrapezProfileGenerator.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

MultiAxisTrapezProfileGenerator::MultiAxisTrapezProfileGenerator(int axes) 
{

};

/*
bool MultiAxisTrapezProfileGenerator::PrepareMotion()
{
	if (_accel <= 0 || _accel > 1) return false;
	if (_maxV <= 0 || _accel > 1) return false;
	
	_startP = _curP;
	_t = 0;
	_curV = _baseV;
	bool forward = _targetP >= _curP;
	_curAccel = forward ? _accel : -_accel;
	_curV = forward ? _baseV : -_baseV;
	
	double t;
	double dd = CalculateDecelerationDistance(_maxV, _accel, &t);
	double remd = GetRemainingDistanceAbs();
	
	double mt = 0;
	if (dd > remd / 2) {
		//no se
		_brakeD = remd / 2;
	} else {
		_brakeD = dd;		
	}
	printf("motion time: %f\n", mt);
	_stage = 1;
	
	return true;
		
	
};

double MultiAxisTrapezProfileGenerator::CalculateDecelerationDistance(double v, double decel, double* t) {
	*t = v / decel;
	double dist = 0.5 * v * v / decel;
	return dist;
}

double MultiAxisTrapezProfileGenerator::CalculateDeceleration(double distance, double v, double* t) {
	//distance = at2/2
	//v = at;
	//t = v/a;
	//distance = a * (v/a)^2 / 2;
	//distance = v * v/a * 0.5 => a * 0.5 = distance / v2 => a = 2 * distance / v*v;
	double a = 0.5 * (v * v) / distance;
	*t = v / a; 
	return a;
}

void MultiAxisTrapezProfileGenerator::NextStep()
{
	if (_stage == 0) {
		return;
	};
	
	int ps = _stage;
	bool fwd = _targetP > _startP;
	if (_stage == 1) {
		_curP += _curV + _curAccel / 2;
		double rd = GetRemainingDistanceAbs();
		if (rd <= _brakeD) {
			_curP = _targetP - (fwd ? _brakeD : -_brakeD);
			printf("newp: %f\n", _curP);
			_stage = 3;
		} else if (_curV >= _maxV) {
			_curV = fwd ? _maxV : -_maxV;
			_stage = 2;
		} else {
			_curV += _curAccel;
		}
	}
	else if (_stage == 2) {
		_curP += _curV;
		double rd = GetRemainingDistanceAbs();
		if (rd <= _brakeD) {
			_curP = _targetP - (fwd ? _brakeD : -_brakeD);
			printf("newp: %f\n", _curP);
			_stage = 3;
		}; 
	}
	else if (_stage == 3) {
		_curP += _curV + _curAccel / 2;
		double rd = GetRemainingDistanceAbs();
		if (rd < 1.0 && trunc(_curP) == trunc(_targetP)) {
			_stage = 0;
			_curP = _targetP;
		} else {
			double vd = fwd ? _curV + _curAccel : - (_curV + _curAccel);
			if (vd > 0) {
				_curV += _curAccel;
			}
			else {
				_curAccel = 0;
				_curV = fwd ? _baseV : -_baseV;
			}
		}
	};
	if (_stage == 3 && ps != _stage) {
		double rd1 = GetRemainingDistanceAbs();
		double mt1;
		_curAccel = CalculateDeceleration(rd1, fwd ? _curV : -_curV, &mt1);
		if (fwd) _curAccel = -_curAccel;
		printf("decel: %f, time: %f\n", _curAccel, mt1);
	};
	_t++;
};

void MultiAxisTrapezProfileGenerator::PrintState(char* buf, int len) {
	snprintf(buf, len, "T:%d, P:%f, V:%f, ST:%d, TOGO: %f", _t, GetCurrentPosition(), GetCurrentVelocity(), _stage, GetRemainingDistanceAbs());
}


*/
