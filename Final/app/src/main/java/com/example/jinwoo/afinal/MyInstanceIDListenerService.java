package com.example.jinwoo.afinal;

import android.content.Intent;

import com.google.android.gms.iid.InstanceIDListenerService;

/**
 * Created by jinwoo on 2017-12-06.
 */

public class MyInstanceIDListenerService extends InstanceIDListenerService {

    private static final String TAG = "MyInstanceIDLS";

    @Override
    public void onTokenRefresh(){

        Intent intent = new Intent(this, RegistrationIntentService.class);
        startService(intent);
    }

}
