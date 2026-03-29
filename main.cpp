#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#include <GLFW/glfw3.h>

#include "core/puzzle_state.h"
#include "algorithms/annealing.h"
#include "algorithms/tabu.h"
#include "render/renderer.h"

extern PuzzleState generateRandomInitial(int shuffles);
extern int calculateManhattan(const PuzzleState &s);

// =========================
// CONTROLES INDEPENDENTES
// =========================
int indexTabu = 0;
int indexAnnealing = 0;

// =========================
// INPUT TABU
// =========================
void processInputTabu(GLFWwindow *window, int maxSize)
{
    static bool leftPressed = false;
    static bool rightPressed = false;

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        if (!rightPressed && indexTabu < maxSize - 1)
            indexTabu++;
        rightPressed = true;
    }
    else
        rightPressed = false;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if (!leftPressed && indexTabu > 0)
            indexTabu--;
        leftPressed = true;
    }
    else
        leftPressed = false;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// =========================
// INPUT ANNEALING
// =========================
void processInputAnnealing(GLFWwindow *window, int maxSize)
{
    static bool leftPressed = false;
    static bool rightPressed = false;

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        if (!rightPressed && indexAnnealing < maxSize - 1)
            indexAnnealing++;
        rightPressed = true;
    }
    else
        rightPressed = false;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if (!leftPressed && indexAnnealing > 0)
            indexAnnealing--;
        leftPressed = true;
    }
    else
        leftPressed = false;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// =========================
// MAIN
// =========================
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    srand(time(NULL));

    // =========================
    // ESTADO INICIAL
    // =========================
    PuzzleState start = generateRandomInitial(50);
    start.cost = calculateManhattan(start);

    // =========================
    // RODAR ALGORITMOS
    // =========================
    std::cout << "Rodando algoritmos...\n";

    std::vector<PuzzleState> tabuPath = solveWithTabu(start);
    std::vector<PuzzleState> annealingPath = solveWithAnnealing(start);

    if (tabuPath.empty() || annealingPath.empty())
    {
        std::cout << "Erro: caminho vazio.\n";
        return 0;
    }

    // =========================
    // RESULTADOS
    // =========================
    std::cout << "\n===== COMPARAÇÃO FINAL =====\n";
    std::cout << "Tabu - passos: " << tabuPath.size() << "\n";
    std::cout << "Simulated Annealing - passos: " << annealingPath.size() << "\n";

    // =========================
    // GLFW INIT
    // =========================
    if (!glfwInit())
    {
        std::cout << "Erro GLFW\n";
        return -1;
    }

    GLFWwindow *windowTabu = glfwCreateWindow(500, 500, "TABU SEARCH", NULL, NULL);
    GLFWwindow *windowAnnealing = glfwCreateWindow(500, 500, "ANNEALING", NULL, windowTabu);

    if (!windowTabu || !windowAnnealing)
    {
        std::cout << "Erro ao criar janelas\n";
        glfwTerminate();
        return -1;
    }

    std::cout << "\n===== CUSTOS =====\n";

    // =========================
    // LOOP
    // =========================
    while (!glfwWindowShouldClose(windowTabu) &&
           !glfwWindowShouldClose(windowAnnealing))
    {
        glfwPollEvents();

        // =====================
        // TABU WINDOW
        // =====================
        glfwMakeContextCurrent(windowTabu);
        processInputTabu(windowTabu, tabuPath.size());

        glClear(GL_COLOR_BUFFER_BIT);
        renderState(tabuPath[indexTabu]);
        static int lastTabu = -1;

        if (lastTabu != indexTabu)
        {
            std::cout << "Custo Tabu: " << tabuPath[indexTabu].cost << std::endl;
            lastTabu = indexTabu;
        }
        glfwSwapBuffers(windowTabu);

        // =====================
        // ANNEALING WINDOW
        // =====================
        glfwMakeContextCurrent(windowAnnealing);
        processInputAnnealing(windowAnnealing, annealingPath.size());

        glClear(GL_COLOR_BUFFER_BIT);
        renderState(annealingPath[indexAnnealing]);

        static int lastAnnealing = -1;

        if (lastAnnealing != indexAnnealing)
        {
            std::cout << "Custo Annealing: " << annealingPath[indexAnnealing].cost << std::endl;
            lastAnnealing = indexAnnealing;
        }
        glfwSwapBuffers(windowAnnealing);
    }

    glfwDestroyWindow(windowTabu);
    glfwDestroyWindow(windowAnnealing);
    glfwTerminate();

    return 0;
}