#include "polygon.h"

Polygon::Polygon()
{

}

Polygon::Polygon(int id,int p)
{
    this->id=id;
    this->pointsnum=p;
}
void Polygon::drawpoly(QPixmap &tempix, QPixmap &pix, QPen &pen)
{

    if(algo==0)
    {
        DDA dda;
        for(int i=0;i<pointsnum;i++)
        {

            pix=tempix;
            dda.ddaline(tempix,pix,pen,polygonpoints[i*2],polygonpoints[i*2+1],polygonpoints[(i*2+2)%(pointsnum*2)],polygonpoints[(i*2+3)%(pointsnum*2)]);

        }
    }
    else{
        Bresenham bre;
        for(int i=0;i<pointsnum;i++)
        {
            pix=tempix;
            bre.breline(tempix,pix,pen,polygonpoints[i*2],polygonpoints[i*2+1],polygonpoints[(i*2+2)%(pointsnum*2)],polygonpoints[(i*2+3)%(pointsnum*2)]);

        }
    }
}
void Polygon:: translate(int x,int y){
    for(int i=0;i<polygonpoints.size()/2;i++)
    {
        polygonpoints[i*2]+=x;
        polygonpoints[i*2+1]+=y;
    }
}

void Polygon::rotate(int x, int y, int r)
{
    int oldx,oldy;
    for(int i=0;i<pointsnum;i++)
    {
        oldx=polygonpoints[i*2];oldy=polygonpoints[i*2+1];
        polygonpoints[i*2]=x+(oldx-x)*cos(r*M_PI/180)-(oldy-y)*sin(r*M_PI/180);
        polygonpoints[i*2+1]=y+(oldy-y)*cos(r*M_PI/180)+(oldx-x)*sin(r*M_PI/180);
    }
}
void Polygon::scale(int x, int y, float s)
{
    for(int i=0;i<pointsnum;i++)
    {
        polygonpoints[i*2]=int(polygonpoints[i*2]*s+x*(1-s)+0.5);
        polygonpoints[i*2+1]=int(polygonpoints[i*2+1]*s+y*(1-s)+0.5);

    }
}
