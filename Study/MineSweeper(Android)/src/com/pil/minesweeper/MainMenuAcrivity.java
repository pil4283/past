package com.pil.minesweeper;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.RelativeLayout;

public class MainMenuAcrivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.mainmenu);
	}
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }
    public void gameStart(View v)
    {
    	Intent intent = new Intent(this,MainActivity.class);
    	startActivity(intent);
    }
    
    public void gameExit(View v)
    {
    	AlertDialog.Builder dlg = new AlertDialog.Builder(this);
    	dlg.setMessage("종료하시겠습니까?");
    	dlg.setTitle("게임종료");
    	dlg.setPositiveButton("확인", new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
				// TODO Auto-generated method stub
				android.os.Process.killProcess(android.os.Process.myPid());
				MainMenuAcrivity.this.finish();
			}
		});
    	dlg.setNegativeButton("취소",new OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
				// TODO Auto-generated method stub
			}
		});
    	dlg.setIcon(R.drawable.flag);
    	dlg.show();
    }
}
