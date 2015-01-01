/*
 * IntMultiAxisTrapezGenerator.h
 *
 *  Created on: Dec 31, 2014
 *      Author: rg
 */

#ifndef INTMULTIAXISTRAPEZGENERATOR_H_
#define INTMULTIAXISTRAPEZGENERATOR_H_

class IntMultiAxisTrapezGenerator {
private:
	int _base;
	long _startPos;
	long _curPos;
	int _curV;
	int _maxV;
	int _accel;
	int _decel;
	long _targetPos;
	int _stage;
	unsigned int _t;
	unsigned int _motionT;
	unsigned int _brakeT;
	int _dir;
	void OnMotionCompleted();
public:
	IntMultiAxisTrapezGenerator();
	virtual ~IntMultiAxisTrapezGenerator();
	void PrepareTrajectory();
	bool MotionInProgress();
	void NextStep();
	unsigned int GetStepCount();
	unsigned int GetMotionEndStep();
	long GetCurrentPosition();
	void SetCurrentPosition(long p);
	long GetTargetPosition();
	void SetTargetPosition(long p);
	int GetCurrentVelocity();
	void SetCurrentVelocity(int v);
	int GetMaxVelocity();
	void SetMaxVelocity(int v);
	int GetAcceleration();
	void SetAcceleration(int a);


};

#endif
