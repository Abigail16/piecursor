#include "toolbar.h"
#include "QPainter"
#include "QMouseEvent"

ToolBar::ToolBar(Cursor::IconNumberEnum e) : Cursor(e)
{
    size = Cursor::SMALL_SIZE;
}

void ToolBar::paintBar(QPainter &painter) {
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(Qt::white);
    QPoint boundaryOffset(size, size);
    QPoint upperLeftPoint(400, 50);
    QPoint rightOffset(size, 0);
    QVector<QRect> rects;
    for (int i=0; i<iconNumber; i++) {
        rects.append(QRect(upperLeftPoint, upperLeftPoint + boundaryOffset));
        upperLeftPoint += rightOffset;
    }
    //颜色
    painter.drawRects(rects);

}

