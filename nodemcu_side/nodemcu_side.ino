//nodemcu side
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>


SoftwareSerial s(D6,D5);
SoftwareSerial s2(D4,D3);

// Update these with values suitable for your network.
const char* ssid = "NikolaTesla";
const char* password = "123456778";
const char* mqtt_server = "192.168.43.47";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

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
  if (strcmp(topic,"majuw")==0) {
  s.write(1);
  delay(2);
  s2.write(i);
  Serial.println(i);
  yield();//prevent wdt reset or esp8266 crash in blocking code
  }
  
  else if (strcmp(topic,"mundurs")==0) {
  s.write(2);
  delay(2);
  s2.write(i);
  Serial.println(i);
  yield();//prevent wdt reset or esp8266 crash in blocking code
  }

  else if (strcmp(topic,"kiria")==0) {
  s.write(3);
  delay(2);
  s2.write(i);
  Serial.println(i);
  yield();//prevent wdt reset or esp8266 crash in blocking code
  }

  else if (strcmp(topic,"kanand")==0) {
  s.write(4);
  delay(2);
  s2.write(i);
  Serial.println(i);
  yield();//prevent wdt reset or esp8266 crash in blocking code
  }

  else if (strcmp(topic,"stopsss")==0) {
  s.write(5);
  delay(2);
  s2.write(i);
  Serial.println(i);
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
      client.subscribe("majuw");
      client.subscribe("mundurs");
      client.subscribe("kanand");
      client.subscribe("kiria");
      client.subscribe("stopsss");
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
  Serial.begin(9600);
  s.begin(115200);
  s2.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
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
