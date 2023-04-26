#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include "Car.h"

using namespace std;

class Puzzle
{
public:
    Puzzle(vector<Car> cars, vector<pair<int, int>> objects, int m, int n);

    bool isGoal();
    vector<Puzzle *> expand();
    bool myCompare(Car c1, Car c2);
    bool operator==(const Puzzle &p) const;

private:
    bool **free;
    int width, height;
    Puzzle *previous;
    vector<Car> cars;
};

#endif