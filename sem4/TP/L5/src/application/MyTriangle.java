package application;

import javafx.geometry.Point2D;
import javafx.scene.control.ToggleButton;
import javafx.scene.paint.Color;
import javafx.scene.shape.Polygon;
/**
 * 
 * @author Grim Reaper
 *	This class creates the Triangle object from MyShape private field.
 *	It adds every custom event handler made by me, so the Triangle can move, resize,
 *	change color etc. The toggleButton is passed down so that is know
 *	if resize/move is selected.
 */

public final class MyTriangle extends MyShape
{
	public MyTriangle(Point2D A, Point2D B, Point2D C, ToggleButton moveResize, Color color)
	{
		setTriangle(new Polygon(A.getX(), A.getY(), B.getX(), B.getY(), C.getX(), C.getY()));
		getTriangle().setStrokeWidth(5);
		getTriangle().setStroke(Color.BLACK);
		getTriangle().setFill(color);
		
		getTriangle().setOnMouseClicked(new MyMouseEventHandler(moveResize));
		getTriangle().setOnMouseDragged(new MyMouseEventHandler(moveResize));
		getTriangle().setOnScroll(new MyScrollEventHandler(moveResize));
		getTriangle().setOnContextMenuRequested(new MyContextMenuEventHandler(moveResize));
	}

}
