#include <ArduinoJson.h>
#include <SPI.h>
#include <Phpoc.h>

char server_name[] = "192.168.0.4"; //raspberry server IP
PhpocClient client;
String jsondata = " ";

unsigned long preTime1, time1, t1, preTime2, time2, t2, preTime3, time3, t3, preTime4, time4, t4, preTime5, time5, t5;
int no, b; //��������� ������ ������ ������
//������ ������ �ɹ�ȣ�� �����Ѵ�.
int echoPin = 12; //������1
int trigPin = 13;//������1
int echoPin2 = 6; //������2
int trigPin2 = 7;//������2
/*int echoPin3 = 4;//������3
int trigPin3 = 5;//������3
int echoPin4 = 10;//������4
int trigPin4 = 11;//������4
int echoPin5 = 8;//������5
int trigPin5 = 9;//������5*/
int relay = 10;//������
int water_pin = A0;      //���м������� A0�� ����
int f1 = 0, f2 = 0, f3 = 0, f4 = 0, f5 = 0; //���� ���� flag
int ultra_f1 = 0, ultra_f2 = 0, ultra_f3 = 0, ultra_f4 = 0, ultra_f5 = 0; //������ ���� flag
void setup() {
  Serial.begin(9600);
  // trig�� ��¸��� ����, echo�� �Է¸��� ����
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
  pinMode( A0,  INPUT); // A0���� �Է����� ����
  Serial.println("PHPoC TCP Client test");
  Phpoc.begin(PF_LOG_SPI | PF_LOG_NET);
}

void loop() {
  Serial.println("*****************************************");
  float duration, distance, duration2, distance2, duration3, distance3, duration4, distance4, duration5, distance5;

  // �����ĸ� ������. �� ������ echo�� HIGH ���·� ����ϰ� �ȴ�.-1
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  // echoPin �� HIGH�� ������ �ð��� ���� �Ѵ�.
  duration = pulseIn(echoPin, HIGH); 
  // HIGH ���� �� �ð�(�����İ� ���´ٰ� �ٽ� ���� �ð�)�� ������ �Ÿ��� ��� �Ѵ�.
  distance = ((float)(340 * duration) / 10000) / 2;  

  // �����ĸ� ������. �� ������ echo�� HIGH ���·� ����ϰ� �ȴ�.-2
  digitalWrite(trigPin2, HIGH);
  delay(10);
  digitalWrite(trigPin2, LOW);
  // echoPin �� HIGH�� ������ �ð��� ���� �Ѵ�.
  duration2 = pulseIn(echoPin2, HIGH); 
  // HIGH ���� �� �ð�(�����İ� ���´ٰ� �ٽ� ���� �ð�)�� ������ �Ÿ��� ��� �Ѵ�.
  distance2 = ((float)(340 * duration2) / 10000) / 2;

  // �����ĸ� ������. �� ������ echo�� HIGH ���·� ����ϰ� �ȴ�.-3
  /*digitalWrite(trigPin3, LOW);
  delay(2);
  digitalWrite(trigPin3, HIGH);
  delay(5);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  // echoPin �� HIGH�� ������ �ð��� ���� �Ѵ�.
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
  // HIGH ���� �� �ð�(�����İ� ���´ٰ� �ٽ� ���� �ð�)�� ������ �Ÿ��� ��� �Ѵ�.
  

  // �����ĸ� ������. �� ������ echo�� HIGH ���·� ����ϰ� �ȴ�.-4
  digitalWrite(trigPin4, LOW);
  delay(2);
  digitalWrite(trigPin4, HIGH);
  delay(5);
  digitalWrite(trigPin4, LOW);
  duration4 = pulseIn(echoPin4, HIGH);
  // echoPin �� HIGH�� ������ �ð��� ���� �Ѵ�.
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
  // HIGH ���� �� �ð�(�����İ� ���´ٰ� �ٽ� ���� �ð�)�� ������ �Ÿ��� ��� �Ѵ�.

  // �����ĸ� ������. �� ������ echo�� HIGH ���·� ����ϰ� �ȴ�.-5
  digitalWrite(trigPin5, LOW);
  delay(2);
  digitalWrite(trigPin5, HIGH);
  delay(5);
  digitalWrite(trigPin5, LOW);
  duration5 = pulseIn(echoPin5, HIGH);
  // echoPin �� HIGH�� ������ �ð��� ���� �Ѵ�.
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

  // HIGH ���� �� �ð�(�����İ� ���´ٰ� �ٽ� ���� �ð�)�� ������ �Ÿ��� ��� �Ѵ�. 
  
  Serial.print("������1 �Ÿ� : ");
  Serial.print(distance);
  Serial.println("cm");
  Serial.print("������2 �Ÿ� : ");
  Serial.print(distance2);
  Serial.println("cm");
  /*Serial.print("������3 �Ÿ� : ");
  Serial.print(distance3);
  Serial.println("cm");
  Serial.print("������4 �Ÿ� : ");
  Serial.print(distance4);
  Serial.println("cm");
  Serial.print("������5 �Ÿ� : ");
  Serial.print(distance5);
  Serial.println("cm");*/
  
  Serial.println(analogRead(A0));  // Serial monitor�� A0���� ������
  delay(100);                       // �Է°��� �����ִµ� 0.1�� ����
  
  // ������ ���� ���
  delay(500);
  if(f1 == 0){
    if(distance<15)
    {
      //preTime1 = millis();
      Serial.println("1��ĭ ��� ��");
      if(ultra_f1 == 0){
        no = 1;
        b = 0;
        sendToUseServer(no, b);
        ultra_f1 = 1;
        //digitalWrite(relay,HIGH); //������ ��� Off
        //delay(200);
      }
    }
    else
    { 
      //time1 = millis();
      //Serial.print("1��ĭ ��� �ð�");
      //Serial.println(time1 - preTime1);
      if(ultra_f1 == 1){
        Serial.println("���� �� ������");
        //digitalWrite(relay,LOW); //������ ��� On
        //delay(10000);
        
        ultra_f1 = 0;
        no = 1;
        b = 1;
        sendToUseServer(no, b);
        Serial.println("1��ĭ ��� ����");
        time1 = 0;
      }
    }
  }

  if(f2 == 0){
    if(distance2<15)
    {
      //preTime2 = millis();
      Serial.println("2��ĭ ��� ��");
      if(ultra_f2 == 0){
        no = 2;
        b = 0;
        sendToUseServer(no, b);
        ultra_f2 = 1;
        //digitalWrite(relay,HIGH); //������ ��� Off
        //delay(200);
      }
    }
    else
    { 
      //time2 = millis();
      //Serial.print("2��ĭ ��� �ð�");
      //Serial.println(time2 - preTime2);
      if(ultra_f2 == 1){
        //digitalWrite(relay,LOW); //������ ��� On
        //delay(5000);
        
        ultra_f2 = 0;
        no = 2;
        b = 1;
        sendToUseServer(no, b);
        Serial.println("2��ĭ ��� ����");
      }
    }
  }

  /*if(f3 == 0){
    if(distance3<15)
    {
      //preTime3 = millis();
      Serial.println("3��ĭ ��� ��");
      if(ultra_f3 == 0){
        no = 3;
        b = 0;
        sendToUseServer(no, b);
        ultra_f3 = 1;
        //digitalWrite(relay,HIGH); //������ ��� Off
        //delay(200);
      }
    }
    else
    { 
      //time3 = millis();
      //Serial.print("3��ĭ ��� �ð�");
      //Serial.println(time3 - preTime3);
      if(ultra_f3 == 1){
        //digitalWrite(relay,LOW); //������ ��� On
        //delay(5000);
        
        ultra_f3 = 0;
        no = 3;
        b = 1;
        sendToUseServer(no, b);
        Serial.println("3��ĭ ��� ����");
      }
    }
  }

  if(f4 == 0){
    if(distance4<15)
    {
      //preTime4 = millis();
      Serial.println("4��ĭ ��� ��");
      if(ultra_f4 == 0){
        no = 4;
        b = 0;
        sendToUseServer(no, b);
        ultra_f4 = 1;
        //digitalWrite(relay,HIGH); //������ ��� Off
        //delay(200);
      }
    }
    else
    { 
      //time4 = millis();
      //Serial.print("4��ĭ ��� �ð�");
      //Serial.println(time4 - preTime4);
      if(ultra_f4 == 1){
        //digitalWrite(relay,LOW); //������ ��� On
        //delay(5000);
        
        ultra_f4 = 0;
        no = 4;
        b = 1;
        sendToUseServer(no, b);
        Serial.println("4��ĭ ��� ����");
      }
    }
  }

  if(f5 == 0){
    if(distance5<15)
    {
      //preTime5 = millis();
      Serial.println("5��ĭ ��� ��");
      if(ultra_f5 == 0){
        no = 5;
        b = 0;
        sendToUseServer(no, b);
        ultra_f5 = 1;
        //digitalWrite(relay,HIGH); //������ ��� Off
        //delay(200);
      }
    }
    else
    { 
      //time5 = millis();
      Serial.print("5��ĭ ��� �ð�");
      Serial.println(time5 - preTime5);
      if(ultra_f5 == 1){
        //digitalWrite(relay,LOW); //������ ��� On
        //delay(5000);
        
        ultra_f5 = 0;
        no = 5;
        b = 1;
        sendToUseServer(no, b);
        Serial.println("5��ĭ ��� ����");
      }
    }
  }*/

  if(analogRead(A0) < 300) // ��������, A0�� 300 ���ϸ� ���Ⱑ ������ ������.
  { 
    if(f1 == 1){
      sendToBlockServer(1, 1);
      f1 = 0;
    }
    delay(100);
    Serial.println("���Ⱑ �����Դϴ�.");
  }
    
  else if(analogRead(A0) >300 ) // ��������, A0�� 300�̻��̸� ���Ⱑ ������.
  { 
    if(f1 == 0){
      sendToBlockServer(1, 0);
      f1 = 1;
    }
    delay(100);
    Serial.println("���Ⱑ �������ϴ�.");
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