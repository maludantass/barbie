#include "raylib.h"
#include "ia.h"
#include "pistas.h"
#include "interface.h"
#include "menu.h"
#include "final.h"
#include <string.h>
#include <stdio.h>

#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 950

Music gameplayMusic;
bool  musicIsPlaying;

int escolhaJogadorComBotoes(const char* pergunta, Pista** listaPistas);



int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Barbie's Love Detective");
    InitAudioDevice();
    SetTargetFPS(60);

    gameplayMusic = LoadMusicStream("assets/DreamHouse.mp3");
    SetMusicVolume(gameplayMusic, 0.1f);
    gameplayMusic.looping = true;

    while (!WindowShouldClose()) {
        Pista* lista = NULL;

        mostrarIntroducao();
        exibirMenu(&lista);

        PlayMusicStream(gameplayMusic);
        musicIsPlaying = true;

        int usarIA;
        // CENA 1
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);
        usarIA = escolhaJogadorComBotoes(
        "O celular da Barbie vibra e uma mensagem de número desconhecido aparece: \"Vamos sair hoje?\". "
        "Ela não viu, mas você percebe que o número parece familiar… talvez alguém do passado? "
        "Você sente aquela curiosidade borbulhando no peito. Vai investigar ou deixa passar?", &lista);
        cenaMensagemMisteriosa(&lista, usarIA, "assets/closet.jpg");

        // CENA 2
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);
        usarIA = escolhaJogadorComBotoes(
        "Um cupcake foi deixado com um bilhete para a Barbie na cantina. "
        "A funcionária menciona um garoto de capuz e mochila de basquete. "
        "Entre lembranças vagas e coincidências visuais, você pensa: devo ir atrás disso ou não me envolver?", &lista);
        cenaCupcakeCantina(&lista, usarIA, "assets/cozinha.jpg");


        // CENA 3
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);
        usarIA = escolhaJogadorComBotoes(
        "No laboratório, um notebook esquecido chama atenção: está logado no Instagram da Barbie. "
        "Você se aproxima e vê que pode haver mais por trás daquela tela aberta... "
        "Deve checar os detalhes ou agir como se nada tivesse acontecido?", &lista);
        cenaComputadorLaboratorio(&lista, usarIA, "assets/computador.jpg");


        // CENA 4
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);
        usarIA = escolhaJogadorComBotoes(
        " Durante um jogo na quadra, você nota um olhar suspeito e um aceno discreto na direção da arquibancada onde a Barbie está. "
        "Talvez um gesto comum… ou uma mensagem silenciosa? "
        "Você decide observar mais de perto ou considera isso apenas coincidência?", &lista);
        cenaOlharNaQuadra(&lista, usarIA, "assets/quadra.jpg");

        // CENA 5
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);
        usarIA = escolhaJogadorComBotoes(
        " Um marcador de página com uma frase apaixonada cai de um livro sobre astrologia recém devolvido por Barbie. "
        "Um nome vem à mente, mas há mais de um possível responsável. "
        "Você resolve investigar esse bilhete curioso ou prefere não se meter em suposições românticas?", &lista);
        cenaMarcadorBiblioteca(&lista, usarIA, "assets/cadeiras.jpg");

        // CENA 6
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);
        usarIA = escolhaJogadorComBotoes(
        " Durante a festa, um bilhete está sobre a mesa da Barbie: 'Nos encontramos às 21h na varanda.' "
        "A letra parece familiar, mas há algo estranho no jeito que foi escrito… imitado, talvez? "
        "Você pega o bilhete para analisar melhor ou deixa que o mistério continue pairando no ar?", &lista);
        cenaBilheteFesta(&lista, usarIA, "assets/festa.jpg");

        // CENA 7
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);
        usarIA = escolhaJogadorComBotoes(
        " Vanessa sussurra algo para uma amiga e você escuta de relance: "
        "\"Foi o Felipe! Eu vi com meus próprios olhos!\". "
        "Sabendo da fama exagerada de Vanessa, será que vale a pena escutar com atenção ou é melhor ignorar a fofoca?", &lista);
        cenaFofoqueira(&lista, usarIA, "assets/garagem.jpg");

        if (musicIsPlaying) {
            StopMusicStream(gameplayMusic);
            musicIsPlaying = false;
        }

        telaFinalAdivinhacao();
        liberarPistas(lista);

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

    if (musicIsPlaying) StopMusicStream(gameplayMusic);
    UnloadMusicStream(gameplayMusic);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

int escolhaJogadorComBotoes(const char* pergunta, Pista** listaPistas) {
    Texture2D fundo = LoadTexture("assets/dentro casa.jpg");

    Rectangle botaoA = { 480, 580, 350, 90 };
    Rectangle botaoB = { 970, 580, 350, 90 };
    Vector2 mouse;

    Font fonte = GetFontDefault();
    int tamanhoFonte = 30;
    float espacamento = 2;

    Rectangle caixaTexto = {
        200, 130,
        SCREEN_WIDTH - 400,
        400
    };

    while (!WindowShouldClose()) {
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);
        mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(fundo, (Rectangle){0, 0, fundo.width, fundo.height},
                       (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
                       (Vector2){0, 0}, 0.0f, WHITE);

        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){255, 182, 193, 100});
        DrawRectangleRounded(caixaTexto, 0.1f, 10, (Color){255, 255, 255, 180});
        DrawTextRec(fonte, pergunta, caixaTexto, tamanhoFonte, espacamento, true, DARKPURPLE);

        Color corA = CheckCollisionPointRec(mouse, botaoA) ? (Color){255, 105, 180, 255} : (Color){255, 182, 193, 255};
        DrawRectangleRounded(botaoA, 0.4f, 12, corA);
        const char* opcaoA = "Desvendar o segredo";
        int larguraA = MeasureText(opcaoA, 24);
        DrawText(opcaoA, botaoA.x + (botaoA.width - larguraA) / 2, botaoA.y + 30, 24, WHITE);

        Color corB = CheckCollisionPointRec(mouse, botaoB) ? (Color){255, 105, 180, 255} : (Color){255, 182, 193, 255};
        DrawRectangleRounded(botaoB, 0.4f, 12, corB);
        const char* opcaoB = "Confiar no destino";
        int larguraB = MeasureText(opcaoB, 24);
        DrawText(opcaoB, botaoB.x + (botaoB.width - larguraB) / 2, botaoB.y + 30, 24, WHITE);

        DrawText("Clique para escolher", 730, 700, 20, BLACK);

        verificarCliqueNoBotaoMenu(listaPistas);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, botaoA)) {
                UnloadTexture(fundo);
                return 1;
            }
            if (CheckCollisionPointRec(mouse, botaoB)) {
                UnloadTexture(fundo);
                return 0;
            }
        }
    }

    UnloadTexture(fundo);
    return 0;
}
