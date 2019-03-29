#include "mathutils.h"
#include "QDebug"
#include "QPoint"
#include "QRandomGenerator"
#include "QtMath"

int MathUtils::calcDirection(const QPoint& last, const QPoint& current, int directionNumber) //计算功能块选择
{
    QPoint offset = current - last;
    return static_cast<int>(qAtan2(offset.y(), offset.x()) * directionNumber / M_PI + 1 + directionNumber * 2) % (directionNumber * 2) / 2;
}

QPoint MathUtils::calcPointByDirection(const QPoint& center, int radius, int directionNumber, int direction) //黑点位置计算
{
    QPoint offset(static_cast<int>(radius * qCos(direction * M_PI * 2 / directionNumber)),
        static_cast<int>(radius * qSin(direction * M_PI * 2 / directionNumber)));
    return center + offset;
}

QVector<int> MathUtils::genRandVector(int iconNumber, int targetNumber)
{
    QRandomGenerator* randGenerator = QRandomGenerator::global();
    QVector<int> randVector;
    int maxSize = iconNumber * targetNumber;
    for (int value = 0; value < maxSize; value++) {
        int index = randGenerator->bounded(value + 1);
        randVector.insert(index, value);
    }
    return randVector;
}
