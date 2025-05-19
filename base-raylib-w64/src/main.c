#include "raylib.h"
#include "ia.h"
#include "pistas.h"
#include "interface.h"
#include "menu.h"
#include "final.h"
#include <stdio.h>

#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 950

// --- globals de música ---
Music gameplayMusic;
bool  musicIsPlaying;


int escolhaJogadorComBotoes(const char* pergunta, Pista** listaPistas);

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Barbie's Love Detective");
    InitAudioDevice();
    SetTargetFPS(60);

    // Carrega a música de gameplay uma vez
    gameplayMusic = LoadMusicStream("assets/musicajogo.mp3");
    SetMusicVolume(gameplayMusic, 0.1f);
    gameplayMusic.looping = true;  // ativa loop automático

    while (!WindowShouldClose()) {
        Pista* lista = NULL;

        // INTRO + MENU + INSTRUÇÕES
        mostrarIntroducao();
        exibirMenu(&lista);

        // Inicia a música de fundo
        PlayMusicStream(gameplayMusic);
        musicIsPlaying = true;

        int usarIA;

        // CENA 1
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);
        usarIA = escolhaJogadorComBotoes("📱 CENA 1: Mensagem misteriosa. Investigar?", &lista);
        cenaMensagemMisteriosa(&lista, usarIA, "assets/closet.jpg");

        // CENA 2
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);
        usarIA = escolhaJogadorComBotoes("🍫 CENA 2: Cupcake da cantina. Investigar?", &lista);
        cenaMarcadorBiblioteca(&lista, usarIA, "assets/cozinha.jpg");

        // CENA 3
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);
        usarIA = escolhaJogadorComBotoes("💻 CENA 3: Computador do laboratório. Investigar?", &lista);
        cenaComputadorLaboratorio(&lista, usarIA, "assets/computador.jpg");

        // CENA 4
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);
        usarIA = escolhaJogadorComBotoes("🏀 CENA 4: Olhar na quadra. Observar?", &lista);
        cenaOlharNaQuadra(&lista, usarIA, "assets/quadra.jpg");

        // CENA 5
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);
        usarIA = escolhaJogadorComBotoes("📚 CENA 5: Marcador na biblioteca. Investigar?", &lista);
        cenaMarcadorBiblioteca(&lista, usarIA, "assets/cadeiras.jpg");

        // CENA 6
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);
        usarIA = escolhaJogadorComBotoes("💌 CENA 6: Bilhete na festa. Ler?", &lista);
        cenaBilheteFesta(&lista, usarIA, "assets/festa.jpg");

        // CENA 7
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);
        usarIA = escolhaJogadorComBotoes("🗣️ CENA 7: Fofoqueira Vanessa. Ouvir?", &lista);
        cenaFofoqueira(&lista, usarIA, "assets/garagem.jpg");

        // Para antes da revelação final
        if (musicIsPlaying) {
            StopMusicStream(gameplayMusic);
            musicIsPlaying = false;
        }

        // Tela final de adivinhação
        telaFinalAdivinhacao();
        liberarPistas(lista);

        // Pergunta se deseja jogar novamente
        while (!WindowShouldClose()) {
            if (musicIsPlaying) UpdateMusicStream(gameplayMusic);

            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Deseja jogar novamente?", 650, 350, 40, DARKPURPLE);
            DrawText("Pressione ENTER para jogar de novo ou ESC para sair", 500, 420, 25, GRAY);
            EndDrawing();

            if (IsKeyPressed(KEY_ENTER)) {
                PlayMusicStream(gameplayMusic);
                musicIsPlaying = true;
                break;
            }
            if (IsKeyPressed(KEY_ESCAPE)) {
                break;
            }
        }
    }

    // Cleanup
    if (musicIsPlaying) StopMusicStream(gameplayMusic);
    UnloadMusicStream(gameplayMusic);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

int escolhaJogadorComBotoes(const char* pergunta, Pista** listaPistas) {
    Rectangle botaoSim = { 500, 400, 300, 80 };
    Rectangle botaoNao = { 1000, 400, 300, 80 };
    Vector2 mouse;

    while (!WindowShouldClose()) {
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);

        mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(pergunta, 100, 150, 40, DARKPURPLE);

        DrawRectangleRec(botaoSim,
            CheckCollisionPointRec(mouse, botaoSim) ? DARKGREEN : GREEN);
        DrawText("SIM", botaoSim.x + 100, botaoSim.y + 25, 30, WHITE);

        DrawRectangleRec(botaoNao,
            CheckCollisionPointRec(mouse, botaoNao) ? MAROON : RED);
        DrawText("NÃO", botaoNao.x + 100, botaoNao.y + 25, 30, WHITE);

        DrawText("Clique para escolher", 700, 600, 20, GRAY);

        verificarCliqueNoBotaoMenu(listaPistas);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, botaoSim)) return 1;
            if (CheckCollisionPointRec(mouse, botaoNao)) return 0;
        }
    }
    return 0;
}
