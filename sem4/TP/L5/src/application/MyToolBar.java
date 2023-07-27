package application;

import javafx.scene.control.Button;
import javafx.scene.control.ColorPicker;
import javafx.scene.control.ToggleButton;
import javafx.scene.control.ToggleGroup;
import javafx.scene.control.ToolBar;

/**
 * 
 * @author Grim Reaper
 * This class build us a tool bar at the top of the screen where all the important buttons lay.
 */

public final class MyToolBar extends ToolBar
{
	/**
	 * @param button1 - create rectangle button
	 * @param button2 - create circle button
	 * @param button3 - create triagnle button
	 * @param button4 - move/resize button
	 */
	final private ToggleButton button1, button2, button3, button4;
	/**
	 * @param infoButton - button that displays the information window
	 * @param instrutctionButton - button to display the instruction window
	 */
	final private Button infoButton, instructionButton;
	/**
	 * @param group - a ToggleGroup, when you add buttons to it and select one of them
	 * all the others deselect automatically
	 */
	final private ToggleGroup group;
	/**@param colorpicker - a color picker to select a color
	 */
	final private ColorPicker colorPicker;
	
	public MyToolBar()
	{
		//create the toolbar
		super();
		//add all the components to it
		button1 = new ToggleButton("Rectangle");
		button2 = new ToggleButton("Circle");
		button3 = new ToggleButton("Triangle");
		button4 = new ToggleButton("Move/Resize");
		infoButton = new Button("Info");
		instructionButton = new Button("Instruction");
		
		//set popup info on action
		infoButton.setOnAction(new MyInfoEventHandler());
		
		//set popup instruction on action
		instructionButton.setOnAction(new MyInstructionEventHandler());
		
		group = new ToggleGroup();
		
		//add all the buttons to the group
		button1.setToggleGroup(group);
		button2.setToggleGroup(group);
		button3.setToggleGroup(group);
		button4.setToggleGroup(group);
		
		colorPicker = new ColorPicker();
		
		//add everything to the toolbar
		getItems().add(colorPicker);
		getItems().add(button1);
		getItems().add(button2);
		getItems().add(button3);
		getItems().add(button4);
		getItems().add(infoButton);
		getItems().add(instructionButton);
	}
	/**@return rectangle button*/
	public final ToggleButton getRectangleButton()
	{
		return button1;
	}
	/**@return circle button*/
	public final ToggleButton getCircleButton()
	{
		return button2;
	}
	/**@return triangle button*/
	public final ToggleButton getTriangleButton()
	{
		return button3;
	}
	/**@return move/resize button*/
	public final ToggleButton getMoveButton()
	{
		return button4;
	}
	/**@return colorPicker*/
	public final ColorPicker getColorPicker()
	{
		return colorPicker;
	}
	/**@return getInfoButton*/
	public final Button getInfoButton()
	{
		return infoButton;
	}
	/**@return instructionButton*/
	public final Button getInstructionButton()
	{
		return instructionButton;
	}
}
