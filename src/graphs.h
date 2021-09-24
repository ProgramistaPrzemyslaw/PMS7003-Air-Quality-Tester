#pragma once
#include <string>

class Graph
{
private:
public:
    virtual void drawGraph() = 0;
    virtual std::string addHeader() = 0;
    virtual std::string addXLabel(int beginning, int end) = 0;
    virtual std::string addYLabel(int beginning, int end) = 0;
    virtual std::string addXTitle(std::string title) = 0;
    virtual std::string addYTitle(std::string title) = 0;
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
    int x_margin_;
    int y_margin_;
    int pos_x_;
    int pos_y_;
    std::string graph_;
    public:
    PM10Graph(int width, int heigth,int rows, int columns);
     void drawGraph();
     std::string addHeader();
     std::string addXLabel(int beginning, int end);
     std::string addYLabel(int beginning, int end);
     std::string addXTitle(std::string title);
     std::string addYTitle(std::string title);
     std::string addAxisLines(std::string axis);
     std::string addPlot();
     std::string addRectangle(int posx, int posy);
     std::string endGraph();
    ~PM10Graph();
};

