#pragma once

class Graph
{
private:
    /* data */
public:
    Graph(int heigth, int width);
    virtual void addRectangle(int posx, int posy, int heigth, int width);
    virtual void addAxisLine(int numberOfLines);
    virtual void addPlot();
    virtual void addXLabel();
    virtual void addYLabel();
    virtual void addXTitle();
    virtual void addYTitle();
    virtual void drawGraph();
    ~Graph();
};

class PM10_Graph: public Graph{
    private:
    public:
};

class PM25_Graph: public Graph{
    private:
    public:
};

class Temperature_Graph: public Graph{
    private:
    public:
};

