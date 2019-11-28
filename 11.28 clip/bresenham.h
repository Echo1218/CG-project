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
    void C_Sclip(int clipx0,int clipy0,int clipx1,int clipy1);
    void L_Bclip(int clipx0,int clipy0,int clipx1,int clipy1);
    int L_Btest(int p,int q,double &u1,double &u2);
};

#endif // BRESENHAM_H
