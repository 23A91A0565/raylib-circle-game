#include "raylib.h"
#include <stdlib.h>
#include <time.h>

int main() {
    // Screen size
    const int SW = 800;
    const int SH = 600;

    InitWindow(SW, SH, "Circle Collector");
    SetTargetFPS(60);

    // Player setup
    Rectangle player = {100, 100, 70, 50};
    float speed = 5.0f;

    // Circle setup
    Vector2 circlePos = {400, 300};
    float circleRadius = 30;

    // Game variables
    bool isCollision = false;
    int score = 0;
    float timer = 30.0f; // seconds

    // Seed random for circle reposition
    srand(time(NULL));

    while (!WindowShouldClose()) {
        // Update timer
        timer -= GetFrameTime();
        if (timer <= 0) timer = 0;

        // Player movement
        if (IsKeyDown(KEY_LEFT)) player.x -= speed;
        if (IsKeyDown(KEY_RIGHT)) player.x += speed;
        if (IsKeyDown(KEY_UP)) player.y -= speed;
        if (IsKeyDown(KEY_DOWN)) player.y += speed;

        // Keep player inside window
        if (player.x < 0) player.x = 0;
        if (player.y < 0) player.y = 0;
        if (player.x + player.width > SW) player.x = SW - player.width;
        if (player.y + player.height > SH) player.y = SH - player.height;

        // Collision check
        isCollision = CheckCollisionCircleRec(circlePos, circleRadius, player);

        // If collision, move circle to new random position
        if (isCollision && timer > 0) {
            score++;
            speed += 0.3f; // Increase difficulty
            circlePos.x = GetRandomValue(circleRadius, SW - circleRadius);
            circlePos.y = GetRandomValue(circleRadius, SH - circleRadius);
        }

        // Draw everything
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw player
        DrawRectangleRec(player, isCollision ? RED : BLUE);

        // Draw circle
        DrawCircleV(circlePos, circleRadius, GREEN);

        // Draw HUD
        DrawText(TextFormat("Score: %d", score), 20, 20, 20, DARKGRAY);
        DrawText(TextFormat("Time: %.1f", timer), SW - 150, 20, 20, DARKGRAY);

        // Game over
        if (timer <= 0) {
            DrawText("TIME'S UP!", SW / 2 - 100, SH / 2 - 40, 40, RED);
            DrawText(TextFormat("Final Score: %d", score), SW / 2 - 120, SH / 2 + 10, 30, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
