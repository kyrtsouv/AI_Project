#ifndef CAR_H
#define CAR_H

class Car
{
private:
    int x;
    int y;
    bool horizontal;

public:
    Car(int x, int y, bool horizontal)
    {
        this->x = x;
        this->y = y;
        this->horizontal = horizontal;
    }
    int getX() { return x; }
    int getY() { return y; }
    bool isHorizontal() { return horizontal; }

    bool operator==(const Car &c) const
    {
        return x == c.x && y == c.y && horizontal == c.horizontal;
    }
    bool operator=(Car c)
    {
        x = c.x;
        y = c.y;
        horizontal = c.horizontal;
        return true;
    }
};

#endif