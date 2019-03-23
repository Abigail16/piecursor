#include "toolbar.h"
#include "QMouseEvent"
#include "QPainter"

ToolBar::ToolBar(Cursor::IconNumberEnum e)
    : Cursor(e)
{
    size = Cursor::SMALL_SIZE;
}

void ToolBar::paintBar(QPainter& painter)
{
    const Qt::GlobalColor pieBrushColors[] = { Qt::red, Qt::yellow, Qt::blue, Qt::green, Qt::darkGray, Qt::magenta, Qt::cyan, Qt::black };
    QPoint boundaryOffset(size, size);
    QPoint upperLeftPoint(400, 50);
    QPoint rightOffset(size, 0);
    QVector<QRect> rects;
    for (int i = 0; i < iconNumber; i++) {
        QRect rect(upperLeftPoint, upperLeftPoint + boundaryOffset);
        if (rect.contains(currentMousePosPoint)) {
            painter.setBrush(pieBrushColors[i]);
            painter.drawRect(rect);

            painter.setBrush(Qt::black); //黑点
            painter.drawEllipse(upperLeftPoint.x() + size / 2 - 2, upperLeftPoint.y() + size + 6, 4, 4);

        } else {
            rects.append(rect);
        }
        upperLeftPoint += rightOffset;
    }
    //颜色
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(Qt::white);
    painter.drawRects(rects);
}

void ToolBar::onMouseMove(const QMouseEvent& event)
{
    Cursor::onMouseMove(event);
    currentMousePosPoint = event.pos();
}
