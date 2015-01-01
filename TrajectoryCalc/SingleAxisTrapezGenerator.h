/*
 * SingleAxisTrapezGenerator.h
 *
 *  Created on: Dec 31, 2014
 *      Author: rg
 */

#ifndef SINGLEAXISTRAPEZGENERATOR_H_
#define SINGLEAXISTRAPEZGENERATOR_H_

class SingleAxisTrapezGenerator {
protected:
	//0 - not moving, 1, 2, 3 - trapezoidal stages
	int _stage;
	unsigned int _t;
	double _accel;
	double _maxV;
	double _currentV;
	double _currentP;
	double _targetP;
	double _startP;
	//braking position
	unsigned int _brakingT;
	unsigned int _motionT;

	//trajectory is in progress
	bool _running;

	void OnMotionCompleted();
public:
	SingleAxisTrapezGenerator();
	virtual ~SingleAxisTrapezGenerator();
	//do a single step
	virtual void SingleStep();
	// check if motion is in progress (trajectory hasnt completed yet)
	virtual bool TrajectoryInProgress();
	/// prepare for running the trajectory
	void PrepareTrajectory();

	double GetCurrentPosition();
	void SetCurrentPosition(double p);
	double GetCurrentVelocity();
	double GetDestinationPosition();
	void SetDestinationPosition(double p);
	void SetMaxVelocity(double d);
	double GetMaxVelocity();
	void SetAcceleration(double d);
	double GetAcceleration();
};

#endif /* SINGLEAXISTRAPEZGENERATOR_H_ */
