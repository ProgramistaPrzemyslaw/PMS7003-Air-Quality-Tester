#include "header.h"
#include "graphs.h"

int Timer = 0;
int TimeInterval = 45000;
float PM1 = 0;
float PM25 = 0;
float PM10 = 0;
float Temperature = 0;
float Humidity = 0;
int sec = 0;
int minute = 0;
int hour = 0;
int sleepPin = 12;
int compensation = 0;
bool readyToRead = false;
bool readyToChangeTime = false;
float array[N][M];
int TimeArray[2][M];
float last24hAverage[N];

const char *ssid = "Air Quality Tester"; 
const char *password = "123456789";  

Adafruit_AHTX0 aht;
PMS pms(Serial);
PMS::DATA data;


void setup(){
    Serial.begin(9600);
    //Serial.println("Begin");
    pinMode(sleepPin, OUTPUT);
    digitalWrite(sleepPin,LOW);
    pms.passiveMode();

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
    server.on("/pm25", drawGraphPM25);
    server.on("/pm10", drawGraphPM10);
    server.on("/temperature",drawGraphTemperature);
    server.on("/settime",handleSetTime);
    server.on("/get",handleSetGet);
    server.begin();
} 

void loop(){

sec = (compensation+millis())/1000;
minute = sec/60;
hour = minute/60;

sensors_event_t hum, temp;

server.handleClient();

if(sec%30 == 0){
aht.getEvent(&hum, &temp);
Humidity = hum.relative_humidity;
Temperature = temp.temperature;
}

if(minute%2 == 0){
if(Temperature > -10 && Temperature <60){

if(!readyToRead){
digitalWrite(sleepPin,HIGH);
pms.wakeUp();
readyToRead = true;
Timer = millis()+TimeInterval;
}

if(readyToRead && millis()==Timer){
pms.requestRead();

if(pms.readUntil(data)){
PM10 = data.PM_AE_UG_10_0;
PM25 = data.PM_AE_UG_2_5;
PM1 = data.PM_AE_UG_1_0;
}

pms.sleep();
digitalWrite(sleepPin,LOW);
addToArray(Temperature, PM1, PM25, PM10);
addToTimeArray(hour,minute);
}

}else{
addToArray(Temperature, PM1, PM25, PM10);
addToTimeArray(hour,minute);
}

}else if(readyToRead){
  readyToRead = false;
}

if(minute%6==0){
calculateAverage();
}

//Serial.println(Humidity);
//Serial.println(Temperature);
//Serial.println("__________ ");

}