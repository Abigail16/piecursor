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
    //virtual void dragEvent(const QMouseEvent&) {}
    virtual int cursorType(){return 1;}
};

#endif // TOOLBAR_H
