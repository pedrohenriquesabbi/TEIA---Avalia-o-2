#ifndef PUZZLE_STATE_H
#define PUZZLE_STATE_H

#include <vector>

/**
 * Estrutura que representa o estado do Jogo de 8 peças.
 * Padronizada para comunicação entre Algoritmos e OpenGL.
 */
struct PuzzleState {
    // Matriz 3x3 representando o tabuleiro (0 é o espaço vazio) [cite: 22]
    int board[3][3]; 
    
    // Posição atual do espaço vazio para evitar buscas desnecessárias na matriz
    int emptyRow;
    int emptyCol;

    // Valor da função de avaliação/energia (Distância de Manhattan) [cite: 15]
    int cost;

    // Operador de comparação: essencial para a Busca Tabu identificar estados repetidos
    bool operator==(const PuzzleState& other) const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != other.board[i][j]) return false;
            }
        }
        return true;
    }
};

// --- Protótipos das Funções de Busca ---

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