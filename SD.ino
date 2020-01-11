#include <ESP8266WiFi.h>
#include <Adafruit_MQTT_Client.h>

#define wifi "Bleh bleh bluh bluh"
#define password "12345678"
#define server "io.adafruit.com"
#define port 1883
#define username "mpokuri74"
#define key "1e34b546c35e46559cbb4ecf0e1aba9e"
int TRIGGER = 5;
int ECHO = 4;

// NodeMCU Pin D1 > TRIGGER | Pin D2 > ECHO
 long duration;
  int distance;
WiFiClient esp;

Adafruit_MQTT_Client mqtt(&esp,server,port,username,key);
Adafruit_MQTT_Publish feed = Adafruit_MQTT_Publish(&mqtt,username"/feeds/sdb");

void setup()
{
   
  Serial.begin (115200);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  
  Serial.println("Adafruit MQTT demo");
  Serial.print("Connecting to ");
  Serial.println(wifi);

  WiFi.begin(wifi,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
     delay(500);
     Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Connecting to MQTT");

  while(mqtt.connect())
  {
    Serial.print(".");
  }

}

void loop()
{ 
  if(mqtt.connected())
  {  
     
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;
  
  Serial.print(distance);
  Serial.println("  cm");
 
    if(feed.publish(distance))
    {
      Serial.println("Success");
    }

    else
    {
      Serial.println("Fail!");
    }

    delay(800);
  }
}
