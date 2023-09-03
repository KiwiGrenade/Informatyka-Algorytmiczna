package application;

import javafx.event.EventHandler;
import javafx.geometry.Point2D;
import javafx.scene.control.ColorPicker;
import javafx.scene.control.ToggleButton;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;

/**
 * 
 * @author Grim Reaper
 *	A pane is where we create the shapes. We add custom made event handlers
 *	to the pane so that we can create our shapes.
 */
public final class MyPane extends Pane
{
	/**@param start - a place on a pane where we press our mouse for the first time
	 * 
	 */
	/**@param middle - second click place, necessary for creating the triangle
	 * 
	 */
	/**@param end - same as middle
	 * 
	 */
	private Point2D start, middle, end;
	/**@param
	 * shape - implement polymorphism. We don't need to create different event handlers for different objects this way.
	 */
	private MyShape shape;
	/**
	 * @param clicks - number of clicks made while createing a triangle
	 */
	private int clicks;

	/**
	 * 
	 * @param rButton - check if we are creating rectangle
	 * @param cButton - check if we are creating circle
	 * @param tButton - check if we are creating triangle
	 * @param moveResize - check if we are moving a shape
	 * @param colorPicker - check what color the shape has to be
	 */
	public MyPane(final ToggleButton rButton, final ToggleButton cButton, final ToggleButton tButton,
					final ToggleButton moveResize, final ColorPicker colorPicker) 
	{
		super();
        setMinSize(1200, 800);
        clicks = 0;
        
		addEventHandler(MouseEvent.MOUSE_PRESSED, new EventHandler <MouseEvent>()
		{
			@Override
			public final void handle(final MouseEvent e)
			{
				//check if we are creating a rectangle or circle
				//they are press and dragg made
				if((rButton.isSelected() || (cButton.isSelected()))
						&& e.getButton().equals(MouseButton.PRIMARY))
				{
					start = new Point2D(e.getSceneX(), e.getSceneY());
				}
			}
		});
		
		addEventHandler(MouseEvent.MOUSE_RELEASED, new EventHandler <MouseEvent>()
		{
			@Override
			public final void handle(final MouseEvent e)
			{
				//if you are creating a rectangle and you clicked with left mouse button
				if(rButton.isSelected() && e.getButton().equals(MouseButton.PRIMARY))
				{
					end = new Point2D(e.getSceneX(),e.getSceneY());
					shape = new MyRectangle(start, end, moveResize, colorPicker.getValue());
			        getMyPane().getChildren().add(shape.getRectangle());
				}
				//if you are creating a circle and you clicked with left mouse button
				if (cButton.isSelected() && e.getButton().equals(MouseButton.PRIMARY))
				{
					end = new Point2D(e.getSceneX(),e.getSceneY());
					shape = new MyCircle(start, end, moveResize, colorPicker.getValue());
			        getMyPane().getChildren().add(shape.getCircle());
				}
			}
		});
		
		addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler <MouseEvent>()
		{
			@Override
			public final void handle(final MouseEvent e)
			{
				//make point of the triangle and create it on the 3rd click
				if (tButton.isSelected() && e.getButton().equals(MouseButton.PRIMARY))
				{
					switch(clicks)
					{
					case 0:
					{
						clicks++;
						start = new Point2D(e.getSceneX(), e.getSceneY());
						break;
					}
					case 1:
					{
						clicks++;
						middle = new Point2D(e.getSceneX(), e.getSceneY());
						break;
					}
					case 2:
					{
						clicks++;
						end = new Point2D(e.getSceneX(), e.getSceneY());
						shape = new MyTriangle(start, middle, end, moveResize, colorPicker.getValue());
						getMyPane().getChildren().add(shape.getTriangle());
						clicks = 0;
						break;
					}
					}
				}
				else
				{
					clicks = 0;
				}
			}
		});
		
	}
	private final MyPane getMyPane()
	{
		return this;
	}
}
