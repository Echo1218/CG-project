#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <QDebug>
#include <QMouseEvent>
#include "graphs.h"

class Ellipse:public Graphs
{
public:
    int x0,y0,rx,ry;
    Ellipse();
    Ellipse(int id,int x0,int y0,int rx,int ry);
    void drawellipse(QPixmap &tempix,QPixmap &pix,QPen &pen,int x0,int y0,int rx,int ry);
    void translate(int x,int y);
    void rotate(int x, int y, int r);
    void scale(int x, int y, float s);
};

#endif // ELLIPSE_H
