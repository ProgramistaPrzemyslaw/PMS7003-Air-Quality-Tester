#pragma once
#include <string>

class Graph
{
private:
public:
    Graph(int heigth, int width);
    virtual void drawGraph() = 0;
    virtual std::string addHeader() = 0;
    virtual std::string addXLabel() = 0;
    virtual std::string addYLabel() = 0;
    virtual std::string addXTitle() = 0;
    virtual std::string addYTitle() = 0;
    virtual std::string addAxisLine(int numberOfLines) = 0;
    virtual std::string addPlot() = 0;
    virtual std::string addRectangle(int posx, int posy) = 0;
    virtual ~Graph();
};

class PM10Graph: public Graph{
    private:
    int width_;
    int heigth_;
    int rows_;
    int colums_;
    int margin_;
    String graph;
    public:
    PM10Graph(int width, int heigth,int rows, int columns);
     void drawGraph();
     std::string addHeader();
     std::string addXLabel();
     std::string addYLabel();
     std::string addXTitle();
     std::string addYTitle();
     std::string addAxisLine(int numberOfLines);
     std::string addPlot();
     std::string addRectangle(int posx, int posy);
    ~PM10Graph();
};

