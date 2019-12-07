#include "bspline.h"

Bspline::Bspline()
{

}
double Bspline::B(int i,int k,double u)
{

    if(k==1)
    {
        if(u>=i&&u<i+1)
            return 1;
        else return 0;
    }
    else {return ((u-i)/(k-1)*B(i,k-1,u)+(i+k-u)/(k-1)*B(i+1,k-1,u));}
}

void Bspline::drawcurve(QPixmap &tempix, QPixmap &pix, QPen &pen)
{

    tempix=pix;
    this->pix=pix;
    this->pen=pen;
    double deltax,deltay;
    for(double u=2;u<ctrlnum;u+=0.01)
    {
        double tmpx=0,tmpy=0;
        for(int i=0;i<ctrlnum;i++)
        {
            deltax=ctrlpoints[2*i];deltay=ctrlpoints[2*i+1];
            deltax*=B(i,3,u);deltay*=B(i,3,u);
            tmpx+=deltax;tmpy+=deltay;
        }

        curvepoints.push_back((int)(tmpx));
        curvepoints.push_back((int)(tmpy));
    }
    for(int j=0;j<curvepoints.size()/2-1;j++)
        bre.breline(pix,pix,pen,curvepoints[j*2],curvepoints[j*2+1],curvepoints[j*2+2],curvepoints[j*2+3]);

}

void Bspline::translate(int x, int y)
{
    for(int i=0;i<ctrlnum;i++)
    {
        ctrlpoints[i*2]+=x;
        ctrlpoints[i*2+1]+=y;
    }
}
void Bspline::rotate(int x, int y, int r)
{
    int oldx,oldy;
    for(int i=0;i<ctrlnum;i++)
    {
        oldx=ctrlpoints[i*2];oldy=ctrlpoints[i*2+1];
        ctrlpoints[i*2]=x+(oldx-x)*cos(r*M_PI/180)-(oldy-y)*sin(r*M_PI/180);
        ctrlpoints[i*2+1]=y+(oldy-y)*cos(r*M_PI/180)+(oldx-x)*sin(r*M_PI/180);
    }
}
void Bspline::scale(int x, int y, float s)
{
    for(int i=0;i<ctrlnum;i++)
    {
        ctrlpoints[i*2]=int(ctrlpoints[i*2]*s+x*(1-s)+0.5);
        ctrlpoints[i*2+1]=int(ctrlpoints[i*2+1]*s+y*(1-s)+0.5);

    }
}
