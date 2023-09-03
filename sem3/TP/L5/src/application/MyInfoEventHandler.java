package application;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;
import javafx.stage.Stage;

/**
 * 
 * @author Grim Reaper
 *	This class adds an event handler to the button "info". Then a new window pops out with a message.
 */
public final class MyInfoEventHandler implements EventHandler<ActionEvent>
{
	@Override
	public final void handle(final ActionEvent e) 
	{
		final String str = "Nazwa: Pain(t)\n"
					+"Autor: Jakub Jaskow\n"
					+"Przeznaczenie: Cierpienie studenta.";
		final Text text = new Text(str);
		text.setX(50);
		text.setY(50);
		final Group root = new Group(text);
		final Stage stage = new Stage();
		stage.setTitle("Info");
		final Scene scene = new Scene(root, 420, 420, Color.PINK);
		stage.setScene(scene);
		stage.show();
		stage.setResizable(false);
	}
}
