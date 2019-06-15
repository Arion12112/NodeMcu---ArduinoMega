//nodemcu side
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>


SoftwareSerial s(D2,D1);

// Update these with values suitable for your network.
const char* ssid = "NikolaTesla";
const char* password = "123456778";
const char* mqtt_server = "iot.eclipse.org";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
/* define L298N or L293D motor control pins */
int leftMotorForward = 2;     /* GPIO2(D4) -> IN3   */
int rightMotorForward = 15;   /* GPIO15(D8) -> IN1  */
int leftMotorBackward = 0;    /* GPIO0(D3) -> IN4   */
int rightMotorBackward = 13;  /* GPIO13(D7) -> IN2  */


/* define L298N or L293D enable pins */
int rightMotorENB = 14; /* GPIO14(D5) -> Motor-A Enable */
int leftMotorENB = 12;  /* GPIO12(D6) -> Motor-B Enable */

void setup_wifi() { 

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

//mengubah payload menjadi int
  payload[length] = '\0';
  String a = String((char*)payload);
  int i= a.toInt();

   //posisi servo1
  if (strcmp(topic,"majuww")==0) {
  MotorForward();
//  for (int i = 0; i < length; i++) {
//    s.write((char)payload[i]);
  }
//  s.write("10");//hash untuk dimodulo, kode: 10 = maju, 11= mundur, 12= kiri, 13=kanan, 14= stop
//  yield();//prevent wdt reset or esp8266 crash in blocking code
//  }

  else if (strcmp(topic,"mundurss")==0) {
    MotorBackward(); 
//  for (int i = 0; i < length; i++) {
//    s.write((char)payload[i]);
//  }
//  s.write("11");
//  yield();//prevent wdt reset or esp8266 crash in blocking code
  }

  else if (strcmp(topic,"kiriaa")==0) {
   TurnLeft();  
//  for (int i = 0; i < length; i++) {
//    s.write((char)payload[i]);
//  }
//  s.write("12");
//  yield();//prevent wdt reset or esp8266 crash in blocking code
  }

  else if (strcmp(topic,"kanandd")==0) {
     TurnRight();
//  for (int i = 0; i < length; i++) {
//    s.write((char)payload[i]);
//  }
//  s.write("13");
//  yield();//prevent wdt reset or esp8266 crash in blocking code
  }

  
  else if (strcmp(topic,"diag1")==0) {
     Diag1();
//  for (int i = 0; i < length; i++) {
//    s.write((char)payload[i]);
//  }
//  s.write("13");
//  yield();//prevent wdt reset or esp8266 crash in blocking code
  }

  else if (strcmp(topic,"diag2")==0) {
     Diag2();
//  for (int i = 0; i < length; i++) {
//    s.write((char)payload[i]);
//  }
//  s.write("13");
//  yield();//prevent wdt reset or esp8266 crash in blocking code
  }

  else if (strcmp(topic,"diag3")==0) {
     Diag3();
//  for (int i = 0; i < length; i++) {
//    s.write((char)payload[i]);
//  }
//  s.write("13");
//  yield();//prevent wdt reset or esp8266 crash in blocking code
  }

  else if (strcmp(topic,"diag4")==0) {
     Diag4();
//  for (int i = 0; i < length; i++) {
//    s.write((char)payload[i]);
//  }
//  s.write("13");
//  yield();//prevent wdt reset or esp8266 crash in blocking code
  }

  else if (strcmp(topic,"stopss")==0) {
     MotorStop();
//  for (int i = 0; i < length; i++) {
//    s.write((char)payload[i]);
//  }
//  s.write("14");
//  yield();//prevent wdt reset or esp8266 crash in blocking code
  }
  
  else if (strcmp(topic,"servobar1")==0) {
     
  for (int i = 0; i < length; i++) {
    s.write((char)payload[i]);
  }
  s.write("15");
  yield();//prevent wdt reset or esp8266 crash in blocking code
  }

  else if (strcmp(topic,"servobar2")==0) {
     
  for (int i = 0; i < length; i++) {
    s.write((char)payload[i]);
  }
  s.write("16");
  yield();//prevent wdt reset or esp8266 crash in blocking code
  }

  else if (strcmp(topic,"servobar3")==0) {
     
  for (int i = 0; i < length; i++) {
    s.write((char)payload[i]);
  }
  s.write("17");
  yield();//prevent wdt reset or esp8266 crash in blocking code
  }

  else if (strcmp(topic,"grip")==0) {
     
  for (int i = 0; i < length; i++) {
    s.write((char)payload[i]);
  }
  s.write("13");
  yield();//prevent wdt reset or esp8266 crash in blocking code
  }
  else if (strcmp(topic,"cutter")==0) {
     
  for (int i = 0; i < length; i++) {
    s.write((char)payload[i]);
  }
  s.write("11");
  yield();//prevent wdt reset or esp8266 crash in blocking code
  }
  else if (strcmp(topic,"defarmpos")==0) {
     
  for (int i = 0; i < length; i++) {
    s.write((char)payload[i]);
  }
  s.write("12");
  yield();//prevent wdt reset or esp8266 crash in blocking code
  }
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("majuww");
      client.subscribe("mundurss");
      client.subscribe("kanandd");
      client.subscribe("kiriaa");
      client.subscribe("stopss");
      client.subscribe("servobar1");
      client.subscribe("servobar2");
      client.subscribe("servobar3");
      client.subscribe("grip");
      client.subscribe("cutter");
      client.subscribe("defarmpos");
      client.subscribe("diag1");
      client.subscribe("diag2");
      client.subscribe("diag3");
      client.subscribe("diag4");    
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
      MotorStop();
    }
  }
}



void setup() {
  Serial.begin(115200);
  s.begin(115200);
//  s2.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  /* initialize motor control pins as output */
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT); 
  pinMode(leftMotorBackward, OUTPUT);  
  pinMode(rightMotorBackward, OUTPUT);

  /* initialize motor enable pins as output */
  pinMode(leftMotorENB, OUTPUT); 
  pinMode(rightMotorENB, OUTPUT);
}
 
void loop() {
if (!client.connected()) {
    reconnect();
  }
  client.loop();
//int data=50;
//if(s.read()=='s')
//{
// s.write(data);
//}
}

void MotorForward(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}

/********************************************* BACKWARD *****************************************************/
void MotorBackward(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorBackward,HIGH);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,LOW);
}

/********************************************* TURN LEFT *****************************************************/
void TurnLeft(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH); 
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,HIGH);  
}

/********************************************* TURN RIGHT *****************************************************/
void TurnRight(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
}

void Diag1(void)
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,LOW);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,LOW);
}

void Diag2(void)
{ 
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,LOW);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,HIGH);
}

void Diag3(void)
{
  digitalWrite(leftMotorENB,LOW);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
}

void Diag4(void)
{ 
  digitalWrite(leftMotorENB,LOW);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,LOW);
}



/********************************************* STOP *****************************************************/
void MotorStop(void)   
{
  digitalWrite(leftMotorENB,LOW);
  digitalWrite(rightMotorENB,LOW);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}
