#ifndef _MultiAxisGearedProfileGenerator_h_included
#define _MultiAxisGearedProfileGenerator_h_included

#include "TrapezProfileGenerator.h"
#include "Vect.h"

class MultiAxisGearedProfileGenerator
{
	private:
		TrapezProfileGenerator _gen;
		Vect<double> _curPos;
		int _masterAxis;
		Vect<double> _ratios;
		
	public:
		MultiAxisGearedProfileGenerator(int axes) : _curPos(axes), _ratios(axes) {
			
		};
		
		bool StartMovingToDestination(Vect<double> dest, double maxAccel, double maxVelocity);
		
		bool InMotion() { 
			return _gen.InMotion();
		};
		
		Vect<double> GetCurrentPos();
		
		void NextStep() {
			_gen.NextStep();
		}
	
};

#endif
