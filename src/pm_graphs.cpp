#include "graphs.h"




PMGraph::PMGraph(std::string title,int PM , int width, int heigth,int rows, int columns):
title_(title), PM_(PM), width_(width), heigth_(heigth),rows_(rows),colums_(columns){

x_margin_ = 0;
y_margin_ = 80;
}

std::string PMGraph::addHeader(){
    char buf[100];
    sprintf(buf,"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%d\" height=\"%d\">\n",width_,heigth_);
    return buf;
}

std::string PMGraph::addRectangle(int posx, int posy){
    pos_x_ = posx;
    pos_y_ = posy;
    rectHeight_ = rows_*((heigth_ - posy - y_margin_)/rows_);
    //int heigth = heigth_ - posy - y_margin_ - compensation;
//-1 down
    x_margin_ = width_-pos_x_-(colums_-1)*((width_-pos_x_)/(colums_-1));
    rectWidth_ =(colums_-1)*((width_-pos_x_)/(colums_-1));
    char buf[200];
    sprintf(buf,"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n",
    posx, posy, rectWidth_, rectHeight_);
    return buf;
}

std::string PMGraph::addXTitle(){
    char buf[200];
    sprintf(buf,"<g class=\"headings x-heading\"><text x=\"%d\" y=\"%d\">Time</text></g>\n",
    (width_-pos_x_)/2, heigth_-20);
    return buf;
}

std::string PMGraph::addYTitle(){
    char buf[200];
    sprintf(buf,"<g class=\"headings y-heading\"><text x=\"%d\" y=\"%d\" transform=\"rotate(-90,%d,%d)\">%s</text></g>\n",
    15, heigth_/2,
    15, heigth_/2,
    title_.c_str());
    return buf;
}

std::string PMGraph::addXLabel(){
    char buf[1000];
    std::string temp = "<g class=\"labels x-labels\">\n";
    int spacing = 0;
    for(int i = 0; i< colums_; i++){
        if(i%2==0){
        sprintf(buf,"<text x=\"%d\" y=\"%d\" transform=\"rotate(45,%d,%d)\">%02d:%02d</text>\n",
        pos_x_+spacing-5, rectHeight_+2*pos_y_,
        pos_x_+spacing-5, rectHeight_+2*pos_y_,
        TimeArray[0][i]%24,TimeArray[1][i]%60);
        spacing += 2*(rectWidth_)/(colums_-1);
        temp += buf;
    }
    }
    temp += "</g>\n";
    return temp;
}

std::string PMGraph::addYLabel(float beginning, float end){
    char buf[1000];
    std::string temp = "<g class=\"labels y-labels\">\n";
    int spacing = pos_y_;
    maxValue_ = (int)end;
    for(int i = rows_; i>=0; i--){
    sprintf(buf,"<text x=\"%d\" y=\"%d\" style=\"alignment-baseline:hanging\">%.1f%%</text>\n",
    pos_x_-40 ,spacing-4, beginning+((float)i/(float)rows_)*end);
    spacing += (heigth_-y_margin_-pos_y_)/rows_;
    temp += buf;
  }
    temp += "</g>\n";
    return temp;
}

std::string PMGraph::addAxisLines(std::string axis){
    char buf[100];
    std::string temp;
    
    if(axis == "y"||axis == "Y"){
        int spacing = pos_y_;
        temp = "<g class=\"axis-lines\">\n";
        for(int i = 0; i<rows_; i++){

        sprintf(buf,"<line x1=\"%d\" x2=\"%d\" y1=\"%d\" y2=\"%d\" stroke=\"black\"></line>\n",
        pos_x_, rectWidth_+pos_x_, spacing, spacing);
        spacing += rectHeight_/rows_;
        temp += buf;
        }
        temp += "</g>\n";
    }else if(axis == "x"||axis == "X"){
        int spacing = pos_x_;
        temp = "<g class=\"axis-lines\">\n";
        for(int i = 0; i<colums_; i++){

        sprintf(buf,"<line x1=\"%d\" x2=\"%d\" y1=\"%d\" y2=\"%d\" stroke=\"black\"></line>\n",
        spacing, spacing, pos_y_, rectHeight_+pos_y_);
        spacing += (rectWidth_)/(colums_-1);
        temp += buf;
        }
        temp += "</g>\n";
    }
    return temp;
}

std::string PMGraph::addPlot(){
    char buf[100];
    std::string temp = "<polyline class=\"graphline\" points=\"";
    int spacing = rectWidth_/(colums_-1);
    if(maxValue_ !=0 ){
    for(int i = 0; i<colums_;i++){
        sprintf(buf,"%d,%d ",
        pos_x_+spacing*i, rectHeight_+pos_y_-(int)(array[PM_][i]*(rectHeight_/maxValue_)));
        temp += buf;
    }
    }else if(maxValue_ == 0){
      for(int i = 0; i<colums_;i++){
        sprintf(buf,"%d,%d ",
        pos_x_+spacing*i, rectHeight_+pos_y_-(int)(array[PM_][i]));
        temp += buf;
    }  
    }
    
    temp += "\" fill=\"none\" stroke=\"green\" stroke-width=\"2\"/>\n";
    return temp;
}

std::string PMGraph::endGraph(){
    return "</svg>\n";
}

std::string PMGraph::drawGraph(){
    std::string graph;
    String page;
    graph += addHeader();
    graph += addRectangle(70,10);
    graph += addYLabel(0,getMaxValue(PM_));
    graph += addAxisLines("y");
    graph += addAxisLines("x");
    graph += addXLabel();
    graph += addYTitle();
    graph += addXTitle();
    graph += addPlot();
    graph += endGraph();
    return graph;
}
