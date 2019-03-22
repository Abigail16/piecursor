#ifndef PIECURSOR_H
#define PIECURSOR_H

#include "cursor.h"
#include "QPoint"

class PieCursor : public Cursor
{
private:
    const int ROUND_DELAY = 5; //鼠标捕捉周期
    QPoint lastMousePosPoint;
    QPoint currentMousePosPoint;
    int choseToolDirection = 0;
    int roundCount = 0;
public:
    PieCursor(Cursor::IconNumberEnum);
    virtual ~PieCursor() {}
    virtual void paintBar(QPainter&) {}
    virtual void paintCursor(QPainter&, const QPoint&);
    virtual void onMouseMove(const QMouseEvent&);
    virtual void dragEvent(QPainter&, const QPoint&);
    virtual int cursorType(){return 2;}
};

#endif // PIECURSOR_H
