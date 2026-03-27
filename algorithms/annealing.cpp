#include "../core/puzzle_state.h"
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <ctime>

// Heurística de Manhattan [cite: 15]
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

// Gera vizinho movendo o espaço vazio [cite: 22]
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
    PuzzleState atual = initial; // Linha 2 do pseudocódigo
    atual.cost = calculateManhattan(atual);
    path.push_back(atual);

    double T = 1.0;             // Temperatura inicial (T)
    double T_min = 0.0001;      // Critério de parada (T = 0)
    double alpha = 0.98;        // Fator de resfriamento (valor que diminui T)

    srand(time(NULL));

    while (T > T_min && atual.cost > 0) {
        // EQUILÍBRIO TÉRMICO: Tenta 100 vezes na mesma T para ser mais estável
        for (int i = 0; i < 100; i++) {
            if (atual.cost == 0) break;

            PuzzleState proximo = getNeighbor(atual); // Linha 7
            int deltaE = proximo.cost - atual.cost; // Linha 8

            // Aceitação baseada em custo ou probabilidade
            if (deltaE < 0 || ((double)rand() / RAND_MAX) < exp(-deltaE / T)) {
                atual = proximo;
                path.push_back(atual);
            }
        }
        T *= alpha; // Esfria T conforme t aumenta
    }
    return path; // Retorna a sequência S
}