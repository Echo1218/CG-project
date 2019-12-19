#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <QDebug>
#include <QMouseEvent>
#include "dda.h"
#include "bresenham.h"
#include "ellipse.h"
#include "polygon.h"
#include "bezier.h"
#include "bspline.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    draw_type=0;
    trans_type=0;
    rotatestart=0;
    scalestart=0;
    ui->setupUi(this);
    setWindowTitle(tr("My Paint"));
    this->resize(QSize(1200,900));
    pix = QPixmap(1200, 900);
    tempix=QPixmap(1200,900);
    finalpix=QPixmap(1200,900);
    pix.fill(Qt::white);
    tempix.fill(Qt::white);
    finalpix.fill(Qt::white);
    pen.setColor(Qt::black);



}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if(event->button()==Qt::LeftButton)
    {   QPoint startpoint=event->pos();
        if(trans_type==11)
        {

            translatex0=startpoint.x();
            translatey0=startpoint.y();
            start=1;end=0;finalend=0;

        }
        else if(trans_type==12)
        {
            if(rotatestart==0)
            {

                rotatecx=startpoint.x();
                rotatecy=startpoint.y();
                start=1;end=0;finalend=0;
            }
            else if(rotatestart==1)
            {
                rotatex0=startpoint.x();
                rotatey0=startpoint.y();

            }

        }
        else if(trans_type==13)
        {
            if(scalestart==0)
            {
                scalecx=startpoint.x();
                scalecy=startpoint.y();
                start=1;end=0;finalend=0;
            }
            else if(scalestart==1)
            {
                scalex0=startpoint.x();
                scaley0=startpoint.y();
            }
        }
        else if(draw_type==1||draw_type==2||draw_type==3)
        {
            finalend=1;
            end=1;
            repaint();
            startpoint=event->pos();
            x0=startpoint.x();
            y0=startpoint.y();
            start=1;
            end=0;
            finalend=0;

        }
        else if(draw_type==4||draw_type==5)
        {
            start=1;
            end=0;finalend=0;


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
                    repaint();
                }
                else{
                    Bresenham bre;
                    bre.breline(tempix,pix,pen,polyp[polynum*2],polyp[polynum*2+1],startpoint.x(),startpoint.y());
                    repaint();
                }
            }
        }
        else if(draw_type==6||draw_type==7)
        {
            start=1;
            end=0;
            finalend=0;
            if(curstart==0) curp.clear();
            curp.push_back(startpoint.x());
            curp.push_back(startpoint.y());

            if(draw_type==6)
            {
                curstart=1;
                Bezier bez(curp);
                bez.drawcurve(tempix,pix,pen);
                repaint();

            }
            else{
                //qDebug()<<"start"<<curp[curp.size()-2]<<curp[curp.size()-1];
                curstart=1;
                Bspline bsp(curp);
                bsp.drawcurve(tempix,pix,pen);
                repaint();
            }
        }

    }


}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{   QPoint midpoint=event->pos();
    if(event->buttons()&Qt::LeftButton){
        if(trans_type==11)
        {
            int translatex=midpoint.x()-translatex0;
            int translatey=midpoint.y()-translatey0;
            if(draw_type==1)
            {

                //qDebug()<<x0<<y0<<x1<<y1<<translatex<<translatey;
                DDA dda(0,x0,y0,x1,y1);
                pix=finalpix;
                dda.translate(translatex,translatey);
                dda.ddaline(tempix,pix,pen,dda.x0,dda.y0,dda.x1,dda.y1);
                repaint();
            }
            else if(draw_type==2)
            {
                Bresenham bre(0,x0,y0,x1,y1);
                pix=finalpix;
                bre.translate(translatex,translatey);
                bre.breline(tempix,pix,pen,bre.x0,bre.y0,bre.x1,bre.y1);
                repaint();
            }
            else if(draw_type==3)
            {
                pix=finalpix;
                Ellipse ell(0,x0,y0,rx,ry);
                ell.translate(translatex,translatey);
                ell.drawellipse(tempix,pix,pen,ell.x0,ell.y0,ell.rx,ell.ry);
                repaint();

            }
            else if(draw_type==4)
            {
                pix=finalpix;
                tempix=pix;
                Polygon poly;
                poly.algo=0;
                for(int i=0;i<polyp.size();i++)
                    poly.polygonpoints.push_back(polyp[i]);
                poly.pointsnum=poly.polygonpoints.size()/2;
                //qDebug()<<"draw poly:";
                poly.translate(translatex,translatey);
                poly.drawpoly(tempix,tempix,pen);
                repaint();
            }
            else if(draw_type==5)
            {
                pix=finalpix;
                tempix=pix;
                Polygon poly;
                poly.algo=1;
                for(int i=0;i<polyp.size();i++)
                    poly.polygonpoints.push_back(polyp[i]);
                poly.pointsnum=poly.polygonpoints.size()/2;
                //qDebug()<<"draw poly:";
                poly.translate(translatex,translatey);
                poly.drawpoly(tempix,tempix,pen);
                repaint();
            }
            else if(draw_type==6)
            {
                pix=finalpix;
                //qDebug()<<curp.size();
                Bezier bez(curp);
                bez.translate(translatex,translatey);
                bez.drawcurve(tempix,pix,pen);
                repaint();
            }
            else if(draw_type==7)
            {
                pix=finalpix;
                //qDebug()<<curp.size();
                Bspline bsp(curp);
                bsp.translate(translatex,translatey);
                bsp.drawcurve(tempix,pix,pen);
                repaint();
            }
        }
        else if(trans_type==12)
        {
            double v1=rotatex0-rotatecx;
            double v2=rotatey0-rotatecy;
            double v3=midpoint.x()-rotatecx;
            double v4=midpoint.y()-rotatecy;
            double angle=(v1*v3+v2*v4)/((sqrt(v1*v1+v2*v2))*(sqrt(v3*v3+v4*v4)));
            angle=acos(angle)*180/M_PI;
            if(angle>60)
            {

                rotatex0=midpoint.x();
                rotatey0=midpoint.y();
            }
            if(draw_type==1)
            {

                DDA dda(0,x0,y0,x1,y1);
                pix=finalpix;
                dda.rotate(rotatecx,rotatecy,(int)angle);
                dda.ddaline(tempix,pix,pen,dda.x0,dda.y0,dda.x1,dda.y1);
                repaint();
                if(angle>60)
                {

                   x0=dda.x0;y0=dda.y0;x1=dda.x1;y1=dda.y1;
                }

            }
            else if(draw_type==2)
            {
                Bresenham bre(0,x0,y0,x1,y1);
                pix=finalpix;
                bre.rotate(rotatecx,rotatecy,(int)angle);
                bre.breline(tempix,pix,pen,bre.x0,bre.y0,bre.x1,bre.y1);
                repaint();
                if(angle>60)
                {

                   x0=bre.x0;y0=bre.y0;x1=bre.x1;y1=bre.y1;
                }
            }
            else if(draw_type==3)
            {


            }
            else if(draw_type==4)
            {
                pix=finalpix;
                tempix=pix;
                Polygon poly;
                poly.algo=0;
                for(int i=0;i<polyp.size();i++)
                    poly.polygonpoints.push_back(polyp[i]);
                poly.pointsnum=poly.polygonpoints.size()/2;
                //qDebug()<<"draw poly:";
                poly.rotate(rotatecx,rotatecy,(int)angle);
                poly.drawpoly(tempix,tempix,pen);
                repaint();
                if(angle>60)
                {
                    for(int i=0;i<polyp.size();i++)
                        polyp[i]=poly.polygonpoints[i];
                }
            }
            else if(draw_type==5)
            {
                pix=finalpix;
                tempix=pix;
                Polygon poly;
                poly.algo=1;
                for(int i=0;i<polyp.size();i++)
                    poly.polygonpoints.push_back(polyp[i]);
                poly.pointsnum=poly.polygonpoints.size()/2;
                //qDebug()<<"draw poly:";
                poly.rotate(rotatecx,rotatecy,(int)angle);
                poly.drawpoly(tempix,tempix,pen);
                repaint();
                if(angle>60)
                {
                    for(int i=0;i<polyp.size();i++)
                        polyp[i]=poly.polygonpoints[i];
                }
            }
            else if(draw_type==6)
            {
                pix=finalpix;
                //qDebug()<<curp.size();
                Bezier bez(curp);
                bez.rotate(rotatecx,rotatecy,(int)angle);
                bez.drawcurve(tempix,pix,pen);
                repaint();
                if(angle>60)
                {
                    for(int i=0;i<curp.size();i++)
                        curp[i]=bez.ctrlpoints[i];
                }
            }
            else if(draw_type==7)
            {
                pix=finalpix;
                //qDebug()<<curp.size();
                Bspline bsp(curp);
                bsp.rotate(rotatecx,rotatecy,(int)angle);
                bsp.drawcurve(tempix,pix,pen);
                repaint();
                if(angle>60)
                {
                    for(int i=0;i<curp.size();i++)
                        curp[i]=bsp.ctrlpoints[i];
                }
            }
        }
        else if(trans_type==13)
        {
            double d1=sqrt((scalex0-scalecx)*(scalex0-scalecx)+(scaley0-scalecy)*(scaley0-scalecy));
            double d2=sqrt((midpoint.x()-scalecx)*(midpoint.x()-scalecx)+(midpoint.y()-scalecy)*(midpoint.y()-scalecy));
            double ratio=d2/d1;
            //qDebug()<<ratio;
            if(draw_type==1)
            {

                //qDebug()<<x0<<y0<<x1<<y1<<translatex<<translatey;
                DDA dda(0,x0,y0,x1,y1);
                pix=finalpix;
                dda.scale(scalecx,scalecy,ratio);
                dda.ddaline(tempix,pix,pen,dda.x0,dda.y0,dda.x1,dda.y1);
                repaint();
            }
            else if(draw_type==2)
            {
                Bresenham bre(0,x0,y0,x1,y1);
                pix=finalpix;
                bre.scale(scalecx,scalecy,ratio);
                bre.breline(tempix,pix,pen,bre.x0,bre.y0,bre.x1,bre.y1);
                repaint();
            }
            else if(draw_type==3)
            {
                pix=finalpix;
                Ellipse ell(0,x0,y0,rx,ry);
                ell.scale(scalecx,scalecy,ratio);
                ell.drawellipse(tempix,pix,pen,ell.x0,ell.y0,ell.rx,ell.ry);
                repaint();

            }
            else if(draw_type==4)
            {
                pix=finalpix;
                tempix=pix;
                Polygon poly;
                poly.algo=0;
                for(int i=0;i<polyp.size();i++)
                    poly.polygonpoints.push_back(polyp[i]);
                poly.pointsnum=poly.polygonpoints.size()/2;
                //qDebug()<<"draw poly:";
                poly.scale(scalecx,scalecy,ratio);
                poly.drawpoly(tempix,tempix,pen);
                repaint();
            }
            else if(draw_type==5)
            {
                pix=finalpix;
                tempix=pix;
                Polygon poly;
                poly.algo=1;
                for(int i=0;i<polyp.size();i++)
                    poly.polygonpoints.push_back(polyp[i]);
                poly.pointsnum=poly.polygonpoints.size()/2;
                //qDebug()<<"draw poly:";
                poly.scale(scalecx,scalecy,ratio);
                poly.drawpoly(tempix,tempix,pen);
                repaint();
            }
            else if(draw_type==6)
            {
                pix=finalpix;
                //qDebug()<<curp.size();
                Bezier bez(curp);
                bez.scale(scalecx,scalecy,ratio);
                bez.drawcurve(tempix,pix,pen);
                repaint();
            }
            else if(draw_type==7)
            {
                pix=finalpix;
                //qDebug()<<curp.size();
                Bspline bsp(curp);
                bsp.scale(scalecx,scalecy,ratio);
                bsp.drawcurve(tempix,pix,pen);
                repaint();
            }
        }
        else if(draw_type==1||draw_type==2)
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

            repaint();
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

            repaint();
        }
        else if(draw_type==4)
        {
            midpoint=event->pos();
            DDA dda;
            dda.ddaline(tempix,pix,pen,polyp[polynum*2],polyp[polynum*2+1],midpoint.x(),midpoint.y());
            repaint();
        }
        else if(draw_type==5)
        {
            midpoint=event->pos();
            Bresenham bre;
            bre.breline(tempix,pix,pen,polyp[polynum*2],polyp[polynum*2+1],midpoint.x(),midpoint.y());
            repaint();
        }
        else if(draw_type==6)
        {
            midpoint=event->pos();
            curp.erase(curp.end()-2,curp.end());
            curp.push_back(midpoint.x());
            curp.push_back(midpoint.y());
            Bezier bez(curp);
            bez.drawcurve(tempix,pix,pen);
            repaint();
        }
        else if(draw_type==7)
        {
            midpoint=event->pos();
            //qDebug()<<"moving"<<midpoint.x()<<midpoint.y();
            //qDebug()<<"remove"<<curp[curp.size()-2]<<curp[curp.size()-1];
            curp.erase(curp.end()-2,curp.end());
            curp.push_back(midpoint.x());
            curp.push_back(midpoint.y());
            Bspline bsp(curp);
            bsp.drawcurve(tempix,pix,pen);
            repaint();
        }
    }

}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{   QPoint endpoint=event->pos();

        if(event->button()==Qt::LeftButton)
        {
            endpoint=event->pos();
        }
        if(trans_type==11)
        {
            int translatex=endpoint.x()-translatex0;
            int translatey=endpoint.y()-translatey0;
            end=1;
            if(draw_type==1)
            {

                //qDebug()<<x0<<y0<<x1<<y1<<translatex<<translatey;
                DDA dda(0,x0,y0,x1,y1);
                pix=finalpix;
                dda.translate(translatex,translatey);
                dda.ddaline(tempix,pix,pen,dda.x0,dda.y0,dda.x1,dda.y1);
                repaint();
                x0=dda.x0;x1=dda.x1;y0=dda.y0;y1=dda.y1;


            }
            else if(draw_type==2)
            {

                //qDebug()<<x0<<y0<<x1<<y1<<translatex<<translatey;
                Bresenham bre(0,x0,y0,x1,y1);
                pix=finalpix;
                bre.translate(translatex,translatey);
                bre.breline(tempix,pix,pen,bre.x0,bre.y0,bre.x1,bre.y1);
                repaint();
                x0=bre.x0;x1=bre.x1;y0=bre.y0;y1=bre.y1;
            }
            else if(draw_type==3)
            {

                pix=finalpix;
                Ellipse ell(0,x0,y0,rx,ry);
                ell.translate(translatex,translatey);
                ell.drawellipse(tempix,pix,pen,ell.x0,ell.y0,ell.rx,ell.ry);
                repaint();
                x0=ell.x0;y0=ell.y0;rx=ell.rx;ry=ell.ry;
            }
            else if(draw_type==4)
            {
                pix=finalpix;
                Polygon poly;
                poly.algo=0;
                for(int i=0;i<polyp.size();i++)
                    poly.polygonpoints.push_back(polyp[i]);
                poly.pointsnum=poly.polygonpoints.size()/2;
                qDebug()<<"draw poly:";
                poly.translate(translatex,translatey);
                poly.drawpoly(tempix,pix,pen);
                repaint();
                for(int i=0;i<polyp.size();i++)
                    polyp[i]=poly.polygonpoints[i];
            }
            else if(draw_type==5)
            {
                pix=finalpix;
                Polygon poly;
                poly.algo=1;
                for(int i=0;i<polyp.size();i++)
                    poly.polygonpoints.push_back(polyp[i]);
                poly.pointsnum=poly.polygonpoints.size()/2;
                qDebug()<<"draw poly:";
                poly.translate(translatex,translatey);
                poly.drawpoly(tempix,pix,pen);
                repaint();
                for(int i=0;i<polyp.size();i++)
                    polyp[i]=poly.polygonpoints[i];
            }
            else if(draw_type==6)
            {
                pix=finalpix;
                qDebug()<<curp.size();
                Bezier bez(curp);
                bez.translate(translatex,translatey);
                bez.drawcurve(tempix,pix,pen);
                repaint();
                for(int i=0;i<curp.size();i++)
                    curp[i]=bez.ctrlpoints[i];
            }
            else if(draw_type==7)
            {
                pix=finalpix;
                //qDebug()<<curp.size();
                Bspline bsp(curp);
                bsp.translate(translatex,translatey);
                bsp.drawcurve(tempix,pix,pen);
                repaint();

                for(int i=0;i<curp.size();i++)
                    curp[i]=bsp.ctrlpoints[i];
            }
        }
        else if(trans_type==12)
        {
            double v1=rotatex0-rotatecx;
            double v2=rotatey0-rotatecy;
            double v3=endpoint.x()-rotatecx;
            double v4=endpoint.y()-rotatecy;
            double angle=(v1*v3+v2*v4)/((sqrt(v1*v1+v2*v2))*(sqrt(v3*v3+v4*v4)));
            angle=acos(angle)*180/M_PI;
            if(rotatestart==0)
                rotatestart=1;
            else if(draw_type==1)
            {
                DDA dda(0,x0,y0,x1,y1);
                pix=finalpix;
                dda.rotate(rotatecx,rotatecy,(int)angle);
                dda.ddaline(tempix,pix,pen,dda.x0,dda.y0,dda.x1,dda.y1);
                repaint();
                x0=dda.x0;x1=dda.x1;y0=dda.y0;y1=dda.y1;
            }
            else if(draw_type==2)
            {

                //qDebug()<<x0<<y0<<x1<<y1<<translatex<<translatey;
                Bresenham bre(0,x0,y0,x1,y1);
                pix=finalpix;
                bre.rotate(rotatecx,rotatecy,(int)angle);
                bre.breline(tempix,pix,pen,bre.x0,bre.y0,bre.x1,bre.y1);
                repaint();
                x0=bre.x0;x1=bre.x1;y0=bre.y0;y1=bre.y1;
            }
            else if(draw_type==3)
            {


            }
            else if(draw_type==4)
            {
                pix=finalpix;
                Polygon poly;
                poly.algo=0;
                for(int i=0;i<polyp.size();i++)
                    poly.polygonpoints.push_back(polyp[i]);
                poly.pointsnum=poly.polygonpoints.size()/2;
                qDebug()<<"draw poly:";
                poly.rotate(rotatecx,rotatecy,(int)angle);
                poly.drawpoly(tempix,pix,pen);
                repaint();
                for(int i=0;i<polyp.size();i++)
                    polyp[i]=poly.polygonpoints[i];
            }
            else if(draw_type==5)
            {
                pix=finalpix;
                Polygon poly;
                poly.algo=1;
                for(int i=0;i<polyp.size();i++)
                    poly.polygonpoints.push_back(polyp[i]);
                poly.pointsnum=poly.polygonpoints.size()/2;
                qDebug()<<"draw poly:";
                poly.rotate(rotatecx,rotatecy,(int)angle);
                poly.drawpoly(tempix,pix,pen);
                repaint();
                for(int i=0;i<polyp.size();i++)
                    polyp[i]=poly.polygonpoints[i];
            }
            else if(draw_type==6)
            {
                pix=finalpix;
                qDebug()<<curp.size();
                Bezier bez(curp);
                bez.rotate(rotatecx,rotatecy,(int)angle);
                bez.drawcurve(tempix,pix,pen);
                repaint();
                for(int i=0;i<curp.size();i++)
                    curp[i]=bez.ctrlpoints[i];
            }
            else if(draw_type==7)
            {
                pix=finalpix;
                //qDebug()<<curp.size();
                Bspline bsp(curp);
                bsp.rotate(rotatecx,rotatecy,(int)angle);
                bsp.drawcurve(tempix,pix,pen);
                repaint();

                for(int i=0;i<curp.size();i++)
                    curp[i]=bsp.ctrlpoints[i];
            }
        }
        else if(trans_type==13)
        {
            double d1=sqrt((scalex0-scalecx)*(scalex0-scalecx)+(scaley0-scalecy)*(scaley0-scalecy));
            double d2=sqrt((endpoint.x()-scalecx)*(endpoint.x()-scalecx)+(endpoint.y()-scalecy)*(endpoint.y()-scalecy));
            double ratio=d2/d1;
            qDebug()<<ratio;
            if(scalestart==0)
                scalestart=1;
            else if(draw_type==1)
            {

                //qDebug()<<x0<<y0<<x1<<y1<<translatex<<translatey;
                DDA dda(0,x0,y0,x1,y1);
                pix=finalpix;
                dda.scale(scalecx,scalecy,ratio);
                dda.ddaline(tempix,pix,pen,dda.x0,dda.y0,dda.x1,dda.y1);
                repaint();
                x0=dda.x0;x1=dda.x1;y0=dda.y0;y1=dda.y1;


            }
            else if(draw_type==2)
            {

                //qDebug()<<x0<<y0<<x1<<y1<<translatex<<translatey;
                Bresenham bre(0,x0,y0,x1,y1);
                pix=finalpix;
                bre.scale(scalecx,scalecy,ratio);
                bre.breline(tempix,pix,pen,bre.x0,bre.y0,bre.x1,bre.y1);
                repaint();
                x0=bre.x0;x1=bre.x1;y0=bre.y0;y1=bre.y1;
            }
            else if(draw_type==3)
            {

                pix=finalpix;
                Ellipse ell(0,x0,y0,rx,ry);
                ell.scale(scalecx,scalecy,ratio);
                ell.drawellipse(tempix,pix,pen,ell.x0,ell.y0,ell.rx,ell.ry);
                repaint();
                x0=ell.x0;y0=ell.y0;rx=ell.rx;ry=ell.ry;
            }
            else if(draw_type==4)
            {
                qDebug()<<"shit";
                pix=finalpix;
                Polygon poly;
                poly.algo=0;
                for(int i=0;i<polyp.size();i++)
                    poly.polygonpoints.push_back(polyp[i]);
                poly.pointsnum=poly.polygonpoints.size()/2;
                qDebug()<<"draw poly:";
                poly.scale(scalecx,scalecy,ratio);
                poly.drawpoly(tempix,pix,pen);
                repaint();
                for(int i=0;i<polyp.size();i++)
                    polyp[i]=poly.polygonpoints[i];
            }
            else if(draw_type==5)
            {
                pix=finalpix;
                Polygon poly;
                poly.algo=1;
                for(int i=0;i<polyp.size();i++)
                    poly.polygonpoints.push_back(polyp[i]);
                poly.pointsnum=poly.polygonpoints.size()/2;
                qDebug()<<"draw poly:";
                poly.scale(scalecx,scalecy,ratio);
                poly.drawpoly(tempix,pix,pen);
                repaint();
                for(int i=0;i<polyp.size();i++)
                    polyp[i]=poly.polygonpoints[i];
            }
            else if(draw_type==6)
            {
                pix=finalpix;
                qDebug()<<curp.size();
                Bezier bez(curp);
                bez.scale(scalecx,scalecy,ratio);
                bez.drawcurve(tempix,pix,pen);
                repaint();
                for(int i=0;i<curp.size();i++)
                    curp[i]=bez.ctrlpoints[i];
            }
            else if(draw_type==7)
            {
                pix=finalpix;
                //qDebug()<<curp.size();
                Bspline bsp(curp);
                bsp.scale(scalecx,scalecy,ratio);
                bsp.drawcurve(tempix,pix,pen);
                repaint();

                for(int i=0;i<curp.size();i++)
                    curp[i]=bsp.ctrlpoints[i];
            }
        }
        else if(draw_type==1) {
            end=1;

            x1=endpoint.x();
            y1=endpoint.y();
            DDA dda;dda.ddaline(tempix,pix,pen,x0,y0,x1,y1);}
        else if(draw_type==2){
            end=1;
            x1=endpoint.x();
            y1=endpoint.y();
            Bresenham bre;bre.breline(tempix,pix,pen,x0,y0,x1,y1);
        }
        else if(draw_type==3)
        {   end=1;
            rx=(endpoint.x()-x0)/2;
            ry=(endpoint.y()-y0)/2;
            int absrx=abs(rx);
            int absry=abs(ry);
            x0=x0+rx;y0=y0+ry;rx=absrx;ry=absry;
            Ellipse ell;ell.drawellipse(tempix,pix,pen,x0,y0,rx,ry);
        }
        else if(draw_type==4)
        {
            end=1;
            polyp.push_back(endpoint.x());
            polyp.push_back(endpoint.y());
            DDA dda;
            dda.ddaline(tempix,pix,pen,polyp[polynum*2],polyp[polynum*2+1],polyp[polynum*2+2],polyp[polynum*2+3]);
            polynum++;
        }
        else if(draw_type==5)
        {
            end=1;
            polyp.push_back(endpoint.x());
            polyp.push_back(endpoint.y());
            Bresenham bre;
            bre.breline(tempix,pix,pen,polyp[polynum*2],polyp[polynum*2+1],polyp[polynum*2+2],polyp[polynum*2+3]);
            polynum++;
        }

        else if(draw_type==7)
        {

            //end=1;
            Bspline bsp(curp);
            bsp.drawcurve(tempix,pix,pen);
        }
        repaint();
        start=0;

}
void MainWindow::paintEvent(QPaintEvent *e)
{

        QPainter Painter1(this);
        //Painter1.end();
        //Painter1.begin(this);

          if(end==0)
          {
            qDebug()<<"draw tempix";
             Painter1.drawPixmap(0,0,tempix);
          }
          else if(finalend==0)
          {
          //QPainter pp(&pix);
          //pp.drawPixmap(0,0, tempix);
              qDebug()<<"draw pix";
          pix=tempix;

          //Painter1.end();
          //Painter1.begin(this);
          Painter1.drawPixmap(0,0,pix);
          }
          else{
              pix=tempix;
              finalpix=pix;
              qDebug()<<"draw finalpix";
              Painter1.drawPixmap(0,0,finalpix);
          }

}



void MainWindow::on_actionred_triggered()
{
    end=1;

    repaint();
    rotatestart=0;
    scalestart=0;
    draw_type=DRAWNOTHING;
    trans_type=TRANSNOTHING;
    pen.setColor(Qt::red);
}

void MainWindow::on_actiongreen_triggered()
{
    end=1;

    repaint();
    rotatestart=0;
    scalestart=0;
    draw_type=DRAWNOTHING;
    trans_type=TRANSNOTHING;
    pen.setColor(Qt::green);
}

void MainWindow::on_actionblue_triggered()
{
    end=1;
    repaint();
    rotatestart=0;
    scalestart=0;
    draw_type=DRAWNOTHING;
    trans_type=TRANSNOTHING;
    pen.setColor(Qt::blue);
}

void MainWindow::on_actionyellow_triggered()
{
    end=1;
    repaint();
    rotatestart=0;
    scalestart=0;
    draw_type=DRAWNOTHING;
    trans_type=TRANSNOTHING;
    pen.setColor(Qt::yellow);
}

void MainWindow::on_actionblack_triggered()
{
    end=1;
    repaint();
    rotatestart=0;
    scalestart=0;
    draw_type=DRAWNOTHING;
    trans_type=TRANSNOTHING;
    pen.setColor(Qt::black);
}

void MainWindow::on_action1_triggered()
{
    end=1;
    repaint();
    rotatestart=0;
    scalestart=0;
    draw_type=DRAWNOTHING;
    trans_type=TRANSNOTHING;
    pen.setWidth(1);
}

void MainWindow::on_action2_triggered()
{
    end=1;
    repaint();
    rotatestart=0;
    scalestart=0;
    draw_type=DRAWNOTHING;
    trans_type=TRANSNOTHING;
    pen.setWidth(2);
}

void MainWindow::on_action3_triggered()
{
    end=1;
    repaint();
    rotatestart=0;
    scalestart=0;
    draw_type=DRAWNOTHING;
    trans_type=TRANSNOTHING;
    pen.setWidth(3);
}

void MainWindow::on_action5_triggered()
{
    end=1;
    repaint();
    rotatestart=0;
    scalestart=0;
    draw_type=DRAWNOTHING;
    trans_type=TRANSNOTHING;
    pen.setWidth(5);
}

void MainWindow::on_action10_triggered()
{
    end=1;
    repaint();
    rotatestart=0;
    scalestart=0;
    draw_type=DRAWNOTHING;
    trans_type=TRANSNOTHING;
    pen.setWidth(10);
}

void MainWindow::on_action15_triggered()
{
    end=1;
    repaint();
    rotatestart=0;
    scalestart=0;
    draw_type=DRAWNOTHING;
    trans_type=TRANSNOTHING;
    pen.setWidth(15);
}

void MainWindow::on_action20_triggered()
{
    end=1;
    repaint();
    rotatestart=0;
    scalestart=0;
    draw_type=DRAWNOTHING;
    trans_type=TRANSNOTHING;
    pen.setWidth(20);
}

void MainWindow::on_actionsquarecap_triggered()
{
    end=1;
    repaint();
    rotatestart=0;
    scalestart=0;
    draw_type=DRAWNOTHING;
    trans_type=TRANSNOTHING;
    pen.setCapStyle(Qt::SquareCap);
}

void MainWindow::on_actionroundcap_triggered()
{
    end=1;
    repaint();
    rotatestart=0;
    scalestart=0;
    draw_type=DRAWNOTHING;
    trans_type=TRANSNOTHING;
    pen.setCapStyle(Qt::RoundCap);
}

void MainWindow::on_actionDDA_triggered()
{
    finalend=1;
    end=1;
    repaint();
    rotatestart=0;
    scalestart=0;
    trans_type=TRANSNOTHING;
    draw_type=DDALINE;
}

void MainWindow::on_actionBresenham_triggered()
{
    finalend=1;
    end=1;
    repaint();
    rotatestart=0;
    scalestart=0;
    trans_type=TRANSNOTHING;
    draw_type=BRELINE;
}

void MainWindow::on_actionellipse_triggered()
{
    finalend=1;
    end=1;
    repaint();
    rotatestart=0;
    scalestart=0;
    trans_type=TRANSNOTHING;
    draw_type=ELLIPSE;
}

void MainWindow::on_actionclear_canvas_triggered()
{

    QPixmap blankpixmap;
    blankpixmap=QPixmap(1200,900);
    blankpixmap.fill(Qt::white);
    pix=blankpixmap;
    tempix=blankpixmap;
    trans_type=TRANSNOTHING;
    draw_type=DRAWNOTHING;
    rotatestart=0;
    scalestart=0;
    repaint();
}

void MainWindow::on_actionsave_triggered()
{
    finalend=1;
    end=1;
    repaint();
    qDebug()<<"shit";
    finalpix.save("line.bmp");
    rotatestart=0;
    scalestart=0;
}

void MainWindow::on_actionpolygon_triggered()
{
    finalend=1;
    end=1;
    repaint();
    trans_type=TRANSNOTHING;
    draw_type=DDAPOLYGON;
    rotatestart=0;
    scalestart=0;
}

void MainWindow::on_actionBresenham_2_triggered()
{
    finalend=1;
    end=1;
    repaint();
    trans_type=TRANSNOTHING;
    draw_type=BREPOLYGON;
    rotatestart=0;
    scalestart=0;
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
    repaint();
    x1=0;y1=0;start=0;polystart=0;

}

void MainWindow::on_actionBezier_triggered()
{
    finalend=1;
    end=1;
    repaint();
    trans_type=TRANSNOTHING;
    draw_type=BEZCUR;
    rotatestart=0;
    scalestart=0;
    curstart=0;
}

void MainWindow::on_actionB_spline_triggered()
{
    finalend=1;
    end=1;
    repaint();
    trans_type=TRANSNOTHING;
    draw_type=BSPLINECUR;
    rotatestart=0;
    scalestart=0;
    curstart=0;
}

void MainWindow::on_actiontranslate_triggered()
{
    trans_type=TRANSLATE;
    rotatestart=0;
    scalestart=0;
}

void MainWindow::on_actionrotate_triggered()
{

    trans_type=ROTATE;
    scalestart=0;
}

void MainWindow::on_actionscale_triggered()
{

    trans_type=SCALE;
    rotatestart=0;
}
