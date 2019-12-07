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
    unsigned short code0=0,code1=0;
    double dx0=(double)x0;
    double dx1=(double)x1;
    double dy0=(double)y0;
    double dy1=(double)y1;
    while(1)
    {   code0=0,code1=0;
        if(dx0<clipx0)code0+=1;
        if(dx0>clipx1)code0+=2;
        if(dy0<clipy0)code0+=4;
        if(dy0>clipy1)code0+=8;
        if(dx1<clipx0)code1+=1;
        if(dx1>clipx1)code1+=2;
        if(dy1<clipy0)code1+=4;
        if(dy1>clipy1)code1+=8;
        //qDebug()<<dx0<<dy0<<dx1<<dy1;

        if((code0|code1)==0)
        {
           // qDebug()<<"in int";
            x0=(int)(dx0+0.5);
            x1=(int)(dx1+0.5);
            y0=(int)(dy0+0.5);
            y1=(int)(dy1+0.5);
            break;
        }
        else if((code0&code1)!=0)
        {
           // qDebug()<<"out of it";
            x0=-1;x1=-1;y0=-1;y1=-1;
            break;
        }
        else{
            double k=(dy1-dy0)/(dx1-dx0);
            if(code0==0)//if point0 is in the clip window,exchange point0 point1
            {
                double tempx,tempy;int tempcode;
                tempx=dx0;tempy=dy0;tempcode=code0;
                dx0=dx1;dy0=dy1;code0=code1;
                dx1=tempx;dy1=tempy;code1=tempcode;
            }
            if((code0&1)!=0)
            {
                dy0=k*(clipx0-dx0)+dy0;
                dx0=clipx0;
            }
            if((code0&2)!=0)
            {
                dy0=k*(clipx1-dx0)+dy0;
                dx0=clipx1;
            }
            if((code0&4)!=0)
            {
                dx0=(clipy0-dy0)/k+dx0;
                dy0=clipy0;
            }
            if((code0&8)!=0)
            {
                dx0=(clipy1-dy0)/k+dx0;
                dy0=clipy1;
            }
        }
    }
}

int DDA::L_Btest(int p,int q,double &u1,double &u2)
{
    double r;
    if(p<0)
    {
        r=((double)q)/p;
        if(r>u2) return 0;
        if(r>u1)
        {
            u1=r;

        }
    }
    else if(p>0)
    {
        r=((double)q)/p;
        if(r<u1)return 0;
        if(r<u2)
        {
            u2=r;
        }

    }
    else if(q<0)
        return 0;
    return 1;
}

void DDA::L_Bclip(int clipx0,int clipy0,int clipx1,int clipy1)
{
    double u0=0,u1=1;
    int p1,p2,p3,p4,q1,q2,q3,q4,dx,dy;
    dx=x1-x0;dy=y1-y0;
    p1=-dx;p2=dx;p3=-dy;p4=dy;q1=x0-clipx0;q2=clipx1-x0;q3=y0-clipy0;q4=clipy1-y0;
    if(L_Btest(p1,q1,u0,u1))
    {
        if(L_Btest(p2,q2,u0,u1))
        {
            if(L_Btest(p3,q3,u0,u1))
            {
                if(L_Btest(p4,q4,u0,u1))
                {

                    if(u1<1)
                    {

                        x1=x0+u1*dx;
                        y1=y0+u1*dy;

                    }
                    if(u0>0)
                    {
                        x0=x0+u0*dx;
                        y0=y0+u0*dy;
                    }
                    return;
                }
            }
        }
    }
    x0=-1;x1=-1;y0=-1;y1=-1;

}

void DDA::rotate(int x, int y, int r)
{

    int oldx,oldy;
    oldx=this->x0;oldy=this->y0;
    this->x0=x+(oldx-x)*cos(r*M_PI/180)-(oldy-y)*sin(r*M_PI/180);
    this->y0=y+(oldy-y)*cos(r*M_PI/180)+(oldx-x)*sin(r*M_PI/180);
    oldx=this->x1;oldy=this->y1;
    this->x1=x+(oldx-x)*cos(r*M_PI/180)-(oldy-y)*sin(r*M_PI/180);
    this->y1=y+(oldy-y)*cos(r*M_PI/180)+(oldx-x)*sin(r*M_PI/180);
}

void DDA::scale(int x, int y, float s)
{

    this->x0=int(this->x0*s+x*(1-s)+0.5);
    this->y0=int(this->y0*s+y*(1-s)+0.5);
    this->x1=int(this->x1*s+x*(1-s)+0.5);
    this->y1=int(this->y1*s+y*(1-s)+0.5);

}
