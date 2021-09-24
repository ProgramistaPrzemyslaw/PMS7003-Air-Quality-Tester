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
    pos_x_ = posx;
    pos_y_ = posy;
    int heigth = heigth_ - posy - y_margin_;
    int width = width_ - posx - x_margin_;
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
    std::string temp = "<g class=\"labels x-labels\">\n";
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
    temp += "</g>\n";
    return temp;
}

std::string PM10Graph::addYLabel(int beginning, int end){
    char buf[1000];
    std::string temp = "<g class=\"labels y-labels\">\n";
    int spacing = pos_y_;
    for(int i = 0; i<rows_; i++){
    sprintf(buf,"<text x=\"%d\" y=\"%d\" style=\"alignment-baseline:hanging\">%d</text>\n",
    x_margin_-20 ,spacing+4, beginning+(end+beginning)/rows_);
    spacing += (heigth_-y_margin_-pos_y_)/rows_;
    temp += buf;
  }
    
    return temp;
}

std::string PM10Graph::addAxisLines(std::string axis){
    char buf[100];
    std::string temp;
    
    if(axis == "y"||axis == "Y"){
        int spacing = pos_y_;
        temp = "<g class=\"axis-lines\">\n";
        for(int i = 0; i<rows_; i++){

        sprintf(buf,"line x1=\"%d\" x2=\"%d\" y1=\"%d\" y2=\"%d\" stroke=\"black\"></line>\n",
        pos_x_, width_-pos_x_, spacing, spacing);
        spacing += (heigth_ - pos_y_ - y_margin_)/rows_;
        temp += buf;
        }
        temp += "</g>\n";
    }else if(axis == "x"||axis == "X"){
        int spacing = pos_x_;
        temp = "<g class=\"axis-lines\">\n";
        for(int i = 0; i<colums_; i++){

        sprintf(buf,"line x1=\"%d\" x2=\"%d\" y1=\"%d\" y2=\"%d\" stroke=\"black\"></line>\n",
        spacing, spacing, pos_y_, heigth_-pos_y_);
        spacing += (width_ - pos_x_ - x_margin_)/colums_;
        temp += buf;
        }
        temp += "</g>\n";
    }
    return temp;
}

std::string PM10Graph::addPlot(){
    char buf[100];
    std::string temp = "<polyline class=\"graphline\" points=\"";
    int spacing = (width_ - pos_x_ - x_margin_)/M;
    for(int i = 0; i<M;i++){
        sprintf(buf,"%d,%d ",
        x_margin_+spacing*i, heigth_+pos_y_-(int)(array[2][i]*2));
        temp += buf;
    }
    temp += "\" fill=\"none\" stroke=\"green\" stroke-width=\"2\"/>\n";
    return temp;
}

std::string PM10Graph::endGraph(){
    return "</svg>\n";
}