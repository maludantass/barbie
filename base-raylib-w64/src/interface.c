#include "interface.h"
#include "raylib.h"
#include "ia.h"
#include "pistas.h"
#include <string.h>

#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 950

void mostrarInstrucoes();
void executarCenas(Pista** lista);
void mostrarResultadoFinal(Pista* lista);

void mostrarIntroducao() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Quem é o Crush Secreto da Barbie?");
    InitAudioDevice();
    SetTargetFPS(60);

    Texture2D fundo = LoadTexture("assets/casa.jpg");
    Texture2D carro = LoadTexture("assets/carro.png");
    Texture2D barbie = LoadTexture("assets/barbie.png");
    Music introMusica = LoadMusicStream("assets/BarbieGirl.mp3");
    PlayMusicStream(introMusica);

    float posCarroX = SCREEN_WIDTH + (carro.width * 1.8f);
    float posCarroY = 150;
    float posBarbieX = -barbie.width * 2.0f;

    bool carroSaiu = false;
    bool barbieChegou = false;

    const char *frases[] = {
        "Olá! Eu sou a Barbie... e estou prestes a viver um mistério cheio de romance!",
        "Nos últimos dias, bilhetes misteriosos apareceram na minha porta...",
        "E agora eu preciso descobrir quem está por trás disso!"
    };
    int fraseAtual = 0;
    int textoIndex = 0;
    float tempoTexto = 0;
    bool mostrarTexto = false;
    bool pulouIntro = false;

    while (!WindowShouldClose() && !pulouIntro) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(fundo, (Rectangle){0, 0, fundo.width, fundo.height},
                       (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, (Vector2){0, 0}, 0.0f, WHITE);

        if (!carroSaiu) {
            DrawTexturePro(carro, (Rectangle){0, 0, carro.width, carro.height},
                           (Rectangle){posCarroX, posCarroY, carro.width * 1.8f, carro.height * 1.8f},
                           (Vector2){0, 0}, 0.0f, WHITE);
            posCarroX -= 6.5f;
            posCarroY += 1.2f;
            if (posCarroX < -(carro.width * 1.8f)) carroSaiu = true;
        }

        if (carroSaiu) {
            DrawTexturePro(barbie, (Rectangle){0, 0, barbie.width, barbie.height},
                           (Rectangle){posBarbieX, 350, barbie.width * 2.8f, barbie.height * 2.8f},
                           (Vector2){0, 0}, 0.0f, WHITE);

            if (posBarbieX < SCREEN_WIDTH * -0.25f) {
                posBarbieX += 4.5f;
            } else if (!barbieChegou) {
                barbieChegou = true;
                mostrarTexto = true;
            }
        }

        if (mostrarTexto) {
            tempoTexto += GetFrameTime();
            if (tempoTexto > 0.05f && textoIndex < strlen(frases[fraseAtual])) {
                textoIndex++;
                tempoTexto = 0;
            }

            DrawRectangle(800, 820, 880, 60, (Color){255, 192, 203, 180});
            DrawText(TextSubtext(frases[fraseAtual], 0, textoIndex), 820, 840, 24, BLACK);

            DrawText("Pressione ENTER para continuar", 600, 900, 20, DARKGRAY);
            if (IsKeyPressed(KEY_ENTER) && textoIndex >= strlen(frases[fraseAtual])) {
                fraseAtual++;
                if (fraseAtual >= 3) pulouIntro = true;
                textoIndex = 0;
            }
        }

        DrawText("Pressione ESPAÇO para pular", 20, 900, 20, DARKGRAY);
        if (IsKeyPressed(KEY_SPACE)) {
            pulouIntro = true;
        }

        EndDrawing();
    }

    UnloadTexture(fundo);
    UnloadTexture(carro);
    UnloadTexture(barbie);
    UnloadMusicStream(introMusica);
    CloseAudioDevice();
    CloseWindow();

    mostrarInstrucoes();
}

void mostrarInstrucoes() {
    InitWindow(800, 600, "Instruções do Jogo");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground((Color){255, 222, 239, 255});
        DrawText("Instruções:", 300, 100, 40, MAGENTA);
        DrawText("- Durante cada cena, você decidirá se quer interagir ou não.", 80, 200, 20, BLACK);
        DrawText("- As pistas aparecerão na tela se você investigar.", 80, 240, 20, BLACK);
        DrawText("- No final, você poderá ver todas as pistas reunidas!", 80, 280, 20, BLACK);
        DrawText("Pressione ESPAÇO para iniciar a investigação.", 180, 400, 24, DARKGRAY);
        EndDrawing();

        if (IsKeyPressed(KEY_SPACE)) {
            CloseWindow();
            break;
        }
    }

    Pista* listaDePistas = NULL;
    executarCenas(&listaDePistas);
    mostrarResultadoFinal(listaDePistas);
    liberarPistas(listaDePistas);
}

void executarCenas(Pista** lista) {
    InitWindow(800, 600, "Investigando...");
    SetTargetFPS(60);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Investigando cena 1...", 100, 100, 20, DARKGRAY);
    EndDrawing();
    cenaMensagemMisteriosa(lista, 1);
    WaitTime(1.5f);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Investigando cena 2...", 100, 100, 20, DARKGRAY);
    EndDrawing();
    cenaBrownieCantina(lista, 1);
    WaitTime(1.5f);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Investigando cena 3...", 100, 100, 20, DARKGRAY);
    EndDrawing();
    cenaComputadorLaboratorio(lista, 1);
    WaitTime(1.5f);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Investigando cena 4...", 100, 100, 20, DARKGRAY);
    EndDrawing();
    cenaOlharNaQuadra(lista, 1);
    WaitTime(1.5f);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Investigando cena 5...", 100, 100, 20, DARKGRAY);
    EndDrawing();
    cenaMarcadorBiblioteca(lista, 1);
    WaitTime(1.5f);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Investigando cena 6...", 100, 100, 20, DARKGRAY);
    EndDrawing();
    cenaBilheteFesta(lista, 1);
    WaitTime(1.5f);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Investigando cena 7...", 100, 100, 20, DARKGRAY);
    EndDrawing();
    cenaFofoqueira(lista, 1);
    WaitTime(1.5f);

    CloseWindow();
}

void mostrarResultadoFinal(Pista* lista) {
    InitWindow(800, 600, "Resultado da Investigação");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("PISTAS COLETADAS:", 20, 20, 20, DARKBLUE);
        mostrarPistasRaylib(lista);
        DrawText("Pressione ENTER para encerrar.", 200, 550, 18, GRAY);
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }

    CloseWindow();
}
