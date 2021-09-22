#include "graphs.h"
#include "header.h"


PM10Graph::PM10Graph(int width, int heigth,int rows, int columns):
width_(width), heigth_(heigth),rows_(rows),colums_(columns){
graph.reserve(10000);
}

void PM10Graph::addHeader(){
    sprintf(graph,"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%d\" height=\"%d\">\n",width_,heigth_);
}