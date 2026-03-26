#include "puzzle_state.h"
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
    srand(time(NULL));

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