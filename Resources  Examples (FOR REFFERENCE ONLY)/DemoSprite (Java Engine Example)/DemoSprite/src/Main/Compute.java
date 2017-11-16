/*
 * Created by Thomas Theis 10/3/2016
 * for teaching and educational purpose. You may not distribute this code without consent of the author.
 * This code cannot be re-published without consent, either.
 * This code may not be re-used to pass off ass your own in any case.
 */
package Main;

import java.awt.event.MouseEvent;



public class Compute
{
		/* object lock, only allowing one object of Compute at once.
	 private static final Compute INSTANCE = new Compute();
	    public Compute(){}
	    public static Compute getInstance() {
	       return INSTANCE;
	    }
		*/
		public int mousex;
		public int mousey;
		public int mouseClicks;

		public boolean dragged = false;

		
		public static int cpu_tick = 0;
		public static int cpu;
		public static long totalCpu = 0;
		
		private int cpuc;
		public boolean spot = false;
		public long Second_Tick = System.currentTimeMillis();
		public static int Seconds;
		
		public int modTicks =0;
		public int modTicksMax =100;
		public boolean modTrack = false;

		public void Computation()
		{
			   cpuc++;
			   totalCpu++;
			   if(System.currentTimeMillis() > Second_Tick + 1000)
			   {
				   Second_Tick+=1000;
				   Seconds++;			   
				   cpu = cpuc;
				   cpuc = 0;
			   }
			
			   if(modTrack)
				{
				   	modTicks+=2;
					if(modTicks >= modTicksMax)
						modTrack = false;
				}
				else
				{
				   	modTicks-=2;
					if(modTicks <= 0)
						modTrack = true;
				}
			   
			 //Count the ticks per computation.
			   cpu_tick++;
			   
			   if(cpu_tick > 50)
				   	cpu_tick = 1;
			   
			//#########################
			   //Main computation calls
			   Initalize.player.playerMove();
			//#########################
			   
			   
		}
	
	   public void setMouseXY(int mX, int mY,int mButton)
	   {
		   mousex = mX;
		   mousey = mY;	   

		   
		   if(mButton == 1)
		   {
			   
		   }else if(mButton == 3)
		   {
			   
		   }else if(mButton == 2)
		   {
			   
		   }

	   }
	   
	   //Handle mouse Hovering
	   public static void checkForHover(MouseEvent event)
	   {
		   int x = event.getX();
		   int y = event.getY();
		   int MouseButton = event.getButton();  
	   }
	   
	   
	}