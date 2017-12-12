package com.example.jinwoo.afinal;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

/**
 * Created by jinwoo on 2017-12-11.
 */

public class ManagerActivity extends AppCompatActivity{

    //TextView tvRecvData;
    String show;
    //List<HashMap<String, String>> fillMaps;
    //SimpleAdapter adapter;
    //ListView listview1;
    String building;
    String floor;
    String no;
    ArrayList<String> data1 = new ArrayList<>();;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_manager);

        //tvRecvData = (TextView)findViewById(R.id.tv_recvData);

        Intent intent = getIntent();
        show = intent.getExtras().getString("info");

        Log.d("@@@@", show);
        jsonParserList1(show);

        ArrayAdapter<String> adapter = new ArrayAdapter<String>
                (this,android.R.layout.simple_list_item_1,data1);


        ListView listView = (ListView)findViewById(R.id.listview);
        listView.setAdapter(adapter);


    }


    void jsonParserList1(String pRecvServerPage){//json parsing
        StringBuffer sb = new StringBuffer();

        try {
            JSONArray jarray = new JSONArray(pRecvServerPage);

            for(int i=0; i < jarray.length(); i++) {

                JSONObject jObject = jarray.getJSONObject(i);
                Log.d("abc",">>>>"+jObject);
                building = jObject.getString("building");
                floor = jObject.getString("floor");
                no = jObject.getString("no");

                data1.add("건물 : " + building + " 층 : " +floor + " 번호 : " +no);

                /*sb.append(
                        "건물 : " + building + "\n" +
                                "층 : " + floor + "\n" +
                                "번호 : " + no + "\n"
                );*/
            }
           // tvRecvData.setText(sb.toString());// show user basic information

        } catch (JSONException e) {
            e.printStackTrace();
        }
    }


}
