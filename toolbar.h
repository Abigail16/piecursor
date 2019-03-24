#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "QPoint"
#include "QRect"
#include "cursor.h"
#include "QVector"

class ToolBar : public Cursor {
private:
    QPoint currentMousePosPoint;
    int selectedIndex = -1;
    QVector<QRect> rects;
    QPoint upperLeftPoint;
    const Qt::GlobalColor pieBrushColors[8] = { Qt::red, Qt::yellow, Qt::blue, Qt::green, Qt::darkGray, Qt::magenta, Qt::cyan, Qt::black };

public:
    ToolBar(Cursor::IconNumberEnum);
    virtual ~ToolBar() {}
    virtual void paintBar(QPainter&);
    virtual void paintCursor(QPainter&, const QPoint&) {}
    virtual void onMouseMove(const QMouseEvent&);
    virtual int cursorType() { return 1; }
    virtual void onMouseClick(const QMouseEvent&);
};

#endif // TOOLBAR_H
