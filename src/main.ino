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

//PMGraph PM10Graph("PM10",PM10_index,800,450,8,M);
std::string title = "PM10 norm";
PMGraph _ZN7PMGraphD1Ev(title,PM10_index,1200,500,8,M);
std::string title1 = "PM25";
PMGraph _ZN7PMGraphD0Ev(title1,PM25_index,1200,500,8,M);
std::string title2= "Temperature";
PMGraph TempGraph(title2,0,1200,500,8,M);
void setup(){
    Serial.begin(9600);
    Serial.println("Begin");
    pinMode(sleepPin, OUTPUT);
    digitalWrite(sleepPin,LOW);
    pms.passiveMode();

    if(! aht.begin()){
        while(1) delay(10);
    }

    WiFi.softAP(ssid,password);

    IPAddress IP = WiFi.softAPIP();
    //Serial.print("AP IP address: ");
    //Serial.println(IP);

    server.on("/", handleRoot);
    server.on("/pm25",[](){
      server.send(200,"image/svg+xml",_ZN7PMGraphD0Ev.drawGraph().c_str());
    });
    server.on("/pm10",[](){
      server.send(200,"image/svg+xml",_ZN7PMGraphD1Ev.drawGraph().c_str());
    });
    //server.on("/temperature",drawGraphTemperature);
    server.on("/temperature",[](){
      server.send(200,"image/svg+xml",TempGraph.drawGraph().c_str());
    });
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
_ZN7PMGraphD1Ev.drawGraph();
_ZN7PMGraphD0Ev.drawGraph();
}

}else{
addToArray(Temperature, PM1, PM25, PM10);
addToTimeArray(hour,minute);
_ZN7PMGraphD1Ev.drawGraph();
_ZN7PMGraphD0Ev.drawGraph();
}

}else if(readyToRead){
  readyToRead = false;
}

if(minute%6==0){
calculateAverage();
}

}