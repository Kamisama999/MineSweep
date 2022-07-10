#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("扫雷");
    mineMap.Create();
    offsetx=5;
    offsety=30;
    setFixedSize(mineMap.Row*20+offsetx*2,mineMap.Column*20+offsety+46);
    runtime=new QTimer(this);
    connect(runtime,SIGNAL(timeout()),this,SLOT(on_sectime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//绘图事件
void MainWindow::paintEvent(QPaintEvent *)
{
    QPixmap nub(":/item1.bmp");
    QPixmap map(":/item2.bmp");
    QPixmap fame(":/item3.bmp");
    QPixmap face(":/item4.bmp");
    QPainter painter(this);

    //绘制上面的框架
    painter.drawPixmap( 0+offsetx, 0+offsety, fame, 0, 0, 70, 40);
    painter.drawPixmap(mineMap.Row * 10 - 20+offsetx, 0+offsety, fame, 80, 0, 40, 40);
    painter.drawPixmap(mineMap.Row * 20 - 70+offsetx, 0+offsety, fame, 130, 0, 70, 40);
    painter.drawPixmap(70+offsetx, 0+offsety, mineMap.Row * 10 - 90, 40, fame, 70, 0, 10, 40);
    painter.drawPixmap(mineMap.Row * 10 + 20+offsetx, 0+offsety, mineMap.Row * 10 - 90, 40, fame, 70, 0, 10, 40);
    painter.drawPixmap(mineMap.Row * 10 - 12+offsetx, 7+offsety, face, mineMap.winflag * 24, 0, 24, 24);

    //绘制雷区
    for(int i=0;i<mineMap.Row;i++)
    {
        for(int j=0;j<mineMap.Column;j++)
        {
            if(mineMap.Map[i][j]>=0&&mineMap.Map[i][j]<9)
            {
                painter.drawPixmap(i*20+offsetx,j*20+40+offsety,map,mineMap.Map[i][j]*20,0,20,20);
            }
            if(mineMap.Map[i][j]==-1)
                painter.drawPixmap(i*20+offsetx,j*20+40+offsety,map,9*20,0,20,20);
            if(mineMap.Map[i][j]>90)
                painter.drawPixmap(i*20+offsetx,j*20+40+offsety,map,10*20,0,20,20);
            if(mineMap.Map[i][j]>40&&mineMap.Map[i][j]<60)
                painter.drawPixmap(i*20+offsetx,j*20+40+offsety,map,11*20,0,20,20);
            if(mineMap.Map[i][j]==-2)
                painter.drawPixmap(i*20+offsetx,j*20+40+offsety,map,12*20,0,20,20);
        }
    }

    int remainMine=mineMap.RemainMine;
    int remainTime=mineMap.timer;

    //绘制剩余雷数
    if(remainMine<0)
        remainMine=0;
    painter.drawPixmap(6+offsetx, 5+offsety, nub, remainMine / 100 * 20, 0, 20, 28);
    if(remainMine>=100)
        remainMine%=100;
    painter.drawPixmap(26+offsetx, 5+offsety, nub, remainMine / 10 * 20, 0, 20, 28);
    painter.drawPixmap(46+offsetx, 5+offsety, nub, remainMine % 10 * 20, 0, 20, 28);

    //绘制时间
    if(remainTime>=1000)
        remainTime%=1000;
    painter.drawPixmap(mineMap.Row*20-66+offsetx, 5+offsety, nub, remainTime / 100 * 20, 0, 20, 28);
    if(remainTime>=100)
        remainTime%=100;
    painter.drawPixmap(mineMap.Row*20 - 46+offsetx, 5+offsety, nub, remainTime / 10 * 20, 0, 20, 28);
    painter.drawPixmap(mineMap.Row*20 - 26+offsetx, 5+offsety, nub, remainTime % 10 * 20, 0, 20, 28);
}

//鼠标按下事件
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int px=event->x()-offsetx;
    int py=event->y() -offsety;
    int x = (px) / 20;
    int y = (py) / 20 - 2;
    if(event->buttons()==(Qt::LeftButton|Qt::RightButton))
    {
        if(mineMap.LRClick(x, y))
            update();
    }
    else if(event->button()==Qt::LeftButton)
    {
        //点击表情图标重新开始
        if (px>mineMap.Row * 10 - 15 && px< mineMap.Row * 10 + 15 && py>4 && py < 34)
        {
            mineMap.Restart();
            update();
        }
        if(mineMap.LClick(x,y))
        {
            if (!(runtime->isActive() ))
                runtime->start(1000);
            update();
        }
        if (mineMap.winflag==0 || mineMap.winflag == 2)
        {
            if (runtime->isActive() )
                runtime->stop();
        }
    }
    else if(event->button()==Qt::RightButton)
    {
        if(mineMap.RClick(x,y))
            update();
    }
}

//新游戏
void MainWindow::on_actionRestart_triggered()
{
    mineMap.Restart();
    update();
}

//关闭
void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

//初级
void MainWindow::on_actionEasy_triggered()
{
    mineMap.Create(10,8,15);
    setFixedSize(mineMap.Row*20+offsetx*2,mineMap.Column*20+offsety+46);
}
//中级
void MainWindow::on_actionIntermediate_triggered()
{
    mineMap.Create(20,15,50);
    setFixedSize(mineMap.Row*20+offsetx*2,mineMap.Column*20+offsety+46);
}
//高级
void MainWindow::on_actionAdvanced_triggered()
{
    mineMap.Create(30,20,100);
    setFixedSize(mineMap.Row*20+offsetx*2,mineMap.Column*20+offsety+46);
}
//计时器每秒加一
void MainWindow::on_sectime()
{
    mineMap.timer++;
    update();
}


