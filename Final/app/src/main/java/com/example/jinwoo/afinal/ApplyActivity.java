package com.example.jinwoo.afinal;


import android.content.Intent;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

public class ApplyActivity extends AppCompatActivity {

    EditText apply_id;
    EditText apply_password;
    EditText apply_name;
    Button okbtn;
    Button nobtn;
   // String token;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        requestWindowFeature(Window.FEATURE_NO_TITLE);// Remove top titlebar
        setContentView(R.layout.activity_apply);
        apply_id = (EditText) findViewById(R.id.apply_id);
        apply_password = (EditText) findViewById(R.id.apply_password);
        apply_name = (EditText) findViewById(R.id.apply_name);
        okbtn = (Button) findViewById(R.id.okbtn);
        nobtn = (Button) findViewById(R.id.nobtn);
        okbtn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){

               /* Intent intent5 = getIntent();
                token = intent5.getExtras().getString("token");
*/
                new JSONTask().execute("http://13.124.118.230:3000/signup");
                Toast.makeText(getApplicationContext(), "가입되었습니다.", Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(getApplicationContext(),MainActivity.class);
                startActivity(intent);
            }
        });

        nobtn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){

                Toast.makeText(getApplicationContext(), "취소했습니다.", Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(getApplicationContext(),MainActivity.class);
                startActivity(intent);
            }
        });

    }
    public class JSONTask extends AsyncTask<String, String, String> {


        @Override
        public String doInBackground(String... urls) {

            try {

               // registrationIntentService = (RegistrationIntentService)getApplicationContext();
                //registrationIntentService.onHandleIntent(null);
                //token = registrationIntentService.token;
                Log.d("234d1", "@@@" + RegistrationIntentService.token);
                //JSONObject를 만들고 key value 형식으로 값을 저장해준다.

                JSONObject jsonObject = new JSONObject();
                jsonObject.accumulate("id", apply_id.getText().toString());
                jsonObject.accumulate("password", apply_password.getText().toString());
                jsonObject.accumulate("name", apply_name.getText().toString());
                jsonObject.accumulate("token",RegistrationIntentService.token);

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
                    Log.d("234d1", "!!!!" + buffer.toString());
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

            //tvData.setText(result);//서버로 부터 받은 값을 출력해주는 부
        }

    }

}

