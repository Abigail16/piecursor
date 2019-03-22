#include "piecursor.h"
#include "QPainter"
#include "QtMath"
#include "QMouseEvent"
#include "mathutils.h"
#include "QDebug"

PieCursor::PieCursor(Cursor::IconNumberEnum e) : Cursor(e)
{
    size = Cursor::SMALL_SIZE;
}


void PieCursor::paintCursor(QPainter &painter, const QPoint &point) {
    int radius = size / 2;

    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(Qt::white);
    QPoint boundaryOffset(radius, radius);
    QRect boundary(point - boundaryOffset, point + boundaryOffset);
    painter.drawEllipse(boundary);

    QVector<QLine> lines;//画圆
    for (int i = 8 / iconNumber; i < 8; i += 16 / iconNumber) {

        QPoint offsetValue(static_cast<int>(radius * qSin(M_PI_4 * i / 2)),
                           static_cast<int>(radius * qCos(M_PI_4 * i / 2)));
        lines.append(QLine(point + offsetValue,
                           point - offsetValue));
    }
    painter.drawLines(lines);

    const Qt::GlobalColor pieBrushColors[] = {Qt::red, Qt::yellow, Qt::blue, Qt::green, Qt::darkGray, Qt::magenta, Qt::cyan, Qt::black};
    painter.setBrush(pieBrushColors[choseToolDirection]);//扇形
    painter.drawPie(boundary, 5760 - 2880 / iconNumber - choseToolDirection * 5760 / iconNumber, 5760 / iconNumber);

    painter.setBrush(Qt::black);//黑点
    painter.drawEllipse(MathUtils::calcPointByDirection(point, radius + 8, iconNumber, choseToolDirection), 3, 3);

}

void PieCursor::onMouseMove(const QMouseEvent &event) {//计算在哪一块
    currentMousePosPoint = event.pos();
    if (++roundCount == ROUND_DELAY) {
        choseToolDirection = MathUtils::calcDirection(lastMousePosPoint, currentMousePosPoint, iconNumber);
        lastMousePosPoint = currentMousePosPoint;
        roundCount = 0;
        //qDebug() << choseToolDirection;
    }
}
void PieCursor::dragEvent(QPainter &painter, const QPoint &point)
{
    if(getType == 1)
    {
        QBrush brush3(QColor(255, 255, 255), Qt::SolidPattern); // 画刷
        painter.setBrush(brush3);                               // 设置画刷
        painter.drawRect(point.x(), point.y(), 8, 8);
    }
    if(getType == 2)
    {
        QBrush brush2(QColor(169, 169, 169), Qt::SolidPattern); // 画刷
        painter.setBrush(brush2);                               // 设置画刷
        painter.drawRect(point.x(), point.y(), 50, 50);
    }
    if(getType == 3)
    {
        QBrush brush3(QColor(211, 211, 211), Qt::SolidPattern); // 画刷
        painter.setBrush(brush3);                               // 设置画刷
        painter.drawRect(point.x(), point.y(), 600, 300);
    }
}
