package rg.PolarImage;

import java.awt.geom.*;
import java.awt.geom.Point2D.Double;

public class BipolarCoordinateCalculator {
	
	private double _a;
	/**
	 * @param a - a is the 'focal' distance, that is we assume
	 * bipolar foci are at (-a, 0) and (0, a)
	 */
	public BipolarCoordinateCalculator(double a) {
		_a = a;
	}
	
	public Point2D toCartesian(Point2D polar) { 
		
		double r1 = polar.getY();
		double r2 = polar.getX();
		r1 *= r1;
		r2 *= r2;
		//x = \frac{r_2^2-r_1^2}{4a}
		double x = (r2 - r1) / 4 * _a;
		//y = \pm \frac{1}{4a}\sqrt{16a^2r_2^2-(r_2^2-r_1^2+4a^2)^2}
		double a2 = _a * _a;
		double t0 = r2 - r1 + 4 * a2;
		double t1 = 16 * a2 * r2 - t0 * t0;
		double y = Math.sqrt(Math.abs(t1)) / (4 * _a);
		if (t1 < 0) y = -y;
		return new Point2D.Double(x, y);
	}
	
	public Point2D toBipolar(Point2D cartesian) {
		//r1: distance from (-a, 0) =>
		double x1 = cartesian.getX() + _a;
		double y2 = cartesian.getY();
		y2 *= y2;
		double r1 = Math.sqrt(x1 * x1 + y2);
		//r2: distance from a, 0
		x1 = cartesian.getX() - _a;
		double r2 = Math.sqrt(x1 * x1 + y2);
		return new Point2D.Double(r1, r2);
	}

}
