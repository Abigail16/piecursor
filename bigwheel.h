#ifndef BIGWHEEL_H
#define BIGWHEEL_H

#include "piecursor.h"

class BigWheel : public PieCursor {
public:
    BigWheel(Cursor::IconNumberEnum);

    virtual ~BigWheel() {}
    virtual int cursorType() { return 3; }
};

#endif // BIGWHEEL_H
