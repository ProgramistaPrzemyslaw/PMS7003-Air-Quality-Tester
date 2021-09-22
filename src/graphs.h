#pragma once

class Graph
{
private:
public:
    Graph(int heigth, int width);
    virtual void drawGraph() = 0;
    virtual void addHeader() = 0;
    virtual void addXLabel() = 0;
    virtual void addYLabel() = 0;
    virtual void addXTitle() = 0;
    virtual void addYTitle() = 0;
    virtual void addAxisLine(int numberOfLines) = 0;
    virtual void addPlot() = 0;
    virtual void addRectangle(int posx, int posy) = 0;
    virtual ~Graph();
};

class PM10Graph: public Graph{
    private:
    int width_;
    int heigth_;
    int rows_;
    int colums_;
    String graph;
    public:
    PM10Graph(int width, int heigth,int rows, int columns);
     void drawGraph();
     void addHeader();
     void addXLabel();
     void addYLabel();
     void addXTitle();
     void addYTitle();
     void addAxisLine(int numberOfLines);
     void addPlot();
     void addRectangle(int posx, int posy);
    ~PM10Graph();
};

