#ifndef PUZZLE_STATE_H
#define PUZZLE_STATE_H

#include <vector>

// Estrutura que representa o estado do Jogo de 8 peças
struct PuzzleState {
    int board[3][3]; 
    
    int emptyRow;
    int emptyCol;

    int cost;

    bool operator==(const PuzzleState& other) const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != other.board[i][j]) return false;
            }
        }
        return true;
    }
};

// Protótipos das Funções de Busca

/**
 * Resolve o problema usando o algoritmo de Têmpera Simulada (Simulated Annealing).
 * Retorna o vetor com a sequência de estados (caminho) para o OpenGL. [cite: 17]
 */
std::vector<PuzzleState> solveWithAnnealing(PuzzleState initial);

/**
 * Resolve o problema usando o algoritmo de Busca Tabu.
 * Retorna o vetor com a sequência de estados (caminho) para o OpenGL. [cite: 17]
 */
std::vector<PuzzleState> solveWithTabu(PuzzleState initial);

#endif // PUZZLE_STATE_H