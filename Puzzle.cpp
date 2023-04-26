#include <algorithm>
#include <iostream>

#include "Puzzle.h"

Puzzle::Puzzle(unordered_map<string, Car> cars, vector<pair<int, int>> objects, int width, int height)
{
    this->cars = cars;
    this->width = width;

    free = new bool *[height];
    for (int i = 0; i < height; i++)
    {
        free[i] = new bool[width];
        for (int j = 0; j < width; j++)
            free[i][j] = true;
    }

    for (pair<int, int> object : objects)
        free[object.second][object.first] = false;

    for (auto &car : cars)
        free[car.second.getY()][car.second.getX()] = false;

    auto comparator = [width](Car &c1, Car &c2)
    { return c1.getY() * width + c1.getX() < c2.getY() * width + c2.getX(); };
    sort((this->cars).begin(), (this->cars).end(), comparator);
}

bool Puzzle::goRight(Puzzle &puzzle, Car &car)
{
    if (car.getX() >= width - 1 || !puzzle.isFree(car.getX(), car.getY()))
        return false;
    puzzle = *this;

    puzzle.setFree(car.getX(), car.getY(), true);
    puzzle.setFree(car.getX() + 1, car.getY(), false);
    puzzle.cars[car.getKey()].setX(car.getX() + 1);

    puzzle.setPrevious(this);
    return true;
}
bool Puzzle::goLeft(Puzzle &puzzle, Car &car) {}
bool Puzzle::goUp(Puzzle &puzzle, Car &car) {}
bool Puzzle::goDown(Puzzle &puzzle, Car &car) {}

vector<Puzzle *> Puzzle::expand()
{
    vector<Puzzle *> children;
    Puzzle *child;

    for (auto &car : cars)
    {

        if (car.second.isHorizontal())
        {
            child = new Puzzle(*this);
            if (goRight(*child, car.second))
                children.push_back(child);
            else
                delete child;

            child = new Puzzle(*this);
            if (goLeft(*child, car.second))
                children.push_back(child);
            else
                delete child;
        }
        else
        {
            child = new Puzzle(*this);
            if (goUp(*child, car.second))
                children.push_back(child);
            else
                delete child;

            child = new Puzzle(*this);
            if (goDown(*child, car.second))
                children.push_back(child);
            else
                delete child;
        }
    }
}

bool Puzzle::isGoal()
{
    return cars.size() == 0;
}

bool Puzzle::operator==(const Puzzle &p) const
{
    return cars == p.cars;
}
