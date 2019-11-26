#include "bresenham.h"

Bresenham::Bresenham()
{

}
Bresenham::Bresenham(int id, int x0, int y0, int x1, int y1)
{
    this->id=id;
    this->x0=x0;
    this->x1=x1;
    this->y0=y0;
    this->y1=y1;
}

void Bresenham::breline(QPixmap &tempix,QPixmap &pix,QPen &pen,int x0,int y0,int x1,int y1){

    tempix=pix;
    QPainter Painter1(&tempix);
    Painter1.setPen(pen);
    int x=x0,y=y0;
    Painter1.drawPoint(x,y);
    int deltax=x1-x0,deltay=y1-y0,signx=1,signy=1;
    int absdelx=abs(deltax),absdely=abs(deltay);
    if(deltax!=0)
    signx=deltax/absdelx;
    if(deltay!=0)
    signy=deltay/absdely;
    int p=0;
    if(absdelx>absdely)
    {   p=2*absdely-absdelx;
      for(int i=0;i<absdelx;i++)
      {
          if(p<0)
          {
              p+=2*absdely;
          }
          else{
              p+=2*absdely-2*absdelx;
              y+=signy;
          }
          x+=signx;
          Painter1.drawPoint(x,y);
      }
    }
    else{
       p=2*absdelx-absdely;
       for(int i=0;i<absdely;i++)
       {
           if(p<0)
           {
               p+=2*absdelx;

           }
           else{

               p+=2*absdelx-2*absdely;
               x+=signx;

           }
           y+=signy;
           Painter1.drawPoint(x,y);
       }
    }
}
