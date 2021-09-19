#include "header.h"

void drawGraph(){
  String out;
  out.reserve(6600);
  int rows = 9;
  int spacing=0;
  char temp[100];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"800\" height=\"450\">\n";
  out += "<rect x=\"60\" width=\"705\" height=\"400\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
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
  out += "<g class=\"headings y-heading\"><text x=\"15\" y=\"200\" transform=\"rotate(-90,15,200)\">PM 10</text></g>";
  out += "<polyline class=\"graphline\" points=\"";
  int a = 100;
  for(int i = 0; i<M; i++){
    sprintf(temp,"%d,%d ",60+15*i,400-(int)array[2][i]*10);
    out += temp;
  }
  out +="\" fill=\"none\" stroke=\"green\" stroke-width=\"5\"/>\n";
  out += "</svg>\n";
  server.send(200, "image/svg+xml", out);
}