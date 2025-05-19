#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pistas.h"

#define QTD_PERSONAGENS 4
#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 950

typedef struct {
    const char* nome;
    int contador;
} RankingPersonagem;

// === Função para desenhar texto centralizado com quebra automática de linha ===
void DrawTextRec(Font font, const char* text, Rectangle bounds, float fontSize, float spacing, bool wordWrap, Color tint) {
    const int length = strlen(text);
    int start = 0;
    int line = 0;
    char buffer[1024];

    int i = 0;
    while (i <= length) {
        while (i <= length) {
            if (text[i] == ' ' || text[i] == '\0' || text[i] == '\n') {
                strncpy(buffer, &text[start], i - start);
                buffer[i - start] = '\0';

                Vector2 textSize = MeasureTextEx(font, buffer, fontSize, spacing);
                if (textSize.x > bounds.width * 0.45f || text[i] == '\n') break;

                if (text[i] == '\n') {
                    i++;
                    break;
                }
                i++;
            } else {
                i++;
            }
        }

        int count = i - start;
        strncpy(buffer, &text[start], count);
        buffer[count] = '\0';

        Vector2 textSize = MeasureTextEx(font, buffer, fontSize, spacing);
        float textX = bounds.x + (bounds.width - textSize.x) / 2.0f;

        int lineSpacing = fontSize + 12;
        float startY = bounds.y;

        DrawTextEx(font, buffer, (Vector2){ textX, startY + line * lineSpacing }, fontSize, spacing, tint);
        start = i;
        line++;
    }
}

// === Função para adicionar pista na lista encadeada ===
void adicionarPista(Pista** lista, const char* descricao, int relevancia) {
    Pista* nova = (Pista*)malloc(sizeof(Pista));
    if (nova == NULL) return;

    strncpy(nova->descricao, descricao, sizeof(nova->descricao) - 1);
    nova->descricao[sizeof(nova->descricao) - 1] = '\0';
    nova->relevancia = relevancia;
    nova->prox = *lista;
    *lista = nova;
}

// === Função de debug via terminal ===
void mostrarPistas(Pista* lista) {
    Pista* atual = lista;
    printf("=== Pistas Coletadas ===\n");
    while (atual != NULL) {
        printf("• %s (Relevância: %d)\n", atual->descricao, atual->relevancia);
        atual = atual->prox;
    }
}

// === Exibição visual das pistas coletadas ===
void mostrarPistasRaylib(Pista* lista, Texture2D menuImg, Rectangle menuArea) {
    Font fontePadrao = GetFontDefault();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){255, 182, 193, 90});
        DrawTexturePro(menuImg, (Rectangle){0, 0, menuImg.width, menuImg.height}, menuArea, (Vector2){0, 0}, 0.0f, WHITE);

        const char* titulo = "--- Pistas Coletadas ---";
        DrawText(titulo, menuArea.x + (menuArea.width - MeasureText(titulo, 22)) / 2, menuArea.y + 190, 22, BLACK);

        Rectangle textoArea = { menuArea.x, menuArea.y + 240, menuArea.width, 600 };

        if (lista == NULL) {
            const char* msg = "Nenhuma pista coletada ainda.";
            DrawText(msg, menuArea.x + (menuArea.width - MeasureText(msg, 22)) / 2, textoArea.y, 22, BLACK);
        } else {
            Pista* temp = lista;
            while (temp != NULL) {
                char linha[300];
                snprintf(linha, sizeof(linha), "Pista: %s (Relevância: %d)", temp->descricao, temp->relevancia);
                DrawTextRec(fontePadrao, linha, textoArea, 20, 1, true, DARKGRAY);
                textoArea.y += 120; // espaçamento entre pistas
                temp = temp->prox;
            }
        }

        const char* instrucoes = "Pressione ENTER para voltar ao menu";
        DrawText(instrucoes, menuArea.x + (menuArea.width - MeasureText(instrucoes, 20)) / 2, 860, 20, GRAY);
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }
}

// === Exibição de uma única pista ===
void mostrarPistaUnicaRaylib(const char* texto) {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (texto == NULL || strlen(texto) == 0) {
            DrawText("Nenhuma pista nesta cena.", 100, 100, 20, BLACK);
        } else {
            DrawText("--- Pista Coletada ---", 100, 80, 20, BLACK);
            DrawText(texto, 100, 120, 18, DARKGRAY);
        }

        DrawText("Pressione ENTER para continuar", 100, 850, 20, GRAY);
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }
}

// === Filtra pistas que contenham o nome do personagem ===
Pista* filtrarPistasPorPersonagem(Pista* lista, const char* personagem) {
    Pista* filtradas = NULL;
    while (lista != NULL) {
        if (strstr(lista->descricao, personagem) != NULL) {
            adicionarPista(&filtradas, lista->descricao, lista->relevancia);
        }
        lista = lista->prox;
    }
    return filtradas;
}

// === Contagem e exibição de ranking de pistas por personagem ===
void contarPistasPorPersonagem(Pista* lista, Texture2D menuImg, Rectangle menuArea) {
    RankingPersonagem ranking[QTD_PERSONAGENS] = {
        {"Micucci", 0},
        {"Bruno", 0},
        {"Felipe", 0},
        {"Samuca", 0}
    };

    while (lista != NULL) {
        for (int i = 0; i < QTD_PERSONAGENS; i++) {
            if (strstr(lista->descricao, ranking[i].nome) != NULL) {
                ranking[i].contador++;
            }
        }
        lista = lista->prox;
    }

    for (int i = 0; i < QTD_PERSONAGENS - 1; i++) {
        for (int j = 0; j < QTD_PERSONAGENS - 1 - i; j++) {
            if (ranking[j].contador < ranking[j + 1].contador) {
                RankingPersonagem temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){255, 182, 193, 90});
        DrawTexturePro(menuImg, (Rectangle){0, 0, menuImg.width, menuImg.height}, menuArea, (Vector2){0, 0}, 0.0f, WHITE);

        const char* titulo = "Ranking de Pistas por Personagem";
        DrawText(titulo, menuArea.x + (menuArea.width - MeasureText(titulo, 30)) / 2, menuArea.y + 150, 30, DARKPURPLE);

        for (int i = 0; i < QTD_PERSONAGENS; i++) {
            char texto[100];
            snprintf(texto, sizeof(texto), "%dº - %s: %d pistas", i + 1, ranking[i].nome, ranking[i].contador);
            DrawText(texto, menuArea.x + (menuArea.width - MeasureText(texto, 24)) / 2, menuArea.y + 230 + i * 45, 24, BLACK);
        }

        const char* instrucoes = "Pressione ENTER para voltar ao menu";
        DrawText(instrucoes, menuArea.x + (menuArea.width - MeasureText(instrucoes, 20)) / 2, menuArea.y + 460, 20, GRAY);

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }
}

// === Libera memória da lista de pistas ===
void liberarPistas(Pista* lista) {
    Pista* atual = lista;
    while (atual != NULL) {
        Pista* temp = atual;
        atual = atual->prox;
        free(temp);
    }
}
