#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPen>
#include <vector>
using namespace std;
#define DRAWNOTHING 0
#define DDALINE 1
#define BRELINE 2
#define ELLIPSE 3
#define DDAPOLYGON 4
#define BREPOLYGON 5
#define BEZCUR 6
#define BSPLINECUR 7

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);




private slots:
    void on_actionred_triggered();

    void on_actiongreen_triggered();

    void on_actionblue_triggered();

    void on_actionyellow_triggered();

    void on_actionblack_triggered();

    void on_action1_triggered();

    void on_action2_triggered();

    void on_action3_triggered();

    void on_action5_triggered();

    void on_action10_triggered();

    void on_action15_triggered();

    void on_action20_triggered();

    void on_actionsquarecap_triggered();

    void on_actionroundcap_triggered();


    void on_actionDDA_triggered();

    void on_actionBresenham_triggered();


    void on_actionellipse_triggered();

    void on_actionclear_canvas_triggered();

    void on_actionsave_triggered();

    void on_actionpolygon_triggered();

    void on_actionBresenham_2_triggered();

    void on_actionEnd_Painting_triggered();

private:
    int draw_type;
    Ui::MainWindow *ui;
    QPixmap pix;
    QPixmap tempix;
    QPen pen;
    int x0,y0,x1,y1,rx,ry;
    int start=0,end=0,polystart=0,polynum=0;
    vector<int> polyp;

};

#endif // MAINWINDOW_H
