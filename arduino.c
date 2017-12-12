#include <ArduinoJson.h>
#include <SPI.h>
#include <Phpoc.h>

char server_name[] = "192.168.0.4"; //raspberry server IP
PhpocClient client;
String jsondata = " ";

//������ ������ �ɹ�ȣ�� �����Ѵ�.
int echoPin = 12; //������1
int trigPin = 13;//������1
int echoPin2 = 6; //������2
int trigPin2 = 7;//������2
int echoPin3 = 30;//������3
int trigPin3 = 31;//������3
int echoPin4 = 32;//������4
int trigPin4 = 33;//������4
int echoPin5 = 34;//������5
int trigPin5 = 35;//������5
int relay = 10;//������
int water_pin = A0;      //���м������� A0�� ����
int f1 = 0, f2 = 0, f3 = 0, f4 = 0, f5 = 0;

void setup() {
  Serial.begin(9600);
  // trig�� ��¸��� ����, echo�� �Է¸��� ����
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
  pinMode( A0,  INPUT); // A0���� �Է����� ����
  Serial.println("PHPoC TCP Client test");
  Phpoc.begin(PF_LOG_SPI | PF_LOG_NET);
}

void loop() {
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
  digitalWrite(trigPin3, HIGH);
  delay(10);
  digitalWrite(trigPin3, LOW);
  // echoPin �� HIGH�� ������ �ð��� ���� �Ѵ�.
  duration3 = pulseIn(echoPin3, HIGH);
  // HIGH ���� �� �ð�(�����İ� ���´ٰ� �ٽ� ���� �ð�)�� ������ �Ÿ��� ��� �Ѵ�.
  distance3 = ((float)(340 * duration3) / 10000) / 2;

  // �����ĸ� ������. �� ������ echo�� HIGH ���·� ����ϰ� �ȴ�.-4
  digitalWrite(trigPin4, HIGH);
  delay(10);
  digitalWrite(trigPin4, LOW);
  // echoPin �� HIGH�� ������ �ð��� ���� �Ѵ�.
  duration4 = pulseIn(echoPin4, HIGH); 
  // HIGH ���� �� �ð�(�����İ� ���´ٰ� �ٽ� ���� �ð�)�� ������ �Ÿ��� ��� �Ѵ�.
  distance4 = ((float)(340 * duration4) / 10000) / 2;  

  // �����ĸ� ������. �� ������ echo�� HIGH ���·� ����ϰ� �ȴ�.-5
  digitalWrite(trigPin5, HIGH);
  delay(10);
  digitalWrite(trigPin5, LOW);
  // echoPin �� HIGH�� ������ �ð��� ���� �Ѵ�.
  duration5 = pulseIn(echoPin5, HIGH); 
  // HIGH ���� �� �ð�(�����İ� ���´ٰ� �ٽ� ���� �ð�)�� ������ �Ÿ��� ��� �Ѵ�.
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
  
  Serial.println(analogRead(A0));  // Serial monitor�� A0���� ������
  delay(100);                       // �Է°��� �����ִµ� 0.1�� ����
  
  // ������ ���� ���
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

  if(analogRead(A0) < 300) // ��������, A0�� 300 ���ϸ� ���Ⱑ ������ ������.
  { 
    if(f1 == 1){
      sendToBlockServer(5, 1);
      f1 = 0;
    }
    delay(100);
    Serial.println("���Ⱑ �����Դϴ�.");
  }
    
  else if(analogRead(A0) >300 ) // ��������, A0�� 300�̻��̸� ���Ⱑ ������.
  { 
    if(f1 == 0){
      sendToBlockServer(5, 0);
      f1 = 1;
    }
    delay(100);
    Serial.println("���Ⱑ �������ϴ�.");
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