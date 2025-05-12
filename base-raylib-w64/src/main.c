#include "raylib.h"
#include "pistas.h"
#include "jogo.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>


#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 950

typedef enum { INTRO, TELA_INICIAL, NARRATIVA, ESCOLHA } EstadoDoJogo;

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Quem é o Crush Secreto da Barbie?");
    InitAudioDevice();
    SetTargetFPS(60);

    Texture2D fundo = LoadTexture("assets/casa.jpg");
    Texture2D carro = LoadTexture("assets/carro.png");
    Texture2D barbie = LoadTexture("assets/barbie.png");
    Music introMusica = LoadMusicStream("assets/BarbieGirl.mp3");

    
    PlayMusicStream(introMusica);

    // ⬇Variáveis de movimento
    float posCarroX = SCREEN_WIDTH + (carro.width * 1.8f);
    float posCarroY = 150;
    float posBarbieX = -barbie.width * 2.0f;

    bool carroSaiu = false;
    bool barbieChegou = false;

    char texto[] = "Olá! Eu sou a Barbie... e estou prestes a viver um mistério cheio de romance!";
    int textoIndex = 0;
    float tempoTexto = 0;

    EstadoDoJogo estado = INTRO;
    Rectangle botaoComecar = { 300, 200, 200, 50 };
    int passoTexto = 0;
    const char *textos[] = {
        "Era uma vez uma Barbie em dúvida...",
        "Bilhetes misteriosos começaram a aparecer.",
        "Alguém está apaixonado por ela!",
        "Mas quem será o admirador secreto?"
    };
    int totalTextos = sizeof(textos) / sizeof(textos[0]);

    Pista* listaPistas = NULL;  // Lista de pistas começa vazia
    int pistaAdicionada = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (estado) {
            case INTRO:
                UpdateMusicStream(introMusica);

                DrawTexturePro(
                    fundo,
                    (Rectangle){ 0, 0, (float)fundo.width, (float)fundo.height },
                    (Rectangle){ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT },
                    (Vector2){ 0, 0 },
                    0.0f,
                    WHITE
                );

                if (!carroSaiu) {
                    DrawTexturePro(
                        carro,
                        (Rectangle){ 0, 0, (float)carro.width, (float)carro.height },
                        (Rectangle){ posCarroX, posCarroY, carro.width * 1.8f, carro.height * 1.8f },
                        (Vector2){ 0, 0 },
                        0.0f,
                        WHITE
                    );
                    posCarroX -= 6.5f;
                    posCarroY += 1.2f;

                    if (posCarroX < -(carro.width * 1.8f)) {
                        carroSaiu = true;
                    }
                }

                if (carroSaiu) {
                    DrawTexturePro(
                        barbie,
                        (Rectangle){ 0, 0, (float)barbie.width, (float)barbie.height },
                        (Rectangle){
                            posBarbieX,
                            350,
                            barbie.width * 2.8f,
                            barbie.height * 2.8f
                        },
                        (Vector2){ 0, 0 },
                        0.0f,
                        WHITE
                    );

                    if (posBarbieX < SCREEN_WIDTH * -0.25f) {
                        posBarbieX += 4.5f;
                    } else if (!barbieChegou) {
                        barbieChegou = true;
                        SetMusicVolume(introMusica, 0.2f);
                    }
                }

                if (barbieChegou) {
                    tempoTexto += GetFrameTime();
                    if (tempoTexto > 0.05f && textoIndex < strlen(texto)) {
                        textoIndex++;
                        tempoTexto = 0;
                    }
                    // Fundo rosinha translúcido atrás do texto
                    DrawRectangle(800, 820, 880, 60, (Color){255, 192, 203, 180});  // RGBA

                    // Texto preto por cima, mais à direita
                    DrawText(TextSubtext(texto, 0, textoIndex), 820, 840, 24, BLACK);


                }

                DrawText("Pressione ENTER para começar", 600, 900, 20, DARKGRAY);
                if (IsKeyPressed(KEY_ENTER)) {
                    estado = TELA_INICIAL;
                }
                break;

            case TELA_INICIAL:
                DrawText("Quem é o Crush Secreto da Barbie?", 100, 100, 30, PINK);
                DrawRectangleRec(botaoComecar, LIGHTGRAY);
                DrawText("COMEÇAR", botaoComecar.x + 50, botaoComecar.y + 15, 20, BLACK);

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), botaoComecar)) {
                    estado = NARRATIVA;
                }
                break;

            case NARRATIVA:
                DrawText(textos[passoTexto], 80, 180, 22, BLACK);
                DrawText("Pressione ESPAÇO para continuar...", 80, 360, 16, GRAY);

                if (IsKeyPressed(KEY_SPACE)) {
                    passoTexto++;
                    if (passoTexto >= totalTextos) {
                        estado = ESCOLHA;
                    }
                }
                break;

            case ESCOLHA:
                DrawText("Barbie tem dois suspeitos:", 80, 100, 22, DARKBLUE);
                DrawText("1 - Ken: sempre elegante e carinhoso", 100, 160, 20, BLACK);
                DrawText("2 - Ryan: divertido, misterioso e ousado", 100, 200, 20, BLACK);
                DrawText("Pressione 1 ou 2 para escolher", 100, 300, 18, GRAY);

                if (IsKeyPressed(KEY_ONE)) {
                    if (!pistaAdicionada) {
                        adicionarPista(&listaPistas, "Ken foi visto deixando flores na porta da Barbie!", 3);
                        pistaAdicionada = 1;
                    }
                }

                if (IsKeyPressed(KEY_TWO)) {
                    if (!pistaAdicionada) {
                        adicionarPista(&listaPistas, "Ryan escreveu um bilhete misterioso.", 2);
                        pistaAdicionada = 1;
                    }
                }

                // Exibe todas as pistas adicionadas
                int y = 350;
                Pista* atual = listaPistas;
                while (atual != NULL) {
                    DrawText(atual->descricao, 100, y, 18, DARKGRAY);
                    y += 30;
                    atual = atual->prox;
                }
                break;
        }

        EndDrawing();
    }

    // Libera recursos e memória alocada
    UnloadTexture(fundo);
    UnloadTexture(carro);
    UnloadTexture(barbie);
    UnloadMusicStream(introMusica);
    CloseAudioDevice();
    CloseWindow();

    // Liberar a memória da lista de pistas
    Pista* temp;
    while (listaPistas != NULL) {
        temp = listaPistas;
        listaPistas = listaPistas->prox;
        free(temp);
    }

    return 0;
}
