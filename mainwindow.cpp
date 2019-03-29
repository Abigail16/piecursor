#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"
#include "QLabel"
#include "QMouseEvent"
#include "QPainter"
#include "QRandomGenerator"
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

void MainWindow::preInitCursor()
{
    if (cursor != nullptr)
        delete cursor;
    setCursor(Qt::ArrowCursor);
}

void MainWindow::postInitCursor()
{
    ui->NeedFeature->setText("需求功能" + QString::number(cursor->getIconIndex()));
    update();
    needRestart = true;
}

void MainWindow::updateTime() //更新时间
{
    QTime t(0, 0);
    ui->Time_Label->setText(t.addMSecs(TimeRecord->elapsed()).toString("hh:mm:ss:zzz")); //显示时间
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) //鼠标移动触发
{
    lastMousePosPoint = currentMousePosPoint;
    currentMousePosPoint = event->pos();
    if (cursor != nullptr) { //如果已经选中某一任务
        cursor->onMouseMove(*event);
        if (cursor->isDragging) { //已经选择功能开始拖动
            switch (cursor->draggingRectType) { //选择某一块方块
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
        } else if (!cursor->isShiftPressed) {
            ui->Feature_Label->setText("当前功能" + QString::number(cursor->getChoseToolIndex()));
            cursor->currentFeature = cursor->getChoseToolIndex();
        }
    }
    update();
}

void MainWindow::paintRects(QPainter& painter)
{
    QBrush brush; // 画刷
    brush.setStyle(Qt::SolidPattern);
    if (cursor != nullptr) {
        switch (cursor->getTargetIndex()) { //选择某一目标
        case 0:
            brush.setColor(QColor(255, 255, 255));
            painter.setBrush(brush); // 设置画刷
            painter.drawRect(QRect(Rect3PosPoint, QSize(8, 8)));
            break;
        case 1:
            brush.setColor(QColor(169, 169, 169));
            painter.setBrush(brush); // 设置画刷
            painter.drawRect(QRect(Rect2PosPoint, QSize(50, 50)));
            break;
        case 2:
            brush.setColor(QColor(211, 211, 211));
            painter.setBrush(brush); // 设置画刷
            painter.drawRect(QRect(Rect1PosPoint, QSize(600, 300)));
            break;
        }
    }
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
        cursor->paintBar(painter); //画toolbar
        if (!cursor->isDragging && !cursor->isShiftPressed) { //如果没有在拉也不是shift状态
            cursor->paintCursor(painter, currentMousePosPoint); //画pie
        }
    }
    painter.end();
}

void MainWindow::mousePressEvent(QMouseEvent* event) //鼠标点击触发
{
    //拖动实现
    QPoint pos = event->pos();
    if (cursor != nullptr) {
        qDebug() << cursor->getIconIndex() << cursor->getTargetIndex();
        cursor->onMouseClick(*event);
        if (needRestart) {
            TimeRecord->restart();
            needRestart = false;
        }
        if (!cursor->isShiftPressed) {
            ui->Feature_Label->setText("当前功能" + QString::number(cursor->getChoseToolIndex()));
            cursor->currentFeature = cursor->getChoseToolIndex();
        }

        timer->start(1); //定时器开始计时，其中1000表示1000ms即1秒
        if (cursor->currentFeature == cursor->getIconIndex()) {
            if (QRect(Rect3PosPoint, QSize(8, 8)).contains(pos) && cursor->getTargetIndex() == 0) { //选择功能
                setCursor(Qt::ClosedHandCursor);
                cursor->isDragging = true;
                cursor->draggingRectType = 3;
            } else if (QRect(Rect2PosPoint, QSize(50, 50)).contains(pos) && cursor->getTargetIndex() == 1) {
                setCursor(Qt::ClosedHandCursor);
                cursor->isDragging = true;
                cursor->draggingRectType = 2;
            } else if (QRect(Rect1PosPoint, QSize(600, 300)).contains(pos) && cursor->getTargetIndex() == 2) {
                setCursor(Qt::ClosedHandCursor);
                cursor->isDragging = true;
                cursor->draggingRectType = 1;
            }
        }

        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (cursor != nullptr) {
        if (cursor->isDragging) {
            cursor->isDragging = false; //关闭拉动状态
            if (cursor->cursorType() == 2) { //pie的时候
                if (cursor->isShiftPressed) { //如果按下shift
                    setCursor(Qt::ArrowCursor);
                } else {
                    setCursor(Qt::BlankCursor);
                }

            } else { //toolbar的时候
                setCursor(Qt::ArrowCursor);
            }

            if (Rect1PosPoint.y() > 500 || Rect2PosPoint.y() > 500 || Rect3PosPoint.y() > 500) { //松开时完成功能
                Rect1PosPoint = QPoint(180, 150); //重置
                Rect2PosPoint = QPoint(455, 275);
                Rect3PosPoint = QPoint(476, 296);
                qDebug() << TimeRecord->elapsed();
                TimeRecord->restart();
                cursor->incrTaskIndex();
                ui->NeedFeature->setText("需求功能" + QString::number(cursor->getIconIndex()));
            }
            update();
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Shift && cursor != nullptr && cursor->cursorType() == 2) {
        //按下时改变鼠标
        cursor->isShiftPressed = true;
        ui->Feature_Label->setText("当前功能" + QString::number(cursor->getChoseToolIndex()));
        cursor->currentFeature = cursor->getChoseToolIndex();

        TimeRecord->restart();
        if (!cursor->isDragging) {
            setCursor(Qt::ArrowCursor);
        }
        update();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Shift && cursor != nullptr && cursor->cursorType() == 2) {
        cursor->isShiftPressed = false;
        TimeRecord->restart();
        if (!cursor->isDragging) {
            setCursor(Qt::BlankCursor);
        }
        update();
    }
}
