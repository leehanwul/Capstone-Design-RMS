package com.example.jinwoo.afinal;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class PaldarF1Activity extends AppCompatActivity {

    String result;
    ImageView room[] = new ImageView[5];
    String tmp;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_paldar_f1);

        room[0] = (ImageView) findViewById(R.id.room1);
        room[1] = (ImageView) findViewById(R.id.room2);
        room[2] = (ImageView) findViewById(R.id.room3);
        room[3] = (ImageView) findViewById(R.id.room4);
        room[4] = (ImageView) findViewById(R.id.room5);

        Intent intent = getIntent();
        result = intent.getExtras().getString("info1");
        //jsonParserList1(result);

      /*  int i = 0;
        while(i < result.length()){
            int idx = result.indexOf('}', i);
            Log.d("234d1", "@@@" + result[idx]);
            i = idx + 1;
        }*/





        String[] pivot = result.split("\\}");

        Log.d("234d1", "@@@" + pivot);

        for(int i=0; i<pivot.length; i++){
            String tmp = pivot[i].substring(pivot[i].length()-1);
            Log.d("234d1", "~~~" + pivot[i]);
            if(tmp.equals("1")){
                room[i].setImageResource(R.drawable.a1);
            }else if(tmp.equals("2")){
                room[i].setImageResource(R.drawable.a2);
            }else if(tmp.equals("3")){
                room[i].setImageResource(R.drawable.a3);
            }

        }

    }


   /* void jsonParserList1(String pRecvServerPage){//json parsing
        StringBuffer sb = new StringBuffer();

        try {
            JSONArray jarray = new JSONArray(pRecvServerPage);

            for(int i=0; i < jarray.length(); i++) {

                JSONObject jObject = jarray.getJSONObject(i);
                Log.d("abc",">>>>"+jObject);

                for(int j=0; j<5; j++){

                    tmp = jObject.getString("state");

                }

                floor = jObject.getString("floor");
                no = jObject.getString("no");

                data1.add("건물 : " + building + " 층 : " +floor + " 번호 : " +no);

                sb.append(
                        "건물 : " + building + "\n" +
                                "층 : " + floor + "\n" +
                                "번호 : " + no + "\n"
                );
            }
            // tvRecvData.setText(sb.toString());// show user basic information

        } catch (JSONException e) {
            e.printStackTrace();
        }
    }*/


}
