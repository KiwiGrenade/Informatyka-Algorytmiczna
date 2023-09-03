package application;

import javafx.geometry.Point2D;
import javafx.scene.control.ToggleButton;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

/**
 * 
 * @author Grim Reaper
 *	This class creates the rectangle object from MyShape private field.
 *	It adds every custom event handler made by me, so the rectangle can move, resize,
 *	change color etc. The toggleButton is passed down so that is know
 *	if resize/move is selected.
 */

public final class MyRectangle extends MyShape
{
	
	public MyRectangle(final Point2D start, final Point2D end, final ToggleButton moveResize, final Color color)
	{
		final double minX = lesserPoint(start.getX(),end.getX());
		final double minY = lesserPoint(start.getY(),end.getY());
		setRectangle(new Rectangle());
		getRectangle().setX(minX);
		getRectangle().setY(minY);

		getRectangle().setWidth(Math.abs(start.getX() - end.getX()));
		getRectangle().setHeight(Math.abs(start.getY() - end.getY()));
		getRectangle().setStrokeWidth(5);
		getRectangle().setStroke(Color.BLACK);
		getRectangle().setFill(color);
		
		//moving
		getRectangle().setOnMouseClicked(new MyMouseEventHandler(moveResize));
		getRectangle().setOnMouseDragged(new MyMouseEventHandler(moveResize));
		//resizing
		getRectangle().setOnScroll(new MyScrollEventHandler(moveResize));
		//context menu - scroll and colorpicker
		getRectangle().setOnContextMenuRequested(new MyContextMenuEventHandler(moveResize));
	}

	/**
	 * 
	 * @param arg0 - point ax
	 * @param arg1 - point bx
	 * @return - return the point that is closer to 0x
	 */
	//see if the start point or the end point is closer to upper left corner
	private final double lesserPoint(double arg0, double arg1)
	{
		if (arg0 < arg1)
		{
			return arg0;
		}
		return arg1;
	}
}
