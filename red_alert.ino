#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "OnePlus KJS"; // Enter your WiFi name
const char *password = "kexo1234";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "/fromesp32";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

int outled = 5;
int inpin = 18;
String var;

void setup() {
  // put your setup code here, to run once:
  pinMode(outled, OUTPUT);
  pinMode(inpin,INPUT_PULLUP);
  //pinMode(13, OUTPUT);
  Serial.begin(9600);

   WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");
 //connecting to a mqtt broker
 client.setServer(mqtt_broker, mqtt_port);
 client.setCallback(callback);
 while (!client.connected()) {
     String client_id = "Nikhil124";
     client_id += String(WiFi.macAddress());
     Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
     if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
         Serial.println("Public emqx mqtt broker connected");
     } else {
         Serial.print("failed with state ");
         Serial.print(client.state());
         delay(2000);
     }
 }
 // publish and subscribe

 }

void callback(char *topic, byte *payload, unsigned int length) 
{
 Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 for (int i = 0; i < length; i++) {
     Serial.print((char) payload[i]);
 }
 Serial.println();
 Serial.println("-----------------------");
}

void loop() {
  // put your main code here, to run repeatedly:
  client.loop();
   if (digitalRead(inpin)== HIGH)
  { 
    client.publish(topic,"2,15.392238006063275,73.88035041026777,Lid ALert ON");
    //client.publish(topic,"");
    client.subscribe(topic);
  }
  else
  {
    client.publish(topic,"0,15.392238006063275,73.88035041026777,All is Well");
    client.subscribe(topic);
  }
 delay(3000);
}
