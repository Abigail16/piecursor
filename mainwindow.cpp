#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QPainter"
#include "QMouseEvent"
#include <QtMath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    mousePosPoint = event->pos();
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::white);
    painter.drawEllipse(mousePosPoint, OuterCircleR, OuterCircleR);
    QVector<QLine> lines;
    for (int i = 1; i < 8; i += 2) {
        lines.append(QLine(mousePosPoint.x() + OuterCircleR * qSin(M_PI * i / 8),
                           mousePosPoint.y() + OuterCircleR * qCos(M_PI * i / 8),
                           mousePosPoint.x() - OuterCircleR * qSin(M_PI * i / 8),
                           mousePosPoint.y() - OuterCircleR * qCos(M_PI * i / 8)));
    }

    painter.drawLines(lines);

    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    painter.drawEllipse(mousePosPoint, InnerCircleR, InnerCircleR);

    painter.end();
}
