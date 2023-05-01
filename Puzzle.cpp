#include <algorithm>

#include "Puzzle.h"

Puzzle::Puzzle(vector<Car> cars, vector<pair<int, int>> objects, int width, int height, Puzzle *previous)
{
    this->cars = cars;
    this->objects = objects;
    this->width = width;
    this->height = height;
    this->previous = previous;
    sort(cars.begin(), cars.end());

    free = new bool *[height];
    for (int i = 0; i < height; i++)
    {
        free[i] = new bool[width];
        for (int j = 0; j < width; j++)
            free[i][j] = true;
    }

    for (pair<int, int> object : objects)
        free[object.second][object.first] = false;

    for (Car car : cars)
        free[car.getY()][car.getX()] = false;

    key = "";
    for (Car car : cars)
        key += car.getKey();
}

int Puzzle::getDepth()
{
    if (previous == NULL)
        return 0;
    return previous->getDepth() + 1;
}

vector<Puzzle *> Puzzle::expand()
{
    vector<Puzzle *> children;
    Puzzle *child;

    for (int i = 0; i < cars.size(); i++)
        if (cars[i].isHorizontal())
        {
            if (goRight(child, i))
                children.push_back(child);
            if (goLeft(child, i))
                children.push_back(child);
        }
        else
        {
            if (goUp(child, i))
                children.push_back(child);
            if (goDown(child, i))
                children.push_back(child);
        }

    return children;
}

bool Puzzle::goRight(Puzzle *&puzzle, int carIndex)
{
    vector<Car> new_cars = this->cars;
    Car car = new_cars[carIndex];

    if (car.getX() + 1 == width)
    {
        new_cars.erase(new_cars.begin() + carIndex);
        puzzle = new Puzzle(new_cars, objects, width, height, this);
        return true;
    }
    if (isFree(car.getX() + 1, car.getY()))
    {
        new_cars[carIndex].setX(car.getX() + 1);
        puzzle = new Puzzle(new_cars, objects, width, height, this);
        return true;
    }
    return false;
}
bool Puzzle::goLeft(Puzzle *&puzzle, int carIndex)
{
    vector<Car> new_cars = this->cars;
    Car car = new_cars[carIndex];
    if (car.getX() == 0)
    {
        new_cars.erase(new_cars.begin() + carIndex);
        puzzle = new Puzzle(new_cars, objects, width, height, this);
        return true;
    }
    if (isFree(car.getX() - 1, car.getY()))
    {
        new_cars[carIndex].setX(car.getX() - 1);
        puzzle = new Puzzle(new_cars, objects, width, height, this);
        return true;
    }
    return false;
}
bool Puzzle::goUp(Puzzle *&puzzle, int carIndex)
{
    vector<Car> new_cars = this->cars;
    Car car = new_cars[carIndex];
    if (car.getY() == 0)
    {
        new_cars.erase(new_cars.begin() + carIndex);
        puzzle = new Puzzle(new_cars, objects, width, height, this);
        return true;
    }
    if (isFree(car.getX(), car.getY() - 1))
    {
        new_cars[carIndex].setY(car.getY() - 1);
        puzzle = new Puzzle(new_cars, objects, width, height, this);
        return true;
    }
    return false;
}
bool Puzzle::goDown(Puzzle *&puzzle, int carIndex)
{
    vector<Car> new_cars = this->cars;
    Car car = new_cars[carIndex];
    if (car.getY() == height - 1)
    {
        new_cars.erase(new_cars.begin() + carIndex);
        puzzle = new Puzzle(new_cars, objects, width, height, this);
        return true;
    }
    if (isFree(car.getX(), car.getY() + 1))
    {
        new_cars[carIndex].setY(car.getY() + 1);
        puzzle = new Puzzle(new_cars, objects, width, height, this);
        return true;
    }
    return false;
}