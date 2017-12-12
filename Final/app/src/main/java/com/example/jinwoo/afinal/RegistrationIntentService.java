package com.example.jinwoo.afinal;

import android.app.IntentService;
import android.content.Intent;
import android.os.AsyncTask;
import android.util.Log;

import com.google.android.gms.gcm.GcmPubSub;
import com.google.android.gms.gcm.GoogleCloudMessaging;
import com.google.android.gms.iid.InstanceID;

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

/**
 * Created by jinwoo on 2017-12-06.
 */

public class RegistrationIntentService extends IntentService {

    private static final String TAG = "MyInstanceIDService";
    private static final String SENDID = "290863150660";
    public static String token;

    public RegistrationIntentService(){
        super(TAG);
        Log.d(TAG, "RegistrationIntentService()");

    }



    public void onHandleIntent(Intent intent){

        try{
            InstanceID instanceID = InstanceID.getInstance(this);
            token = instanceID.getToken(SENDID, GoogleCloudMessaging.INSTANCE_ID_SCOPE, null);
          /*  new JSONTask().execute("http://13.124.118.230:3000/sendToken");*/
            Log.i(TAG, "token@@: " + token);


        }catch(Exception e){
            Log.d(TAG, "Failed to complete token refresh", e);
        }
    }


    /*public class JSONTask extends AsyncTask<String, String, String> {

        @Override
        protected String doInBackground(String... urls) {

            try {

                //JSONObject를 만들고 key value 형식으로 값을 저장해준다.

                JSONObject jsonObject = new JSONObject();
                jsonObject.accumulate("token", token);

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

            Log.d("234d1", "Ok" + result);
            //Intent intent2 = new Intent(getApplicationContext(),PaldarF1Activity.class);
            //intent2.putExtra("info", result);
            Log.d("234d1", "Fail" + result);
            //startActivity(intent2);
           *//* if(result.equals("ok")){

                Toast.makeText(getApplicationContext(), "로그인했습니다.", Toast.LENGTH_LONG).show();
                Intent intent1 = new Intent(getApplicationContext(),SelectBuildingActivity.class);
                startActivity(intent1);

            }else if(result.equals("")){
                Toast.makeText(getApplicationContext(), "입력해주세요.", Toast.LENGTH_LONG).show();

            }else{
                Toast.makeText(getApplicationContext(), "다시 로그인해주세요.", Toast.LENGTH_LONG).show();

            }*//*

            //tvData.setText(show);//서버로 부터 받은 값을 출력해주는 부
            //성공 : result :
            //실패 : result : fail
        }
    }*/


}
