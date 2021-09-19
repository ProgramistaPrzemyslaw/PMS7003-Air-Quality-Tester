
#include "header.h"

ESP8266WebServer server(80);

//Remember not to have empty lines as spacing
void handleRoot(){
    char page[1000];

    snprintf(page,1000,

    "<html>\
  <head>\
    <meta name=\"viewport\" http-equiv='refresh' content='5' content=\"width=device-width, initial-scale=1\">\
    <link rel=\"icon\" href=\"data:,\">\
    <title>Air Quality Tester</title>\
    <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Air Quality Tester</h1>\
    <h2>Temperature:%.2f C</h2>\
    <h2>Humidity:%.2f%% </h2>\
    <h2>PM 1.0: %.2f ug/m3</h2>\
    <h2>PM 2.5: %.2f ug/m3; %.2f%%</h2>\
    <h2>PM 10: %.2f ug/m3; %.2f%%</h2>\
    <h2>Time elapsed since turned on</h2>\ 
    <h2>%02d:%02d:%02d</h2>\
    <h1>Last 24h Average Values</h1>\
    <h2>T=%.2f C, PM1=%.2f ug/m3</h2>\
    <h2>PM2.5=%.2f%%, PM10=%.2f%%</h2>\
    <img src=\"/test\" />\
      </body>\
</html>",   

          Temperature, Humidity, PM1, PM25, PM25/25*100, PM10, PM10/50*100,
          hour%24, minute%60, sec%60,
          last24hAverage[0], last24hAverage[1], last24hAverage[2], last24hAverage[3]
    );
    server.send(200, "text/html", page);
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
tempPM25[0] = PM25*25/100;
tempPM10[0] = PM10*50/100;

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


void drawGraph(){
  String out;
  out.reserve(6600);
  int columns = 9;
  int y1=0;
  char temp[100];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"780\" height=\"450\">\n";
  out += "<rect x=\"60\" width=\"720\" height=\"400\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"black\">\n";
  int y = rand() % 130;
  for (int x = 10; x < 390; x += 10) {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x+50, 140 - y, x+50 + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += "</g>\n";

  out += "<g class=\"labels y-labels\">\n";

  for(int i = 0; i<columns; i++){
    sprintf(temp,"<text x=\"30\" y=\"%d\" style=\"alignment-baseline:hanging\">%d</text>\n",y1,800-2*y1);
    y1 += 50;
    out += temp;
  }
  out += "</g>\n";

  out += "<g class=\"labels x-labels\"><text x=\"50\" y=\"420\">0</text><text x=\"770\" y=\"420\">24</text></g>\n";
  out += "<g class=\"headings x-heading\"><text x=\"50%\" y=\"450\">Time</text></g>\n";
  out += "<g class=\"headings y-heading\"><text x=\"15\" y=\"200\" transform=\"rotate(-90,15,200)\">PM 10</text></g>";
  out += "</svg>\n";
  server.send(200, "image/svg+xml", out);
}