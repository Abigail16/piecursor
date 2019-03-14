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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    ui->setupUi(this);

    timer = new QTimer(this);  //初始化定时器
    TimeRecord = new QTime(0, 0, 0); //初始化时间
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));//关联定时器计满信号和相应的槽函数
    timer->start(1000);//定时器开始计时，其中1000表示1000ms即1秒
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()
{
    *TimeRecord = TimeRecord->addSecs(1);
    qDebug() << TimeRecord->toString("hh:mm:ss");
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    currentMousePosPoint = event->pos();
    if (cursor != nullptr) {
        cursor->onMouseMove(*event);
    }

    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);

    if (cursor != nullptr) {
        cursor->paintBar(painter);
        cursor->paintCursor(painter, currentMousePosPoint);
    }

    painter.end();
}

void MainWindow::mousePressEvent(QMouseEvent *)
{
    timer->stop();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    timer->start();
}

