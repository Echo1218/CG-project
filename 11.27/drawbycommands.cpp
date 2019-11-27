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
        graphs.clear();
        canvasx=list[1].toInt();
        canvasy=list[2].toInt();
        pix=QPixmap(canvasx,canvasy);
        pix.fill(Qt::white);


    }
    else if(list[0]=="setColor")
    {
        int r=list[1].toInt();
        int g=list[2].toInt();
        int b=list[3].toInt();
        QColor mycolor(r,g,b);
        color=mycolor;
        pen.setColor(color);
    }
    else if(list[0]=="drawLine")
    {
        if(list[6]=="DDA")
        {
            DDA *dda=new DDA(list[1].toInt(),list[2].toInt(),list[3].toInt(),list[4].toInt(),list[5].toInt());
            graphs.push_back(dda);
            dda->type=DDALINE;
            dda->color=color;
            graphindex.push_back(list[1].toInt());
            dda->ddaline(pix,pix,pen,dda->x0,dda->y0,dda->x1,dda->y1);
        }
        else if(list[6]=="Bresenham")
        {
            Bresenham *bre=new Bresenham(list[1].toInt(),list[2].toInt(),list[3].toInt(),list[4].toInt(),list[5].toInt());
            graphs.push_back(bre);
            bre->color=color;
            bre->type=BRELINE;
            graphindex.push_back(list[1].toInt());
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
        ell->type=ELLIPSE;
        ell->color=color;
        graphindex.push_back(list[1].toInt());
        ell->drawellipse(pix,pix,pen,ell->x0,ell->y0,ell->rx,ell->ry);

    }
    else if(list[0]=="drawPolygon")
    {
        Polygon *poly=new Polygon(list[1].toInt(),list[2].toInt());
        if(list[3]=="DDA") {poly->algo=0;poly->type=DDAPOLYGON;}
        else {poly->algo=1;poly->type=BREPOLYGON;}
        poly->color=color;
        graphindex.push_back(list[1].toInt());
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
        vector<int>::iterator it=find(graphindex.begin(),graphindex.end(),list[1].toInt());
        int index=std::distance(std::begin(graphindex),it);
        pix=QPixmap(canvasx,canvasy);
        pix.fill(Qt::white);
        graphs[index]->translate(list[2].toInt(),list[3].toInt());

        for(int i=0;i<graphs.size();i++)
        {
            QPen temppen;temppen.setColor(graphs[i]->color);
            if(graphs[i]->type==DDAPOLYGON||graphs[i]->type==BREPOLYGON)
                ((Polygon*)graphs[i])->drawpoly(pix,pix,temppen);
            else if(graphs[i]->type==DDALINE)
            {
                ((DDA*)graphs[i])->ddaline(pix,pix,temppen,((DDA*)graphs[i])->x0,((DDA*)graphs[i])->y0,((DDA*)graphs[i])->x1,((DDA*)graphs[i])->y1);
            }
            else if(graphs[i]->type==BRELINE)
            {
                ((Bresenham*)graphs[i])->breline(pix,pix,temppen,((Bresenham*)graphs[i])->x0,((Bresenham*)graphs[i])->y0,((Bresenham*)graphs[i])->x1,((Bresenham*)graphs[i])->y1);
            }
            else if(graphs[i]->type==ELLIPSE){
                ((Ellipse*)graphs[i])->drawellipse(pix,pix,temppen,((Ellipse*)graphs[i])->x0,((Ellipse*)graphs[i])->y0,((Ellipse*)graphs[i])->rx,((Ellipse*)graphs[i])->ry);
            }
            else if(graphs[i]->type==BEZCUR)
            {
                ((Bezier*)graphs[i])->drawcurve(pix,pix,temppen);
            }
        }

    }
    else if(list[0]=="drawCurve")
    {
        if(list[3]=="Bezier")
        {
            Bezier *bezcur=new Bezier();
            bezcur->id=list[1].toInt();
            bezcur->type=BEZCUR;
            bezcur->ctrlnum=list[2].toInt();
            bezcur->color=color;
            graphindex.push_back(bezcur->id);
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
                bezcur->ctrlpoints.push_back(list[i].toInt());
            }
            bezcur->drawcurve(pix,pix,pen);
            graphs.push_back(bezcur);
        }
        else{

        }
    }
    else if(list[0]=="clip")
    {
        vector<int>::iterator it=find(graphindex.begin(),graphindex.end(),list[1].toInt());
        int index=std::distance(std::begin(graphindex),it);

        if(list[6]=="Cohen-Sutherland")
        {
            if(graphs[index]->type==DDALINE)
            {
                ((DDA*)graphs[index])->C_Sclip(list[2].toInt(),list[3].toInt(),list[4].toInt(),list[5].toInt());
            }
            else{

            }
        }
        else{

        }

        for(int i=0;i<graphs.size();i++)
        {
            QPen temppen;temppen.setColor(graphs[i]->color);
            if(graphs[i]->type==DDAPOLYGON||graphs[i]->type==BREPOLYGON)
                ((Polygon*)graphs[i])->drawpoly(pix,pix,temppen);
            else if(graphs[i]->type==DDALINE)
            {
                ((DDA*)graphs[i])->ddaline(pix,pix,temppen,((DDA*)graphs[i])->x0,((DDA*)graphs[i])->y0,((DDA*)graphs[i])->x1,((DDA*)graphs[i])->y1);
            }
            else if(graphs[i]->type==BRELINE)
            {
                ((Bresenham*)graphs[i])->breline(pix,pix,temppen,((Bresenham*)graphs[i])->x0,((Bresenham*)graphs[i])->y0,((Bresenham*)graphs[i])->x1,((Bresenham*)graphs[i])->y1);
            }
            else if(graphs[i]->type==ELLIPSE){
                ((Ellipse*)graphs[i])->drawellipse(pix,pix,temppen,((Ellipse*)graphs[i])->x0,((Ellipse*)graphs[i])->y0,((Ellipse*)graphs[i])->rx,((Ellipse*)graphs[i])->ry);
            }
            else if(graphs[i]->type==BEZCUR)
            {
                ((Bezier*)graphs[i])->drawcurve(pix,pix,temppen);
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
