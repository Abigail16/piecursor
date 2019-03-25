#ifndef MATHUTILS_H
#define MATHUTILS_H

class QPoint;
class MathUtils {
private:
    MathUtils() {}

public:
    static int calcDirection(const QPoint& x, const QPoint& y, int directionNumber); //计算线位置
    static QPoint calcPointByDirection(const QPoint& center, int radius, int directionNumber, int direction); //计算黑点位置
};

#endif // MATHUTILS_H
