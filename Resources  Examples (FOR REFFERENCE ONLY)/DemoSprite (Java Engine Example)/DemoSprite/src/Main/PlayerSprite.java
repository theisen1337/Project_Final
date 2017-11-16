/*
 * Created by Thomas Theis 10/3/2016
 * for teaching and educational purpose. You may not distribute this code without consent of the author.
 * This code cannot be re-published without consent, either.
 * This code may not be re-used to pass off ass your own in any case.
 */
package Main;



import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import java.awt.geom.Line2D;
import java.awt.geom.Rectangle2D;
import java.awt.geom.RoundRectangle2D;
import java.awt.Toolkit;

import java.awt.Image;
import java.awt.Shape;

import javax.swing.ImageIcon;

import java.awt.image.AffineTransformOp;
import java.awt.image.BufferedImage;
import java.io.*;
import java.util.ArrayList;

import javax.imageio.ImageIO;
import javax.swing.JPanel;





public class PlayerSprite 
{
	public int playerX, playerY, playerW, playerH;
	private Color playerC;
	public static boolean pWest, pNorth, pSouth, pEast,pSprint;
	
	private double initialspeed = 2d;
	private double speed = initialspeed;
	private double boost = initialspeed*2;
	private int Stamina = 100; 
	private int StaminaTimer;
	
	public static float Scale = 1.00f;
	
	
	
	
	private int tempPlayerX, tempPlayerY;
	
	 
	 int pPos =0;
	 int ptick = 0;
	
	final int width = 20;
	final int height = 40;
	final int rows = 4;
	final int cols = 4;
	
	private BufferedImage pSheet;

	private BufferedImage[] pSprite = new BufferedImage[rows * cols];
	
	public boolean playerAlive = true;
	

	

	public PlayerSprite()
	{
		playerX = 250;
		playerY = 250;
		playerW = 20;
		playerH = 40;
		playerC = Color.blue;
		
		//try to load png into BufferedImage pSheet
		try{
				pSheet = ImageIO.read(new File("Player\\playerSheet.png"));
		      }catch(Exception e){System.out.println(e+"!");
		   }
		//split the bufferedImage into seperate sprite images, in the buffered image array.
		for (int i = 0; i < rows; i++)
	      {
	          for (int j = 0; j < cols; j++)
	          {
	              pSprite[(i * cols) + j] = pSheet.getSubimage(
	                  j * width,
	                  i * height,
	                  width,
	                  height
	              );
	          }
	      }
	}


	
public void playerMove()
	{
		int[] MoveWest = {3,3,3,3,11,11,11,11,3,3,3,3,7,7,7,7};
		int[] MoveEast = {2,2,2,2,10,10,10,10,2,2,2,2,6,6,6,6};	
		int[] MoveNorth = {0,0,0,0,4,4,4,4,0,0,0,0,8,8,8,8};
		int[] MoveSouth = {1,1,1,1,5,5,5,5,1,1,1,1,9,9,9,9};
		
		//For sprinting and Stamina 
		if(pSprint && Stamina >0)
		{
			speed = boost * Scale;
			Stamina--;
			StaminaTimer = Compute.Seconds+(((Stamina - 100) * -1) /25);
			
		}
		
		else{
			speed = (int)(initialspeed * Scale);
			}
		
		if(StaminaTimer < Compute.Seconds && Stamina < 100 && (Compute.cpu_tick % 2 == 0))
			Stamina++;
		
			tempPlayerX = playerX;
			tempPlayerY = playerY;
			if((pWest && pSouth) || (pWest && pNorth) || (pEast && pSouth) || (pEast && pNorth))
			{
				ptick++;
				speed = speed * 1;
				if(pWest && pSouth)
				{
					playerX-=speed;

				}
				else if(pWest && pNorth)
				{
					playerX-=speed;

				}
				else if(pEast && pSouth)
				{
					playerX+=speed;

				}
				else if(pEast && pNorth)
				{
					playerX+=speed;

				}
			}else
			{
				if(pWest){
					//Actual movement math, to move the players accords
					playerX-=speed;
					//legit, go through the array infinitly and call the index 0 to (length -1) 
					pPos = MoveWest[(ptick % MoveWest.length)];
					//increment the movement of the player.
					ptick++;
					}
				else if(pEast){playerX+=speed; pPos = MoveEast[(ptick % MoveEast.length)];ptick++;}
				else if(pSouth){playerY+=speed; pPos = MoveSouth[(ptick % MoveSouth.length)];ptick++;}
				else if(pNorth){playerY-=speed; pPos = MoveNorth[(ptick % MoveNorth.length)];ptick++;}
			}

		
		}
	
	public int getX()
	{
		return playerX;
	}
	public int getY()
	{
		return playerY;
	}
	
	public void draw(Graphics2D canvas)
	   {
	      Graphics2D g = (Graphics2D) canvas;
	      
	      
	      drawHUI(g);
	      	
	      BufferedImage after = new BufferedImage((int)(playerW*Scale), (int)(playerH*Scale), BufferedImage.TYPE_INT_ARGB);
	      AffineTransform at = new AffineTransform();
	      at.scale(Scale, Scale);
	      AffineTransformOp scaleOp = 
	         new AffineTransformOp(at, AffineTransformOp.TYPE_BILINEAR);
	      after = scaleOp.filter(pSprite[pPos], after);
	      g.drawImage(after,playerX,playerY,null);

	      
	   }
	private void drawHUI(Graphics2D g)
	{
		drawStamina(g);
	}
	private void drawText(Graphics2D g)
	{
		g.setColor(playerC);
	      g.drawString(Double.toString(speed)+ " X: "+playerX+" "+"Y: "+playerY,playerX,playerY+60);
	}
	private void drawHitBox(Graphics2D g)
	{
		int Left_Top_X = (playerX + (int)initialspeed), Left_Top_Y = (playerY+(playerH / 2)+(int)initialspeed);
		int Left_Down_X = (playerX + (int)initialspeed), Left_Down_Y = (playerY+(playerH -1)-((int)(initialspeed)));
		int Right_Top_X = (playerX + playerW) -(int)initialspeed, Right_Top_Y = (playerY+(playerH / 2)+(int)initialspeed);
		int Right_Down_X = (playerX + playerW) -(int)initialspeed, Right_Down_Y = (playerY+(playerH)-(int)initialspeed);
		int size = 1;
      
      
      
      g.setColor(Color.black);
      g.fillRect(playerX,playerY+((playerH/ 2)), 20,20);
      g.setColor(Color.blue);
      //g.fillRect(playerX+1,playerY+((playerH/ 2)+1), 18,18);
      
      g.fillRect(Left_Top_X,Left_Top_Y, size,size);
      g.fillRect(Left_Down_X,Left_Down_Y, size,size);
      g.fillRect(Right_Top_X,Right_Top_Y, size,size);
      g.fillRect(Right_Down_X,Right_Down_Y, size,size);
	}
	private void drawStamina(Graphics2D g)
	{
		//Stamina Bar
		
		//Variables
		int xslice = 20;
		int yslice = 40;
		
		int x = (main.frame.getWidth() / xslice)*14;
		int y = (main.frame.getHeight() / yslice)*2;
		int w = (main.frame.getWidth() / xslice)*5;
		int h = (main.frame.getHeight() / yslice)*2;
		
		int borderWidth = 3*(int)speed;
		
		//Color Scheme
		Color Border = new Color(0,0,0,(30)+(Compute.Seconds));
		Color Back = new Color(0,0,0,150);
		Color Blue = new Color(0,0,255,250);
		Color White = new Color(255,255,255,250);
		
		GradientPaint BAR = new GradientPaint(
				x,
				y*18,
				White, 
				((w/10)*8),
				h/2,
				Blue);
		
		//dashed line
		float linestart = (float)(Compute.totalCpu/2);
		BasicStroke defaultStroke = (BasicStroke) g.getStroke();
		
		float dash1[] = {10.0f};
		BasicStroke dashed = new BasicStroke(1.0f,
		                        BasicStroke.CAP_BUTT,
		                        BasicStroke.JOIN_MITER,
		                        10.0f, dash1, linestart);
		//outer border
		g.setColor(Border);
		g.draw(new RoundRectangle2D.Double(x-borderWidth,y-borderWidth,w+(borderWidth*2),h+(borderWidth*2),10,10));
		
		//background
		g.setColor(Back);
		g.fill(new RoundRectangle2D.Double(x-(borderWidth/2), y-(borderWidth/2),w+(borderWidth/2)*2,h+(borderWidth/2)*2,10, 10));
		
		//dashed rectangle
		g.setStroke(dashed);
		g.setColor(Back);
		g.draw(new RoundRectangle2D.Double(x, y,w,h,10, 10));
		
		//Stamina Bar
		g.setPaint(BAR);
		g.fillRect(x+(w/10), y+(h/5)*2,(int)(((w/10)*8)*(Stamina/100.00)),h/2);
		
		g.drawString(""+Stamina,x+(w/10)+((int)(((w/10)*8)*(Stamina/100.00))), (y+(h/5)*4));
		g.drawString("Stamina",x+ (w/40)*15, (y+(h/5)*2)-2);
		g.setStroke(defaultStroke);
		
	}

	






}

