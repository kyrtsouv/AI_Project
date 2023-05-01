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
            for (Puzzle *child : children)
            {
                if (closed.count(child->getKey()) == 0)
                    agenda.push(child);
            }
        }
    }
    return nullptr;
}

int main()
{

    int TEST = 3;

    long long mem, examined;

    int width, height;
    vector<Car> cars;
    vector<pair<int, int>> objects;
    if (TEST == 1)
    {
        width = 4;
        height = 4;
        cars = {{2, 0}, {2, 1, false}, {1, 1}, {1, 2, false}};
        objects = {
            {0, 1}, {2, 2}, {3, 0}, {1, 3}};
    }
    if (TEST == 2)
    {
        width = 5;
        height = 5;
        cars = {{1, 1, false}, {4, 1}, {1, 3}, {3, 3, false}, {4, 3, false}};
        objects = {
            {1, 0}, {3, 1}, {0, 3}, {4, 4}};
    }
    if (TEST == 3)
    {
        width = 6;
        height = 6;
        cars = {{4, 1, false}, {5, 1}, {0, 3, false}, {2, 4}, {3, 4}, {4, 5, false}};
        objects = {{1, 1}, {5, 3}, {0, 4}};
    }

    Puzzle puzzle(cars, objects, width, height);

    Puzzle *solution = BFS(&puzzle, mem, examined);
    cout << "BFS " << endl
         << "---" << endl;
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