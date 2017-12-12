package com.example.jinwoo.afinal;

import android.content.Intent;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

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

public class SelectFloorActivity extends AppCompatActivity {

    Button floor_1;
    Button floor_2;
    Button floor_3;
    Button floor_4;
    Integer flag_1;
    Integer flag_2;
    Integer flag_3;
    Integer flag_4;
    String name;
    String show;
    Integer floor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_select_floor);
        floor_1 = (Button) findViewById(R.id.floor_1);
        floor_2 = (Button) findViewById(R.id.floor_2);
        floor_3 = (Button) findViewById(R.id.floor_3);
        floor_4 = (Button) findViewById(R.id.floor_4);

        floor_1.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){

                Intent intent = getIntent();
                name = intent.getExtras().getString("name");


                //intent2.putExtra("name", name);
                floor = 1;
                flag_1 = 1;
                //intent2.putExtra("building_floor", floor);

                try {
                    new JSONTask().execute("http://13.124.118.230:3000/view");


                }catch(Exception e){
                    e.printStackTrace();
                }

            }

        });

        floor_2.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){

               // Intent intent = new Intent(getApplicationContext(),PaldarF1Activity.class);
                Intent intent = getIntent();
                name = intent.getExtras().getString("name");
                //intent.putExtra("name", name);
                floor = 2;
                flag_2 = 2;
                //intent.putExtra("building_floor", floor);

                try {
                    new JSONTask().execute("http://13.124.118.230:3000/view");

                }catch(Exception e){
                    e.printStackTrace();
                }

                startActivity(intent);

            }

        });

        floor_3.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){

               // Intent intent = new Intent(getApplicationContext(),PaldarF1Activity.class);
                Intent intent = getIntent();
                name = intent.getExtras().getString("name");
                intent.putExtra("name", name);
                floor = 3;
                flag_3 = 3;
                intent.putExtra("building_floor", floor);

                try {
                    new JSONTask().execute("http://13.124.118.230:3000/view");

                }catch(Exception e){
                    e.printStackTrace();
                }

                startActivity(intent);

            }

        });

        floor_4.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){

                //Intent intent = new Intent(getApplicationContext(),PaldarF1Activity.class);
                Intent intent = getIntent();
                name = intent.getExtras().getString("name");
                intent.putExtra("name", name);
                floor = 4;
                flag_4 = 4;
                intent.putExtra("building_floor", floor);

                try {
                    new JSONTask().execute("http://13.124.118.230:3000/view");

                }catch(Exception e){
                    e.printStackTrace();
                }

                startActivity(intent);

            }

        });

    }

    public class JSONTask extends AsyncTask<String, String, String> {

        @Override
        protected String doInBackground(String... urls) {

            try {

                //JSONObject를 만들고 key value 형식으로 값을 저장해준다.

                JSONObject jsonObject = new JSONObject();
                jsonObject.accumulate("building", name);
                jsonObject.accumulate("floor", floor);

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

            Log.d("234d1", "###" + result);

            if(flag_1 == 1) {

                Intent intent2 = new Intent(getApplicationContext(), PaldarF1Activity.class);
                intent2.putExtra("info", result);
                Log.d("234d1", "&&&" + result);
                startActivity(intent2);

            } else if(flag_2 == 2){

                Intent intent2 = new Intent(getApplicationContext(), PaldarF2Activity.class);
                intent2.putExtra("info", result);
                Log.d("234d1", "&&&" + result);
                startActivity(intent2);

            } else if (flag_3 == 3) {

                Intent intent2 = new Intent(getApplicationContext(), PaldarF3Activity.class);
                intent2.putExtra("info", result);
                Log.d("234d1", "&&&" + result);
                startActivity(intent2);

            } else if (flag_4 == 4){

                Intent intent2 = new Intent(getApplicationContext(), PaldarF4Activity.class);
                intent2.putExtra("info", result);
                Log.d("234d1", "&&&" + result);
                startActivity(intent2);

            }
           /* if(result.equals("ok")){

                Toast.makeText(getApplicationContext(), "로그인했습니다.", Toast.LENGTH_LONG).show();
                Intent intent1 = new Intent(getApplicationContext(),SelectBuildingActivity.class);
                startActivity(intent1);

            }else if(result.equals("")){
                Toast.makeText(getApplicationContext(), "입력해주세요.", Toast.LENGTH_LONG).show();

            }else{
                Toast.makeText(getApplicationContext(), "다시 로그인해주세요.", Toast.LENGTH_LONG).show();

            }*/

            //tvData.setText(show);//서버로 부터 받은 값을 출력해주는 부
            //성공 : result :
            //실패 : result : fail
        }
    }

    public void goPaldarF1(View v){
        Toast.makeText(getApplicationContext(), "  1층을 선택하셨습니다. ", Toast.LENGTH_SHORT);
        Intent intent1 = new Intent(getApplicationContext(),PaldarF1Activity.class);
        startActivity(intent1);
    }
}
