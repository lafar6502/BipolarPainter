#include "TrapezProfileGenerator.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

TrapezProfileGenerator::TrapezProfileGenerator()
{
	_curP = _targetP = _startP = 0;
	_curV = 0;
	_accel = 0;
	_baseV = 0;
	_t = 0;
};

void TrapezProfileGenerator::PrepareMotion()
{
	_startP = _curP;
	_t = 0;
	_curV = _baseV;
	
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
	
	
		
	
};

double TrapezProfileGenerator::CalculateDecelerationDistance(double v, double decel, double* t) {
	*t = v / decel;
	double dist = 0.5 * v * v / decel;
	return dist;
}

double TrapezProfileGenerator::CalculateDeceleration(double distance, double v, double* t) {
	//distance = at2/2
	//v = at;
	//t = v/a;
	//distance = a * (v/a)^2 / 2;
	//distance = v * v/a * 0.5 => a * 0.5 = distance / v2 => a = 2 * distance / v*v;
	double a = 2 * distance / (v * v);
	*t = v / a;
	return a;
}

void TrapezProfileGenerator::NextStep()
{
	if (_stage == 0) {
		return;
	};
	
	int ps = _stage;
		
	if (_stage == 1) {
		_curP += _curV + _accel / 2;
		double rd = GetRemainingDistanceAbs();
		if (rd <= _brakeD) {
			_curP = _targetP - _brakeD;
			_stage = 3;
		} else if (_curV >= _maxV) {
			_curV = _maxV;
			_stage = 2;
		} else {
			_curV += _accel;
		}
	}
	else if (_stage == 2) {
		_curP += _curV;
		double rd = GetRemainingDistanceAbs();
		if (rd <= _brakeD) {
			_curP = _targetP - _brakeD;
			_stage = 3;
		}; 
	}
	else if (_stage == 3) {
		_curP += _curV + _decel / 2;
		
		
		double rd = GetRemainingDistanceAbs();
		if (rd < 1.0 && trunc(_curP) == trunc(_targetP)) {
			_stage = 0;
			_curP = _targetP;
		} else {
			if (_curV > _decel) {
				_curV -= _decel;
			}
			else {
				_decel = 0;
				_curV = _baseV;
			}
				
		}
	};
	if (_stage == 3 && ps != _stage) {
		double rd1 = GetRemainingDistanceAbs();
		double mt1;
		_decel = CalculateDeceleration(rd1, _curV, &mt1);
		printf("decel: %f, time: %f\n", _decel, mt1);
	};
};

void TrapezProfileGenerator::PrintState(char* buf, int len) {
	snprintf(buf, len, "T:%d, P:%f, V:%f, ST:%d, TOGO: %f", _t, GetCurrentPosition(), GetCurrentVelocity(), _stage, GetRemainingDistanceAbs());
}
