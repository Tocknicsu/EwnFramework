#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

struct Movement {
    int index;
    enum Direction {
        None,
        Down,
        Right,
        RightDown
    } direction;
};

#endif
