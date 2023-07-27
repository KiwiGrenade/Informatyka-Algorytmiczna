package application;

import javafx.event.EventHandler;
import javafx.scene.control.ToggleButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.shape.Shape;

/**
 * 
 * @author Grim Reaper
 *
 *This is the move event handler class. Whenever we move a shape, this guy is called. It adds custom made event handlers to a shape
 *so that the shape can move freely in our scene.
 */
public final class MyMouseEventHandler implements EventHandler<MouseEvent>
{
	/**
	 * @param shape - a shape is an abstract parent class of other classes such as Rectangle and Circle
	 * It's the reason why we don't need to write new event handlers for each object separetly
	 * @param 
	 
	 */
	private Shape shape;
	/**@param x,y - this is a coordinate x and y
	 */
	private double x,y;
	private ToggleButton MoveResize;
	
	public MyMouseEventHandler(final ToggleButton MoveResize)
	{
		this.MoveResize = MoveResize;
	}

	@Override
	public final void handle(final MouseEvent e)
	{
		shape = (Shape) e.getSource();
		if(e.getEventType().equals(MouseEvent.MOUSE_CLICKED) && MoveResize.isSelected() == true
				&& e.isPrimaryButtonDown())
		{
			x = e.getSceneX();
			y = e.getSceneY();
		}
		if(e.getEventType().equals(MouseEvent.MOUSE_DRAGGED) && MoveResize.isSelected() == true
				&& e.isPrimaryButtonDown())
		{
			move(e);
		}
	}
	private final void move (final MouseEvent e)
	{
		/**
		 * @param dX - distance that the shape travels in x
		 * @param dY - distance that the shape travels in y
		 */
		final double dX = e.getSceneX() - x - shape.getBoundsInLocal().getCenterX();
		final double dY = e.getSceneY() - y - shape.getBoundsInLocal().getCenterY();
		shape.setLayoutX(shape.getLayoutX() + dX);
		shape.setLayoutY(shape.getLayoutY() + dY);
		x += dX;
		y += dY;
	}

}
