#ifndef CURSOR_H
#define CURSOR_H

#include "mathutils.h"

#include <QVector>

class QPainter;
class QPoint;
class QMouseEvent;
class Cursor {
protected:
    const int SMALL_SIZE = 32; //像素大小
    const int BIG_SIZE = 128;
    int iconNumber;
    int size;
    int choseToolDirection = -1;
    int taskIndex = 0;

public:
    enum IconNumberEnum { Four,
        Eight }; //功能数量
    bool isDragging = false;
    bool isShiftPressed = false;
    int draggingRectType = 0;
    int getChoseToolIndex() { return choseToolDirection; }

    QVector<int> randVector;

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
        randVector = MathUtils::genRandVector(iconNumber, 3);
    }

    int currentFeature = -1;

    int getIconIndex()
    {
        return randVector.at(taskIndex) % iconNumber;
    }

    int getTargetIndex()
    {
        return randVector.at(taskIndex) / iconNumber;
    }

    int incrTaskIndex()
    {
        taskIndex = (taskIndex + 1) % (iconNumber * 3);
        return taskIndex;
    }

    virtual ~Cursor() {}
    virtual void paintBar(QPainter&) {}
    virtual void paintCursor(QPainter&, const QPoint&) {}
    virtual void onMouseMove(const QMouseEvent&) {}
    virtual void onMouseClick(const QMouseEvent&) {}
    virtual int cursorType() = 0;
};

#endif // CURSOR_H
