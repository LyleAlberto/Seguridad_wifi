#include <ESP8266WiFi.h>

int ledPin = BUILTIN_LED;
WiFiServer server(80);
WiFiClient client;

//void conexionred(id,pass)
//{
  
//}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP("ESPsoftAP_01", "pass-to-soft-AP");
  if(result == true)
  {
    Serial.println("Ready");
  }
  else
  {
    Serial.println("Failed!");
  }

  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
    
  server.begin();
  Serial.println("Server started");
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop()
{
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("id") && request.indexOf("pass") != -1) {
    int pos=request.indexOf("id");
      if(request.indexOf("=")!= -1){
      int pos1=request.indexOf("=");
        if(request.indexOf("&")!= -1){
        int pos2=request.indexOf("&");     
     String stringresponse = request.substring(pos1+1 , pos2);
     char id[stringresponse.length()];
     stringresponse.toCharArray(id, stringresponse.length()+1);
     Serial.println(stringresponse);
     if(request.indexOf("&&")!= -1){
      int pos1=request.indexOf("&&");
      String stringresponse = request.substring(pos1+2 , request.length());
      if(stringresponse.indexOf("=")!= -1){
      int pos1=stringresponse.indexOf("=");
      String stringresponse1 = stringresponse.substring(pos1+1 , request.length());  
      Serial.println(stringresponse1);
              
              char pass[stringresponse1.length()];
              stringresponse1.toCharArray(pass, stringresponse1.length());
            Serial.println(id);Serial.println(pass);
            WiFi.begin(id , pass);
            while (WiFi.status() != WL_CONNECTED)
            {
              delay(500);
              Serial.print(".");
            }
            Serial.println(" wifi connected");
              digitalWrite(ledPin, HIGH);
              value = HIGH;
    } 
    }  
    }
    }
    }
    //conexionred(stringresponse,stringresponse1);
    


    Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}
