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

            dda.ddaline(tempix,pix,pen,polygonpoints[i*2],polygonpoints[i*2+1],polygonpoints[(i*2+2)%(pointsnum*2)],polygonpoints[(i*2+3)%(pointsnum*2)]);

        }
    }
    else{
        Bresenham bre;
        for(int i=0;i<pointsnum;i++)
        {

            bre.breline(tempix,pix,pen,polygonpoints[i*2],polygonpoints[i*2+1],polygonpoints[(i*2+2)%(pointsnum*2)],polygonpoints[(i*2+3)%(pointsnum*2)]);

        }
    }
}
