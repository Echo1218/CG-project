#include "ellipse.h"

Ellipse::Ellipse()
{

}
Ellipse::Ellipse(int id, int x0, int y0, int rx, int ry)
{
    this->id=id;
    this->x0=x0;
    this->rx=rx;
    this->y0=y0;
    this->ry=ry;
}

void Ellipse::drawellipse(QPixmap &tempix,QPixmap &pix,QPen &pen,int x0,int y0,int rx,int ry)
{


    tempix=pix;
    QPainter Painter1(&tempix);
    Painter1.setPen(pen);

    long long int rx2=rx*rx,ry2=ry*ry;
    float p;
    long long int x = 0;
    long long int y = ry;
    long long int dy = 0;
    long long int dx = 2*rx2 * y;

    Painter1.drawPoint(x0+x,y0+y);
    Painter1.drawPoint(x0-x,y0+y);
    Painter1.drawPoint(x0+x,y0-y);
    Painter1.drawPoint(x0-x,y0-y);
      //第一象限切线斜率绝对值<1时，
    p = ry2 - (rx2 * ry) + (0.25 * rx2);
    while (dy < dx) {
        if (p < 0) {
            p+=ry2*(2*x+3);
        }
        else {
            p+=ry2*(2 * x + 3) + rx2*(-2 * y + 2);
            y--;
            dx -= 2*rx2;//y每减1，dx就减少2*2rx2
        }
        x++;
        dy += 2*ry2;//x每加1，dy就加2*ry2
        Painter1.drawPoint(x0+x,y0+y);
        Painter1.drawPoint(x0-x,y0+y);
        Painter1.drawPoint(x0+x,y0-y);
        Painter1.drawPoint(x0-x,y0-y);
    }
       //第一象限切线斜率绝对值>=1时，
    p =  ry2*(x + 0.5)*(x + 0.5) + rx2*(y - 1) *(y - 1)- (ry2*rx2);
    while (y > 0) {

        if (p > 0) {
            p += rx2*(-2 * y + 3);
        }
        else {

            p += ry2*(2 * x + 2) + rx2*(-2 * y + 3);
            x++;
        }
        y--;
        Painter1.drawPoint(x0+x,y0+y);
        Painter1.drawPoint(x0-x,y0+y);
        Painter1.drawPoint(x0+x,y0-y);
        Painter1.drawPoint(x0-x,y0-y);
    }

}
void Ellipse::translate(int x,int y){
    x0+=x;y0+=y;
}
void Ellipse::rotate(int x, int y, int r)
{
    int oldx,oldy;
    oldx=this->x0;oldy=this->y0;
    this->x0=x+(oldx-x)*cos(r*M_PI/180)-(oldy-y)*sin(r*M_PI/180);
    this->y0=y+(oldy-y)*cos(r*M_PI/180)+(oldx-x)*sin(r*M_PI/180);
    if(r%180!=0&&r%90==0)
    {
        int tmp=this->rx;
        this->rx=this->ry;
        this->ry=tmp;
    }

}

void Ellipse::scale(int x, int y, float s)
{
    this->rx=int(this->rx*s);
    this->ry=int(this->ry*s);
    this->x0=int(this->x0*s+x*(1-s)+0.5);
    this->y0=int(this->y0*s+y*(1-s)+0.5);
}
