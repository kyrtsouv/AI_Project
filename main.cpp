#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

#include "Puzzle.h"

using namespace std;

Puzzle *BFS(Puzzle *puzzle, long long &mem, long long &examined)
{
    queue<Puzzle *> agenda;
    unordered_map<string, Puzzle *> closed;

    agenda.push(puzzle);
    examined = 0;
    mem = 1;

    Puzzle *current;
    while (agenda.size() > 0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();

        current = agenda.front();
        agenda.pop();

        if (current->isGoal())
            return current;
        if (closed.count(current->getKey()) == 0)
        {
            examined++;
            closed.insert({current->getKey(), current});
            vector<Puzzle *> children = current->expand();
            for (int i = 0; i < children.size(); i++)
            {
                if (closed.count(children[i]->getKey()) == 0)
                    agenda.push(children[i]);
            }
        }
    }
    return nullptr;
}

#define TEST 2
int main()
{

    long long mem, examined;

    int width, height;
    vector<Car> cars;
    vector<pair<int, int>> objects;
    if (TEST == 1)
    {
        width = 4;
        height = 3;
        Car c1{2, 0, true};
        Car c2{2, 1, false};
        Car c3{1, 1, true};
        cars = {c1, c2, c3};
        objects = {
            {0, 1}, {2, 2}, {3, 0}};
    }
    if (TEST == 2)
    {
        width = 5;
        height = 5;
        Car c1{1, 1, false};
        Car c2{4, 1, true};
        Car c3{1, 3, true};
        Car c4{3, 3, false};
        Car c5{4, 3, false};
        cars = {c1, c2, c3, c4, c5};
        objects = {
            {1, 0}, {3, 1}, {0, 3}, {4, 4}};
    }
    Puzzle puzzle(cars, objects, width, height);

    Puzzle *solution = BFS(&puzzle, mem, examined);
    cout << "BFS: " << endl;
    if (solution == nullptr)
        cout << "No solution found" << endl;
    else
    {
        cout << "Examined: " << examined << endl;
        cout << "Memory: " << mem << endl;
        cout << "Depth: " << solution->getDepth() << endl;
    }

    return 0;
}