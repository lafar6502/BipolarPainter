#ifndef _MULTIAXISTRAPEZPROFILEGENERATOR_H_INCLUDED
#define _MULTIAXISTRAPEZPROFILEGENERATOR_H_INCLUDED

#include "Vect.h"

class MultiAxisTrapezProfileGenerator 
{
	private:
		Vect<double> _curP;
		Vect<double> _targetP;
		Vect<double> _curV;
		Vect<double> _maxAccel;
		Vect<double> _maxV;
		Vect<double> _curAccel;
		Vect<double> _baseV;
		
		int _t;
		int _stage;
	public:
		MultiAxisTrapezProfileGenerator();	
		double GetCurrentPosition() { return _curP; }
		void SetCurrentPosition(double p) { 
			_curP = p;
		};
		void SetTargetPosition(double p) { 
			_targetP = p;
		};
		double GetTargetPosition() { 
			return _targetP;
		};
		
		
		double GetCurrentVelocity() { 
			return _curV;
		};

		void SetCurrentVelocity(double value) {
			_curV = value;
		};
		double GetMaxVelocity() { 
			return _maxV;
		};
		void SetMaxVelocity(double value) {
			_maxV = value;
		};
		double GetBaseVelocity() { 
			return _baseV;
		};
		void SetBaseVelocity(double value) {
			_baseV = value;
		};
		double GetAcceleration() { 
			return _accel;
		};
		void SetAcceleration(double v) {
			_accel = v;
			_baseV = _accel / 20;
		};
		
		bool InMotion() {
			return _stage != 0;
		};
		
		double GetRemainingDistanceAbs() {
			double v = _targetP - _curP;
			return v < 0 ? -v : v;
		};
		
		double CalculateDecelerationDistance(double v, double decel, double* time);
		double CalculateDeceleration(double distance, double v, double* t);
		bool PrepareMotion();
		void NextStep();
		virtual void PrintState(char*buf, int len);
		
};

#endif
