#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"
#include "QPainter"
#include "QMouseEvent"
#include "QtMath"
#include "QTimer"
#include "QMouseEvent"
#include "QTime"
#include "QLabel"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(960, 600);                                      //设置窗口大小
    timer = new QTimer(this);                                    //初始化定时器
    TimeRecord = new QTime(0, 0, 0, 0);                          //初始化时间
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime())); //关联定时器计满信号和相应的槽函数
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()//更新时间
{
    *TimeRecord = TimeRecord->addMSecs(1);
    //qDebug() << TimeRecord->toString("hh:mm:ss:zzz");//显示时间
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)//鼠标移动触发
{
    currentMousePosPoint = event->pos();
    if (cursor != nullptr)
    {
        cursor->onMouseMove(*event);
    }

    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
//画的 新变成一个类
    QBrush brush1(QColor(211, 211, 211), Qt::SolidPattern); // 画刷
    painter.setBrush(brush1);                               // 设置画刷
    painter.drawRect(180, 150, 600, 300);

    QBrush brush2(QColor(169, 169, 169), Qt::SolidPattern); // 画刷
    painter.setBrush(brush2);                               // 设置画刷
    painter.drawRect(455, 275, 50, 50);

    QBrush brush3(QColor(255, 255, 255), Qt::SolidPattern); // 画刷
    painter.setBrush(brush3);                               // 设置画刷
    painter.drawRect(476, 296, 8, 8);

    QVector<QLine> lines; //距离50个像素的线
    QPoint offset1(0, 500);
    QPoint offset2(960, 500);
    lines.append(QLine(offset1, offset2));
    painter.drawLines(lines);

    if (cursor != nullptr && !cursor->drag)
    {
        cursor->paintBar(painter);
        cursor->paintCursor(painter, currentMousePosPoint);
    }
    else if (cursor != nullptr && cursor->drag)
    {
        cursor->dragEvent(painter, currentMousePosPoint);
    }

    painter.end();
}

void MainWindow::mousePressEvent(QMouseEvent *)//鼠标点击触发
{
    //拖动实现
    QRect rectBig(180, 150, 600, 300);
    QRect rectMid(455, 275, 50, 50);
    QRect rectSmall(476, 296, 8, 8);
    if (cursor != nullptr)
    {
        cursor->drag = true;
        setCursor(Qt::ClosedHandCursor);
        if(rectSmall.contains(currentMousePosPoint))
        {
            cursor->getType = 1;
        }
        else if(rectMid.contains(currentMousePosPoint))
        {
            cursor->getType = 2;
        }
        else if(rectBig.contains(currentMousePosPoint))
        {
            cursor->getType = 3;
        }
    }
    timer->start(1); //定时器开始计时，其中1000表示1000ms即1秒
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    if(currentMousePosPoint.y()>500)
    {
       // TimeRecord = new QTime(0, 0, 0, 0);//时间重置
        if(cursor != nullptr)
        {
            cursor->drag = false;
            if(cursor->cursorType() == 2)
            {
                setCursor(Qt::BlankCursor);
            }
            else
            {
                setCursor(Qt::ArrowCursor);
            }
        }
    }
    else
    {
        //回归原位
    }
    timer->stop();
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift && cursor->cursorType() == 2)
    {
        //不画了
        setCursor(Qt::ArrowCursor);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift && cursor->cursorType() == 2)
    {
        //继续画
    }
}
