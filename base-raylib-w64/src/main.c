#include "raylib.h"
#include "ia.h"
#include "pistas.h"
#include "interface.h"
#include <stdio.h>
#include "menu.h"
#include "final.h"

#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 950

int escolhaJogadorComBotoes(const char* pergunta, Pista** listaPistas);

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Barbie's Love Detective");
    InitAudioDevice();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Pista* lista = NULL;

        // INTRODUÇÃO ANIMADA DO JOGO
        mostrarIntroducao();
        exibirMenu(&lista);

        int usarIA;

        usarIA = escolhaJogadorComBotoes("📱 CENA 1: Mensagem misteriosa. Investigar?", &lista);
        cenaMensagemMisteriosa(&lista, usarIA);

        usarIA = escolhaJogadorComBotoes("🍫 CENA 2: Brownie da cantina. Investigar?", &lista);
        cenaBrownieCantina(&lista, usarIA);

        usarIA = escolhaJogadorComBotoes("💻 CENA 3: Computador do laboratório. Investigar?", &lista);
        cenaComputadorLaboratorio(&lista, usarIA);

        usarIA = escolhaJogadorComBotoes("🏀 CENA 4: Olhar na quadra. Observar?", &lista);
        cenaOlharNaQuadra(&lista, usarIA);

        usarIA = escolhaJogadorComBotoes("📚 CENA 5: Marcador na biblioteca. Investigar?", &lista);
        cenaMarcadorBiblioteca(&lista, usarIA);

        usarIA = escolhaJogadorComBotoes("💌 CENA 6: Bilhete na festa. Ler?", &lista);
        cenaBilheteFesta(&lista, usarIA);

        usarIA = escolhaJogadorComBotoes("🗣️ CENA 7: Fofoqueira Vanessa. Ouvir?", &lista);
        cenaFofoqueira(&lista, usarIA);

        // Tela final de adivinhação
        telaFinalAdivinhacao();

        liberarPistas(lista);

        // Pergunta se deseja jogar novamente
        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Deseja jogar novamente?", 650, 350, 40, DARKPURPLE);
            DrawText("Pressione ENTER para jogar de novo ou ESC para sair", 500, 420, 25, GRAY);
            EndDrawing();

            if (IsKeyPressed(KEY_ENTER)) break;  // Recomeça o loop externo
            if (IsKeyPressed(KEY_ESCAPE)) {
                CloseAudioDevice();
                CloseWindow();
                return 0;
            }
        }
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}

int escolhaJogadorComBotoes(const char* pergunta, Pista** listaPistas) {
    Rectangle botaoSim = { 500, 400, 300, 80 };
    Rectangle botaoNao = { 1000, 400, 300, 80 };
    Vector2 mouse;

    while (!WindowShouldClose()) {
        mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(pergunta, 100, 150, 40, DARKPURPLE);

        DrawRectangleRec(botaoSim, CheckCollisionPointRec(mouse, botaoSim) ? DARKGREEN : GREEN);
        DrawText("SIM", botaoSim.x + 100, botaoSim.y + 25, 30, WHITE);

        DrawRectangleRec(botaoNao, CheckCollisionPointRec(mouse, botaoNao) ? MAROON : RED);
        DrawText("NÃO", botaoNao.x + 100, botaoNao.y + 25, 30, WHITE);

        DrawText("Clique para escolher", 700, 600, 20, GRAY);

        verificarCliqueNoBotaoMenu(listaPistas);  // Se estiver no menu

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, botaoSim)) return 1;
            if (CheckCollisionPointRec(mouse, botaoNao)) return 0;
        }
    }

    return 0;
}
