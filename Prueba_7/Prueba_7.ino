/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

const char* host = "data.sparkfun.com";
const char* streamId   = "....................";
const char* privateKey = "....................";
int ledPin = BUILTIN_LED;
WiFiServer server(80);
boolean alreadyConnected = false; // whether or not the client was connected previously

void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  boolean result = WiFi.softAP("ESPsoftAP_01", "pass-to-soft-AP");
  if (result == true) {
    Serial.println("Ready");
  } else {
    Serial.println("Failed!");
  }
  Serial.println("Server started");
}

void loop() {

  server.begin();
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("id") && request.indexOf("pass") != -1) {
    int pos = request.indexOf("id");
    if (request.indexOf("=") != -1) {
      int pos1 = request.indexOf("=");
      if (request.indexOf("&") != -1) {
        int pos2 = request.indexOf("&");     
        String stringresponse = request.substring(pos1+1 , pos2);
        char id[stringresponse.length()];
        stringresponse.toCharArray(id, stringresponse.length()+1);
        Serial.println(stringresponse);
        if (request.indexOf("&&") != -1) {
          int pos1 = request.indexOf("&&");
          String stringresponse = request.substring(pos1+2 , request.length());
          if (stringresponse.indexOf("=") != -1) {
            int pos1 = stringresponse.indexOf("=");
            String stringresponse1 = stringresponse.substring(pos1+1 , request.length());  
            Serial.println(stringresponse1);
          
            char pass[stringresponse1.length()];
            stringresponse1.toCharArray(pass, stringresponse1.length()-8);
            //server.close();
            //WiFi.softAPdisconnect();
            if (!alreadyConnected) {
              wificonnect(id,pass);
              alreadyConnected = true;
            }
                
            digitalWrite(ledPin, HIGH);
            value = HIGH;
          } 
        }  
      }
    }
  }

  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}

void wificonnect(const char* ssid, const char* password) {
  Serial.print(ssid);
  Serial.println(password);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(WiFi.status());
    Serial.println(WL_DISCONNECTED);
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  //Serial.println(WiFi.localIP());
  
}
