/*
 * IntSingleAxisTrapezGenerator.cpp
 *
 *  Created on: Dec 31, 2014
 *      Author: rg
 */

#include "IntSingleAxisTrapezGenerator.h"
#include <math.h>

IntSingleAxisTrapezGenerator::IntSingleAxisTrapezGenerator() {
	// TODO Auto-generated constructor stub
	_accel = _decel = 1;
	_maxV = 100;
	_curPos = 0;
	_curV = 0;
	_t = _motionT = _brakeT = 0;
	_stage = 0;
}

IntSingleAxisTrapezGenerator::~IntSingleAxisTrapezGenerator() {
	// TODO Auto-generated destructor stub
}

void IntSingleAxisTrapezGenerator::PrepareTrajectory() {
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
		_motionT = sqrt(dist * 2 / _accel);
		_brakeT = _motionT / 2;
	}

}

bool IntSingleAxisTrapezGenerator::MotionInProgress() {
	return _stage > 0;
}

void IntSingleAxisTrapezGenerator::NextStep() {
	long pv = _curV;
	if (_stage == 1) {
		_curV += _accel * _dir;
		if (_curV * _dir >= _maxV) {
			_curV = _maxV * _dir;
			_stage = 2;
		}
	};

	if (_stage == 3) {
		_curV -= _decel * _dir;
		//TODO crawl to destination if necessary and _currentV reaches 0
	};
	_curPos += (pv + _curV) / 2;
	_t++;
	if (_stage == 2 || _stage == 1) {
		if (_t >= _brakeT) {
			_stage = 3;
		}
	};
	if (_t >= _motionT) {
		_stage = 0;
		OnMotionCompleted();
	}
}

unsigned int IntSingleAxisTrapezGenerator::GetStepCount() {
	return _t;
}

unsigned int IntSingleAxisTrapezGenerator::GetMotionEndStep() {
	return _motionT;
}

long IntSingleAxisTrapezGenerator::GetCurrentPosition() {
	return _curPos;
}

void IntSingleAxisTrapezGenerator::SetCurrentPosition(long p) {
	_curPos = p;
}

long IntSingleAxisTrapezGenerator::GetTargetPosition() {
	return _targetPos;
}

void IntSingleAxisTrapezGenerator::SetTargetPosition(long p) {
	_targetPos = p;
}

int IntSingleAxisTrapezGenerator::GetCurrentVelocity() {
	return _curV;
}

void IntSingleAxisTrapezGenerator::SetCurrentVelocity(int v) {
	_curV = v;
}

int IntSingleAxisTrapezGenerator::GetMaxVelocity() {
	return _maxV;
}

void IntSingleAxisTrapezGenerator::SetMaxVelocity(int v) {
	_maxV = v;
}

int IntSingleAxisTrapezGenerator::GetAcceleration() {
	return _accel;
}

void IntSingleAxisTrapezGenerator::OnMotionCompleted() {

}

void IntSingleAxisTrapezGenerator::SetAcceleration(int a) {
	_accel = a;
	_decel = a;
}
