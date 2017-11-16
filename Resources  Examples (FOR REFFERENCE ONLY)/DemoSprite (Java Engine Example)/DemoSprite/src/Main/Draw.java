/*
 * Created by Thomas Theis 10/3/2016
 * for teaching and educational purpose. You may not distribute this code without consent of the author.
 * This code cannot be re-published without consent, either.
 * This code may not be re-used to pass off ass your own in any case.
 */


package Main;

import javax.swing.JComponent;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Graphics;


public class Draw extends JComponent{
	
	public boolean  ShowInfo = true;
	public static int fps = 0;
	   private int fpsc = 0;
	   private int wait = 0;
	   
	public void paint(Graphics g)
	   {		   
	      Graphics2D g2 = (Graphics2D) g; // Recover Graphics2D so we can draw on it
	      setFPS();
	      if(ShowInfo)
	    	  DrawText(g2);
	      
	      //##############
	      //Draw main stuff here.
	      	Initalize.player.draw(g2);
	      //##############
	   }
	
	   public void DrawText(Graphics2D g2)
	   {
			   int lines = 1;
			   int linesW = 18;
		      //draw text to screen, to display a few messages.
			  g2.setColor(new Color(0,0,0,125));
			  g2.fillRect(8, 10, 100, 130);
			  g2.setColor(Color.YELLOW);
			  
		      g2.drawString("FPS: "+fps,10, lines++*linesW);
		      g2.drawString("CPU: "+Compute.cpu,10,lines++*linesW);
		      g2.drawString("CPU_Ticks: "+Compute.cpu_tick,10,lines++*linesW);
		      g2.drawString("Seconds: "+Compute.Seconds,10,lines++*linesW);
		      g2.drawString("Total_CPU: "+Compute.totalCpu,10,lines++*linesW);
		      //g2.drawString("Tiles: "+GridLength+"x"+GridHeight,10,lines++*linesW);
		      //g2.drawString("pTicks: "+Window.npc.player.ptick,10,lines++*linesW);
		      //g2.drawString("Skeltals: "+Window.npc.monsters.size(),10,lines++*linesW);
	   
	   }
	   
	   public void setFPS()
	   {
		   fpsc++;
		   if(Compute.Seconds > wait)
		   {
			   wait++;
			   this.fps = fpsc;
			   fpsc = 0;
		   }
		   
	   }  
	
	
}
