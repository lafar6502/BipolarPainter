package rg.PolarImage;

import java.io.*;

import javax.imageio.*;

import java.awt.geom.*;
import java.awt.geom.*;
import java.awt.geom.Point2D.Double;
import java.util.logging.*;
//bipolar bitmap painter
//generates a motion sequence for bipolar painting
public class BitmapPainter {
	protected Logger log = LogManager.getLogManager().getLogger("BitmapPainter");
	
	protected double _bpWidth = 100;
	
	public static Point2D p(double x, double y) {
		return new Point2D.Double(x, y);
	}
	
	//create snake path through a rectangle
	public void polarTraverse(Rectangle2D cartesianRect, boolean fromLeftPole) {
		BipolarCoordinateCalculator bc = new BipolarCoordinateCalculator(_bpWidth);
		//1. starting corner
		double y = cartesianRect.getMinY();
		double x = fromLeftPole ? cartesianRect.getMinX() : cartesianRect.getMaxX();
		//log.info("start point: " + x + ", " + y);
		Point2D start = bc.toBipolar(new Point2D.Double(x, y));
		Point2D cur = start;
		
		double r1 = start.getX(), r2 = start.getY();
		boolean down = true;
		while(true) {
			Point2D imgpt = bc.toCartesian(cur);
			if (cartesianRect.contains(imgpt)) {
				
				if (fromLeftPole) {
					cur = p(cur.getX(), cur.getY() + (down ? 1 : -1));
				} else {
					cur = p(cur.getX() + (down ? 1 : -1), cur.getY());
				}
			} else {
				down = !down;
				//increment row
				if (fromLeftPole) {
					cur = p(cur.getX() + 1, cur.getY());
				} else {
					cur = p(cur.getX(), cur.getY() + 1);
				}
			}
		}
	}
	
	
}
