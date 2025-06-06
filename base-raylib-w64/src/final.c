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
    int escolha = -1;

    // Carregar fundo inicial
    Texture2D fundoInicial  = LoadTexture("assets/dentro casa.jpg");
    Texture2D fundoFinal    = LoadTexture("assets/finalMicucci.jpg");
    Texture2D fundoErradoBruno  = LoadTexture("assets/finalBruno.jpg");
    Texture2D fundoErradoFelipe = LoadTexture("assets/finalFelipe.jpg");
    Texture2D fundoErradoSamuca = LoadTexture("assets/finalSamuca.jpg");

    // Escolha do jogador
    while (acertou == -1 && !WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(
            fundoInicial,
            (Rectangle){0, 0, fundoInicial.width, fundoInicial.height},
            (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
            (Vector2){0, 0},
            0.0f,
            WHITE
        );
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){255, 182, 193, 120});

        DrawText(" Quem você acha que é o crush secreto da Barbie?", 300, 150, 30, BLACK);

        for (int i = 0; i < 4; i++) {
            bool hover = CheckCollisionPointRec(mouse, botoes[i]);
            Color corBotao = hover ? (Color){255, 105, 180, 255} : (Color){255, 182, 193, 255};

            DrawRectangleRounded(botoes[i], 0.5f, 12, corBotao);
            int textWidth = MeasureText(personagens[i], 30);
            DrawText(personagens[i], botoes[i].x + (botoes[i].width - textWidth) / 2, botoes[i].y + 20, 30, BLACK);
        }

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < 4; i++) {
                if (CheckCollisionPointRec(mouse, botoes[i])) {
                    escolha = i;
                    acertou = (strcmp(personagens[i], crushReal) == 0) ? 1 : 0;
                }
            }
        }
    }

    Music finalMusic = {0};
    if (acertou == 1) {
        finalMusic = LoadMusicStream("assets/finalcerto.mp3");
        SeekMusicStream(finalMusic, 67.0f);
        PlayMusicStream(finalMusic);
    }

    // Tela final
    while (!WindowShouldClose()) {
        if (acertou == 1) UpdateMusicStream(finalMusic);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Texture2D fundoAtual = fundoInicial;
        if (acertou == 1) {
            fundoAtual = fundoFinal;
        } else {
            if (strcmp(personagens[escolha], "Bruno") == 0) fundoAtual = fundoErradoBruno;
            else if (strcmp(personagens[escolha], "Felipe") == 0) fundoAtual = fundoErradoFelipe;
            else if (strcmp(personagens[escolha], "Samuca") == 0) fundoAtual = fundoErradoSamuca;
        }

        DrawTexturePro(
            fundoAtual,
            (Rectangle){0, 0, fundoAtual.width, fundoAtual.height},
            (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
            (Vector2){0, 0},
            0.0f,
            WHITE
        );

        if (acertou == 0) {
            
            DrawText("Não foi dessa vez!", 600, 400, 30, RED);
        }

        DrawText("Pressione ENTER para continuar", 600, 600, 20, DARKGRAY);
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }

    if (acertou == 1) {
        StopMusicStream(finalMusic);
        UnloadMusicStream(finalMusic);
    }

    // Libera recursos
    UnloadTexture(fundoInicial);
    UnloadTexture(fundoFinal);
    UnloadTexture(fundoErradoBruno);
    UnloadTexture(fundoErradoFelipe);
    UnloadTexture(fundoErradoSamuca);
}
