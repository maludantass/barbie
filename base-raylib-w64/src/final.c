#include "raylib.h"
#include <string.h>
#include "final.h"

void telaFinalAdivinhacao() {
    const char* personagens[] = {"Micucci", "Bruno", "Felipe", "Samuca"};
    const char* crushReal = "Micucci";

    Rectangle botoes[4] = {
        {400, 300, 300, 70},
        {800, 300, 300, 70},
        {400, 450, 300, 70},
        {800, 450, 300, 70},
    };

    int acertou = -1;

    while (acertou == -1 && !WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("🧠 Quem você acha que é o crush secreto da Barbie?", 300, 150, 30, DARKPURPLE);

        for (int i = 0; i < 4; i++) {
            Color cor = CheckCollisionPointRec(mouse, botoes[i]) ? SKYBLUE : LIGHTGRAY;
            DrawRectangleRec(botoes[i], cor);
            DrawText(personagens[i], botoes[i].x + 20, botoes[i].y + 20, 30, BLACK);
        }

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < 4; i++) {
                if (CheckCollisionPointRec(mouse, botoes[i])) {
                    if (strcmp(personagens[i], crushReal) == 0) {
                        acertou = 1;
                    } else {
                        acertou = 0;
                    }
                }
            }
        }
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (acertou == 1) {
            DrawText("🎉 Parabéns! Você acertou quem é o crush da Barbie!", 400, 400, 30, DARKGREEN);
        } else {
            DrawText("😢 Não foi dessa vez! O verdadeiro crush era:", 500, 400, 30, RED);
            DrawText(crushReal, 780, 450, 40, BLACK);
        }

        DrawText("Pressione ENTER para sair", 600, 600, 20, DARKGRAY);

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }
}
