package com.pil.minesweeper;

import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;

import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {
	
	static final int BLIND = 1; //map만
	static final int SEE = 2;   //map만
	static final int FLAG = 3;  //map만
	static final int SAFE = 0;  //Sweeper만
	static final int MINE = -1; //Sweeper만
	
	static final int WIDTH = 48;
	static final int HEIGHT = 48;
	
	boolean flagmode;
	boolean minemode;
	
	Random mR;
	static View view;
	Resources res;
	
	int mMap[][] = new int[10][10];
	int mSweeper[][] = new int[10][10];
	int minecount;
	static int timecount;
	TextView time;
	
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //setContentView(R.layout.mainmenu);
        setContentView(R.layout.activity_main);
        
        RelativeLayout layout = (RelativeLayout)findViewById(R.id.Layout1);
        //RelativeLayout menu = (RelativeLayout)findViewById(R.id.Layout2);
        
        Button flag = (Button)findViewById(R.id.Flag);
        Button reset = (Button)findViewById(R.id.Reset);
        Button mine = (Button)findViewById(R.id.Mine);
        time = (TextView)findViewById(R.id.Time);
        
        view = new View(this);
        res = this.getResources();
        //Timer timer = new Timer();
        //timer.schedule(new workTask(), 0, 1000);
        
        
        flag.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				
				flagmode = true;
				minemode = false;
			}
		});
        
        reset.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				ini();
				view.invalidate();
			}
		});
        
        mine.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				minemode = true;
				flagmode = false;
			}
		});
        
        onView vi = new onView(this);
        layout.addView(vi);
        
		mR = new Random();
		ini();
		//mView = new MainView(this);
        //setContentView(mView);
    }
    
	Handler mHandler = new Handler();
	Timer mTimer  = new Timer();
	
	public void setTimer(int sec)
	{
		TimerTask task = new TimerTask() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				Log.v("setTimer", ""+timecount);
				upDate();
			}
		};
		mTimer.schedule(task, 0, sec);
	}
	
	public void upDate()
	{
		Runnable runnable = new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				if(timecount != 0)
				{
					//Log.v("update", ""+timecount);
					timecount--;
				}
			}
		};
		mHandler.post(runnable);
	}
	
	public void killTimer()
	{
		mTimer.cancel();
	}
	
    /*public static class workTask extends TimerTask{

		@Override
		public void run() {
			// TODO Auto-generated method stub
			if(timecount != 0)
			{
				Log.v("worktask", ""+timecount);
				timecount--;
				view.invalidate();
			}
		}
    	
    }
    */
	public void ini()
	{	
		flagmode = false;
		minemode = true;
		
		timecount = 60;
		minecount = 0;
		
		for(int y = 0;y < 10;y++)
		{
			for(int x = 0;x < 10;x++)
			{
				mMap[y][x] = BLIND;
				mSweeper[y][x] = SAFE;
			}
		}
		setTimer(1000);
		setMine();
	}
	
	public void setMine()
	{
		Log.v("setmine", "setmine");
		int y,x;
		
		for(int i=0;i<10;i++)
		{
			y = mR.nextInt(10);
			x = mR.nextInt(10);
			if(mSweeper[y][x] == MINE)
			{
				i--;
				continue;
			}
			mSweeper[y][x] = MINE;
			setNumber(x,y);
		}
	}
	
	public void setNumber(int x,int y)
	{
		/*
		 * 10:30 /   12   / 1:30
		 *   9   /  MINE  /  3
		 *  7:30 /   6    / 4:30
		 */
		
		//12
		if(0 <= y-1)
		{
			if(mSweeper[y-1][x] != MINE)
			{
				mSweeper[y-1][x]++;
			}
		}
		//1:30
		if(x+1 < 10 && 0 <= y-1)
		{
			if(mSweeper[y-1][x+1] != MINE)
			{
				mSweeper[y-1][x+1]++;
			}
		}
		//3
		if(x+1 < 10)
		{
			if(mSweeper[y][x+1] != MINE)
			{
				mSweeper[y][x+1]++;
			}
		}
		//4:30
		if(x+1 < 10 && y+1 < 10)
		{
			if(mSweeper[y+1][x+1] != MINE)
			{
				mSweeper[y+1][x+1]++;
			}
		}
		//6
		if(y+1 < 10)
		{
			if(mSweeper[y+1][x] != MINE)
			{
				mSweeper[y+1][x]++;
			}
		}
		//7:30
		if(0 <= x-1 && y+1 < 10)
		{
			if(mSweeper[y+1][x-1] != MINE)
			{
				mSweeper[y+1][x-1]++;
			}
		}
		//9
		if(0 <= x-1)
		{
			if(mSweeper[y][x-1] != MINE)
			{
				mSweeper[y][x-1]++;
			}
		}
		//10:30
		if(0 <= x-1 && 0 <= y-1)
		{
			if(mSweeper[y-1][x-1] != MINE)
			{
				mSweeper[y-1][x-1]++;
			}
		}
	}
	
	public void scout(int x,int y)
	{
		/*
		 * 10:30 /   12   / 1:30
		 *   9   /  MINE  /  3
		 *  7:30 /   6    / 4:30
		 */
		
		//12
		
		if(0 <= y-1)
		{
			if(mMap[y-1][x] == BLIND)
			{
				mMap[y-1][x] = SEE;
				if(SAFE == mSweeper[y-1][x])
				{
					scout(x,y-1);
				}
			}
		}
		//1:30
		if(0 <= y-1 && x+1 <= 9)
		{
			if(mMap[y-1][x+1] == BLIND)
			{
				mMap[y-1][x+1] = SEE;
				if(SAFE == mSweeper[y-1][x+1])
				{
					scout(x+1,y-1);
				}
			}
		}
		//3
		if(x+1 <= 9)
		{
			if(mMap[y][x+1] == BLIND)
			{
				mMap[y][x+1] = SEE;
				if(SAFE == mSweeper[y][x+1])
				{
					scout(x+1,y);
				}
			}
		}
		//4:30
		if(x+1 <= 9 && y+1 <= 9)
		{
			if(mMap[y+1][x+1] == BLIND)
			{
				mMap[y+1][x+1] = SEE;
				if(SAFE == mSweeper[y+1][x+1])
				{
					scout(x+1,y+1);
				}
			}
		}
		//6
		if(y+1 <= 9)
		{
			if(mMap[y+1][x] == BLIND)
			{
				mMap[y+1][x] = SEE;
				if(SAFE == mSweeper[y+1][x])
				{
					scout(x,y+1);
				}
			}
		}
		//7:30
		if(y+1 <= 9 && 0 <= x-1)
		{
			if(mMap[y+1][x-1] == BLIND)
			{
				mMap[y+1][x-1] = SEE;
				if(SAFE == mSweeper[y+1][x-1])
				{
					scout(x-1,y+1);
				}
			}
		}
		//9
		if(0 <= x-1)
		{
			if(mMap[y][x-1] == BLIND)
			{
				mMap[y][x-1] = SEE;
				if(SAFE == mSweeper[y][x-1])
				{
					scout(x-1,y);
				}
			}
		}
		//10:30
		if(0 <= y-1 && 0 <= x-1)
		{
			if(mMap[y-1][x-1] == BLIND)
			{
				mMap[y-1][x-1] = SEE;
				if(SAFE == mSweeper[y-1][x-1])
				{
					scout(x-1,y-1);
				}
			}
		}
	}
	
	public boolean checkGameOver()
	{
		if(10 <= minecount)
		{
			return true;
		}
		return false;
	}
	
	public void check(int x,int y)
	{
		int xpos = x/WIDTH;
		int ypos = (y-150)/HEIGHT;
		
		mMap[ypos][xpos] = SEE;
		
		if(MINE == mSweeper[ypos][xpos])
		{
			//Toast.makeText(mContext, "GameOver", Toast.LENGTH_LONG).show();
		}
		else if(SAFE == mSweeper[ypos][xpos])
		{
			scout(xpos,ypos);
		}
	}
	public void check2(int x,int y)
	{
		int xpos = x/WIDTH;
		int ypos = (y-150)/HEIGHT;
		
		mMap[ypos][xpos] = FLAG;
		
		if(MINE == mSweeper[ypos][xpos])
		{
			minecount++;
		}
	}
	
	public class onView extends View
	{
		public boolean onKeyDown(int keyCode, KeyEvent event) {
			// TODO Auto-generated method stub
			Log.v("keyDown", ""+keyCode);
			if(keyCode == KeyEvent.KEYCODE_BACK)
			{
				killTimer();
				Log.v("keyDown", "backkey");
				MainActivity.this.finish();
				android.os.Process.killProcess(android.os.Process.myTid());
			}
			return super.onKeyDown(keyCode, event);
		}
		
		public onView(Context context) {
			super(context);
			// TODO Auto-generated constructor stub
		}
		public void onDraw(Canvas canvas)
		{
			time.setText(""+timecount);
			Paint paint = new Paint();
			Bitmap flag = BitmapFactory.decodeResource(res, R.drawable.flag);
			int xpos,ypos;
			
			for(int y=0;y<10;y++)
			{
				for(int x=0;x<10;x++)
				{
					xpos = x*WIDTH;
					ypos = y*HEIGHT+150;
					
					paint.setColor(Color.BLACK);
					canvas.drawLine(0, ypos, 10*WIDTH, ypos, paint);
					canvas.drawLine(xpos, 150, xpos, (10*HEIGHT)+150, paint);
					
					if(mMap[y][x] == BLIND)
					{
						paint.setColor(Color.BLUE);
						canvas.drawRect(xpos,ypos,xpos+WIDTH-1,ypos+HEIGHT-1,paint);
					}
					else if(SEE == mMap[y][x])
					{
						if(MINE == mSweeper[y][x])
						{
							paint.setColor(Color.RED);
							canvas.drawRect(xpos, ypos, xpos+WIDTH-1, ypos+HEIGHT-1, paint);
						}
						else if (0 < mSweeper[y][x])
						{
							paint.setColor(Color.BLACK);
							canvas.drawText(""+mSweeper[y][x], xpos+WIDTH/2, ypos+HEIGHT/2, paint);	
						}
						else
						{
							paint.setColor(Color.GREEN);
							canvas.drawText(""+mSweeper[y][x], xpos+WIDTH/2, ypos+HEIGHT/2, paint);
						}
					}
					else if(FLAG == mMap[y][x])
					{
						canvas.drawBitmap(flag, xpos, ypos, paint);
						
						//paint.setColor(Color.DKGRAY);
						//canvas.drawText("F", xpos+WIDTH/2, ypos+HEIGHT/2, paint);
					}
				}
			}
		}
		public boolean onTouchEvent(MotionEvent event)
		{
			if(MotionEvent.ACTION_DOWN == event.getAction())
			{
				int x = (int)event.getX();
				int y = (int)event.getY();
				
				if(x < WIDTH*10 && 150 < y && y < HEIGHT*10+150)
				{
					if(minemode)
					{
						check(x,y);
					}
					else if(flagmode)
					{
						check2(x,y);
						if(true == checkGameOver())
						{
							killTimer();
							ini();
							invalidate();
						}
					}
				}
			}
			invalidate();
			return super.onTouchEvent(event);
		}
	}
}