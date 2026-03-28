#include "../core/puzzle_state.h"
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <ctime>

// Heurística de Manhattan
int calculateManhattan(const PuzzleState& s) {
    int distance = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int val = s.board[i][j];
            if (val != 0) {
                int targetRow = (val - 1) / 3;
                int targetCol = (val - 1) % 3;
                distance += abs(i - targetRow) + abs(j - targetCol);
            }
        }
    }
    return distance;
}

// Gera vizinho movendo o espaço vazio
PuzzleState getNeighbor(PuzzleState current) {
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    while (true) {
        int dir = rand() % 4;
        int nextR = current.emptyRow + dr[dir];
        int nextC = current.emptyCol + dc[dir];
        if (nextR >= 0 && nextR < 3 && nextC >= 0 && nextC < 3) {
            std::swap(current.board[current.emptyRow][current.emptyCol], current.board[nextR][nextC]);
            current.emptyRow = nextR;
            current.emptyCol = nextC;
            current.cost = calculateManhattan(current);
            return current;
        }
    }
}

std::vector<PuzzleState> solveWithAnnealing(PuzzleState initial) {
    std::vector<PuzzleState> path;
    PuzzleState current = initial;
    current.cost = calculateManhattan(current);
    path.push_back(current);

    double T = 1.0;
    double T_min = 0.01;
    double alpha = 0.999;

    srand(time(NULL));

    while (T > T_min && current.cost > 0) {
        for (int i = 0; i < 100; i++) {
            if (current.cost == 0) break;

            PuzzleState next = getNeighbor(current);
            int deltaE = next.cost - current.cost;

            // Aceitação baseada em custo ou probabilidade
            if (deltaE < 0 || ((double)rand() / RAND_MAX) < exp(-deltaE / T)) {
                current = next;
                path.push_back(current);
            }
        }
        T *= alpha;
    }
    return path;
}