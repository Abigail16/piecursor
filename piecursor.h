#ifndef PIECURSOR_H
#define PIECURSOR_H

#include "QPoint"
#include "cursor.h"

class PieCursor : public Cursor {
private:
    const int ROUND_DELAY = 5; //鼠标捕捉周期
    QPoint lastMousePosPoint;
    QPoint currentMousePosPoint;
    int roundCount = 0;

public:
    PieCursor(Cursor::IconNumberEnum);
    virtual ~PieCursor() {}
    virtual void paintBar(QPainter&) {}
    virtual void paintCursor(QPainter&, const QPoint&);
    virtual void onMouseMove(const QMouseEvent&);
    virtual int cursorType() { return 2; }
};

#endif // PIECURSOR_H
