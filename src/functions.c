
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
    <img src=\"/pm25\" />\
    <img src=\"/pm10\" />\
    <img src=\"/temperature\" />\
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


void drawGraphPM10(){
  String out;
  out.reserve(6600);
  int rows = 9;
  int spacing=0;
  char temp[100];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"800\" height=\"450\">\n";
  
  out += "<rect x=\"60\" width=\"705\" height=\"400\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g class=\"axis-lines\">\n";
  for(int i = 0; i<rows; i++){
    sprintf(temp,"<line x1=\"60\" x2=\"765\" y1=\"%d\" y2=\"%d\" stroke=\"black\"></line>\n",spacing,spacing);
    out += temp;
    spacing += 50;
  }
  out += "</g>\n";
  spacing = 0;
  out += "<g class=\"labels y-labels\">\n";

  for(int i = 0; i<rows; i++){
    sprintf(temp,"<text x=\"30\" y=\"%d\" style=\"alignment-baseline:hanging\">%d</text>\n",spacing,800-2*spacing);
    spacing += 50;
    out += temp;
  }
  out += "</g>\n";

  out += "<g class=\"labels x-labels\">\n";
  spacing = 0;
  for(int i = 0; i<24; i++){

    sprintf(temp,"<text x=\"%d\" y=\"420\">%d</text>\n",50+spacing,i);
    spacing += 30;
    out += temp;
  }
  
  out += "</g>\n";
  out += "<g class=\"headings x-heading\"><text x=\"50%\" y=\"450\">Time</text></g>\n";
  out += "<g class=\"headings y-heading\"><text x=\"15\" y=\"250\" transform=\"rotate(-90,15,250)\">PM 10 norm (%)</text></g>";
  out += "<polyline class=\"graphline\" points=\"";
  int a = 100;
  for(int i = 0; i<M; i++){
    sprintf(temp,"%d,%d ",60+15*i,400-(int)array[3][i]);
    out += temp;
  }
  out +="\" fill=\"none\" stroke=\"green\" stroke-width=\"5\"/>\n";
  out += "</svg>\n";
  server.send(200, "image/svg+xml", out);
}


void drawGraphPM25(){
  String out;
  out.reserve(6600);
  int rows = 9;
  int spacing=0;
  char temp[100];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"800\" height=\"450\">\n";
  out += "<rect x=\"60\" width=\"705\" height=\"400\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  
   out += "<g class=\"axis-lines\">\n";
  for(int i = 0; i<rows; i++){
    sprintf(temp,"<line x1=\"60\" x2=\"765\" y1=\"%d\" y2=\"%d\" stroke=\"black\"></line>\n",spacing,spacing);
    out += temp;
    spacing += 50;
  }
  out += "</g>\n";
  spacing = 0;
  out += "<g class=\"labels y-labels\">\n";
  for(int i = 0; i<rows; i++){
    sprintf(temp,"<text x=\"30\" y=\"%d\" style=\"alignment-baseline:hanging\">%d</text>\n",spacing,800-2*spacing);
    spacing += 50;
    out += temp;
  }
  out += "</g>\n";

  out += "<g class=\"labels x-labels\">\n";
  spacing = 0;
  for(int i = 0; i<24; i++){

    sprintf(temp,"<text x=\"%d\" y=\"420\">%d</text>\n",50+spacing,i);
    spacing += 30;
    out += temp;
  }
  
  out += "</g>\n";
  out += "<g class=\"headings x-heading\"><text x=\"50%\" y=\"450\">Time</text></g>\n";
  out += "<g class=\"headings y-heading\"><text x=\"15\" y=\"250\" transform=\"rotate(-90,15,250)\">PM 2.5 norm (%)</text></g>";
  out += "<polyline class=\"graphline\" points=\"";
  int a = 100;
  for(int i = 0; i<M; i++){
    sprintf(temp,"%d,%d ",60+15*i,400-(int)(array[2][i]*2));
    out += temp;
  }
  out +="\" fill=\"none\" stroke=\"green\" stroke-width=\"5\"/>\n";
  out += "</svg>\n";
  server.send(200, "image/svg+xml", out);
}

void drawGraphTemperature(){
  String out;
  out.reserve(6600);
  int rows = 8;
  int spacing=0;
  int temperature[] ={-30,-20,-10,0,10,20,30,40}; 
  char temp[100];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"800\" height=\"400\">\n";
  out += "<rect x=\"60\" width=\"705\" height=\"350\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";

  out += "<g class=\"axis-lines\">\n";
  for(int i = 0; i<rows; i++){
    sprintf(temp,"<line x1=\"60\" x2=\"765\" y1=\"%d\" y2=\"%d\" stroke=\"black\"></line>\n",spacing,spacing);
    out += temp;
    spacing += 50;
  }
  out += "</g>\n";
  out += "<g class=\"labels y-labels\">\n";
  spacing=0;
  for(int i = 0; i<rows; i++){
    sprintf(temp,"<text x=\"30\" y=\"%d\" style=\"alignment-baseline:hanging\">%d</text>\n",spacing,temperature[rows-1-i]);
    spacing += 50;
    out += temp;
  }
  out += "</g>\n";

  out += "<g class=\"labels x-labels\">\n";
  spacing = 0;

  for(int i = 0; i<24; i++){
    sprintf(temp,"<text x=\"%d\" y=\"370\">%d</text>\n",60+spacing,i);
    spacing += 30;
    out += temp;
  }
  
  out += "</g>\n";
  out += "<g class=\"headings x-heading\"><text x=\"50%\" y=\"400\">Time</text></g>\n";
  out += "<g class=\"headings y-heading\"><text x=\"15\" y=\"235\" transform=\"rotate(-90,15,235)\">Temperature(C)</text></g>";
  out += "<polyline class=\"graphline\" points=\"";
  int a = 100;
  for(int i = 0; i<M; i++){
    sprintf(temp,"%d,%d ",60+15*i,200-(int)(array[0][i]*5));
    out += temp;
  }
  out +="\" fill=\"none\" stroke=\"green\" stroke-width=\"5\"/>\n";
  out += "</svg>\n";
  server.send(200, "image/svg+xml", out);
}


