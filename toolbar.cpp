#include "toolbar.h"
#include "QPainter"

ToolBar::ToolBar(Cursor::IconNumberEnum e) : Cursor(e)
{
    size = Cursor::SMALL_SIZE;
}

void ToolBar::paintBar(QPainter &painter) {
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::white);
    QPoint boundaryOffset(size, size);
    QPoint upperLeftPoint(700, 50);
    QPoint rightOffset(size, 0);
    QVector<QRect> rects;
    for (int i=0; i<iconNumber; i++) {
        rects.append(QRect(upperLeftPoint, upperLeftPoint + boundaryOffset));
        upperLeftPoint += rightOffset;
    }
    painter.drawRects(rects);
}
