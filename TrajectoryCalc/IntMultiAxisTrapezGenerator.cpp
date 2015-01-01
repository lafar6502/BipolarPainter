/*
 * IntMultiAxisTrapezGenerator.cpp
 *
 *  Created on: Dec 31, 2014
 *      Author: rg
 */

#include "IntMultiAxisTrapezGenerator.h"
#include <math.h>
#include <stdio.h>

IntMultiAxisTrapezGenerator::IntMultiAxisTrapezGenerator() {
	// TODO Auto-generated constructor stub
	_accel = _decel = 1;
	_maxV = 100;
	_curPos = 0;
	_curV = 0;
	_t = _motionT = _brakeT = 0;
	_stage = 0;
}

IntMultiAxisTrapezGenerator::~IntMultiAxisTrapezGenerator() {
	// TODO Auto-generated destructor stub
}

void IntMultiAxisTrapezGenerator::PrepareTrajectory() {
	_t = 0;
	_startPos = _curPos;
	_dir = _targetPos > _startPos ? 1 : -1;
	_stage = 1;
	long dist = _dir * (_targetPos - _curPos);
	long acct = _maxV / _accel;
	long dect = _maxV / _accel;

	long s1 = acct * _maxV / 2;
	long s2 = dect * _maxV / 2;

	if (s1 + s2 < dist) {
		_motionT = acct + dect + (dist - s1 - s2) / _maxV;
		_brakeT = _motionT - dect;
	} else {
		//accel = decel, mkay?
		//dist = accel * t^2 / 2;=> t = sqrt(2*dist/accel)
		_brakeT = sqrt(dist / _accel);
		_motionT = _brakeT + _brakeT;
	}

}

bool IntMultiAxisTrapezGenerator::MotionInProgress() {
	return _stage > 0;
}

void IntMultiAxisTrapezGenerator::NextStep() {
	long pv = _curV;
	if (_stage == 1) {
		_curV += _accel * _dir;
		if (_curV * _dir >= _maxV) {
			_curV = _maxV * _dir;
			_stage = 2;
		}
	};

	if (_stage == 3) {
		int remd = (_targetPos - _curPos) * 2;
		int remt = _motionT - _t;
		int cdist = _curV * remt;
		int dif = remt == 0 ? 0 : (remd - cdist) / (remt * 2);
		//printf("dif: %d, rem: %d, cdist: %d\n", dif, remd, cdist);
		_curV -= (_decel - dif) * _dir;
	};
	_curPos += (pv + _curV) / 2;
	_t++;
	if (_stage == 2 || _stage == 1) {
		if (_t >= _brakeT) {
			_stage = 3;

		}
	};

	if (_t > _motionT) {
		_stage = 0;
		OnMotionCompleted();
	}
}

unsigned int IntMultiAxisTrapezGenerator::GetStepCount() {
	return _t;
}

unsigned int IntMultiAxisTrapezGenerator::GetMotionEndStep() {
	return _motionT;
}

long IntMultiAxisTrapezGenerator::GetCurrentPosition() {
	return _curPos;
}

void IntMultiAxisTrapezGenerator::SetCurrentPosition(long p) {
	_curPos = p;
}

long IntMultiAxisTrapezGenerator::GetTargetPosition() {
	return _targetPos;
}

void IntMultiAxisTrapezGenerator::SetTargetPosition(long p) {
	_targetPos = p;
}

int IntMultiAxisTrapezGenerator::GetCurrentVelocity() {
	return _curV;
}

void IntMultiAxisTrapezGenerator::SetCurrentVelocity(int v) {
	_curV = v;
}

int IntMultiAxisTrapezGenerator::GetMaxVelocity() {
	return _maxV;
}

void IntMultiAxisTrapezGenerator::SetMaxVelocity(int v) {
	_maxV = v;
}

int IntMultiAxisTrapezGenerator::GetAcceleration() {
	return _accel;
}

void IntMultiAxisTrapezGenerator::OnMotionCompleted() {

}

void IntMultiAxisTrapezGenerator::SetAcceleration(int a) {
	_accel = a;
	_decel = a;
}
