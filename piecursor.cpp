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
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::white);
    QPoint boundaryOffset(size / 2, size / 2);
    QRect boundary(point - boundaryOffset, point + boundaryOffset);
    painter.drawEllipse(boundary);

    QVector<QLine> lines;
    for (int i = 8 / iconNumber; i < 8; i += 16 / iconNumber) {

        QPoint offsetValue(static_cast<int>(size * qSin(M_PI_4 * i / 2) / 2),
                           static_cast<int>(size * qCos(M_PI_4 * i / 2) / 2));
        lines.append(QLine(point + offsetValue,
                           point - offsetValue));
    }
    painter.drawLines(lines);

    painter.setBrush(Qt::red);
    painter.drawPie(boundary, 5760 - 2880 / iconNumber - choseToolDirection * 5760 / iconNumber, 5760 / iconNumber);
}

void PieCursor::onMouseMove(const QMouseEvent &event) {
    currentMousePosPoint = event.pos();
    if (++roundCount == ROUND_DELAY) {
        choseToolDirection = MathUtils::calcDirection(lastMousePosPoint, currentMousePosPoint, iconNumber);
        lastMousePosPoint = currentMousePosPoint;
        roundCount = 0;
        qDebug() << choseToolDirection;
    }
}
