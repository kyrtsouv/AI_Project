#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Puzzle.h"

using namespace std;

Puzzle *BFS(Puzzle *puzzle, long long &mem, long long &examined)
{
    queue<Puzzle *> agenda;
    vector<Puzzle> closed;

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
        if (find(closed.begin(), closed.end(), *current) == closed.end())
        {
            examined++;
            closed.push_back(*current);
            vector<Puzzle *> children = current->expand();
            for (Puzzle *child : children)
                if (find(closed.begin(), closed.end(), *child) == closed.end())
                    agenda.push(child);
        }
    }
    return nullptr;
}

int main()
{

    long long mem, examined;

    int m{4}, n{3};
    vector<Car> cars = {
        Car(2, 0, true),
        Car(2, 1, false),
        Car(1, 1, true)};

    vector<pair<int, int>> objects = {
        make_pair(0, 1),
        make_pair(2, 2),
        make_pair(3, 0)};

    Puzzle puzzle(cars, objects, m, n);

    Puzzle *solution = BFS(&puzzle, mem, examined);
}