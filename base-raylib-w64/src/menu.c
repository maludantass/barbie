#include "menu.h"
#include "raylib.h"
#include <string.h>
#include <stdio.h>

void exibirMenu(Pista** listaPistas) {
    int iniciarJogo = 0;

    while (!iniciarJogo && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("=== MENU DO JOGO ===", 100, 50, 30, BLACK);
        DrawText("1 - Começar o jogo", 100, 100, 20, DARKGRAY);
        DrawText("2 - Contar pistas por personagem", 100, 130, 20, DARKGRAY);
        DrawText("3 - Filtrar pistas por personagem", 100, 160, 20, DARKGRAY);
        DrawText("4 - Ver todas as pistas", 100, 190, 20, DARKGRAY);
        DrawText("Use as teclas 1 a 4 para escolher.", 100, 260, 18, GRAY);

        EndDrawing();

        if (IsKeyPressed(KEY_ONE)) {
            iniciarJogo = 1;
        } else if (IsKeyPressed(KEY_TWO)) {
            contarPistasPorPersonagem(*listaPistas);
        } else if (IsKeyPressed(KEY_THREE)) {
            const char* nomes[] = {"Micucci", "Bruno", "Felipe", "Samuca"};
            int escolha = -1;

            while (escolha == -1 && !WindowShouldClose()) {
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Escolha o personagem para filtrar:", 100, 80, 24, BLACK);
                for (int i = 0; i < 4; i++) {
                    char opcaoTexto[100];
                    snprintf(opcaoTexto, sizeof(opcaoTexto), "%d - %s", i + 1, nomes[i]);
                    DrawText(opcaoTexto, 100, 130 + i * 30, 20, DARKGRAY);
                }
                EndDrawing();

                if (IsKeyPressed(KEY_ONE)) escolha = 0;
                else if (IsKeyPressed(KEY_TWO)) escolha = 1;
                else if (IsKeyPressed(KEY_THREE)) escolha = 2;
                else if (IsKeyPressed(KEY_FOUR)) escolha = 3;
            }

            if (escolha >= 0 && escolha < 4) {
                Pista* filtradas = filtrarPistasPorPersonagem(*listaPistas, nomes[escolha]);
                mostrarPistasRaylib(filtradas);
                liberarPistas(filtradas);
            }
        } else if (IsKeyPressed(KEY_FOUR)) {
            mostrarPistasRaylib(*listaPistas);
        }
    }
}
