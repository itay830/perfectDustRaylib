#include <raylib.h>
#include <iostream>
#include <thread>
#include <math.h>
#include "headers/particle.h"

using std::thread;

class Game
{
public:
    int SW;
    int SH;
    Particle *particlesArr;
    int particlesArrSize;
    float attractionFactor;

    Game(int sWidth, int sHeight, int numOfParticles, float attractionFactor)
    {
        SW = sWidth;
        SH = sHeight;
        particlesArr = (Particle *)malloc(numOfParticles * sizeof(Particle));
        particlesArrSize = numOfParticles;
        this->attractionFactor = attractionFactor;
        initParticles();
    }

    ~Game()
    {
        free(particlesArr);
    }

    void Draw()
    {
        BeginDrawing();
        ClearBackground(BLACK);
        for (int i = 0; i < particlesArrSize; i++)
        {
            DrawPixelV(particlesArr[i].pos, particlesArr[i].color);
            // DrawCircleV(particlesArr[i].pos, 5, particlesArr[i].color);
        }
        EndDrawing();
    }

    void updateParticles(int start, int end, float attractionFactor)
    {
        for (int i = start; i < end; i++)
        {
            attraction(particlesArr[i], attractionFactor, SW, SH);
        }
    }

    void initParticles()
    {
        for (int i = 0; i < particlesArrSize; i++)
        {
            particlesArr[i] = Particle{
                Vector2{(float)GetRandomValue(0, SW), (float)GetRandomValue(0, SH)}, // Pos
                Vector2{0, 0},                                                       // vel
                Color{255, 255, 255, 200}                                            // Color
            };
        }
    }
};

void threadUpdate(Game &game, int threadsNum)
{
    thread threads[threadsNum];
    for (int i = 1; i <= threadsNum; i++)
    {
        threads[i - 1] = thread(&Game::updateParticles, &game, game.particlesArrSize * (i - 1) / threadsNum, game.particlesArrSize * i / threadsNum, game.attractionFactor);
    }

    for (int i = 0; i < threadsNum; i++)
    {
        threads[i].join();
    }
}

int main(void)
{
    InitWindow(0, 0, "Dust Simulator");
    ToggleFullscreen();
    const int WIDTH = GetScreenWidth();
    const int HEIGHT = GetScreenHeight();
    int threadsNum = 2;
    const float attractionFactor = 3;
    SetTargetFPS(60);

    Game game = Game{WIDTH, HEIGHT, 100000, attractionFactor};

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_R)) {
            game.initParticles();
        }
        threadUpdate(game, threadsNum);
        game.Draw();
    }

    CloseWindow();
    return 0;
}