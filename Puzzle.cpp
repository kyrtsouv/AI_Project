#include <algorithm>
#include <iostream>

#include "Puzzle.h"

Puzzle::Puzzle(vector<Car> cars, vector<pair<int, int>> objects, int width, int height)
{
    this->cars = cars;
    this->width = width;
    this->height = height;
    free = new bool *[height];
    for (int i = 0; i < height; i++)
    {
        free[i] = new bool[width];
        for (int j = 0; j < width; j++)
            free[i][j] = true;
    }

    for (Car car : cars)
        free[car.getY()][car.getX()] = false;

    for (pair<int, int> object : objects)
        free[object.second][object.first] = false;
}

bool Puzzle::isGoal()
{
    return cars.size() == 0;
}

vector<Puzzle *> Puzzle::expand()
{
}

bool Puzzle::operator==(const Puzzle &p) const
{
    sort(cars.begin(), cars.end(), myCompare);
    // sort(p.cars.begin(), p.cars.end(), myCompare);
    return cars == p.cars;
}

bool Puzzle::myCompare(Car c1, Car c2)
{
    // return c1.getY() * width + c1.getX() < c2.getY() * width + c2.getX();
    return true;
}