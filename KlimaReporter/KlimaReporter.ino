#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

/*
 *  HTTP over TLS (HTTPS) example sketch
 *
 *  This example demonstrates how to use
 *  WiFiClientSecure class to access HTTPS API.
 *  We fetch and display the status of
 *  esp8266/Arduino project continuous integration
 *  build.
 *
 *  Created by Ivan Grokhotkov, 2015.
 *  This example is in public domain.
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>

const char* ssid = "...";
const char* password = "...";

const char* host = "klima.justjakob.de";
const char* tag = "klima01";

#define DHT_PIN D2
#define DHT_TYPE DHT22
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  dht.begin();

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

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

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
}

void loop() {
}
