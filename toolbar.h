#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "cursor.h"

class ToolBar : public Cursor
{
public:
    ToolBar(Cursor::IconNumberEnum);
    virtual ~ToolBar() {}
    virtual void paintBar(QPainter&);
    virtual void paintCursor(QPainter&, const QPoint&) {}
    virtual void onMouseMove(const QMouseEvent&) {}
};

#endif // TOOLBAR_H
