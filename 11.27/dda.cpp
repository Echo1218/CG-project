#include "dda.h"

DDA::DDA()
{

}
DDA::DDA(int id, int x0, int y0, int x1, int y1)
{
    this->id=id;
    this->x0=x0;
    this->x1=x1;
    this->y0=y0;
    this->y1=y1;
}

void DDA::ddaline(QPixmap &tempix,QPixmap &pix,QPen &pen,int x0,int y0,int x1,int y1){
    tempix=pix;
    QPainter Painter1(&tempix);
    Painter1.setPen(pen);
    float xinc,yinc,deltax,deltay,x,y;//xinc，yinc为xy每次的增量， deltax，deltay为终点减起点，x，y为起点
    int loop=0;//循环次数，以deltax，deltay较长的一个的长度为循环次数
    deltax=x1-x0;deltay=y1-y0;
    if(abs(deltay)>abs(deltax))
    {
        loop=abs(deltay)+1;
        xinc=deltax/abs(deltay);
        yinc=deltay/abs(deltay);
    }
    else{
        loop=abs(deltax)+1;
        xinc=deltax/abs(deltax);
        yinc=deltay/abs(deltax);
    }

    x = x0;
    y = y0;

    for (int i = 0; i < loop; i++)
    {
        Painter1.drawPoint(int(x+0.5),int(y+0.5));//加0.5是为了四舍五入 x.5+0.5取整=x+1;x.4+0.5取整=x
        x += xinc;
        y += yinc;
    }
}
void DDA:: translate(int x,int y){
    x0+=x;x1+=x;y0+=y;y1+=y;
}
void DDA::C_Sclip(int clipx0,int clipy0,int clipx1,int clipy1){

}
