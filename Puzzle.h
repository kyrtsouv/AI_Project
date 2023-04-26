#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <unordered_map>
#include <string>

#include "Car.h"

using namespace std;

class Puzzle
{
private:
    bool **free;
    int width;
    Puzzle *previous;
    unordered_map<string, Car> cars;

public:
    Puzzle(unordered_map<string, Car> cars, vector<pair<int, int>> objects, int m, int n);

    void setPrevious(Puzzle *p) { previous = p; }
    void setFree(int x, int y, bool value) { free[y][x] = value; }

    bool isFree(int x, int y) { return free[y][x]; }

    vector<Puzzle *> expand();
    bool goRight(Puzzle &puzzle, Car &car);
    bool goLeft(Puzzle &puzzle, Car &car);
    bool goUp(Puzzle &puzzle, Car &car);
    bool goDown(Puzzle &puzzle, Car &car);

    bool isGoal();
    bool operator==(const Puzzle &p) const;
};

#endif