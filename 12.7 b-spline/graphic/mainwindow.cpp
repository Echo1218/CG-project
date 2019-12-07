#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <QDebug>
#include <QMouseEvent>
#include "dda.h"
#include "bresenham.h"
#include "ellipse.h"
#include "polygon.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    draw_type=0;
    ui->setupUi(this);
    setWindowTitle(tr("My Paint"));
    this->resize(QSize(1200,900));
    pix = QPixmap(1200, 900);
    tempix=QPixmap(1200,900);
    pix.fill(Qt::white);
    tempix.fill(Qt::white);
    pen.setColor(Qt::black);



}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if(event->button()==Qt::LeftButton)
    {   QPoint startpoint=event->pos();;
        if(draw_type==1||draw_type==2||draw_type==3)
        {
            startpoint=event->pos();
            x0=startpoint.x();
            y0=startpoint.y();
            start=1;
            end=0;

        }
        else if(draw_type==4||draw_type==5)
        {
            start=1;
            end=0;
            startpoint=event->pos();

            if(polystart==0)
            {
                polystart=1;
                polyp.clear();
                polyp.push_back(startpoint.x());
                polyp.push_back(startpoint.y());
                polynum=0;

            }
            else{
                if(draw_type==4){
                    DDA dda;
                    dda.ddaline(tempix,pix,pen,polyp[polynum*2],polyp[polynum*2+1],startpoint.x(),startpoint.y());
                    update();
                }
                else{
                    Bresenham bre;
                    bre.breline(tempix,pix,pen,polyp[polynum*2],polyp[polynum*2+1],startpoint.x(),startpoint.y());
                    update();
                }
            }
        }

    }


}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{   QPoint midpoint=event->pos();
    if(event->buttons()&Qt::LeftButton){
        if(draw_type==1||draw_type==2)
        {
            midpoint=event->pos();

            {
               x1=midpoint.x();
               y1=midpoint.y();
               //qDebug()<<x1<<" "<<y1;
            }
            if(draw_type==1) {DDA dda;dda.ddaline(tempix,pix,pen,x0,y0,x1,y1);}
            else if(draw_type==2){
                Bresenham bre;bre.breline(tempix,pix,pen,x0,y0,x1,y1);
            }

            update();
        }
        else if(draw_type==3)
        {
           midpoint=event->pos();

           rx=(midpoint.x()-x0)/2;
           ry=(midpoint.y()-y0)/2;
           int absrx=abs(rx);
           int absry=abs(ry);

           Ellipse ell;ell.drawellipse(tempix,pix,pen,x0+rx,y0+ry,absrx,absry);
               //qDebug()<<x1<<" "<<y1;

            update();
        }
        else if(draw_type==4)
        {
            midpoint=event->pos();
            DDA dda;
            dda.ddaline(tempix,pix,pen,polyp[polynum*2],polyp[polynum*2+1],midpoint.x(),midpoint.y());
            update();
        }
        else if(draw_type==5)
        {
            midpoint=event->pos();
            Bresenham bre;
            bre.breline(tempix,pix,pen,polyp[polynum*2],polyp[polynum*2+1],midpoint.x(),midpoint.y());
            update();
        }
    }

}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{   QPoint endpoint=event->pos();

        if(event->button()==Qt::LeftButton)
        {   end=1;
            endpoint=event->pos();
        }
        if(draw_type==1) {
            x1=endpoint.x();
            y1=endpoint.y();
            DDA dda;dda.ddaline(tempix,pix,pen,x0,y0,x1,y1);}
        else if(draw_type==2){
            x1=endpoint.x();
            y1=endpoint.y();
            Bresenham bre;bre.breline(tempix,pix,pen,x0,y0,x1,y1);
        }
        else if(draw_type==3)
        {   rx=(endpoint.x()-x0)/2;
            ry=(endpoint.y()-y0)/2;
            int absrx=abs(rx);
            int absry=abs(ry);

            Ellipse ell;ell.drawellipse(tempix,pix,pen,x0+rx,y0+ry,absrx,absry);
        }
        else if(draw_type==4)
        {
            polyp.push_back(endpoint.x());
            polyp.push_back(endpoint.y());
            DDA dda;
            dda.ddaline(tempix,pix,pen,polyp[polynum*2],polyp[polynum*2+1],polyp[polynum*2+2],polyp[polynum*2+3]);
            polynum++;
        }
        else if(draw_type==5)
        {
            polyp.push_back(endpoint.x());
            polyp.push_back(endpoint.y());
            Bresenham bre;
            bre.breline(tempix,pix,pen,polyp[polynum*2],polyp[polynum*2+1],polyp[polynum*2+2],polyp[polynum*2+3]);
            polynum++;
        }
        update();
        x1=0;y1=0;start=0;

}
void MainWindow::paintEvent(QPaintEvent *e)
{

        QPainter Painter1(this);
        //Painter1.end();
        //Painter1.begin(this);

          if(end==0)
              Painter1.drawPixmap(0,0,tempix);
          else{
              //QPainter pp(&pix);
              //pp.drawPixmap(0,0, tempix);
              pix=tempix;

              //Painter1.end();
              //Painter1.begin(this);
              Painter1.drawPixmap(0,0,pix);
          }

}



void MainWindow::on_actionred_triggered()
{
    pen.setColor(Qt::red);
}

void MainWindow::on_actiongreen_triggered()
{
    pen.setColor(Qt::green);
}

void MainWindow::on_actionblue_triggered()
{
    pen.setColor(Qt::blue);
}

void MainWindow::on_actionyellow_triggered()
{
    pen.setColor(Qt::yellow);
}

void MainWindow::on_actionblack_triggered()
{
    pen.setColor(Qt::black);
}

void MainWindow::on_action1_triggered()
{
    pen.setWidth(1);
}

void MainWindow::on_action2_triggered()
{
    pen.setWidth(2);
}

void MainWindow::on_action3_triggered()
{
    pen.setWidth(3);
}

void MainWindow::on_action5_triggered()
{
    pen.setWidth(5);
}

void MainWindow::on_action10_triggered()
{
    pen.setWidth(10);
}

void MainWindow::on_action15_triggered()
{
    pen.setWidth(15);
}

void MainWindow::on_action20_triggered()
{
    pen.setWidth(20);
}

void MainWindow::on_actionsquarecap_triggered()
{
    pen.setCapStyle(Qt::SquareCap);
}

void MainWindow::on_actionroundcap_triggered()
{
    pen.setCapStyle(Qt::RoundCap);
}

void MainWindow::on_actionDDA_triggered()
{
    draw_type=DDALINE;
}

void MainWindow::on_actionBresenham_triggered()
{
    draw_type=BRELINE;
}

void MainWindow::on_actionellipse_triggered()
{
    draw_type=ELLIPSE;
}

void MainWindow::on_actionclear_canvas_triggered()
{

    QPixmap blankpixmap;
    blankpixmap=QPixmap(1200,900);
    blankpixmap.fill(Qt::white);
    pix=blankpixmap;
    tempix=blankpixmap;
    update();
}

void MainWindow::on_actionsave_triggered()
{
    pix.save("line.bmp");
}

void MainWindow::on_actionpolygon_triggered()
{
    draw_type=DDAPOLYGON;
}

void MainWindow::on_actionBresenham_2_triggered()
{
    draw_type=BREPOLYGON;
}

void MainWindow::on_actionEnd_Painting_triggered()
{
    if(draw_type==4)
    {

        DDA dda;
        dda.ddaline(tempix,pix,pen,polyp[0],polyp[1],polyp[polynum*2],polyp[polynum*2+1]);

    }
    else if(draw_type==5)
    {

        Bresenham bre;
        bre.breline(tempix,pix,pen,polyp[0],polyp[1],polyp[polynum*2],polyp[polynum*2+1]);

    }
    update();
    x1=0;y1=0;start=0;polystart=0;

}
