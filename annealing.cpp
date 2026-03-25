#include "../core/puzzle_state.h"
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <ctime>

// Função auxiliar para calcular a Distância de Manhattan (Custo/Energia)
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

// Função para gerar um vizinho aleatório movendo o espaço vazio (0)
PuzzleState getNeighbor(PuzzleState current) {
    int dr[] = {-1, 1, 0, 0}; // Cima, Baixo, Esquerda, Direita
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

    double T = 1.0;            // Temperatura inicial (T)
    double T_min = 0.0001;     // Critério de parada (T = 0)
    double alpha = 0.9995;     // Fator de resfriamento (valor que diminui T)

    srand(time(NULL));

    // Loop principal: t = 1 até T_min
    while (T > T_min) {
        if (atual.cost == 0) break; // Objetivo alcançado!

        PuzzleState proximo = getNeighbor(atual); // Vizinho aleatório
        
        // Delta E = Próximo.valor - Atual.valor
        // Como queremos MINIMIZAR, um DeltaE negativo é bom.
        int deltaE = proximo.cost - atual.cost;

        if (deltaE < 0) { 
            // Se melhorou, aceita sempre (equivalente à linha 9-10 adaptada)
            atual = proximo;
            path.push_back(atual);
        } else {
            // Se piorou, aceita com probabilidade e^(-deltaE / T)
            double prob = exp(-deltaE / T);
            if (((double)rand() / RAND_MAX) < prob) { // Linha 12
                atual = proximo;
                path.push_back(atual);
            }
        }

        T *= alpha; // T diminui conforme as iterações aumentam
    }

    return path; // Retorna S (o caminho percorrido)
}
