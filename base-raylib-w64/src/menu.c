#include "menu.h"
#include "raylib.h"
#include <string.h>
#include <stdio.h>

extern Music gameplayMusic;
extern bool  musicIsPlaying;

#define SCALE 3.0f
#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 950

// Função auxiliar para centralizar texto com quebras de linha dentro de uma área
void DrawTextCentralizado(const char* texto, Rectangle area, int fontSize, Color cor) {
    Font font = GetFontDefault();
    int espaçamento = 6;
    char buffer[1024];
    strcpy(buffer, texto);

    char* linha = strtok(buffer, "\n");
    int linhas = 0;

    while (linha != NULL) {
        linhas++;
        linha = strtok(NULL, "\n");
    }

    strcpy(buffer, texto);
    linha = strtok(buffer, "\n");

    int i = 0;
    while (linha != NULL) {
        Vector2 tamanho = MeasureTextEx(font, linha, fontSize, espaçamento);
        float x = area.x + (area.width - tamanho.x) / 2.0f;
        float y = area.y + i * (fontSize + 10);
        DrawTextEx(font, linha, (Vector2){x, y}, fontSize, espaçamento, cor);
        linha = strtok(NULL, "\n");
        i++;
    }
}

void exibirMenu(Pista** listaPistas) {
    int iniciarJogo = 0;

    Texture2D imagemMenu = LoadTexture("assets/menu.png");
    float largura = imagemMenu.width * SCALE;
    float altura = imagemMenu.height * SCALE;
    float posX = (SCREEN_WIDTH - largura) / 2.0f;
    float posY = (SCREEN_HEIGHT - altura) / 2.0f;

    Rectangle menuArea = {
        posX,
        posY,
        largura,
        altura
    };

    Rectangle areaTexto = {
        posX + 80,
        posY + 180,
        largura - 160,
        altura - 180
    };

    while (!iniciarJogo && !WindowShouldClose()) {
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Fundo rosa translúcido
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){255, 182, 193, 90});

        // Imagem do menu centralizada
        DrawTextureEx(imagemMenu, (Vector2){posX, posY}, 0.0f, SCALE, WHITE);

        const char* menuTexto =
            "=== MENU DO JOGO ===\n"
            "1 - Jogar\n"
            "2 - Contar pistas por personagem\n"
            "3 - Filtrar pistas por personagem\n"
            "4 - Ver todas as pistas\n\n\n\n\n\n"
            "Use as teclas 1 a 4 para escolher.";

        DrawTextCentralizado(menuTexto, areaTexto, 35, BLACK);

        EndDrawing();

        if (IsKeyPressed(KEY_ONE)) {
            iniciarJogo = 1;
        } else if (IsKeyPressed(KEY_TWO)) {
            contarPistasPorPersonagem(*listaPistas, imagemMenu, menuArea);
        } else if (IsKeyPressed(KEY_THREE)) {
            const char* nomes[] = {"Micucci", "Bruno", "Felipe", "Samuca"};
            int escolha = -1;

            while (escolha == -1 && !WindowShouldClose()) {
                if (musicIsPlaying) UpdateMusicStream(gameplayMusic);

                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){255, 182, 193, 90});
                DrawTextureEx(imagemMenu, (Vector2){posX, posY}, 0.0f, SCALE, WHITE);

                const char* titulo = "Escolha o personagem para filtrar:";
                DrawText(titulo, areaTexto.x + (areaTexto.width - MeasureText(titulo, 24)) / 2, areaTexto.y + 30, 24, DARKPURPLE);

                for (int i = 0; i < 4; i++) {
                    char texto[100];
                    snprintf(texto, sizeof(texto), "%d - %s", i + 1, nomes[i]);
                    int larguraTexto = MeasureText(texto, 22);
                    DrawText(texto, areaTexto.x + (areaTexto.width - larguraTexto) / 2, areaTexto.y + 80 + i * 40, 22, BLACK);
                }


                EndDrawing();

                if (IsKeyPressed(KEY_ONE)) escolha = 0;
                else if (IsKeyPressed(KEY_TWO)) escolha = 1;
                else if (IsKeyPressed(KEY_THREE)) escolha = 2;
                else if (IsKeyPressed(KEY_FOUR)) escolha = 3;
            }

            if (escolha >= 0 && escolha < 4) {
                Pista* filtradas = filtrarPistasPorPersonagem(*listaPistas, nomes[escolha]);
                mostrarPistasRaylib(filtradas, imagemMenu, menuArea);
                liberarPistas(filtradas);
            }
        } else if (IsKeyPressed(KEY_FOUR)) {
            mostrarPistasRaylib(*listaPistas, imagemMenu, menuArea);
        }
    }

    UnloadTexture(imagemMenu);
}

void verificarCliqueNoBotaoMenu(Pista** listaPistas) {
    Rectangle botaoMenu = {1600, 20, 100, 50}; // Aumentei um pouco para o texto "MENU" caber melhor
    Vector2 mouse = GetMousePosition();

    if (musicIsPlaying) UpdateMusicStream(gameplayMusic);

    // Cores do botão
    Color corBotao = CheckCollisionPointRec(mouse, botaoMenu)
                     ? (Color){255, 105, 180, 255}   // rosa choque no hover
                     : (Color){255, 182, 193, 255};  // rosa claro padrão

    // Desenha botão arredondado
    DrawRectangleRounded(botaoMenu, 0.4f, 12, corBotao);

    // Centraliza o texto "MENU"
    const char* texto = "MENU";
    int fontSize = 20;
    int textWidth = MeasureText(texto, fontSize);
    int textX = botaoMenu.x + (botaoMenu.width - textWidth) / 2;
    int textY = botaoMenu.y + (botaoMenu.height - fontSize) / 2;
    DrawText(texto, textX, textY, fontSize, BLACK);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(mouse, botaoMenu)) {
        exibirMenu(listaPistas);
    }
}
