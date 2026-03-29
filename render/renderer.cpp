#include <GL/gl.h>
#include "renderer.h"
#include <vector>
#include <cstdlib>
static const float NUM_SCALE = 0.8f;

// -------------------- CONFETE --------------------
struct Particle
{
    float x, y;
    float vx, vy;
    float r, g, b;
};

std::vector<Particle> particles;
bool showConfetti = false;

// CRIAR CONFETE
void spawnConfetti()
{
    particles.clear();

    for (int i = 0; i < 150; i++)
    {
        Particle p;

        p.x = ((rand() % 200) / 100.0f) - 1.0f;
        p.y = 1.0f;

        p.vx = ((rand() % 100) / 5000.0f) - 0.01f;
        p.vy = -((rand() % 100) / 2000.0f);

        // cores mais bonitas
        p.r = (rand() % 100) / 100.0f;
        p.g = (rand() % 100) / 100.0f;
        p.b = (rand() % 100) / 100.0f;

        particles.push_back(p);
    }
}

// ATUALIZAR + DESENHAR
void updateAndDrawConfetti()
{
    float size = 0.015f;

    glBegin(GL_QUADS);
    for (auto &p : particles)
    {
        p.x += p.vx;
        p.y += p.vy;

        // gravidade
        p.vy -= 0.0005f;

        glColor3f(p.r, p.g, p.b);

        glVertex2f(p.x, p.y);
        glVertex2f(p.x + size, p.y);
        glVertex2f(p.x + size, p.y - size);
        glVertex2f(p.x, p.y - size);
    }
    glEnd();
}

// -------------------- NÚMEROS --------------------

void drawOne(float x, float y)
{
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y - 0.2f);
    glEnd();
}

void drawTwo(float x, float y)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(x, y);
    glVertex2f(x + 0.1f, y);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x, y - 0.1f);
    glVertex2f(x, y - 0.2f);
    glVertex2f(x + 0.1f, y - 0.2f);
    glEnd();
}

void drawThree(float x, float y)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(x, y);
    glVertex2f(x + 0.1f, y);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.2f);
    glVertex2f(x, y - 0.2f);
    glEnd();
}

void drawFour(float x, float y)
{
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y - 0.1f);

    glVertex2f(x, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.1f);

    glVertex2f(x + 0.1f, y);
    glVertex2f(x + 0.1f, y - 0.2f);
    glEnd();
}

void drawFive(float x, float y)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(x + 0.1f, y);
    glVertex2f(x, y);
    glVertex2f(x, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.2f);
    glVertex2f(x, y - 0.2f);
    glEnd();
}

void drawSix(float x, float y)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(x + 0.1f, y);
    glVertex2f(x, y);
    glVertex2f(x, y - 0.2f);
    glVertex2f(x + 0.1f, y - 0.2f);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x, y - 0.1f);
    glEnd();
}

void drawSeven(float x, float y)
{
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x + 0.1f, y);

    glVertex2f(x + 0.1f, y);
    glVertex2f(x, y - 0.2f);
    glEnd();
}

void drawEight(float x, float y)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + 0.1f, y);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x, y - 0.1f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.2f);
    glVertex2f(x, y - 0.2f);
    glEnd();
}

// -------------------- DRAW NUMBER --------------------

void drawNumber(float x, float y, int value, float scale)
{
    glPushMatrix();

    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    switch (value)
    {
    case 1:
        drawOne(0, 0);
        break;
    case 2:
        drawTwo(0, 0);
        break;
    case 3:
        drawThree(0, 0);
        break;
    case 4:
        drawFour(0, 0);
        break;
    case 5:
        drawFive(0, 0);
        break;
    case 6:
        drawSix(0, 0);
        break;
    case 7:
        drawSeven(0, 0);
        break;
    case 8:
        drawEight(0, 0);
        break;
    }

    glPopMatrix();
}

// -------------------- TILE --------------------

void drawRoundedTile(float x, float y, float size)
{
    float r = 0.02f;

    glBegin(GL_POLYGON);
    glVertex2f(x + r, y);
    glVertex2f(x + size - r, y);
    glVertex2f(x + size, y - r);
    glVertex2f(x + size, y - size + r);
    glVertex2f(x + size - r, y - size);
    glVertex2f(x + r, y - size);
    glVertex2f(x, y - size + r);
    glVertex2f(x, y - r);
    glEnd();
}

// -------------------- RENDER --------------------

void renderState(const PuzzleState &state)
{
    glClearColor(0.6f, 0.45f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(6.0f);

    float boardSize = 1.6f;

    // Espaçamento pequeno
    float spacing = 0.02f;

    // Calcula tamanho do tile automaticamente
    float tileSize = (boardSize - 2 * spacing) / 3.0f;

    // Centraliza o tabuleiro
    float startX = -boardSize / 2.0f;
    float startY = boardSize / 2.0f;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            int value = state.board[i][j];

            float x = startX + j * (tileSize + spacing);
            float y = startY - i * (tileSize + spacing);

            if (value != 0)
            {
                glColor3f(0.9f, 0.9f, 0.9f);
                drawRoundedTile(x, y, tileSize);

                glColor3f(0.7f, 0.7f, 0.7f);
                glBegin(GL_LINE_LOOP);
                glVertex2f(x, y);
                glVertex2f(x + tileSize, y);
                glVertex2f(x + tileSize, y - tileSize);
                glVertex2f(x, y - tileSize);
                glEnd();

                float centerX = x + tileSize * 0.35f;
                float centerY = y - tileSize * 0.25f;

                glColor3f(0.2f, 0.2f, 0.2f);
                drawNumber(centerX, centerY, value, tileSize * 2.5f);
            }
        }
    }

    // ATIVAR CONFETE
    if (state.cost == 0 && !showConfetti)
    {
        showConfetti = true;
        spawnConfetti();
    }

    // reset se voltar estados
    if (state.cost != 0)
    {
        showConfetti = false;
    }

    // DESENHAR CONFETE
    if (showConfetti)
    {
        updateAndDrawConfetti();
    }

    glFlush();
}