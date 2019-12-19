#ifndef BSPLINE_H
#define BSPLINE_H
#include "graphs.h"
#include <vector>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <QDebug>
#include <QMouseEvent>
#include "bresenham.h"
#include "dda.h"


class Bspline:public Graphs
{
public:
    Bspline();
    Bspline(vector<int>a);
    int ctrlnum;
    vector<int> ctrlpoints;
    vector<int> curvepoints;
    QPixmap pix;
    QPen pen;
    Bresenham bre;
    double B(int i,int k,double u);
    void drawcurve(QPixmap &tempix,QPixmap &pix,QPen &pen);
    void translate(int x,int y);
    void rotate(int x, int y, int r);
    void scale(int x, int y, float s);
};

#endif // BSPLINE_H
