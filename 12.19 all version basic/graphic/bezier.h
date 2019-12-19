#ifndef BEZIER_H
#define BEZIER_H
#include "graphs.h"
#include <vector>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <QDebug>
#include <QMouseEvent>
#include "bresenham.h"
#include "dda.h"

class Bezier:public Graphs
{
public:
    int ctrlnum;
    vector<int> ctrlpoints;
    Bezier(vector<int>a);
    Bezier();
    QPixmap pix;
    QPen pen;
    Bresenham bre;
    void drawcurve(QPixmap &tempix,QPixmap &pix,QPen &pen);
    void drawpoints(vector<double> ctrlp);
    void translate(int x,int y);
    void rotate(int x, int y, int r);
    void scale(int x, int y, float s);
};

#endif // BEZIER_H
