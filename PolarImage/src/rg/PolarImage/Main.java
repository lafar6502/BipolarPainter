package rg.PolarImage;

import java.awt.geom.*;
import java.awt.geom.Point2D.Double;
import java.awt.image.BufferedImage;
import java.io.Console;

import javax.imageio.*;

import java.io.*;

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		BipolarCoordinateCalculator pc = new BipolarCoordinateCalculator(1);
		
		Point2D[] arr = {
				new Point2D.Double(1, 1),
				new Point2D.Double(2, 2),
				new Point2D.Double(1, Math.sqrt(5)),
				new Point2D.Double(Math.sqrt(5), 1)
		};
		
		for(int i=0; i<arr.length; i++) {
			Point2D cart = pc.toCartesian(arr[i]);
			System.out.println("" + arr[i].toString() + " => " + cart.toString() + " => " + pc.toBipolar(cart).toString());
		}
		

	}
	
	public static void convertImageToBipolar(String path) throws IOException {
		File f = new File(path);
		BufferedImage img = ImageIO.read(f);
		convertImage(img);
	}
	
	//generate motion path
	//
	public static void convertImage(BufferedImage img) {
		
	}

}
