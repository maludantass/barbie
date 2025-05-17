#include "interface.h"
#include "raylib.h"
#include <string.h>


#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 950


void mostrarIntroducao() {
    SetTargetFPS(60);


    Texture2D fundo = LoadTexture("assets/casa.jpg");
    Texture2D carro = LoadTexture("assets/carro.png");
    Texture2D barbie = LoadTexture("assets/barbie.png");
    Music introMusica = LoadMusicStream("assets/BarbieGirl.mp3");
    Music menuMusica = LoadMusicStream("assets/DreamHouse.mp3");
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
    bool musicaMenuTocando = false;
    float fade = 0.0f;
    bool fadingOutIntro = false;
    bool fadingInMenu = false;


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);


        if (!pulouIntro) {
            UpdateMusicStream(introMusica);
        } else {
            if (!musicaMenuTocando) {
                fadingOutIntro = true;
                fadingInMenu = true;
                SeekMusicStream(menuMusica, 31.0f);
                PlayMusicStream(menuMusica);
                SetMusicVolume(menuMusica, 0.0f);
                musicaMenuTocando = true;
            } else {
                UpdateMusicStream(menuMusica);
                if (fadingInMenu && fade < 1.0f) {
                    fade += 0.01f;
                    SetMusicVolume(menuMusica, 0.3f * fade); // volume mais baixo no máximo
                }
            }


            if (fadingOutIntro && fade < 1.0f) {
                fade += 0.005f; // fade out mais lento da intro
                SetMusicVolume(introMusica, 1.0f - fade);
                if (fade >= 1.0f) StopMusicStream(introMusica);
            }
        }


        if (!pulouIntro) {
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
                    SetMusicVolume(introMusica, 0.2f);
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
        } else {
            ClearBackground((Color){255, 182, 193, 255});
            DrawText("Instruções do Jogo:", 600, 200, 40, DARKPURPLE);
            DrawText("Explore os cenários e descubra quem é o admirador secreto da Barbie!", 300, 300, 30, BLACK);
            DrawText("Use as setas para se mover, pressione 1, 2 ou 3 para responder perguntas.", 280, 360, 26, BLACK);
            DrawText("Pressione ESPAÇO para Começar", 600, 500, 28, DARKGRAY);


            if (IsKeyPressed(KEY_SPACE)) {
                break;
            }
        }


        EndDrawing();
    }


    UnloadTexture(fundo);
    UnloadTexture(carro);
    UnloadTexture(barbie);
    UnloadMusicStream(introMusica);
    UnloadMusicStream(menuMusica);
}
