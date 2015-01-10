#ifndef _TRAPEZPROFILEGENERATOR_H_INCLUDED
#define _TRAPEZPROFILEGENERATOR_H_INCLUDED

#include "ProfileGenerator.h"

class TrapezProfileGenerator : public ProfileGenerator
{
	private:
		double _curP;
		double _targetP;
		double _startP;
		double _curV;
		double _maxV;
		double _accel;
		double _curAccel;
		double _baseV;
		double _brakeD; //where to start braking
		int _t;
		int _stage;
	public:
		TrapezProfileGenerator();	
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
