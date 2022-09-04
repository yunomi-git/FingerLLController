#ifndef __DIRECTION__
#define __DIRECTION__

struct Direction
{
    Direction() = default;
    
    Direction(float dir)
    {
        value = dir;
    }

    boolean equals(Direction d)
    {
        return d.value == value;
    }

    float value;
};

const Direction POSITIVE_DIRECTION = Direction(1.0);
const Direction NEGATIVE_DIRECTION = Direction(-1.0);

#endif