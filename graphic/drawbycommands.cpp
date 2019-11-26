#include "drawbycommands.h"

DrawByCommands::DrawByCommands(QString a,QString b)
{
    cmdfile=a;
    savepath=b;
}
void DrawByCommands::cmdresolver(QString cmd)
{
    QStringList list=cmd.split(" ");
    if(list[0]=="resetCanvas")
    {
        int a=list[1].toInt();
        int b=list[2].toInt();
        pix=QPixmap(a,b);
        pix.fill(Qt::white);


    }
    else if(list[0]=="setColor")
    {
        int r=list[1].toInt();
        int g=list[2].toInt();
        int b=list[3].toInt();
        QColor mycolor(r,g,b);
        pen.setColor(mycolor);
    }
    else if(list[0]=="drawLine")
    {
        if(list[6]=="DDA")
        {
            DDA *dda=new DDA(list[1].toInt(),list[2].toInt(),list[3].toInt(),list[4].toInt(),list[5].toInt());
            graphs.push_back(dda);
            dda->ddaline(pix,pix,pen,dda->x0,dda->y0,dda->x1,dda->y1);
        }
        else if(list[6]=="Bresenham")
        {
            Bresenham *bre=new Bresenham(list[1].toInt(),list[2].toInt(),list[3].toInt(),list[4].toInt(),list[5].toInt());
            graphs.push_back(bre);
            bre->breline(pix,pix,pen,bre->x0,bre->y0,bre->x1,bre->y1);
        }
    }
    else if(list[0]=="saveCanvas")
    {
        QString savep=savepath+"\\"+list[1]+".bmp";
        pix.save(savep);

    }
    else if(list[0]=="drawEllipse")
    {
        Ellipse *ell=new Ellipse(list[1].toInt(),list[2].toInt(),list[3].toInt(),list[4].toInt(),list[5].toInt());
        graphs.push_back(ell);
        ell->drawellipse(pix,pix,pen,ell->x0,ell->y0,ell->rx,ell->ry);

    }
    else if(list[0]=="drawPolygon")
    {
        Polygon *poly=new Polygon(list[1].toInt(),list[2].toInt());
        if(list[3]=="DDA") poly->algo=0;
        else poly->algo=1;

        QString t;
        if(!file.atEnd())
        {
           t=file.readLine();
           if(t.length()-1>=0)
               if(t[t.length()-1]=='\n')
                   t=t.left(t.size()-1);
        }
        list=t.split(" ");
        for(int i=0;i<list.length();i++)
        {
            poly->polygonpoints.push_back(list[i].toInt());
        }
        poly->drawpoly(pix,pix,pen);
        graphs.push_back(poly);
    }
    else if(list[0]=="translate")
    {
        for(int i=0;i<graphs.size();i++)
        {
            if(graphs[i]->id==list[1].toInt())
            {
                qDebug()<<"find shit:"<<i;
            }
        }
    }

}

void DrawByCommands::readfile()
{

    file.setFileName(cmdfile);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString t ;
        while(!file.atEnd())
        {
            t=file.readLine();
            if(t.length()-1>=0)
                if(t[t.length()-1]=='\n')
                    t=t.left(t.size()-1);
            cmdresolver(t);
        }

        file.close();
    }
}
