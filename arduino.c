#include <ArduinoJson.h>
#include <SPI.h>
#include <Phpoc.h>

char server_name[] = "192.168.0.4"; //raspberry server IP
PhpocClient client;
String jsondata = " ";

unsigned long preTime1, time1, t1, preTime2, time2, t2, preTime3, time3, t3, preTime4, time4, t4, preTime5, time5, t5;
int no, b; //라즈베리파이 서버에 전송할 데이터
//초음파 센서의 핀번호를 설정한다.
int echoPin = 12; //초음파1
int trigPin = 13;//초음파1
int echoPin2 = 6; //초음파2
int trigPin2 = 7;//초음파2
/*int echoPin3 = 4;//초음파3
int trigPin3 = 5;//초음파3
int echoPin4 = 10;//초음파4
int trigPin4 = 11;//초음파4
int echoPin5 = 8;//초음파5
int trigPin5 = 9;//초음파5*/
int relay = 10;//릴레이
int water_pin = A0;      //수분수위센서 A0에 연결
int f1 = 0, f2 = 0, f3 = 0, f4 = 0, f5 = 0; //수위 센서 flag
int ultra_f1 = 0, ultra_f2 = 0, ultra_f3 = 0, ultra_f4 = 0, ultra_f5 = 0; //초음파 센서 flag
void setup() {
  Serial.begin(9600);
  // trig를 출력모드로 설정, echo를 입력모드로 설정
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
 /* pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(trigPin5, OUTPUT);
  pinMode(echoPin5, INPUT);*/
  //pinMode(relay,OUTPUT);
  pinMode( A0,  INPUT); // A0핀을 입력으로 설정
  Serial.println("PHPoC TCP Client test");
  Phpoc.begin(PF_LOG_SPI | PF_LOG_NET);
}

void loop() {
  Serial.println("*****************************************");
  float duration, distance, duration2, distance2, duration3, distance3, duration4, distance4, duration5, distance5;

  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.-1
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  duration = pulseIn(echoPin, HIGH); 
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  distance = ((float)(340 * duration) / 10000) / 2;  

  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.-2
  digitalWrite(trigPin2, HIGH);
  delay(10);
  digitalWrite(trigPin2, LOW);
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  duration2 = pulseIn(echoPin2, HIGH); 
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  distance2 = ((float)(340 * duration2) / 10000) / 2;

  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.-3
  /*digitalWrite(trigPin3, LOW);
  delay(2);
  digitalWrite(trigPin3, HIGH);
  delay(5);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  distance3 = (duration3/2)/29.1;
  if(digitalRead(echoPin3) == LOW){
    duration3 = pulseIn(echoPin3, HIGH);
    distance3 = ((float)(340 * duration3) / 10000) / 2;
  }
  else {
    pinMode(echoPin3, OUTPUT);
    digitalWrite(echoPin3, LOW);
    pinMode(echoPin3, INPUT);
  }
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  

  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.-4
  digitalWrite(trigPin4, LOW);
  delay(2);
  digitalWrite(trigPin4, HIGH);
  delay(5);
  digitalWrite(trigPin4, LOW);
  duration4 = pulseIn(echoPin4, HIGH);
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  distance4 = (duration4/2)/29.1;
  
  if(digitalRead(echoPin4) == LOW){
    duration4 = pulseIn(echoPin4, HIGH);
    distance4 = ((float)(340 * duration4) / 10000) / 2;
  }
  else {
    pinMode(echoPin4, OUTPUT);
    digitalWrite(echoPin4, LOW);
    pinMode(echoPin4, INPUT);
  }
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.

  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.-5
  digitalWrite(trigPin5, LOW);
  delay(2);
  digitalWrite(trigPin5, HIGH);
  delay(5);
  digitalWrite(trigPin5, LOW);
  duration5 = pulseIn(echoPin5, HIGH);
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  distance5 = (duration5/2)/29.1;
  
  if(digitalRead(echoPin5) == LOW){
    duration5 = pulseIn(echoPin5, HIGH);
    distance5 = ((float)(340 * duration5) / 10000) / 2;
  }
  else {
    pinMode(echoPin5, OUTPUT);
    digitalWrite(echoPin5, LOW);
    pinMode(echoPin5, INPUT);
  }*/

  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다. 
  
  Serial.print("초음파1 거리 : ");
  Serial.print(distance);
  Serial.println("cm");
  Serial.print("초음파2 거리 : ");
  Serial.print(distance2);
  Serial.println("cm");
  /*Serial.print("초음파3 거리 : ");
  Serial.print(distance3);
  Serial.println("cm");
  Serial.print("초음파4 거리 : ");
  Serial.print(distance4);
  Serial.println("cm");
  Serial.print("초음파5 거리 : ");
  Serial.print(distance5);
  Serial.println("cm");*/
  
  Serial.println(analogRead(A0));  // Serial monitor로 A0값을 보여줌
  delay(100);                       // 입력값을 보여주는데 0.1초 설정
  
  // 수정한 값을 출력
  delay(500);
  if(f1 == 0){
    if(distance<15)
    {
      //preTime1 = millis();
      Serial.println("1번칸 사용 중");
      if(ultra_f1 == 0){
        no = 1;
        b = 0;
        sendToUseServer(no, b);
        ultra_f1 = 1;
        //digitalWrite(relay,HIGH); //릴레이 모듈 Off
        //delay(200);
      }
    }
    else
    { 
      //time1 = millis();
      //Serial.print("1번칸 사용 시간");
      //Serial.println(time1 - preTime1);
      if(ultra_f1 == 1){
        Serial.println("변기 물 내리기");
        //digitalWrite(relay,LOW); //릴레이 모듈 On
        //delay(10000);
        
        ultra_f1 = 0;
        no = 1;
        b = 1;
        sendToUseServer(no, b);
        Serial.println("1번칸 사용 가능");
        time1 = 0;
      }
    }
  }

  if(f2 == 0){
    if(distance2<15)
    {
      //preTime2 = millis();
      Serial.println("2번칸 사용 중");
      if(ultra_f2 == 0){
        no = 2;
        b = 0;
        sendToUseServer(no, b);
        ultra_f2 = 1;
        //digitalWrite(relay,HIGH); //릴레이 모듈 Off
        //delay(200);
      }
    }
    else
    { 
      //time2 = millis();
      //Serial.print("2번칸 사용 시간");
      //Serial.println(time2 - preTime2);
      if(ultra_f2 == 1){
        //digitalWrite(relay,LOW); //릴레이 모듈 On
        //delay(5000);
        
        ultra_f2 = 0;
        no = 2;
        b = 1;
        sendToUseServer(no, b);
        Serial.println("2번칸 사용 가능");
      }
    }
  }

  /*if(f3 == 0){
    if(distance3<15)
    {
      //preTime3 = millis();
      Serial.println("3번칸 사용 중");
      if(ultra_f3 == 0){
        no = 3;
        b = 0;
        sendToUseServer(no, b);
        ultra_f3 = 1;
        //digitalWrite(relay,HIGH); //릴레이 모듈 Off
        //delay(200);
      }
    }
    else
    { 
      //time3 = millis();
      //Serial.print("3번칸 사용 시간");
      //Serial.println(time3 - preTime3);
      if(ultra_f3 == 1){
        //digitalWrite(relay,LOW); //릴레이 모듈 On
        //delay(5000);
        
        ultra_f3 = 0;
        no = 3;
        b = 1;
        sendToUseServer(no, b);
        Serial.println("3번칸 사용 가능");
      }
    }
  }

  if(f4 == 0){
    if(distance4<15)
    {
      //preTime4 = millis();
      Serial.println("4번칸 사용 중");
      if(ultra_f4 == 0){
        no = 4;
        b = 0;
        sendToUseServer(no, b);
        ultra_f4 = 1;
        //digitalWrite(relay,HIGH); //릴레이 모듈 Off
        //delay(200);
      }
    }
    else
    { 
      //time4 = millis();
      //Serial.print("4번칸 사용 시간");
      //Serial.println(time4 - preTime4);
      if(ultra_f4 == 1){
        //digitalWrite(relay,LOW); //릴레이 모듈 On
        //delay(5000);
        
        ultra_f4 = 0;
        no = 4;
        b = 1;
        sendToUseServer(no, b);
        Serial.println("4번칸 사용 가능");
      }
    }
  }

  if(f5 == 0){
    if(distance5<15)
    {
      //preTime5 = millis();
      Serial.println("5번칸 사용 중");
      if(ultra_f5 == 0){
        no = 5;
        b = 0;
        sendToUseServer(no, b);
        ultra_f5 = 1;
        //digitalWrite(relay,HIGH); //릴레이 모듈 Off
        //delay(200);
      }
    }
    else
    { 
      //time5 = millis();
      Serial.print("5번칸 사용 시간");
      Serial.println(time5 - preTime5);
      if(ultra_f5 == 1){
        //digitalWrite(relay,LOW); //릴레이 모듈 On
        //delay(5000);
        
        ultra_f5 = 0;
        no = 5;
        b = 1;
        sendToUseServer(no, b);
        Serial.println("5번칸 사용 가능");
      }
    }
  }*/

  if(analogRead(A0) < 300) // 수위센서, A0가 300 이하면 변기가 막히지 않은것.
  { 
    if(f1 == 1){
      sendToBlockServer(1, 1);
      f1 = 0;
    }
    delay(100);
    Serial.println("변기가 정상입니다.");
  }
    
  else if(analogRead(A0) >300 ) // 수위센서, A0가 300이상이면 변기가 막힌것.
  { 
    if(f1 == 0){
      sendToBlockServer(1, 0);
      f1 = 1;
    }
    delay(100);
    Serial.println("변기가 막혔습니다.");
  }
}

void sendToBlockServer(int no, int flag){
  jsondata = " ";
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["no"] = no;
  root["flag"] = flag;
  root.printTo(jsondata);
  Serial.println(jsondata);

  if(client.connect(server_name, 3000))
  {
    Serial.println("connected");
    client.print("POST /block HTTP/1.1\r\n");
    client.print("Cache-Control: no-cache\r\n");
    client.print("Host: 192.168.0.4:3000\r\n");
    client.print("User-Agent: Arduino\r\n");
    client.print("Content-Type: application/json\r\n");
    client.print("Content-Length: ");
    client.println(jsondata.length());
    client.println();
    client.println(jsondata);
    client.print("\r\n\r\n");
    client.stop();
  }
  
  else
    Serial.println("connection failed");
    
  if(client.available())
  {
    char c = client.read();
    Serial.print(c);
  }

  if(!client.connected())
  {
    Serial.println("disconnected");
    client.stop();
    //while(1)
     // ;
  }
}

void sendToUseServer(int no, int flag){
  jsondata = " ";
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["no"] = no;
  root["flag"] = flag;
  root.printTo(jsondata);
  Serial.println(jsondata);
  delay(3000);
  if(client.connect(server_name, 3000))
  {
    Serial.println("connected");
    client.print("POST /use HTTP/1.1\r\n");
    client.print("Cache-Control: no-cache\r\n");
    client.print("Host: 192.168.0.4:3000\r\n");
    client.print("User-Agent: Arduino\r\n");
    client.print("Content-Type: application/json\r\n");
    client.print("Content-Length: ");
    client.println(jsondata.length());
    client.println();
    client.println(jsondata);
    client.print("\r\n\r\n");
    client.stop();
  }
  
  else
    Serial.println("connection failed");
  
  if(client.available())
  {
    char c = client.read();
    Serial.print(c);
  }

  if(!client.connected())
  {
    Serial.println("disconnected");
    client.stop();
    //while(1)
      //;
  }
}