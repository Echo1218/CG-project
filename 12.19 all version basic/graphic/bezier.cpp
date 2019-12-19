#include "bezier.h"

Bezier::Bezier()
{

}
Bezier::Bezier(vector<int>a)
{
    ctrlpoints=a;
    ctrlnum=a.size()/2;
}
void Bezier::drawpoints(vector<double>ctrlp)
{
    int i=0;double d=0,a=0,b=0,c=0;
    a=ctrlp[ctrlnum*2-1]-ctrlp[1];
    b=ctrlp[0]-ctrlp[ctrlnum*2-2];
    c=ctrlp[ctrlnum*2-2]*ctrlp[1]-ctrlp[0]*ctrlp[ctrlnum*2-1];
    double e=sqrt(a*a+b*b);
    for(i=1;i<ctrlp.size()/2-1;i++)
    {
        if(e==0)
            d=(ctrlp[i*2]-ctrlp[0])*(ctrlp[i*2]-ctrlp[0])+(ctrlp[i*2+1]-ctrlp[1])*(ctrlp[i*2+1]-ctrlp[1]);
        else d=abs((a*ctrlp[i*2]+b*ctrlp[i*2+1]+c)/e);

        if(d>0.1)break;
    }
    if(i==ctrlp.size()/2-1)
    {

        for(int j=0;j<ctrlnum-1;j++)
            bre.breline(pix,pix,pen,(int)(ctrlp[j*2]+0.5),(int)(ctrlp[j*2+1]+0.5),(int)(ctrlp[j*2+2]+0.5),(int)(ctrlp[j*2+3]+0.5));
    }
    else{
        vector<vector<double>>arrayp(ctrlnum);

        for(int j=0;j<ctrlp.size();j++)
        {
            arrayp[0].push_back(ctrlp[j]);

        }

        for(int j=1;j<ctrlnum;j++)
        {
            for(int l=0;l<arrayp[j-1].size()-2;l++)
            {
                arrayp[j].push_back((arrayp[j-1][l]+arrayp[j-1][l+2])/2.0);

            }
        }
        vector<double>a;vector<double>b;
        for(int j=0;j<ctrlnum;j++)
        {
            a.push_back(arrayp[j][0]);
            a.push_back(arrayp[j][1]);
            b.push_back(arrayp[ctrlnum-1-j][j*2]);
            b.push_back(arrayp[ctrlnum-1-j][j*2+1]);
        }
        for(int j=0;j<arrayp.size();j++)
        {
            arrayp[j].clear();
        }
        arrayp.clear();

        drawpoints(a);
        drawpoints(b);
    }
}

void Bezier::drawcurve(QPixmap &tempix, QPixmap &pix, QPen &pen)
{
    if(ctrlnum<2)
        return;
    tempix=pix;
    this->pix=pix;
    this->pen=pen;
    vector<double>cc;
    for(int i=0;i<ctrlpoints.size();i++)
        cc.push_back((double)ctrlpoints[i]);
    drawpoints(cc);
    tempix=this->pix;

}

void Bezier::translate(int x, int y)
{
    for(int i=0;i<ctrlnum;i++)
    {
        ctrlpoints[i*2]+=x;
        ctrlpoints[i*2+1]+=y;
    }
}

void Bezier::rotate(int x, int y, int r)
{

    int oldx,oldy;
    for(int i=0;i<ctrlnum;i++)
    {
        oldx=ctrlpoints[i*2];oldy=ctrlpoints[i*2+1];
        ctrlpoints[i*2]=x+(oldx-x)*cos(r*M_PI/180)-(oldy-y)*sin(r*M_PI/180);
        ctrlpoints[i*2+1]=y+(oldy-y)*cos(r*M_PI/180)+(oldx-x)*sin(r*M_PI/180);
    }
}
void Bezier::scale(int x, int y, float s)
{
    for(int i=0;i<ctrlnum;i++)
    {
        ctrlpoints[i*2]=int(ctrlpoints[i*2]*s+x*(1-s)+0.5);
        ctrlpoints[i*2+1]=int(ctrlpoints[i*2+1]*s+y*(1-s)+0.5);

    }
}
