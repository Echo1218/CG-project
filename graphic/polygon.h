#ifndef POLYGON_H
#define POLYGON_H
#include "graphs.h"
#include <vector>
#include "dda.h"
#include "bresenham.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <QDebug>
#include <QMouseEvent>
using namespace std;

class Polygon:public Graphs
{
public:
    vector<int> polygonpoints;
    int algo;
    int pointsnum;
    Polygon();
    Polygon(int id,int p);
    void drawpoly(QPixmap &tempix,QPixmap &pix,QPen &pen);
};

#endif // POLYGON_H
