#include <vector>
#include "../core/puzzle_state.h"
#include "../core/utils.h"
#include <climits>

int TABU_SIZE = 50;
int MAX_ITERS = 10000;

// verifica se está na tabu list
bool isTabu(const PuzzleState &s, const std::vector<PuzzleState> &tabuList)
{
    for (const auto &t : tabuList)
    {
        if (t == s)
            return true;
    }
    return false;
}

// tabu search
std::vector<PuzzleState> solveWithTabu(PuzzleState initial)
{
    std::vector<PuzzleState> path;
    std::vector<PuzzleState> tabuList;

    PuzzleState current = initial;
    current.cost = calculateManhattan(current);

    PuzzleState best = current;

    path.push_back(current);

    for (int iter = 0; iter < MAX_ITERS; iter++)
    {

        if (current.cost == 0)
            break;

        auto neighbors = getNeighbors(current);

        PuzzleState bestNeighbor;
        bool found = false;
        int bestCost = INT_MAX;

        for (auto &n : neighbors)
        {

            n.cost = calculateManhattan(n);

            // tabu + aspiration
            if (isTabu(n, tabuList) && n.cost >= best.cost)
                continue;

            if (!found || n.cost < bestCost)
            {
                bestNeighbor = n;
                bestCost = n.cost;
                found = true;
            }
        }

        // aspiration simples (se tudo tabu)
        if (!found)
        {
            bestNeighbor = neighbors[0];
            bestNeighbor.cost = calculateManhattan(bestNeighbor);
        }

        current = bestNeighbor;
        path.push_back(current);

        // atualiza melhor global
        if (current.cost < best.cost)
            best = current;

        // adiciona na tabu list
        tabuList.push_back(current);

        if (tabuList.size() > TABU_SIZE)
        {
            tabuList.erase(tabuList.begin()); // remove o mais antigo
        }
    }

    return path;
}