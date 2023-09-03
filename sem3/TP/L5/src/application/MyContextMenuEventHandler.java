package application;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.ColorPicker;
import javafx.scene.control.ContextMenu;
import javafx.scene.control.MenuItem;
import javafx.scene.control.Slider;
import javafx.scene.control.ToggleButton;
import javafx.scene.input.ContextMenuEvent;
import javafx.scene.shape.Shape;
import javafx.scene.transform.Rotate;

/**
 * 
 * @author Grim Reaper
 *	This is the event handler that creates ContextMenu with which we can rotate the shape
 *	and change it's color. The constructor creates the Slide, ColorPicker. Then it adds
 *	the event handler to the slider, so taht we can rotate the shape.
 */
public final class MyContextMenuEventHandler implements EventHandler <ContextMenuEvent>
{
	private Shape shape;
	final private ContextMenu contextMenu;
	final private ColorPicker colorPicker;
	final private Slider slider;
	final private MenuItem menuColor, menuSlider;
	final private Rotate rotation;
	final private ToggleButton MoveResize;
	/**
	 * 
	 * @param MoveResize - button to move a figure
	 */
	public MyContextMenuEventHandler(final ToggleButton MoveResize)
	{
		this.MoveResize = MoveResize;
		contextMenu = new ContextMenu();
		
        colorPicker = new ColorPicker();
        slider = new Slider(0,360, 0);
        
        menuColor = new MenuItem(null, colorPicker);
        menuSlider = new MenuItem(null, slider);
		rotation = new Rotate();
        
        slider.setShowTickMarks(true);
        slider.setShowTickLabels(true);
        
        //set angle on slider action
		slider.valueProperty().addListener(new ChangeListener <Number> ()
		{
			@Override
			public void changed(final ObservableValue<? extends Number> Observable, final Number oldValue, final Number newValue) {
				// TODO Auto-generated method stub
				rotation.setAngle((double) newValue);
			}});
		
		contextMenu.getItems().addAll(menuColor, menuSlider);
	}
	
	@Override
	/**
	 *@param ContextMenuEvent - event
	 *
	 */
	public final void handle (final ContextMenuEvent e) 
	{
		if(MoveResize.isSelected() && e.getEventType().equals(ContextMenuEvent.CONTEXT_MENU_REQUESTED))
		{
			shape = (Shape) e.getSource();
			contextMenu.show(shape, e.getScreenX(), e.getScreenY());
			rotation.setPivotX(shape.getBoundsInLocal().getCenterX());
			rotation.setPivotY(shape.getBoundsInLocal().getCenterY());
			
			//change shape color on selecting color
			menuColor.setOnAction(new EventHandler <ActionEvent>()
			{
				@Override
				public void handle(final ActionEvent event) 
				{
					shape.setFill(colorPicker.getValue());
				}
			});
			shape.getTransforms().add(rotation);
		}
	}
}
