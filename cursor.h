#ifndef CURSOR_H
#define CURSOR_H

class QPainter;
class QPoint;
class QMouseEvent;
class Cursor {
protected:
    const int SMALL_SIZE = 32; //像素大小
    const int BIG_SIZE = 128;
    int iconNumber;
    int size;

public:
    enum IconNumberEnum { Four,
        Eight }; //功能数量
    bool isDragging = false;
    int draggingRectType = 0;
    Cursor(IconNumberEnum e)
    {
        switch (e) {
        case IconNumberEnum::Four:
            iconNumber = 4;
            break;
        case IconNumberEnum::Eight:
            iconNumber = 8;
            break;
        }
    }

    virtual ~Cursor() {}
    virtual void paintBar(QPainter&) {}
    virtual void paintCursor(QPainter&, const QPoint&) {}
    virtual void onMouseMove(const QMouseEvent&) {}
    virtual int cursorType() = 0;
};

#endif // CURSOR_H
