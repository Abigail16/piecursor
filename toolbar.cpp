#include "toolbar.h"
#include "QMouseEvent"
#include "QPainter"

ToolBar::ToolBar(Cursor::IconNumberEnum e)
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

void ToolBar::paintBar(QPainter& painter)
{
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(Qt::white);
    painter.drawRects(rects);

    for (int i=0; i<iconNumber; i++) {
        const QRect &rect = rects.at(i);
        if (rect.contains(currentMousePosPoint)) {
            painter.setBrush(Qt::black); //黑点
            painter.drawEllipse(rect.center().x() - 2, rect.bottom() + 6, 4, 4);
            break;
        }
    }

    if (selectedIndex >= 0) {
        const QRect &rect = rects.at(selectedIndex);
        painter.setBrush(pieBrushColors[selectedIndex]);
        painter.drawRect(rect);
    }
}

void ToolBar::onMouseMove(const QMouseEvent& event)
{
    currentMousePosPoint = event.pos();
}

void ToolBar::onMouseClick(const QMouseEvent& event)
{
    for (int i=0; i<iconNumber; i++) {
        const QRect &rect = rects.at(i);
        if (rect.contains(event.pos())) {
            selectedIndex = i;
            break;
        }
    }
}
