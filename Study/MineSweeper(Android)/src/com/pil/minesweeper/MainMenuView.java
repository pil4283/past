package com.pil.minesweeper;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.View;
import android.widget.RelativeLayout;

public class MainMenuView extends View {

	Context mContext;
	
	public MainMenuView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
		mContext = context;
	}

	@Override
	public void draw(Canvas canvas) {
		// TODO Auto-generated method stub
		super.draw(canvas);
		Paint paint = new Paint();
		
		
		//paint.setColor(Color.GREEN);
		//canvas.drawText("MainMenu", 200, 200, paint);
	}
}