#ifndef BRESENHAM_H
#define BRESENHAM_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <QDebug>
#include <QMouseEvent>
#include "graphs.h"

class Bresenham:public Graphs
{
public:
    int x0,y0,x1,y1;
    Bresenham();
    Bresenham(int id,int x0,int y0,int x1,int y1);
    void breline(QPixmap &tempix,QPixmap &pix,QPen &pen,int x0,int y0,int x1,int y1);
    void translate(int x,int y);
};

#endif // BRESENHAM_H
