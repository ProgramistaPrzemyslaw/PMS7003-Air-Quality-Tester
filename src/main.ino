#include "header.h"

Adafruit_AHTX0 aht;
PMS pms(Serial);
PMS::DATA data;

void setup(){
    Serial.begin(9600);
    Serial.println("Begin");
    if(! aht.begin()){
        Serial.println("AHT not found");
        while(1) delay(10);
    }
    Serial.println("AHT found");

}

void loop(){
sensors_event_t hum, temp;
aht.getEvent(&hum, &temp);
Humidity = hum.relative_humidity;
Temperature = temp.temperature;

Serial.println(Humidity);
Serial.println(Temperature);
Serial.println("__________ ");
delay(100);
}