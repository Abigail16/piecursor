#ifndef PIECURSOR_H
#define PIECURSOR_H

#include "cursor.h"
#include "QPoint"

class PieCursor : public Cursor
{
private:
    const int ROUND_DELAY = 3;
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
};

#endif // PIECURSOR_H
