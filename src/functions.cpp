#include "header.h"

ESP8266WebServer server(80);

//Remember not to have empty lines as spacing


void handleRoot(){
    char page[2000];

    snprintf(page,2000,

    "<html>\
  <head>\
    <meta name=\"viewport\" http-equiv='refresh' content='60' content=\"width=device-width, initial-scale=1\">\
    <link rel=\"icon\" href=\"data:,\">\
    <title>Air Quality Tester</title>\
    <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
      .button { background-color: #0000c9; border: none; color: white; padding: 2px 4px;text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\
    </style>\
  </head>\
  <body>\
    <h1>Air Quality Tester</h1>\
    <h2>%02d:%02d:%02d</h2>\
    <h2>Temperature:%.2f C</h2>\
    <h2>Humidity:%.2f%% </h2>\
    <h2>PM 1.0: %.2f ug/m3</h2>\
    <h2>PM 2.5: %.2f ug/m3; %.2f%%</h2>\
    <h2>PM 10: %.2f ug/m3; %.2f%%</h2>\
    <h1>Last 24h Average Values</h1>\
    <h2>T=%.2f C, PM1=%.2f ug/m3</h2>\
    <h2>PM2.5=%.2f%%, PM10=%.2f%%</h2>\
    <img src=\"/pm25\" />\
    <img src=\"/pm10\" />\
    <img src=\"/temperature\" />\
    <p><a href=\"/settime\"><button class=\"button\">Set Time</button></a></p>\
      </body>\
</html>",   

          hour%24, minute%60, sec%60, Temperature, Humidity,
           PM1, PM25, PM25/25*100, PM10, PM10/50*100,
          last24hAverage[0], last24hAverage[1], last24hAverage[2], last24hAverage[3]
    );
    readyToChangeTime = false;
    server.send(200, "text/html", page);
}
//<p><a href=\"/settime\" class=\"btn btn-default btn-sm\" role=\"button\">Set Time</a></p>\

void handleSetTime(){
  char page[1000];

  sprintf(page,
  "<html>\
  <head>\
    <meta name=\"viewport\" http-equiv='refresh' content='60' content=\"width=device-width, initial-scale=1\">\
    <link rel=\"icon\" href=\"data:,\">\
    <title>Air Quality Tester</title>\
    <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
      .button { background-color: #0000c9; border: none; color: white; padding: 10px 20px;text-decoration: none; font-size: 40px; margin: 2px; cursor: pointer;}\
    </style>\
  </head>\
  <body>\
  <h2>Set Time (format 24h hh:mm)</h2>\
  <h1>Current Time: %02d:%02d:%02d</h1>\
  <form action=\"/get\">\
  <input type=\"text\" maxlength=\"5\" size=\"4\" name=\"time\" value=\"hh:mm\"><br>\
  <input type=\"submit\" size=\"4\" value=\"Set\">\
  </form>\
  <p> </p>\
  <p> </p>\
  <p> </p>\
  <p> </p>\
  <p><a href=\"/\"><button class=\"button\">Back to main page</button></a></p>\
      </body>\
</html>", hour%24, minute%60, sec%60
);
readyToChangeTime = true;
server.send(200, "text/html", page);
}

void handleSetGet(){
    char page[1000];
  sprintf(page,
  "<html>\
  <head>\
    <meta name=\"viewport\" http-equiv='refresh' content='60' content=\"width=device-width, initial-scale=1\">\
    <link rel=\"icon\" href=\"data:,\">\
    <title>Air Quality Tester</title>\
    <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
      .button { background-color: #40ff00; border: none; color: white; padding: 2px 4px;text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}\
    </style>\
  </head>\
  <body>\
  <h2>Current Time: %02d:%02d:%02d</h2>\
  <p><a href=\"/\"><button class=\"button\">Back to main page</button></a></p>\
      </body>\
</html>", hour%24, minute%60, sec%60
);
if(readyToChangeTime){
String header = server.arg("time");
String hourString = header.substring(0,2);
String minuteString = header.substring(3,5);
int hour = hourString.toInt();
int minute = minuteString.toInt();
compensation = compensatedMillis(hour,minute);
readyToChangeTime = false;
}
server.send(200, "text/html", page);

}

void addToTimeArray(int hour, int minute){
int tempHour[M];
int tempMinute[M];
for(int i=0;i<M-1;i++){
tempHour[i+1] = TimeArray[0][i];
tempMinute[i+1] = TimeArray[1][i];
}
tempHour[0] = hour;
tempMinute[0] = minute;
for(int i=0;i<M-1;i++){
TimeArray[0][i] = tempHour[i];
TimeArray[1][i] = tempMinute[i];
}

}

void addToArray(float Temperature, float PM1, float PM25, float PM10){

float tempTemp[M];
float tempPM1[M];
float tempPM25[M];
float tempPM10[M];

for(int i=0;i<M-1;i++){
tempTemp[i+1] = array[0][i];
tempPM1[i+1] = array[1][i];
tempPM25[i+1] = array[2][i];
tempPM10[i+1] = array[3][i];
}
tempTemp[0] = Temperature;
tempPM1[0] = PM1;
tempPM25[0] = PM25/25*100;
tempPM10[0] = PM10/50*100;

for(int i=0;i<M;i++){
array[0][i]=tempTemp[i];
array[1][i]=tempPM1[i];
array[2][i]=tempPM25[i];
array[3][i]=tempPM10[i];
}

}

void calculateAverage(){
  for(int i = 0; i<N; i++){
    for(int j = 0; j<M; j++){
      last24hAverage[i] += array[i][j]; 
    }
    last24hAverage[i] /= M;
  }
}


void drawGraphTemperature(){
  String out;
  out.reserve(6600);
  int rows = 8;
  int spacing=10;
  int temperature[] ={-30,-20,-10,0,10,20,30,40}; 
  char temp[100];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"800\" height=\"450\">\n";
  out += "<rect x=\"60\" y=\"10\" width=\"705\" height=\"350\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";

  out += "<g class=\"axis-lines\">\n";
  for(int i = 0; i<rows; i++){
    sprintf(temp,"<line x1=\"60\" x2=\"765\" y1=\"%d\" y2=\"%d\" stroke=\"black\"></line>\n",spacing,spacing);
    out += temp;
    spacing += 50;
  }
  spacing = 60;
  for(int i = 0; i<M; i++){
    sprintf(temp,"<line x1=\"%d\" x2=\"%d\" y1=\"10\" y2=\"360\" stroke=\"black\"></line>\n",spacing,spacing);
    out += temp;
    spacing += 15;
  }

  out += "</g>\n";
  out += "<g class=\"labels y-labels\">\n";
  spacing=0;
  for(int i = 0; i<rows; i++){
    sprintf(temp,"<text x=\"30\" y=\"%d\" style=\"alignment-baseline:hanging\">%d</text>\n",spacing+4,temperature[rows-1-i]);
    spacing += 50;
    out += temp;
  }
  out += "</g>\n";

  out += "<g class=\"labels x-labels\">\n";
  spacing = 0;

  for(int i = 0; i<M; i++){
    if(i%2==0){
    sprintf(temp,"<text x=\"%d\" y=\"380\" transform=\"rotate(45,%d,380)\">%02d:%02d</text>\n",55+spacing, 55+spacing,TimeArray[0][i]%24,TimeArray[1][i]%60);
    spacing +=30;
    out += temp;
    }
  }
  
  out += "</g>\n";
  out += "<g class=\"headings x-heading\"><text x=\"50%\" y=\"440\">Time</text></g>\n";
  out += "<g class=\"headings y-heading\"><text x=\"15\" y=\"235\" transform=\"rotate(-90,15,235)\">Temperature(C)</text></g>";
  out += "<polyline class=\"graphline\" points=\"";
  for(int i = 0; i<M; i++){
    sprintf(temp,"%d,%d ",60+15*i,210-(int)(array[0][i]*5));
    out += temp;
  }
  out +="\" fill=\"none\" stroke=\"green\" stroke-width=\"2\"/>\n";
  out += "</svg>\n";
  server.send(200, "image/svg+xml", out);
}

int compensatedMillis(int hour, int minute){
  return (hour*60*60*1000+minute*60*1000 - millis());
}

int getMaxValue(int index){
  int maxValue = 0;
  for(int i = 0; i<M; i++){
    int temp = (int)array[index][i];

    if(maxValue<temp)
    maxValue = temp;

  }
  return maxValue;
}