package application;

import javafx.geometry.Point2D;
import javafx.scene.control.ToggleButton;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

/**
 * 
 * @author Grim Reaper
 *	This class creates the Circle object from MyShape private field.
 *	It adds every custom event handler made by me, so the circle can move, resize,
 *	change color etc. The toggleButton is passed down so that is know
 *	if resize/move is selected.
 */

public final class MyCircle extends MyShape
{
	public MyCircle(Point2D start, Point2D end, ToggleButton moveResize, Color color)
	{
		setCircle(new Circle(start.getX(),start.getY(),start.distance(end), color));
		getCircle().setStroke(Color.BLACK);
        getCircle().setStrokeWidth(3);
        
        getCircle().setOnMouseClicked(new MyMouseEventHandler(moveResize));
        getCircle().setOnMouseDragged(new MyMouseEventHandler(moveResize));
        getCircle().setOnScroll(new MyScrollEventHandler(moveResize));
        getCircle().setOnContextMenuRequested(new MyContextMenuEventHandler(moveResize));
	}
}
