#include <vector>
#include "../core/puzzle_state.h"
#include "../core/utils.h"
#include <string>
#include <set>
#include <queue>

std::string stateHash(const PuzzleState &s) {
    std::string h;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            h += std::to_string(s.board[i][j]) + ",";
        }
    }
    return h;
}

std::vector<PuzzleState> solveWithTabu(PuzzleState initial) {
    std::vector<PuzzleState> path;

    PuzzleState current = initial;
    current.cost = calculateManhattan(current);

    PuzzleState best = current;

    std::set<std::string> tabuSet;
    std::queue<std::string> tabuQueue;

    int TABU_SIZE = 50;
    int MAX_ITERS = 10000;

    path.push_back(current);

    for (int iter = 0; iter < MAX_ITERS; iter++) {

        if (current.cost == 0)
            break;

        auto neighbors = getNeighbors(current);

        PuzzleState bestNeighbor;
        bool found = false;
        int bestCost = INT_MAX;

        for (auto &n : neighbors) {

            std::string hash = stateHash(n); // você precisa implementar

            // 🔴 se está na tabu list, ignora
            if (tabuSet.count(hash))
                continue;

            n.cost = calculateManhattan(n);

            if (!found || n.cost < bestCost) {
                bestNeighbor = n;
                bestCost = n.cost;
                found = true;
            }
        }

        // se tudo tabu, relaxa regra (aspiration criteria simples)
        if (!found) {
            bestNeighbor = neighbors[0];
            bestNeighbor.cost = calculateManhattan(bestNeighbor);
        }

        current = bestNeighbor;
        path.push_back(current);

        // atualiza melhor global
        if (current.cost < best.cost)
            best = current;

        // adiciona na tabu list
        std::string h = stateHash(current);

        tabuSet.insert(h);
        tabuQueue.push(h);

        if (tabuQueue.size() > TABU_SIZE) {
            tabuSet.erase(tabuQueue.front());
            tabuQueue.pop();
        }
    }

    return path;
}