#ifndef MATHUTILS_H
#define MATHUTILS_H

class QPoint;
class MathUtils
{
private:
    MathUtils() {}
public:
    static int calcDirection(const QPoint &x, const QPoint &y, int DirectionNumber);
};

#endif // MATHUTILS_H
