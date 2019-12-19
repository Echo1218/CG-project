#ifndef DRAWBYCOMMANDS_H
#define DRAWBYCOMMANDS_H
#include <QString>
#include <QPen>
#include "qpainter.h"
#include <QDebug>
#include "dda.h"
#include "bresenham.h"
#include "ellipse.h"
#include <QStringList>
#include <QFile>
#include <QColor>
#include <vector>
#include "graphs.h"
#include "polygon.h"
#include "bezier.h"
#include "bspline.h"

using namespace std;

class DrawByCommands
{
public:
    DrawByCommands(QString a,QString b);
    void readfile();
    void cmdresolver(QString cmd);
    QString cmdfile;
    QString savepath;
    QPixmap pix;
    QPen pen;
    QColor color;
    vector<Graphs*> graphs;
    vector<int>graphindex;
    QFile file;
    int canvasx,canvasy;

};

#endif // DRAWBYCOMMANDS_H
