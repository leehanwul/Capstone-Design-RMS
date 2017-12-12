#include <ArduinoJson.h>
#include <SPI.h>
#include <Phpoc.h>

char server_name[] = "192.168.0.4"; //raspberry server IP
PhpocClient client;
String jsondata = " ";

//초음파 센서의 핀번호를 설정한다.
int echoPin = 12; //초음파1
int trigPin = 13;//초음파1
int echoPin2 = 6; //초음파2
int trigPin2 = 7;//초음파2
int echoPin3 = 30;//초음파3
int trigPin3 = 31;//초음파3
int echoPin4 = 32;//초음파4
int trigPin4 = 33;//초음파4
int echoPin5 = 34;//초음파5
int trigPin5 = 35;//초음파5
int relay = 10;//릴레이
int water_pin = A0;      //수분수위센서 A0에 연결
int f1 = 0, f2 = 0, f3 = 0, f4 = 0, f5 = 0;

void setup() {
  Serial.begin(9600);
  // trig를 출력모드로 설정, echo를 입력모드로 설정
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(trigPin5, OUTPUT);
  pinMode(echoPin5, INPUT);
  pinMode(relay,OUTPUT);
  pinMode( A0,  INPUT); // A0핀을 입력으로 설정
  Serial.println("PHPoC TCP Client test");
  Phpoc.begin(PF_LOG_SPI | PF_LOG_NET);
}

void loop() {
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
  digitalWrite(trigPin3, HIGH);
  delay(10);
  digitalWrite(trigPin3, LOW);
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  duration3 = pulseIn(echoPin3, HIGH);
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  distance3 = ((float)(340 * duration3) / 10000) / 2;

  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.-4
  digitalWrite(trigPin4, HIGH);
  delay(10);
  digitalWrite(trigPin4, LOW);
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  duration4 = pulseIn(echoPin4, HIGH); 
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  distance4 = ((float)(340 * duration4) / 10000) / 2;  

  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.-5
  digitalWrite(trigPin5, HIGH);
  delay(10);
  digitalWrite(trigPin5, LOW);
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  duration5 = pulseIn(echoPin5, HIGH); 
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  distance5 = ((float)(340 * duration5) / 10000) / 2;  
  
  Serial.print(ultrasonic1 : distance);
  Serial.println("cm");
  Serial.print(ultrasonic2 : distance2);
  Serial.println("cm");
  Serial.print(ultrasonic3 : distance3);
  Serial.println("cm");
  Serial.print(ultrasonic4 : distance4);
  Serial.println("cm");
  Serial.print(ultrasonic5 : distance5);
  Serial.println("cm");
  
  Serial.println(analogRead(A0));  // Serial monitor로 A0값을 보여줌
  delay(100);                       // 입력값을 보여주는데 0.1초 설정
  
  // 수정한 값을 출력
  delay(500);

  if(distance<75)
  {
    digitalWrite(relay,LOW);
    delay(5000);
  }
    
  if(distance>75)
  {
    digitalWrite(relay,HIGH);
    delay(200);
  }

  if(analogRead(A0) < 300) // 수위센서, A0가 300 이하면 변기가 막히지 않은것.
  { 
    if(f1 == 1){
      sendToBlockServer(5, 1);
      f1 = 0;
    }
    delay(100);
    Serial.println("변기가 정상입니다.");
  }
    
  else if(analogRead(A0) >300 ) // 수위센서, A0가 300이상이면 변기가 막힌것.
  { 
    if(f1 == 0){
      sendToBlockServer(5, 0);
      f1 = 1;
    }
    delay(100);
    Serial.println("변기가 막혔습니다.");
  }
}

void sendToBlockServer(int no, int flag){
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

  jsondata = " ";
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
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["no"] = no;
  root["flag"] = flag;
  root.printTo(jsondata);
  Serial.println(jsondata);
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