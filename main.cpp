#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#include <GLFW/glfw3.h>

#include "core/puzzle_state.h"
#include "algorithms/annealing.h"
#include "render/renderer.h"

extern PuzzleState generateRandomInitial(int shuffles);
extern int calculateManhattan(const PuzzleState& s);

// ---------- CONTROLE ----------
int indexState = 0;

// ---------- INPUT (TECLADO) ----------
void processInput(GLFWwindow* window, int pathSize) {
    static bool leftPressed = false;
    static bool rightPressed = false;

    // → Avançar
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (!rightPressed && indexState < pathSize - 1) {
            indexState++;
        }
        rightPressed = true;
    } else {
        rightPressed = false;
    }

    // ← Voltar
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (!leftPressed && indexState > 0) {
            indexState--;
        }
        leftPressed = true;
    } else {
        leftPressed = false;
    }

    // ESC sair
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // =========================
    // ESTADO INICIAL
    // =========================
    srand(time(NULL));
    PuzzleState start = generateRandomInitial(50);
    start.cost = calculateManhattan(start);

    std::cout << "\nExecutando Simulated Annealing...\n";
    std::vector<PuzzleState> path = solveWithAnnealing(start);

    if (path.empty()) {
        std::cout << "Nenhum caminho gerado.\n";
        return 0;
    }

    // =========================
    // GLFW INIT
    // =========================
    if (!glfwInit()) {
        std::cout << "Erro ao iniciar GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(600, 600, "8-Puzzle", NULL, NULL);
    if (!window) {
        std::cout << "Erro ao criar janela\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // =========================
    // LOOP PRINCIPAL
    // =========================
    while (!glfwWindowShouldClose(window)) {

        // INPUT
        processInput(window, path.size());

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT);
        renderState(path[indexState]);

        // INFO NO CONSOLE (simples e funciona muito bem)
        system("cls");
        std::cout << "Estado: " << indexState + 1 << " / " << path.size() << "\n";
        std::cout << "Custo: " << path[indexState].cost << "\n";
        std::cout << "[<-] Voltar | [->] Avancar | [ESC] Sair\n";

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}