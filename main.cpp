#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include "core/puzzle_state.h"

extern PuzzleState generateRandomInitial(int shuffles);
extern int calculateManhattan(const PuzzleState& s);

std::vector<PuzzleState> solveWithTabu(PuzzleState initial) {
    return {initial};
}

void printBoard(const PuzzleState& s) {
    std::cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (s.board[i][j] == 0) std::cout << "  ";
            else std::cout << s.board[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\nCusto: " << s.cost << "\n-----------\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    PuzzleState start = generateRandomInitial(50); 
    start.cost = calculateManhattan(start); 

    system("cls");
    std::cout << "--- ESTADO INICIAL GERADO ---\n";
    printBoard(start);

    std::cout << "\nExecutando Simulated Annealing...\n";
    std::vector<PuzzleState> path = solveWithAnnealing(start);

    if (!path.empty()) {
        if (path.back().cost == 0) {
            std::cout << "\nSOLUÇÃO ENCONTRADA COM " << path.size() << " ESTADOS.\n";
        } else {
            std::cout << "\nSOLUÇÃO NÃO ENCONTRADA. FORAM FEITOS " << path.size() << " ESTADOS.\n";
        }

        std::cout << "\nCONTROLES:\n";
        std::cout << "\n[->] AvanÇar | [<-] Voltar | [ESC] Sair\n";
        std::cout << "\nPressione qualquer tecla para iniciar...";
        _getch();

        int index = 0;
        bool exit = false;

        do {
            system("cls");
            std::cout << "Estado: " << index + 1 << " / " << path.size() << "\n";
            std::cout << "\nUse as setas para navegar. [ESC] para fechar.\n";
            printBoard(path[index]);

            int key = _getch();

            if (key == 27) { // Tecla ESC
                exit = true;
            } 
            else if (key == 0 || key == 224) {
                key = _getch();
                if (key == 77) { // Seta direita
                    if (index < (int)path.size() - 1) index++;
                } 
                else if (key == 75) { // Seta esquerda
                    if (index > 0) index--;
                }
            }
            system("cls");
        } while (!exit);
    }

    return 0;
}