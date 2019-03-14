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
    const int ROUND_DELAY = 10;
    static int roundCount = 0;

    currentMousePosPoint = event->pos();

    if (++roundCount == ROUND_DELAY) {
        choseToolDirection = calcDirection(lastMousePosPoint, currentMousePosPoint);
        lastMousePosPoint = currentMousePosPoint;
        roundCount = 0;
        qDebug() << choseToolDirection;
    }

    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);

    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::white);
    QPoint boundaryOffset(OuterCircleR, OuterCircleR);
    QRect boundary(currentMousePosPoint - boundaryOffset, currentMousePosPoint + boundaryOffset);
    painter.drawEllipse(boundary);

    QVector<QLine> lines;
    for (int i = 1; i < 8; i += 2) {
        QPoint offsetValue(static_cast<int>(OuterCircleR * qSin(M_PI_4 * i / 2)),
                           static_cast<int>(OuterCircleR * qCos(M_PI_4 * i / 2)));
        lines.append(QLine(currentMousePosPoint + offsetValue,
                           currentMousePosPoint - offsetValue));
    }
    painter.drawLines(lines);

    painter.setBrush(Qt::red);
    painter.drawPie(boundary, 5400 - choseToolDirection * 720, 720);

    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    painter.drawEllipse(currentMousePosPoint, InnerCircleR, InnerCircleR);

    painter.end();
}

MainWindow::Direction MainWindow::calcDirection(QPoint last, QPoint current)
{
    QPoint offset = current - last;
    return static_cast<MainWindow::Direction>((static_cast<int>(qAtan2(offset.y(), offset.x()) / (M_PI_4 / 2)) + 17) % 16 / 2);
}
