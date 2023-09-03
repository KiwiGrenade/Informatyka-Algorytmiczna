package application;
	
import java.util.ArrayList;

import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
//update
///Main class used to create GUI and threads.
public class Main extends Application
{
	/**
	 * @param p - probability
	 */
	private static double p;
	/**
	 * @param m - number of columns
	 */
	private static int m;
	/**
	 * @param n - number of rows
	 */
	private static int n;
	/**
	 * @param k - variable k
	 */
	private static long k;
	//update git
	@Override
	public void start(Stage primaryStage) throws InterruptedException
	{
		/**
		 * Starting program. This method creates and sets the whole GUI
		 * and is responsible for creating and starting all the threads.
		 */
		/**
		 * @param stage - standard stage
		 */
		Stage stage = new Stage();
		/**
		 * @param grid - GridPane responsible for placing rectangles in a scene
		 */
		GridPane grid = new GridPane();
		stage.setResizable(false);
		stage.setOnCloseRequest(event ->{
			javafx.application.Platform.exit();
		});
		/**
		 * @param scene - standard scene 1200 x 800
		 */
		Scene scene = new Scene(grid, 1200, 800);
		
		//create the 2d array list of MyThread
		/**
		 * @param torus - 2D ArrayList of objects MyThread
		 */
		ArrayList <ArrayList<MyThread>> torus = new ArrayList<ArrayList<MyThread>>();
		for (int col = 0; col < m; col++)
		{
			torus.add(new ArrayList<MyThread>());
			for (int row = 0; row < n; row++)
			{
				MyThread myThread = new MyThread((scene.getWidth() / m), (scene.getHeight() / n), p, k, col, row);
				///add the thread to 2d arraylist
				torus.get(col).add(myThread);
				///add the rectangle from MyThread to the grid
				grid.add(torus.get(col).get(row).getRectangle(), col, row);
			}
		}
		
		Object synchronizer = new Object();
		
		///pass the torus to MyThread class
		///and pass the synchronizer
		//don't set static objects in another class like that
		new MyThread().setArrayList(torus);
		new MyThread().setSynchObject(synchronizer);
		new MyThread().setNM(n, m);
		
		//start all of the threads
		for (int col = 0; col < m; col++)
		{
			for (int row = 0; row < n; row++)
			{
				torus.get(col).get(row).start();
			}
		}
		
		//set the scene and show the window
		stage.setScene(scene);
		stage.show();
	}
	
	public static void main(String[] args)
	{
		/**
		 * Main method
		 */
		
		p = Double.parseDouble(args[0]);
		m = Integer.parseInt(args[1]);
		n = Integer.parseInt(args[2]);
		k = Long.parseLong(args[3]);
		
		launch(args);
	}
}
