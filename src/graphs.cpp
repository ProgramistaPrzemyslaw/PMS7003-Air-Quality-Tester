#include "graphs.h"
#include "header.h"


PM10Graph::PM10Graph(int width, int heigth,int rows, int columns):
width_(width), heigth_(heigth),rows_(rows),colums_(columns){

margin_ = 50;
}

std::string PM10Graph::addHeader(){
    char buf[100];
    sprintf(buf,"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%d\" height=\"%d\">\n",width_,heigth_);
    return buf;
}

std::string PM10Graph::addRectangle(int posx, int posy){
    int heigth = heigth_ - posy - margin_;
    int width = width_ - posx - margin_;
    char buf[100];
    sprintf(buf,"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n",
    posx, posy, width, heigth );
    return buf;
}

std::string PM10Graph::addXTitle(std::string title){
    char buf[100];
    sprintf(buf,"<g class=\"headings x-heading\"><text x=\"50%\" y=\"%d\">%s</text></g>\n",
    heigth_-20,title);
    return buf;
}

std::string PM10Graph::addYTitle(std::string title){
    char buf[100];
    sprintf(buf,"<g class=\"headings y-heading\"><text x=\"%d\" y=\"%d\" transform=\"rotate(-90,%d,%d)\">%s</text></g>\n",
    15, heigth_-20, 15, heigth_-20, title);
    return buf;
}
