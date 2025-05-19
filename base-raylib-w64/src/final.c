#include "raylib.h"
#include <string.h>
#include "final.h"

#define SCREEN_WIDTH  1800
#define SCREEN_HEIGHT 950

void telaFinalAdivinhacao() {
    const char* personagens[] = {"Micucci", "Bruno", "Felipe", "Samuca"};
    const char* crushReal     = "Micucci";

    Rectangle botoes[4] = {
        {400, 300, 300, 70},
        {800, 300, 300, 70},
        {400, 450, 300, 70},
        {800, 450, 300, 70},
    };

    int acertou = -1;

    // Carregar fundo
    Texture2D fundo = LoadTexture("assets/dentro casa.jpg");

    // Escolha do jogador
    while (acertou == -1 && !WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(fundo, 0, 0, WHITE);

        DrawText(" Quem você acha que é o crush secreto da Barbie?", 300, 150, 30, DARKPURPLE);

        for (int i = 0; i < 4; i++) {
            bool hover = CheckCollisionPointRec(mouse, botoes[i]);
            Color corBotao = hover ? (Color){255, 105, 180, 255} : (Color){255, 182, 193, 255}; // Hot pink e rosa claro

            DrawRectangleRounded(botoes[i], 0.5f, 12, corBotao); // Cantos arredondados
            int textWidth = MeasureText(personagens[i], 30);
            DrawText(personagens[i], botoes[i].x + (botoes[i].width - textWidth) / 2, botoes[i].y + 20, 30, BLACK);
        }

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < 4; i++) {
                if (CheckCollisionPointRec(mouse, botoes[i])) {
                    acertou = (strcmp(personagens[i], crushReal) == 0) ? 1 : 0;
                }
            }
        }
    }

    // Se acertou, prepare música de vitória
    Music finalMusic = {0};
    if (acertou == 1) {
        finalMusic = LoadMusicStream("assets/finalcerto.mp3");
        SeekMusicStream(finalMusic, 67.0f); // Avança para 1:07
        PlayMusicStream(finalMusic);
    }

    // Tela de resultado
    while (!WindowShouldClose()) {
        if (acertou == 1) UpdateMusicStream(finalMusic);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(fundo, 0, 0, WHITE);

        if (acertou == 1) {
            DrawText(" Parabéns! Você acertou quem é o crush da Barbie!", 300, 400, 30, DARKGREEN);
        } else {
            DrawText(" Não foi dessa vez!", 600, 400, 30, RED);
        }

        DrawText("Pressione ENTER para continuar", 600, 600, 20, DARKGRAY);
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }

    if (acertou == 1) {
        StopMusicStream(finalMusic);
        UnloadMusicStream(finalMusic);
    }

    UnloadTexture(fundo);
}
