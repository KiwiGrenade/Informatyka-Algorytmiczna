package application;
	
import javafx.application.Application;
import javafx.stage.Stage;

/**
 * 
 * @author GrimReaper
 *
 *
 */
public class Main extends Application
{
	/**
	 * 
	 * @param args Standard main argument.
	 */
	public static void main(String[] args)
	{
		launch(args);
	}
	@Override
	public void start(Stage stage)
	{
		new MyStage();
	}
}
