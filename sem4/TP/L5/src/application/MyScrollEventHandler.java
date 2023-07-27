package application;

import javafx.event.EventHandler;
import javafx.scene.control.ToggleButton;
import javafx.scene.input.ScrollEvent;
import javafx.scene.shape.Shape;
/**
 * 
 * @author Grim Reaper
 *	Custom made event handler. It resizes the shpae on scroll activation.
 */

public final class MyScrollEventHandler implements EventHandler<ScrollEvent> {

	/**
	 * @param MoveResize - move/resize button so we can check if we are in move/resize mode
	 */
	private ToggleButton MoveResize;
	/**
	 * @param shape - a shape to be resized
	 */
	private Shape shape;
	
	public MyScrollEventHandler(final ToggleButton MoveResize)
	{
		this.MoveResize = MoveResize;
	}
	
	@Override
	public void handle(final ScrollEvent e)
	{
		//cast the source of event to a shape so that we can change it's scale
		shape = (Shape) e.getSource();
		if(e.getEventType().equals(ScrollEvent.SCROLL) && MoveResize.isSelected() == true)
		{
			//set the zoom factior
			double zoomFactor = 1.05;
			final double deltaY = e.getDeltaY();
			if(deltaY < 0)
			{
				zoomFactor = 2 - zoomFactor;
			}
			shape.setScaleX(shape.getScaleX() * zoomFactor);
			shape.setScaleY(shape.getScaleY() * zoomFactor);
		}
	}

}
