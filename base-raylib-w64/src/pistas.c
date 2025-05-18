#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pistas.h"
#define QTD_PERSONAGENS 4

typedef struct {
    const char* nome;
    int contador;
} RankingPersonagem;

void adicionarPista(Pista** lista, const char* descricao, int relevancia) {
    Pista* nova = (Pista*)malloc(sizeof(Pista));
    if (nova == NULL) return;

    strncpy(nova->descricao, descricao, sizeof(nova->descricao) - 1);
    nova->descricao[sizeof(nova->descricao) - 1] = '\0';
    nova->relevancia = relevancia;
    nova->prox = *lista;
    *lista = nova;
}

// Mostra todas as pistas no terminal (debug ou modo texto)
void mostrarPistas(Pista* lista) {
    Pista* atual = lista;
    printf("=== Pistas Coletadas ===\n");
    while (atual != NULL) {
        printf("• %s (Relevância: %d)\n", atual->descricao, atual->relevancia);
        atual = atual->prox;
    }
}

// Mostra todas as pistas visualmente com Raylib
void mostrarPistasRaylib(Pista* lista) {
    int yOffset = 50;
    int lineHeight = 20;
    int padding = 10;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (lista == NULL) {
            DrawText("Nenhuma pista coletada ainda.", 100, 100, 20, BLACK);
        } else {
            DrawText("--- Pistas Coletadas ---", 100, yOffset, 20, BLACK);
            yOffset = 80;

            Pista* temp = lista;
            while (temp != NULL) {
                char text[300];
                snprintf(text, sizeof(text), "Pista: %s (Relevância: %d)", temp->descricao, temp->relevancia);
                DrawText(text, 100, yOffset, 16, DARKGRAY);
                yOffset += lineHeight + padding;
                temp = temp->prox;
            }
            DrawText("--- Fim das Pistas ---", 100, yOffset + 10, 20, BLACK);
        }

        DrawText("Pressione ENTER para continuar", 100, 850, 20, GRAY);
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }
}

// Mostra uma única pista isolada (por cena)
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


// Filtra pistas que contêm o nome do personagem na descrição
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

void contarPistasPorPersonagem(Pista* lista) {
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

    // Bubble Sort decrescente por contador
    for (int i = 0; i < QTD_PERSONAGENS - 1; i++) {
        for (int j = 0; j < QTD_PERSONAGENS - 1 - i; j++) {
            if (ranking[j].contador < ranking[j + 1].contador) {
                RankingPersonagem temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }

    // Mostrar ranking na tela com Raylib
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("🏆 Ranking de Pistas por Personagem", 500, 100, 30, DARKPURPLE);

        for (int i = 0; i < QTD_PERSONAGENS; i++) {
            char texto[100];
            snprintf(texto, sizeof(texto), "%dº - %s: %d pistas", i + 1, ranking[i].nome, ranking[i].contador);
            DrawText(texto, 550, 180 + i * 40, 24, BLACK);
        }

        DrawText("Pressione ENTER para voltar ao menu", 550, 400, 20, GRAY);

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }
}

// Libera toda a memória da lista
void liberarPistas(Pista* lista) {
    Pista* atual = lista;
    while (atual != NULL) {
        Pista* temp = atual;
        atual = atual->prox;
        free(temp);
    }
}