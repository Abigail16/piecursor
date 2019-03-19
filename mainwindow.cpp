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

void MainWindow::updateTime()
{
    *TimeRecord = TimeRecord->addMSecs(1);
    qDebug() << TimeRecord->toString("hh:mm:ss:zzz");
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
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

    QBrush brush1(QColor(211, 211, 211), Qt::SolidPattern); // 画刷
    painter.setBrush(brush1);                               // 设置画刷
    painter.drawRect(180, 150, 600, 300);

    QBrush brush2(QColor(169, 169, 169), Qt::SolidPattern); // 画刷
    painter.setBrush(brush2);                               // 设置画刷
    painter.drawRect(455, 275, 50, 50);

    QBrush brush3(QColor(255, 255, 255), Qt::SolidPattern); // 画刷
    painter.setBrush(brush3);                               // 设置画刷
    painter.drawRect(478, 298, 4, 4);

    QVector<QLine> lines; //距离50个像素的线
    QPoint offset1(0, 500);
    QPoint offset2(960, 500);
    lines.append(QLine(offset1, offset2));
    painter.drawLines(lines);

    if (cursor != nullptr)
    {
        cursor->paintBar(painter);
        cursor->paintCursor(painter, currentMousePosPoint);
    }

    painter.end();
}

void MainWindow::mousePressEvent(QMouseEvent *)
{
    timer->start(1); //定时器开始计时，其中1000表示1000ms即1秒
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    timer->stop();
}
