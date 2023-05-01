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

int main()
{

    long long mem, examined;

    int m{4}, n{3};
    Car c1(2, 0, true);
    Car c2(2, 1, false);
    Car c3(1, 1, true);

    vector<Car> cars = {c1, c2, c3};
    vector<pair<int, int>>
        objects = {
            {0, 1}, {2, 2}, {3, 0}};

    Puzzle puzzle(cars, objects, m, n);

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