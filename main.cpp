#include <iostream>
#include <vector>
#include "core/puzzle_state.h"

// Stub para a Busca Tabu (para o código compilar enquanto o colega não termina)
std::vector<PuzzleState> solveWithTabu(PuzzleState initial) {
    std::cout << "\n[Aviso] Busca Tabu ainda não implementada pelo membro do grupo.\n";
    return {initial};
}

// Função para imprimir o tabuleiro no terminal (ajuda no teste sem OpenGL)
void printBoard(const PuzzleState& s) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (s.board[i][j] == 0) std::cout << "  ";
            else std::cout << s.board[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "Cost (Manhattan): " << s.cost << "\n-----------\n";
}

int main() {
    // 1. Gerar estado inicial aleatório (conforme requisito e.3) [cite: 23]
    // Importante: use a função do utils.cpp que criamos
    extern PuzzleState generateRandomInitial(int shuffles); 
    PuzzleState inicio = generateRandomInitial(30); 

    std::cout << "--- ESTADO INICIAL GENERADO ---\n";
    printBoard(inicio);

    // 2. Executar o SEU algoritmo (Annealing) [cite: 13, 16]
    std::cout << "Executando Simulated Annealing...\n";
    std::vector<PuzzleState> caminho = solveWithAnnealing(inicio);

    // 3. Mostrar progresso no terminal
    if (caminho.back().cost == 0) {
        std::cout << "SUCESSO! Objetivo alcancado em " << caminho.size() << " estados.\n";
        
        char op;
        std::cout << "Deseja ver o passo a passo no terminal? (s/n): ";
        std::cin >> op;
        
        if (op == 's' || op == 'S') {
            for (const auto& estado : caminho) {
                printBoard(estado);
            }
        }
    } else {
        std::cout << "O algoritmo parou sem encontrar a solucao perfeita (T chegou ao minimo).\n";
        std::cout << "Ultimo custo alcancado: " << caminho.back().cost << "\n";
    }

    return 0;
}