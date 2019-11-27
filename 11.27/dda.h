#ifndef DDA_H
#define DDA_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <QDebug>
#include <QMouseEvent>
#include "graphs.h"

class DDA:public Graphs
{
public:
    int x0,y0,x1,y1;
    DDA();
    DDA(int id,int x0,int y0,int x1,int y1);
    void ddaline(QPixmap &tempix,QPixmap &pix,QPen &pen,int x0,int y0,int x1,int y1);
    void translate(int x,int y);
    void C_Sclip(int clipx0,int clipy0,int clipx1,int clipy1);
};

#endif // DDA_H
