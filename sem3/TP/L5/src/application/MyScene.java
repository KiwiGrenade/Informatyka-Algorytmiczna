package application;

import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.paint.Color;

/**
 * 
 * @author Grim Reaper
 *Simply create a scene with the parameters that i want
 */

public final  class MyScene extends Scene {
	/**
	 * 
	 * @param root - a parent to a scene, it tells us how the nodes in a sene should be layed out
	 */
	public MyScene(Parent root)
	{
		super(root, 1200, 800, Color.YELLOW);
	}
}
