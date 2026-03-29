#include "puzzle_state.h"
#include "utils.h"
#include <algorithm>
#include <ctime>
#include <cstring> // Necessário para o memset

// Função para criar o estado objetivo (Goal State)
PuzzleState getGoalState() {
    PuzzleState goal;
    // CORREÇÃO: memset agora dentro da função para limpar o lixo de memória
    memset(&goal, 0, sizeof(PuzzleState)); 

    int val = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 2 && j == 2) goal.board[i][j] = 0;
            else goal.board[i][j] = val++;
        }
    }
    goal.emptyRow = 2;
    goal.emptyCol = 2;
    goal.cost = 0;
    return goal;
}

// Gera um estado inicial aleatório garantidamente solucionável
PuzzleState generateRandomInitial(int shuffles) {
    PuzzleState state = getGoalState();

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < shuffles; i++) {
        int dir = rand() % 4;
        int nextR = state.emptyRow + dr[dir];
        int nextC = state.emptyCol + dc[dir];

        if (nextR >= 0 && nextR < 3 && nextC >= 0 && nextC < 3) {
            std::swap(state.board[state.emptyRow][state.emptyCol], state.board[nextR][nextC]);
            state.emptyRow = nextR;
            state.emptyCol = nextC;
        }
    }

    return state;
}

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

std::vector<PuzzleState> getNeighbors(const PuzzleState& state) {
    std::vector<PuzzleState> neighbors;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int newR = state.emptyRow + dr[i];
        int newC = state.emptyCol + dc[i];

        if (newR >= 0 && newR < 3 && newC >= 0 && newC < 3) {
            PuzzleState newState = state;

            // troca o 0 com o vizinho
            std::swap(
                newState.board[state.emptyRow][state.emptyCol],
                newState.board[newR][newC]
            );

            newState.emptyRow = newR;
            newState.emptyCol = newC;

            // atualiza custo
            newState.cost = calculateManhattan(newState);

            neighbors.push_back(newState);
        }
    }

    return neighbors;
}