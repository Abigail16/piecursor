#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"
#include "QLabel"
#include "QMouseEvent"
#include "QPainter"
#include "QTime"
#include "QTimer"
#include "QtMath"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , Rect1PosPoint(180, 150)
    , Rect2PosPoint(455, 275)
    , Rect3PosPoint(476, 296)
{
    ui->setupUi(this);

    setFixedSize(960, 600); //设置窗口大小
    timer = new QTimer(this); //初始化定时器
    TimeRecord = new QTime(0, 0, 0, 0); //初始化时间
    connect(timer, SIGNAL(timeout()), this,
        SLOT(updateTime())); //关联定时器计满信号和相应的槽函数
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::updateTime() //更新时间
{
    *TimeRecord = TimeRecord->addMSecs(1);
    // qDebug() << TimeRecord->toString("hh:mm:ss:zzz");//显示时间
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) //鼠标移动触发
{
    lastMousePosPoint = currentMousePosPoint;
    currentMousePosPoint = event->pos();
    if (cursor != nullptr) {
        cursor->onMouseMove(*event);
        if (cursor->isDragging) {
            switch (cursor->draggingRectType) {
            case 1:
                Rect1PosPoint += currentMousePosPoint - lastMousePosPoint;
                break;
            case 2:
                Rect2PosPoint += currentMousePosPoint - lastMousePosPoint;
                break;
            case 3:
                Rect3PosPoint += currentMousePosPoint - lastMousePosPoint;
                break;
            }
        }
    }
    update();
}

void MainWindow::paintRects(QPainter& painter)
{
    QBrush brush1(QColor(211, 211, 211), Qt::SolidPattern); // 画刷
    painter.setBrush(brush1); // 设置画刷
    painter.drawRect(QRect(Rect1PosPoint, QSize(600, 300)));

    QBrush brush2(QColor(169, 169, 169), Qt::SolidPattern); // 画刷
    painter.setBrush(brush2); // 设置画刷
    painter.drawRect(QRect(Rect2PosPoint, QSize(50, 50)));

    QBrush brush3(QColor(255, 255, 255), Qt::SolidPattern); // 画刷
    painter.setBrush(brush3); // 设置画刷
    painter.drawRect(QRect(Rect3PosPoint, QSize(8, 8)));
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);

    QVector<QLine> lines; //距离50个像素的线
    QPoint offset1(0, 500);
    QPoint offset2(960, 500);
    lines.append(QLine(offset1, offset2));
    painter.drawLines(lines);

    this->paintRects(painter);
    if (cursor != nullptr) {
        cursor->paintBar(painter);
        if (!cursor->isDragging) {
            cursor->paintCursor(painter, currentMousePosPoint);
        }
    }
    painter.end();
}

void MainWindow::mousePressEvent(QMouseEvent* event) //鼠标点击触发
{
    //拖动实现
    QPoint pos = event->pos();
    if (cursor != nullptr) {
        cursor->onMouseClick(*event);

        if (QRect(Rect3PosPoint, QSize(8, 8)).contains(pos)) {
            setCursor(Qt::ClosedHandCursor);
            cursor->isDragging = true;
            cursor->draggingRectType = 3;
        } else if (QRect(Rect2PosPoint, QSize(50, 50)).contains(pos)) {
            setCursor(Qt::ClosedHandCursor);
            cursor->isDragging = true;
            cursor->draggingRectType = 2;
        } else if (QRect(Rect1PosPoint, QSize(600, 300)).contains(pos)) {
            setCursor(Qt::ClosedHandCursor);
            cursor->isDragging = true;
            cursor->draggingRectType = 1;
        }
    }
    timer->start(1); //定时器开始计时，其中1000表示1000ms即1秒
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (cursor != nullptr) {
        if (cursor->isDragging) {
            cursor->isDragging = false;
            if (cursor->cursorType() == 2) {
                setCursor(Qt::BlankCursor);
            } else {
                setCursor(Qt::ArrowCursor);
            }

            if (event->y() > 500) {
                // TimeRecord = new QTime(0, 0, 0, 0);//时间重置
                Rect1PosPoint = QPoint(180, 150);
                Rect2PosPoint = QPoint(455, 275);
                Rect3PosPoint = QPoint(476, 296);
                update();
            }
            timer->stop();
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Shift && cursor->cursorType() == 2) {
        //不画了
        setCursor(Qt::ArrowCursor);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Shift && cursor->cursorType() == 2) {
        //继续画
    }
}
