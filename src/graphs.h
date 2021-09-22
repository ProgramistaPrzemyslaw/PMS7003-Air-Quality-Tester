#pragma once

class Graph
{
private:
    /* data */
public:
    Graph(int heigth, int width);
    void drawGraph();
    ~Graph();
};


class Label{
    private:
    public:
    Label();
    void addXLabel();
    void addYLabel();
    ~Label();
};

class Title{
    private:
    public:
    Title();
    void addXTitle();
    void addYTitle();
    ~Title();
};

class Lines{
    private:
    public:
    Lines();
    void addAxisLine(int numberOfLines);
    void addPlot();
    ~Lines();
};

class Rectangle{
    private:
    public:
    Rectangle();
    void addRectangle(int posx, int posy, int heigth, int width);
    ~Rectangle();
};


