#include "../core/puzzle_state.h"
#include "../core/utils.h"
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <ctime>

std::vector<PuzzleState> solveWithAnnealing(PuzzleState initial) {
    std::vector<PuzzleState> path;

    PuzzleState current = initial;
    current.cost = calculateManhattan(current);
    path.push_back(current);

    double T = 1.0;
    double T_min = 0.01;
    double alpha = 0.99;

    while (T > T_min && current.cost > 0) {
        for (int i = 0; i < 100; i++) {
            if (current.cost == 0) break;

             // pega todos os vizinhos
            auto neighbors = getNeighbors(current);

            // escolhe um aleatório
            PuzzleState next = neighbors[rand() % neighbors.size()];

            int deltaE = next.cost - current.cost;

            double prob = (double)rand() / RAND_MAX;

            // Aceitação baseada em custo ou probabilidade
            if (deltaE < 0 || prob < exp(-deltaE / T)) {
                current = next;
                path.push_back(current);
            }
        }

        T *= alpha;
    }
    return path;
}