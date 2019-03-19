#ifndef MATHUTILS_H
#define MATHUTILS_H

class QPoint;
class MathUtils
{
private:
    MathUtils() {}
public:
    static int calcDirection(const QPoint &x, const QPoint &y, int directionNumber);
    static QPoint calcPointByDirection(const QPoint &center, int radius, int directionNumber, int direction);
};

#endif // MATHUTILS_H
