package rg.MotionCalc;

//first attempt - lets implement this with floating point
//correctly, then we'll think about integer arithmetic
public class TrapezoidPath 
{
	private double _curPos;
	private double _curV;
	private double _maxV;
	private double _maxAccel;
	private double _curAccel;
	private double _targetPos;
	private double _startPos;
	private double _baseV;
	private int _stage;
	private int _dir;
	private int _decelT;
	private int _t;
	
	public TrapezoidPath()
	{
		_dir = 1;
		_curPos = _targetPos = _startPos = 0;
		_curV = _maxV = 0;
		_maxAccel = _curAccel = 0;
		_stage = 0;
		_t = 0;
	}
	
	public void PreparePath()
	{
		//prep basev.
		_curV = _baseV;
		_curAccel = _maxAccel;
		_startPos = _curPos;
		_t = 0;
		_stage = 1;
		
	}
	
	public  void NextStep()
	{
		if (_stage == 0) {
			return;
		};
		
		_curPos += _curV + _curAccel * 0.5; //
		
		if (_stage == 1) {
			if (_curV >= _maxV) {
				_curAccel = 0;
				_curV = _maxV;
				_stage = 2;
			}
		};
		
		if (_stage == 2) {
			
		}
		
		if (_stage == 3) {
			
		}
		
		
		
		_t++;
	}
	
	public void setAcceleration(double acc) {
		_maxAccel = acc;
	}
	
	
	/*
	
	public class ProfileData
	{
		double startPos;
		double endPos;
		int totalSteps;
		int stage2Step;
		int stage3Step;
		double startV;
		double endV;
		double decel;
		double accel;
	}
	
	
	public ProfileData calculateTrapezoidalProfile(double targetPos, double startPos, double maxV, double maxAccel, double startV, double endV) {
		ProfileData pd = new ProfileData();
		
		
		return pd;
	}
	*/
	
	
}
