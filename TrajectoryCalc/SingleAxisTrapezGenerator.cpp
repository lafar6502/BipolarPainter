/*
 * SingleAxisTrapezGenerator.cpp
 *
 *  Created on: Dec 31, 2014
 *      Author: rg
 */

#include "SingleAxisTrapezGenerator.h"
#include <math.h>

SingleAxisTrapezGenerator::SingleAxisTrapezGenerator() {
	// TODO Auto-generated constructor stub

}

SingleAxisTrapezGenerator::~SingleAxisTrapezGenerator() {
	// TODO Auto-generated destructor stub
}

void SingleAxisTrapezGenerator::SingleStep() {
	if (!_running) return;
	double dir = _targetP > _currentP ? 1.0 : -1.0;
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

bool SingleAxisTrapezGenerator::TrajectoryInProgress() {
	return _running;
}

void SingleAxisTrapezGenerator::PrepareTrajectory() {
	_currentP = _startP;
	_t = 0;
	double dir = _targetP > _startP ? 1.0 : -1.0;
	double dist = dir * (_targetP - _startP);

	double acct = _maxV / _accel;
	double dect = _maxV / _accel;

	double s1 = acct * _maxV / 2;
	double s2 = dect * _maxV / 2;
	if (s1 + s2 > dist) {
		//we don't reach _maxv

//		acc*t1^2 + dec * t2^2 = dist;
//		t1 * acc = t2 * dec; => t2 = t1 * acc / dec;
//		acc * t1^2 + (t1 * acc) ^ 2 / dec = dist;
//		acc t1^2 + acc^2/dec t1^2 = dist;
//		t1^2 * (acc + acc^2/dec) = dist;

		_motionT = (int) round(acct + dect);
		_brakingT = _motionT - (int)round(dect);
	} else {
		//we reach maxv
		_motionT = (int) round(acct + dect + (dist - s1 - s2) / _maxV);
		_brakingT = _motionT - (int) round(dect);
	}
	//1. check if we'll reach max v
	_running = true;
	_stage = 1;
}

double SingleAxisTrapezGenerator::GetCurrentPosition() {
	return _currentP;
}

double SingleAxisTrapezGenerator::GetCurrentVelocity() {
	return _currentV;
}

double SingleAxisTrapezGenerator::GetDestinationPosition() {
	return _targetP;
}

void SingleAxisTrapezGenerator::SetDestinationPosition(double p) {
	_targetP = p;
}

void SingleAxisTrapezGenerator::SetMaxVelocity(double d) {
	_maxV = d;
}

double SingleAxisTrapezGenerator::GetMaxVelocity() {
	return _maxV;
}

void SingleAxisTrapezGenerator::SetAcceleration(double d) {
	_accel = d;
}

void SingleAxisTrapezGenerator::SetCurrentPosition(double p) {
	//_currentP = p;
	_startP = p;
}

void SingleAxisTrapezGenerator::OnMotionCompleted() {
	_running = false;
}

double SingleAxisTrapezGenerator::GetAcceleration() {
	return _accel;
}
