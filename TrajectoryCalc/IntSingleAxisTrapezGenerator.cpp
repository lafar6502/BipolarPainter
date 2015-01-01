/*
 * IntSingleAxisTrapezGenerator.cpp
 *
 *  Created on: Dec 31, 2014
 *      Author: rg
 */

#include "IntSingleAxisTrapezGenerator.h"
#include <math.h>

IntSingleAxisTrapezGenerator::IntSingleAxisTrapezGenerator(int base) {
	// TODO Auto-generated constructor stub

}

IntSingleAxisTrapezGenerator::~IntSingleAxisTrapezGenerator() {
	// TODO Auto-generated destructor stub
}

void IntSingleAxisTrapezGenerator::PrepareTrajectory() {
	_t = 0;
	_dir = _targetPos > _startPos ? 1 : -1;
	_curPos = _startPos;
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


	double pv = _currentV; //prev velocity
	if (_stage == 1) {
		_currentV += _accel * dir;
		if (dir * _currentV >= _maxV) {
			_currentV = _maxV * dir;
			_stage = 2;
		}
	};
	if (_stage == 3) {
		_currentV -= _accel * dir;
		//TODO crawl to destination if necessary and _currentV reaches 0
	};
	_currentP += (pv + _currentV) / 2.0;
	_t++;
	if (_stage == 2 || _stage == 1) {

		if (_t >= _brakingT) {
			_stage = 3;
		}
	};
	if (_t >= _motionT) {
		_stage = 0;
		OnMotionCompleted();
	}
}

unsigned int IntSingleAxisTrapezGenerator::GetStepCount() {
}

unsigned int IntSingleAxisTrapezGenerator::GetMotionEndStep() {
}
