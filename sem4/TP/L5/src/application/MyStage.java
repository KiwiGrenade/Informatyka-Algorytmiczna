package application;

import javafx.scene.Group;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
/**
 * 
 * @author Grim Reaper
 * A class that places scene into display.
 * This class creates a Stage() object and add every private
 * parameter that it has to the stage.
 *
 */
public class MyStage extends Stage {
	final private Group root;
	final private MyScene scene;
	final private MyToolBar toolBar;
	final private Pane pane;
	public MyStage()
	{
		super();
		setTitle("Pain");
		setResizable(false);
		
		root = new Group();
		
		toolBar = new MyToolBar();
		
		pane = new MyPane(toolBar.getRectangleButton(), toolBar.getCircleButton(),
							toolBar.getTriangleButton(), toolBar.getMoveButton(),
							toolBar.getColorPicker());
		
		root.getChildren().add(pane);
		root.getChildren().add(toolBar);
		
		scene = new MyScene(root);
		
		setScene(scene);
		show();
	}
}
