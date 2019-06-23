//nodemcu side
//#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>


//SoftwareSerial s(D2,D1);

// Update these with values suitable for your network.
const char* ssid = "NikolaTesla";
const char* password = "123456778";
const char* mqtt_server = "192.168.43.47";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int pinServo1 = 15; //D8
int pinServo2 = 13; //D7
int pinServo3 = 12; //D6
int pinServo4 = 14; //D5
int pinServo5 = 2; //D4
int pinServo6 = 0; //D3
/* define L298N or L293D motor control pins */


Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

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

 //adjuster servo
 if (strcmp(topic,"ak1")==0) {
    servo1.write(i);
//  for (int i = 0; i < length; i++) {
//    s.write((char)payload[i]);
//  }
//  s.write("13");
 yield();//prevent wdt reset or esp8266 crash in blocking code
  }

   else if (strcmp(topic,"aka1")==0) {
    servo2.write(i);
//  for (int i = 0; i < length; i++) {
//    s.write((char)payload[i]);
//  }
//  s.write("13");
 yield();//prevent wdt reset or esp8266 crash in blocking code
  }

   else if (strcmp(topic,"ada")==0) {
    servo3.write(i);
//  for (int i = 0; i < length; i++) {
//    s.write((char)payload[i]);
//  }
//  s.write("13");
 yield();//prevent wdt reset or esp8266 crash in blocking code
  }

//grip
  else if (strcmp(topic,"capitki")==0){
    if(i == 1)
     servo4.write(90);
     else if(i == 0)  servo4.write(25);
     yield();//prevent wdt reset or esp8266 crash in blocking code
    }

    else if (strcmp(topic,"capitka")==0){
    if(i == 1)
     servo5.write(90);
     else if(i == 0)  servo5.write(25);
     yield();//prevent wdt reset or esp8266 crash in blocking code
    }

    else if (strcmp(topic,"capitda")==0){
    if(i == 1)
     servo6.write(90);
     else if(i == 0)  servo6.write(25);
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
      client.subscribe("ak1");
      client.subscribe("aka1");
      client.subscribe("ada");
      client.subscribe("capitki");
      client.subscribe("capitka");
      client.subscribe("capitda");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



void setup() {
  Serial.begin(115200);
//  s.begin(115200);
//  s2.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);


  //servo
  servo1.attach(pinServo1);
  servo2.attach(pinServo2);
  servo3.attach(pinServo3);
  servo4.attach(pinServo4);
  servo5.attach(pinServo5);
  servo6.attach(pinServo6);
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
