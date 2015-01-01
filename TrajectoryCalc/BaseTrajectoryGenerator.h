/*
 * BaseTrajectoryGenerator.h
 *
 *  Created on: Dec 31, 2014
 *      Author: rg
 */

#ifndef BASETRAJECTORYGENERATOR_H_
#define BASETRAJECTORYGENERATOR_H_

class BaseTrajectoryGenerator {
protected:
	int _axes;
public:
	BaseTrajectoryGenerator();
	virtual ~BaseTrajectoryGenerator();

	void SetAxes(int axes);
	int GetAxes();
	virtual void SetCurrentPosition(int* pos);


};

#endif /* BASETRAJECTORYGENERATOR_H_ */
