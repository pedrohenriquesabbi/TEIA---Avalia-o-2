#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <windows.h>
#include <conio.h> // Essencial para capturar as setas (_getch)
#include "core/puzzle_state.h"

extern PuzzleState generateRandomInitial(int shuffles);
extern int calculateManhattan(const PuzzleState& s);

std::vector<PuzzleState> solveWithTabu(PuzzleState initial) {
    return {initial};
}

void printBoard(const PuzzleState& s) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (s.board[i][j] == 0) std::cout << "  ";
            else std::cout << s.board[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "Custo: " << s.cost << "\n-----------\n";
}

int main() {
    PuzzleState inicio = generateRandomInitial(50); 
    inicio.cost = calculateManhattan(inicio); 

    std::cout << "--- ESTADO INICIAL GERADO ---\n";
    printBoard(inicio);

    std::cout << "Executando Simulated Annealing...\n";
    std::vector<PuzzleState> caminho = solveWithAnnealing(inicio);

    if (!caminho.empty()) {
        if (caminho.back().cost == 0) {
            std::cout << "\nSOLUCAO ENCONTRADA COM " << caminho.size() << " ESTADOS.\n";
        } else {
            std::cout << "\nSOLUCAO NAO ENCONTRADA. FORAM FEITOS " << caminho.size() << " ESTADOS.\n";
        }

        std::cout << "\nCONTROLES:\n";
        std::cout << "[->] Avancar | [<-] Voltar | [ESC] Sair\n";
        std::cout << "Pressione qualquer tecla para iniciar...";
        _getch();

        int indice = 0;
        bool sair = false;

        while (!sair) {
            system("cls");
            std::cout << "Estado: " << indice + 1 << " / " << caminho.size() << "\n";
            std::cout << "Use as setas para navegar. [ESC] para fechar.\n";
            printBoard(caminho[indice]);

            // Captura a tecla
            int tecla = _getch();

            if (tecla == 27) { // ESC
                sair = true;
            } 
            else if (tecla == 0 || tecla == 224) { // Teclas especiais (setas)
                tecla = _getch(); // Pega o código real da seta
                if (tecla == 77) { // Seta para DIREITA
                    if (indice < (int)caminho.size() - 1) indice++;
                } 
                else if (tecla == 75) { // Seta para ESQUERDA
                    if (indice > 0) indice--;
                }
            }
        }
    }

    return 0;
}