#include "raylib.h"
#include "GameTimer.h"
#include "Client.h"
#include "Player.h"

int main(void) {

    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Player Class Example");
//     SetWindowState(FLAG_FULLSCREEN_MODE);
    Client c;
    int x = c.run();
    GameTimer gameTimer;
    Player player1(screenWidth,screenHeight);
    SetTargetFPS(1000);
    while (!WindowShouldClose()) {
        float deltaTime = gameTimer.run();
        if (deltaTime > 0.04){
            deltaTime = 0.04;
        }
        player1.update(deltaTime);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(player1.getPlayerCamera());
        DrawText(TextFormat("Delta time: %f", deltaTime), 10, 10, 20, LIGHTGRAY);
        DrawText(TextFormat("FPS: %i", gameTimer.fps), 10, 40, 20, LIGHTGRAY);
        DrawText(TextFormat("Client: %f", x), 10, 70, 20, LIGHTGRAY);
        player1.draw(gameTimer.getCurrentTimeInSeconds() * 7);
        EndMode2D();

        EndDrawing();
    }
    UnloadTexture(player1.playerTextureMap);
    UnloadTexture(player1.playerTextureMapAttack);
    CloseWindow();

    return 0;
}


