#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "am2320.h"
#include <Wire.h>

const char* ssid = "...";
const char* password = "...";

const char* host = "klima.justjakob.de";
const char* tag = "klima04";

TwoWire wire;
AM2320 sensor = AM2320(wire);

void setup() {
  wire.begin(SDA, SCL);
  sensor.begin();

  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  sensor.read();
  float humidity = sensor.getHumidity();
  float temperature = sensor.getTemperature();

  Serial.print("temp: ");
  Serial.println(temperature);
  Serial.print("humidity: ");
  Serial.println(humidity);

  WiFiClient client;
  if (!client.connect(host, 80)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/api/klima";
  Serial.print("requesting URL: ");
  Serial.println(url);

  String postData = String("{\"host\":\"") + tag + "\"," +
                    "\"temperature\":" + temperature + "," +
                    "\"humidity\":" + humidity + "}";

  Serial.println(postData);

  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266WifiClient\r\n" +
               "Content-Type: application/json\r\n" +
               "Content-Length: ");
  client.print (postData.length());
  client.print("\r\nConnection: close\r\n\r\n");
  client.print(postData);
  
  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  client.stop();


  Serial.println("going to deep sleep...");

  ESP.deepSleep(30 * 1e6);
  //delay(30000);
}
