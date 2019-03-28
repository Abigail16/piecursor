#include "toolbar.h"
#include "QMouseEvent"
#include "QPainter"
#include "mathutils.h"

ToolBar::ToolBar(Cursor::IconNumberEnum e)//初始矩形
    : Cursor(e)
{
    size = Cursor::SMALL_SIZE;
    upperLeftPoint = QPoint(400, 50);
    QPoint boundaryOffset(size, size);
    QPoint rightOffset(size, 0);
    for (int i = 0; i < iconNumber; i++) {
        QRect rect(upperLeftPoint, upperLeftPoint + boundaryOffset);
        rects.append(rect);
        upperLeftPoint += rightOffset;
    }
}

void ToolBar::paintBar(QPainter& painter)//颜色
{
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(Qt::white);
    painter.drawRects(rects);

    for (int i=0; i<iconNumber; i++) {
        const QRect &rect = rects.at(i);
        if (rect.contains(currentMousePosPoint)) {
            painter.setBrush(pieBrushColors[i]);
            painter.drawRect(rect);
            painter.setBrush(Qt::black); //黑点
            painter.drawEllipse(rect.center().x() - 2, rect.bottom() + 6, 4, 4);
            break;
        }
    }

    if (choseToolDirection >= 0) {//已经选中时，颜色不变
        const QRect &rect = rects.at(choseToolDirection);
        painter.setBrush(pieBrushColors[choseToolDirection]);
        painter.drawRect(rect);
    }
}

void ToolBar::onMouseMove(const QMouseEvent& event)
{
    currentMousePosPoint = event.pos();
}

void ToolBar::onMouseClick(const QMouseEvent& event)//点击的时候
{
    for (int i=0; i<iconNumber; i++) {
        const QRect &rect = rects.at(i);
        if (rect.contains(event.pos())) {
            choseToolDirection = i;
            break;
        }
    }
}
