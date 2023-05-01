#ifndef CAR_H
#define CAR_H

using namespace std;

class Car
{
private:
    int x;
    int y;
    bool horizontal;

public:
    Car()
    {
        x = 0;
        y = 0;
        horizontal = false;
    }
    Car(int x, int y, bool horizontal = true)
    {
        this->x = x;
        this->y = y;
        this->horizontal = horizontal;
    }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }

    int getX() { return x; }
    int getY() { return y; }
    bool isHorizontal() { return horizontal; }
    string getKey() const
    {
        return to_string(x) + to_string(y) + to_string(horizontal);
    }

    bool operator==(const Car &c) const
    {
        return x == c.x && y == c.y && horizontal == c.horizontal;
    }
    Car operator=(Car c)
    {
        x = c.x;
        y = c.y;
        horizontal = c.horizontal;
        return *this;
    }
    bool operator<(const Car &c) const
    {
        return this->getKey() < c.getKey();
    }
};

#endif