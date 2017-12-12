package com.example.jinwoo.afinal;

import android.content.Intent;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class SelectBuildingActivity extends AppCompatActivity {

    Button paldalbtn;
    Button jonghapbtn;
    Button sinhakbtn;
    Button yulgokbtn;
    Button managerbtn;
    String mode;
    String show;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_select_building);
        paldalbtn = (Button) findViewById(R.id.paldalbtn);
        jonghapbtn = (Button) findViewById(R.id.jonghapbtn);
        sinhakbtn = (Button) findViewById(R.id.sinhakbtn);
        yulgokbtn = (Button) findViewById(R.id.yulgokbtn);
        managerbtn = (Button) findViewById(R.id.button2);


        paldalbtn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){

                Intent intent = new Intent(getApplicationContext(),Pal_SelectFloorActivity.class);
                intent.putExtra("name","paldal");
                startActivity(intent);

            }

        });

        jonghapbtn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){

                Intent intent = new Intent(getApplicationContext(),Jong_SelectFloorActivity.class);
                intent.putExtra("name","jonghap");
                startActivity(intent);

            }

        });

        sinhakbtn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){

                Intent intent = new Intent(getApplicationContext(),SelectFloorActivity.class);
                intent.putExtra("name","sinhak");
                startActivity(intent);

            }

        });

        yulgokbtn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){

                Intent intent = new Intent(getApplicationContext(),SelectFloorActivity.class);
                intent.putExtra("name","yulgok");
                startActivity(intent);

            }

        });

        managerbtn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){

                Intent intent2 = getIntent();
                mode = intent2.getExtras().getString("mode");

                //Intent intent = new Intent(getApplicationContext(),ManagerActivity.class);
                //intent.putExtra("name","paldal");

                try {
                    new SelectBuildingActivity.JSONTask().execute("http://13.124.118.230:3000/manager");
                    //

                }catch(Exception e){
                    e.printStackTrace();
                }

                //startActivity(intent);

            }

        });

    }

    public class JSONTask extends AsyncTask<String, String, String> {

        @Override
        protected String doInBackground(String... urls) {

            try {

                //JSONObject를 만들고 key value 형식으로 값을 저장해준다.

                JSONObject jsonObject = new JSONObject();
                //jsonObject.accumulate("id", login_id.getText().toString());
                //jsonObject.accumulate("password", login_password.getText().toString());

                HttpURLConnection con = null;
                BufferedReader reader = null;

                try{

                    //URL url = new URL("http://192.168.25.16:3000/users");

                    URL url = new URL(urls[0]);

                    //연결을 함

                    con = (HttpURLConnection) url.openConnection();

                    con.setRequestMethod("POST");//POST방식으로 보냄
                    con.setRequestProperty("Cache-Control", "no-cache");//캐시 설정
                    con.setRequestProperty("Content-Type", "application/json");//application JSON 형식으로 전송
                    con.setRequestProperty("Accept", "text/html");//서버에 response 데이터를 html로 받음
                    con.setDoOutput(true);//Outstream으로 post 데이터를 넘겨주겠다는 의미
                    con.setDoInput(true);//Inputstream으로 서버로부터 응답을 받겠다는 의미

                    con.connect();

                    //서버로 보내기위해서 스트림 만듬

                    OutputStream outStream = con.getOutputStream();

                    //버퍼를 생성하고 넣음

                    BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(outStream));

                    writer.write(jsonObject.toString());

                    writer.flush();

                    writer.close();//버퍼를 받아줌

                    //서버로 부터 데이터를 받음

                    InputStream stream = con.getInputStream();

                    reader = new BufferedReader(new InputStreamReader(stream));

                    StringBuffer buffer = new StringBuffer();

                    String line = "";

                    while((line = reader.readLine()) != null){

                        buffer.append(line);

                    }

                    show = buffer.toString();
                    return buffer.toString();//서버로 부터 받은 값을 리턴해줌 아마 OK!!가 들어올것임

                } catch (MalformedURLException e){

                    e.printStackTrace();

                } catch (IOException e) {

                    e.printStackTrace();

                } finally {

                    if(con != null){

                        con.disconnect();

                    }

                    try {

                        if(reader != null){

                            reader.close();//버퍼를 닫아줌

                        }

                    } catch (IOException e) {

                        e.printStackTrace();

                    }

                }

            } catch (Exception e) {

                e.printStackTrace();

            }
            return null;
        }

        @Override

        protected void onPostExecute(String result) {

            super.onPostExecute(result);
/*
            Intent intent1 = new Intent(getApplicationContext(),SelectBuildingActivity.class);
            startActivity(intent1);*/

            if(mode.equals("1")){

                Toast.makeText(getApplicationContext(), "관리자 페이지입니다.", Toast.LENGTH_SHORT).show();
                Intent intent3 = new Intent(getApplicationContext(),ManagerActivity.class);
                intent3.putExtra("info",show);
                startActivity(intent3);

            }else if(mode.equals("0")){
                Toast.makeText(getApplicationContext(), "관리자만 가능합니다.", Toast.LENGTH_SHORT).show();

            }else{
                Toast.makeText(getApplicationContext(), "다시 로그인해주세요.", Toast.LENGTH_SHORT).show();

            }

            //tvData.setText(show);//서버로 부터 받은 값을 출력해주는 부
            //성공 : result :
            //실패 : result : fail
        }

    }


  /*  public void goSelectFloor(View v){
        Toast.makeText(getApplicationContext(), "  팔달관을 선택하셨습니다. ", Toast.LENGTH_SHORT);
        Intent intent1 = new Intent(getApplicationContext(),SelectFloorActivity.class);
        startActivity(intent1);
    }*/
}
