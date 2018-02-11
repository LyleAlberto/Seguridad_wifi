#include <ESP8266WiFi.h>
#include <ArduinoJson.h>


const char* ssid = "214087118143";
const char* password = "789332411817";

const char* host = "34.212.125.15";
String key;
WiFiClient client;

void comunicacion()
{
  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    Serial.println("connected]");
    Serial.println("[Sending a request]");
    String request = String("GET /testproject/response.php?key=" + key) + " HTTP/1.1\r\n" +
                            "Host: " + host + "\r\n" +
                            "Connection: close\r\n" +
                            "\r\n";
    client.print(request);
    Serial.print(request);
    
    Serial.println("[Response:]");
    peticionKey();
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
}
void peticionKey()
{
  StaticJsonBuffer<200> jsonBuffer;
  while (client.connected())
    {
      if (client.available())
      {
        String response = client.readString();
        //Serial.println(line);    
        int index_first = response.lastIndexOf('{');
        int index_last = response.lastIndexOf('}');
        String stringJSON = response.substring(index_first, index_last + 1);

        const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
        DynamicJsonBuffer jsonBuffer(capacity);
      
        // Parse JSON object
        JsonObject& root = jsonBuffer.parseObject(stringJSON);
        if (!root.success()) {
          Serial.println(F("Parsing failed!"));
          //return;
        }
      
        // Extract values
        Serial.println(F("Response:"));
        Serial.println(root["key"].as<char*>());
        key=root["key"].as<char*>();
        Serial.println(key);
        //Serial.println(root["other"].as<char*>());
        //Serial.println(root["response"].as<char*>());
      
        // Disconnect
        client.stop();
      }
    } 
}


void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
  key="ABC";
}


void loop()
{
  if (Serial.available() > 0) 
  {
  int evento = Serial.read();
   if(evento == '5')
  {
    comunicacion();
  }
  }
  delay(500);
}
