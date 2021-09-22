#include "graphs.h"
#include "header.h"


PM10Graph::PM10Graph(int width, int heigth,int rows, int columns):
width_(width), heigth_(heigth),rows_(rows),colums_(columns){
graph.reserve(10000);
margin_ = 50;
}

void PM10Graph::addHeader(){
    sprintf(graph,"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%d\" height=\"%d\">\n",width_,heigth_);
}

void PM10Graph::addRectangle(int posx, int posy){
    int heigth = heigth_ - posy - margin_;
    int width = width_ - posx - margin_;
    sprintf(graph,"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n",
    posx, posy, width, heigth );
}