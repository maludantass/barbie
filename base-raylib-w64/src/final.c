// final.c

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

    // Escolha do jogador
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
                    acertou = (strcmp(personagens[i], crushReal) == 0) ? 1 : 0;
                }
            }
        }
    }

    // Se acertou, prepare música de vitória
    Music finalMusic = {0};
    if (acertou == 1) {
        finalMusic = LoadMusicStream("assets/finalcerto.mp3");
        // Avança para o minuto 1:07 (67 segundos)
        SeekMusicStream(finalMusic, 67.0f);
        PlayMusicStream(finalMusic);
    }

    // Tela de resultado
    while (!WindowShouldClose()) {
        // Atualiza o streaming da música de vitória, se estiver tocando
        if (acertou == 1) UpdateMusicStream(finalMusic);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (acertou == 1) {
            DrawText("🎉 Parabéns! Você acertou quem é o crush da Barbie!", 400, 400, 30, DARKGREEN);
        } else {
            DrawText("😢 Não foi dessa vez! ", 500, 400, 30, RED);
            
        }

        DrawText("Pressione ENTER para continuar", 600, 600, 20, DARKGRAY);
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }

    // Para e descarrega a música de vitória
    if (acertou == 1) {
        StopMusicStream(finalMusic);
        UnloadMusicStream(finalMusic);
    }
}
