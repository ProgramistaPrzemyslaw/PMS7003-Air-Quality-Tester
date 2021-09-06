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
    <h2>Temperature:%.2f</h2>\
    <h2>Humidity:%.2f</h2>\
      </body>\
</html>",   

          Temperature, Humidity
    );
    server.send(200, "text/html", page);
}