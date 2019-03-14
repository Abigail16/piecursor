#ifndef BIGWHEEL_H
#define BIGWHEEL_H

#include "piecursor.h"

class BigWheel : public PieCursor
{
public:
    BigWheel(Cursor::IconNumberEnum);

    virtual ~BigWheel() {}
};

#endif // BIGWHEEL_H
