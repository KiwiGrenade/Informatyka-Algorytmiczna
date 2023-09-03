package application;

import javafx.scene.shape.Circle;
import javafx.scene.shape.Polygon;
import javafx.scene.shape.Rectangle;
import javafx.scene.shape.Shape;

/**
 * 
 * @author Grim Reaper
 * 	This is the abstract class which we use for polymorphism. That way
 * we don't need to set up new evetn handlers for each specific figure, becasue
 * we just need to set them up for the type MyShape class.
 */
public abstract class MyShape extends Shape
{
	/**
	 * @param rectangle - a recgangle that we create for polymorphism
	 */
	private Rectangle rectangle;
	
	/**
	 * @param circle - a circle that we create for polymorphism
	 */
	private Circle circle;
	
	/**
	 * @param triangle - triangle that we create for polymorphism
	 */
	private Polygon triangle;
	/**
	 * 
	 * @return the rectangle inside MyShape object
	 */
	public final  Rectangle getRectangle()
	{
		return rectangle;
	}
	/**
	 * 
	 * @return the circle inside MyShape object
	 */
	public final Circle getCircle()
	{
		return circle;
	}
	/**
	 * 
	 * @return the polygon inside MyShape object
	 */
	public final Polygon getTriangle()
	{
		return triangle;
	}
	/**
	 * 
	 * @param rectangle - rectangle to be set as our rectangle 
	 */
	public void setRectangle(final Rectangle rectangle)
	{
		this.rectangle = rectangle;
	}
	/**
	 * 
	 * @param rectangle - circle to be set as our circle
	 */
	public void setCircle(final Circle circle)
	{
		this.circle = circle;
	}
	/**
	 * 
	 * @param polygon - polygon to be set as our polygon
	 */
	public void setTriangle(final Polygon triangle)
	{
		this.triangle = triangle;
	}
}
