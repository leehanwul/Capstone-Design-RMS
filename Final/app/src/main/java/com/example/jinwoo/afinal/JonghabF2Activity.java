package com.example.jinwoo.afinal;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.ImageView;

/**
 * Created by jinwoo on 2017-12-13.
 */

public class JonghabF2Activity extends AppCompatActivity {

    String result;
    ImageView room[] = new ImageView[4];

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_paldar_f1);

        room[0] = (ImageView) findViewById(R.id.room1);
        room[1] = (ImageView) findViewById(R.id.room2);
        room[2] = (ImageView) findViewById(R.id.room3);
        room[3] = (ImageView) findViewById(R.id.room4);

        Intent intent = getIntent();
        result = intent.getExtras().getString("info");

      /*  int i = 0;
        while(i < result.length()){
            int idx = result.indexOf('}', i);
            Log.d("234d1", "@@@" + result[idx]);
            i = idx + 1;
        }*/
        String[] pivot = result.split("\\}");


        for(int i=0; i<pivot.length; i++){
            String tmp = pivot[i].substring(pivot[i].length()-1);

            if(tmp.equals("1")){
                room[i].setImageResource(R.drawable.a1);
            }else if(tmp.equals("2")){
                room[i].setImageResource(R.drawable.a2);
            }else if(tmp.equals("3")){
                room[i].setImageResource(R.drawable.a3);
            }

        }

    }
}
