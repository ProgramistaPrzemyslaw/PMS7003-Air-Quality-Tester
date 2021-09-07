#include "header.h"

const char *ssid = "Air Quality Tester"; 
const char *password = "123456789";  

Adafruit_AHTX0 aht;
PMS pms(Serial);
PMS::DATA data;


void setup(){
    Serial.begin(9600);
    //Serial.println("Begin");
    
    if(! aht.begin()){
      //  Serial.println("AHT not found");
        while(1) delay(10);
    }
    //Serial.println("AHT found");

    WiFi.softAP(ssid,password);

    IPAddress IP = WiFi.softAPIP();
    //Serial.print("AP IP address: ");
    //Serial.println(IP);

    server.on("/", handleRoot);
    server.begin();
} 

void loop(){
sensors_event_t hum, temp;
server.handleClient();
aht.getEvent(&hum, &temp);
Humidity = hum.relative_humidity;
Temperature = temp.temperature;
if(pms.read(data)){
PM10 = data.PM_AE_UG_10_0;
PM25 = data.PM_AE_UG_2_5;
PM1 = data.PM_AE_UG_1_0;
}
//Serial.println(Humidity);
//Serial.println(Temperature);
//Serial.println("__________ ");
delay(100);
}