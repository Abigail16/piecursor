#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "cursor.h"
#include "QPoint"

class ToolBar : public Cursor
{
private:
    QPoint currentMousePosPoint;
public:
    ToolBar(Cursor::IconNumberEnum);
    virtual ~ToolBar() {}
    virtual void paintBar(QPainter&);
    virtual void paintCursor(QPainter&, const QPoint&) {}
    virtual void onMouseMove(const QMouseEvent&);
};

#endif // TOOLBAR_H
