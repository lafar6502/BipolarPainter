/*
 * IntSingleAxisTrapezGenerator.h
 *
 *  Created on: Dec 31, 2014
 *      Author: rg
 */

#ifndef INTSINGLEAXISTRAPEZGENERATOR_H_
#define INTSINGLEAXISTRAPEZGENERATOR_H_

class IntSingleAxisTrapezGenerator {
private:
	int _base;
	long _startPos;
	long _curPos;
	long _curV;
	long _maxV;
	long _accel;
	long _decel;
	long _targetPos;
	int _stage;
	unsigned int _t;
	unsigned int _motionT;
	unsigned int _brakeT;
	int _dir;
public:
	IntSingleAxisTrapezGenerator(int base);
	virtual ~IntSingleAxisTrapezGenerator();
	void PrepareTrajectory();
	bool MotionInProgress();
	void NextStep();
	unsigned int GetStepCount();
	unsigned int GetMotionEndStep();


};

#endif /* INTSINGLEAXISTRAPEZGENERATOR_H_ */
