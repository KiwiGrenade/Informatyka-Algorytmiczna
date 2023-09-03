package application;

import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.Semaphore;

import javafx.application.Platform;
import javafx.event.EventHandler;
import javafx.scene.input.MouseEvent;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;


/**
 * \class MyThread
 * \brief Custom Thread class responsible for firing threads.
 * \details This class is responsible for creation and functionality of MyThread objects.
 * It uses synchronization and semaphores to get rid of deadlocks.
 */
public final class MyThread extends Thread
{
	/**
	 * @param threadSuspended - informs wether thread is suspended.
	 */
	private volatile boolean threadSuspended;
	/**
	 * @param rectangle - rectangle shown in GUI.
	 */
	private Rectangle rectangle;
	/**
	 * @param updater - updater object for multithreading in JavaFX.
	 */
	private Runnable updater;
	/**
	 * @param rng - random number generator.
	 */
	private static final Random rng = new Random();
	/**
	 * @param probability - probability of changing color of the rectangle for another randomly generated color.
	 */
	private double probability;
	/**
	 * @param k - variable responsible for changing the random generated time to wait.
	 */
	private long k;
	/**
	 * @param x,y - coordinates of placement of the thread in a 2D Arraylist of MyThreads.
	 */
	private int x, y;
	/**
	 * @param checker - 2D ArrayList of MyThreads
	 */
	private static ArrayList <ArrayList<MyThread>> checker;
	/**
	 * @param thisN, thisM - dimensions of checker
	 */
	private static int thisN, thisM;
	
	/**
	 * \brief Constructor of MyThread class.
	 * \details Create the thread. Set threadSuspended to false.
	 * Set the probability, coordinates. Initialize the semaphore, rng and rectangle.
	 * Add and event handler to rectangle.
	 * @param w - width of the rectangle.
	 * @param h - height of the rectangle.
	 * @param p - probability.
	 * @param k - variable of time.
	 * @param x - coordinate x of place in ArrayList where the thread resides.
	 * @param y - coordinate x of place in ArrayList where the thread resides.
	 */
	private static Object myObject;
	public MyThread(double w, double h, double p, long k, int x, int y)
	{
		super();
		threadSuspended = false;
		probability = p;
		this.k = k;
		this.x = x;
		this.y = y;
		rectangle = new Rectangle( w, h, Color.rgb(rng.nextInt(256), rng.nextInt(256), rng.nextInt(256)));
		rectangle.setOnMouseClicked(e->
		{
			synchronized(this)
			{
				threadSuspended = !threadSuspended;
				if(threadSuspended == false)
				{
					notify();
				}
			}
		});
	}
	/**
	 * brief Constructor for setting 2D ArrayList, thisN, thisM.
	 */
	public MyThread() {}
	
	/**
	 * Method responsible for running thre thread.
	 * Create updater variable so that you can later do Platform.runLater(updater).
	 */
	//update git
	@Override
	public final void run()
	{
		
		updater = new Runnable()
		{
			/**
			 * Method necesarry to execute runLater method
			 * 
			 */
			@Override
			public final void run() 
			{
				if(rng.nextDouble() <= probability && threadSuspended == false)
				{
					changeColorToRandom();
				}
				else if(threadSuspended == false)
				{
					changeColorToAverage();
				}
			}
		};
		
		while(true)
		{
			while(threadSuspended == true)
			{
				//synchronize loop with myThread and suspend function
				synchronized(this)
				{
					try 
					{
						wait();
					} 
					catch (InterruptedException e) 
					{
						e.printStackTrace();
					}
				}
			}
			try 
			{
				sleep(getRandomTime());
			} 
			catch (InterruptedException e) 
			{
				e.printStackTrace();
			}
			Platform.runLater(updater);
		}
	}
	
	/**
	 * \brief Change rectagnle color to other random color.
	 */
	private final void changeColorToRandom()
	{
		synchronized(myObject)
		{
			rectangle.setFill(Color.rgb(rng.nextInt(256), rng.nextInt(256), rng.nextInt(256)));
		}
	}
	
	/**
	 * \brief Random time generator.
	 * @return random time  (long).
	 */
	private final long getRandomTime()
	{
		return (long)((rng.nextDouble() + 0.5) * k);
	}

	/*
	 * \brief Change rectangle color to average.
	 */
	private final synchronized void changeColorToAverage()
	{
		synchronized(myObject)
		{
			/**
			 * @param activeCounter - counter of active threads.
			 */
			int activeCounter = 0;
			/**
			 * @param *bucket - store values of red from neigbours colors.
			 */
			double redBucket = 0, greenBucket = 0, blueBucket = 0;
			ArrayList <MyThread> threads = getNeighbours();
			for (int i = 0; i < threads.size(); i++)
			{
				synchronized(this)
				{
					if(threads.get(i).threadSuspended == false)
					{
						activeCounter++;
						redBucket += ((Color)threads.get(i).rectangle.getFill()).getRed();
						greenBucket += ((Color)threads.get(i).rectangle.getFill()).getGreen();
						blueBucket += ((Color)threads.get(i).rectangle.getFill()).getBlue();
					}	
				}
			}
			if(activeCounter != 0)
			{
				/**
				 * @param red - amount of red in a color.
				 * @param green - amount of green in a color.
				 * @param blue - amount of blue in a clor .
				 */
				int red = ((int)((redBucket / activeCounter) * 255));
				int green = ((int)((greenBucket / activeCounter) * 255));
				int blue = ((int)((blueBucket / activeCounter) * 255));
				
				rectangle.setFill(Color.rgb(red, green, blue));
			}
		}
	}
	
	/**
	 * \brief Get 4 neighbours of a rectangle.
	 * @return ArrayList with neigbouring rectangles.
	 */
	private final ArrayList<MyThread> getNeighbours()
	{
			ArrayList <MyThread> threads = new ArrayList<MyThread>();
			threads.add(getTorusThread(x + 1, y));
			threads.add(getTorusThread(x - 1, y));
			threads.add(getTorusThread(x, y + 1));
			threads.add(getTorusThread(x, y - 1));
			return threads;
	}
	
	/**
	 * \brief Get thread from 2D ArrayList of MyThreads
	 * \details This function gets the specified thread from a 2D ArrayList of MyThreads
	 * in a torus like fashion.
	 * @param x - x coordinates of thread in checker
	 * @param y - y coordinates of thread in checker
	 * @return MyThread from position (x,y) in torus
	 */
	private static final MyThread getTorusThread(int x, int y)
	{
		synchronized(myObject)
		{
			return checker.get((x % thisN + thisN) % thisN).get((y % thisM + thisM) % thisM);
		}
	}
	
	/**
	 * \brief get rectangle from MyThread
	 * @return rectangle
	 */
	public Rectangle getRectangle()
	{
		return rectangle;
	}
	
	/**
	 * \brief Set the static 2D ArrayList of MyThreads
	 * @param list - 2D ArrayList of objects MyThreads
	 */
	public final static void setArrayList(ArrayList <ArrayList <MyThread>>list)
	{
		checker = list;
	}
	
	/**
	 * \brief Set thisN and ThisM
	 * @param n - number of columns in a checker
	 * @param m - number of rows in a checker
	 */
	public final static void setNM(int n, int m)
	{
		thisN = n;
		thisM = m;
	}
	/**
	 * \brief Set the object (key) for synchronization among threads
	 * @param o - setting object
	 */
	public final static void setSynchObject(Object o)
	{
		myObject = o;
	}
}
