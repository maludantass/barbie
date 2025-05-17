#include "raylib.h"
#include "ia.h"
#include "pistas.h"
#include "interface.h"  // <- necessário para mostrarIntroducao
#include <stdio.h>
#include "menu.h" 

#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 950

int escolhaJogadorComBotoes(const char* pergunta);

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Barbie's Love Detective");
    InitAudioDevice();
    SetTargetFPS(60);
    Pista* lista = NULL;     

    // INTRODUÇÃO ANIMADA DO JOGO
    mostrarIntroducao();  // NÃO fecha a janela
    exibirMenu(&lista);  // Mostra o menu antes das cenas começarem


    int usarIA;

    usarIA = escolhaJogadorComBotoes("📱 CENA 1: Mensagem misteriosa. Investigar?");
    cenaMensagemMisteriosa(&lista, usarIA);

    usarIA = escolhaJogadorComBotoes("🍫 CENA 2: Brownie da cantina. Investigar?");
    cenaBrownieCantina(&lista, usarIA);

    usarIA = escolhaJogadorComBotoes("💻 CENA 3: Computador do laboratório. Investigar?");
    cenaComputadorLaboratorio(&lista, usarIA);

    usarIA = escolhaJogadorComBotoes("🏀 CENA 4: Olhar na quadra. Observar?");
    cenaOlharNaQuadra(&lista, usarIA);

    usarIA = escolhaJogadorComBotoes("📚 CENA 5: Marcador na biblioteca. Investigar?");
    cenaMarcadorBiblioteca(&lista, usarIA);

    usarIA = escolhaJogadorComBotoes("💌 CENA 6: Bilhete na festa. Ler?");
    cenaBilheteFesta(&lista, usarIA);

    usarIA = escolhaJogadorComBotoes("🗣️ CENA 7: Fofoqueira Vanessa. Ouvir?");
    cenaFofoqueira(&lista, usarIA);

    // Tela final
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("🔍 Todas as cenas foram jogadas!", 500, 400, 30, BLACK);
        DrawText("Pressione ENTER para sair.", 500, 450, 20, GRAY);
        EndDrawing();
        if (IsKeyPressed(KEY_ENTER)) break;
    }

    liberarPistas(lista);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}


int escolhaJogadorComBotoes(const char* pergunta) {
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

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, botaoSim)) return 1;
            if (CheckCollisionPointRec(mouse, botaoNao)) return 0;
        }
    }

    return 0;
}
