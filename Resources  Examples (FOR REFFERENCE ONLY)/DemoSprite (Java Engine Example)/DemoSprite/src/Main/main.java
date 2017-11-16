/*
 * Created by Thomas Theis 10/3/2016
 * for teaching and educational purpose. You may not distribute this code without consent of the author.
 * This code cannot be re-published without consent, either.
 * This code may not be re-used to pass off ass your own in any case.
 */

package Main;

import java.awt.Color;
import java.awt.Frame;
import java.awt.Toolkit;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class main extends JPanel
	{
		public main() {
			KeyListener listener = new MyKeyListener();
			addKeyListener(listener);
			setFocusable(true);
		}
		//##################################[Variables]
		public static int TICKS_PER_SECOND = 50;
		//##################################[Variables]
		
		public static Draw plane = new Draw();
		public static JFrame frame; 
		public static boolean debug = false;
		private boolean invisable = false;
		
	   public static void main(String [] args)
	   {
	      Compute newCompute = new Compute();
	      main Keyboard = new main();
	      
	      frame = new JFrame();
	      frame.setTitle("AMCS CLUB");
	      frame.add(Keyboard);
	      frame.setSize(825,846);
	      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	      frame.setResizable(false);
	      frame.setBackground(new Color(150,150,150));
	      frame.add(plane);
	      frame.setVisible(true);

	      //############################[Game Variables]
	      long next_game_tick = System.currentTimeMillis();
	      int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	      int MAX_FRAME_SKIP = 5;
	      int looped;
	      float interpolation = 0f;  
	      boolean GameRunning = true;

	      while(GameRunning)
	      {

		    	  looped = 0;
		    	  while( System.currentTimeMillis() > next_game_tick && looped < MAX_FRAME_SKIP)
		    	  {
		    		  //Computation takes place here, so 30 ticks per-second with frame skip attribute for slow PCs
		    		  newCompute.Computation();
		    		  next_game_tick += SKIP_TICKS;
		              looped++;
		          }
		    	  interpolation = (float)( System.currentTimeMillis() + SKIP_TICKS - next_game_tick )/ (float)( SKIP_TICKS ); //off put.
		          frame.repaint(); //Draw graphics every chance you get, but only move objects in Computation   

	      }
	      Runtime.getRuntime().exit(0);
	   }
	   

	   //Controls
		public class MyKeyListener implements KeyListener {
			@Override
			public void keyTyped(KeyEvent e) {
			}

			@Override
			public void keyPressed(KeyEvent e) {

				
				switch(e.getKeyCode())
				{
				

					case KeyEvent.VK_Q: Runtime.getRuntime().exit(0); break;
					case KeyEvent.VK_F1:break;
					case KeyEvent.VK_F2: break;
					case KeyEvent.VK_ESCAPE: Runtime.getRuntime().exit(0); break;

					
					//#########################################
					//Player Movement controls
					case KeyEvent.VK_W: Initalize.player.pNorth = true; break;
					case KeyEvent.VK_S: Initalize.player.pSouth = true; break;
					case KeyEvent.VK_A: Initalize.player.pWest  = true; break;
					case KeyEvent.VK_D: Initalize.player.pEast  = true; break;
					case KeyEvent.VK_SHIFT: Initalize.player.pSprint = true; break;
					
					//Player Scaler Controls
					case KeyEvent.VK_UP: Initalize.player.Scale += .1; break;
					case KeyEvent.VK_DOWN: if(Initalize.player.Scale > 0)Initalize.player.Scale -= .1; break;
					//#########################################
				}
				
				
			}

			@Override
			public void keyReleased(KeyEvent e) {
				//System.out.println("keyReleased="+KeyEvent.getKeyText(e.getKeyCode()));
				switch(e.getKeyCode())
				{
				
				case KeyEvent.VK_F3: plane.ShowInfo = !plane.ShowInfo; break;
				case KeyEvent.VK_P: break;
				//#########################################
				//Player Movement controls
				case KeyEvent.VK_W: Initalize.player.pNorth = false; break;
				case KeyEvent.VK_S: Initalize.player.pSouth = false; break;
				case KeyEvent.VK_A: Initalize.player.pWest  = false; break;
				case KeyEvent.VK_D: Initalize.player.pEast  = false; break;
				case KeyEvent.VK_SHIFT: Initalize.player.pSprint = false; break;
				//#########################################
				}
			}
		}
	   

	
}