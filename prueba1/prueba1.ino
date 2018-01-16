void setup()
   {  pinMode(BUILTIN_LED, OUTPUT); // Onboard LED
      Serial.begin(9600);
   }

void loop()
   { digitalWrite(BUILTIN_LED, HIGH);  // turn on LED with voltage HIGH
     delay(1000);                      // wait one second
     digitalWrite(BUILTIN_LED, LOW);   // turn off LED with voltage LOW
     delay(1000);                      // wait one second
     Serial.println(BUILTIN_LED);
   }
