#include "mathutils.h"
#include "QPoint"
#include "QtMath"
#include "QDebug"

int MathUtils::calcDirection(const QPoint &last, const QPoint &current, int DirectionNumber)
{
    QPoint offset = current - last;
    return static_cast<int>(qAtan2(offset.y(), offset.x()) * DirectionNumber / M_PI + 1 + DirectionNumber * 2) % (DirectionNumber * 2) / 2;
}
