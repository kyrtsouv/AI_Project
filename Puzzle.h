#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>

#include "Car.h"

using namespace std;

class Puzzle
{
private:
    bool **free;
    int width;
    int height;
    string key;
    Puzzle *previous;
    vector<Car> cars;
    vector<pair<int, int>> objects;

public:
    Puzzle(vector<Car> cars, vector<pair<int, int>> objects, int m, int n, Puzzle *previous = NULL);

    void setCars(vector<Car> cars) { this->cars = cars; }
    void setPrevious(Puzzle *p) { previous = p; }
    void setFree(int x, int y, bool value) { free[y][x] = value; }

    bool isFree(int x, int y) { return free[y][x]; }
    bool isGoal() { return cars.empty(); }
    string getKey() { return key; };
    int getDepth();

    vector<Puzzle *> expand();
    bool goRight(Puzzle *&puzzle, int carIndex);
    bool goLeft(Puzzle *&puzzle, int carIndex);
    bool goUp(Puzzle *&puzzle, int carIndex);
    bool goDown(Puzzle *&puzzle, int carIndex);
};

#endif