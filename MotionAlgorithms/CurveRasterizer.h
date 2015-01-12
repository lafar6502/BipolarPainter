#ifndef _CURVE_RASTERIZER_H_INCLUDED_
#define _CURVE_RASTERIZER_H_INCLUDED_

/*
curve rasterization?

1. input function - parametric curve
f(t) => vect(x, y, z)
2. reverse kinematic function
vect => vect
3. rasterization

we assume no discontinuities in the reverse kinematics formula (or more advanced motion planning would be required)

*/

class CurveRasterizer
{
	private:
		ParametricCurve _curve;
		void*	_state;
		double _t;
		double _res; //resolution
	public:
		typedef void (*ParametricCurve)(double t, void* state, double* retVal);
		CurveRasterizer(ParametricCurve curve, void* state);
		
		double GetResolution() { 
			return _res;
		};
		
		void SetResolution(double res) {
			_res = res;
		}
		
		void NextStep();
		
		
};






#endif
