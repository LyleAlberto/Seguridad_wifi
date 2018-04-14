#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
//wifi direct

const char* ssid = "GABALAN";
const char* password = "51895677";

const char* host = "34.212.125.15";
String key;
String request={};
WiFiClient client;

int comunicacion(int n)
{ 
  String request={};
  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, 80))
  {
    Serial.println("connected]");
    Serial.println("[Sending a request]");
    
    switch (n) {
      case 1:
        request = String("GET /testproject/response.php?key=" + key) + " HTTP/1.1\r\n" +
                            "Host: " + host + "\r\n" +
                            "Connection: close\r\n" +
                            "\r\n";
        break;
      case 2:
        request = String("GET /response.php?key=" + key);/* + " HTTP/1.1\r\n" +
                            "Host: " + host + "\r\n" +
                            "Connection: close\r\n" +
                            "\r\n";*/ 
        break;
      default:
        // statements
        break;
    }
    
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
{ StaticJsonBuffer<200> jsonBuffer;  
  while (client.connected())
    {
      if (client.available())
      {
        String stado=client.readStringUntil('\n');
        int index_first1 = stado.indexOf('{');
        String stringresponse = stado.substring(0 , index_first1);
        int OKstring = stringresponse.indexOf(String(200));
        

        if(OKstring>-1)
        {
          Serial.println("si existe OK");
        
        //char A=stado1[10];
        /*for(int i=10;i<13;i=i++)
        {char A=stado[i];}*/
        //Serial.println(A);
            
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
      else
      {
        Serial.println("Error");
        Serial.println(client.readStringUntil('\n'));
      }
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
  //funcion cada vez q haga una conexion reinicie el token parametro obligatorio key, tiempo time 
  //milware key action 
}

void loop()
{
  if (Serial.available() > 0) 
  {
  int evento = Serial.read();
   if(evento == '1')
  {
    comunicacion(1);
  }
  if(evento == '2')
  {
    comunicacion(2);
  }
  }
  delay(500);
}
