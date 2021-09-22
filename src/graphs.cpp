#include "graphs.h"
#include "header.h"


PM10Graph::PM10Graph(int width, int heigth,int rows, int columns):
width_(width), heigth_(heigth),rows_(rows),colums_(columns){

x_margin_ = 50;
y_margin_ = 60;
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

std::string PM10Graph::addXLabel(int beginning, int end){
    char buf[1000];
    std::string temp;
    int spacing = 0;
    for(int i = 0; i< colums_; i++){
        if(i%2==0){
        sprintf(buf,"<text x=\"%d\" y=\"%d\" transform=\"rotate(45,%d,380)\">%02d:%02d</text>\n",
        x_margin_+spacing+5, heigth_-y_margin_, x_margin_+spacing+5, heigth_-y_margin_,
        TimeArray[0][i]%24,TimeArray[1][i]%60);
        spacing +=30;
        temp += buf;
    }
    }
    return temp;
}

std::string PM10Graph::addYLabel(int beginning, int end){
    char buf[1000];
    std::string temp;
    int spacing = pos_y;
    for(int i = 0; i<rows; i++){
    sprintf(buf,"<text x=\"%d\" y=\"%d\" style=\"alignment-baseline:hanging\">%d</text>\n",
    ,x_margin_-20 ,spacing+4, beginning+(end+beginning)/rows_);
    spacing += (heigth_-y_margin_-pos_y)/rows_;
    temp += buf;
  }
    return temp;
}