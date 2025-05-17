#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pistas.h"

// 🔧 Declaração antecipada
void inserirOrdenado(Pista** ordenado, Pista* novaPista);

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

// Ordena a lista de pistas em ordem alfabética pela descrição
void ordenarPistasPorPersonagem(Pista** lista) {
    if (*lista == NULL || (*lista)->prox == NULL) return;

    Pista* ordenado = NULL;
    Pista* atual = *lista;
    while (atual != NULL) {
        Pista* proximo = atual->prox;
        inserirOrdenado(&ordenado, atual);
        atual = proximo;
    }
    *lista = ordenado;
}

void inserirOrdenado(Pista** ordenado, Pista* novaPista) {
    if (*ordenado == NULL || strcmp(novaPista->descricao, (*ordenado)->descricao) < 0) {
        novaPista->prox = *ordenado;
        *ordenado = novaPista;
    } else {
        Pista* atual = *ordenado;
        while (atual->prox != NULL && strcmp(novaPista->descricao, atual->prox->descricao) > 0) {
            atual = atual->prox;
        }
        novaPista->prox = atual->prox;
        atual->prox = novaPista;
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

// Conta quantas pistas mencionam cada personagem
void contarPistasPorPersonagem(Pista* lista) {
    const char* personagens[] = {"Micucci", "Bruno", "Felipe", "Samuca"};
    int contadores[4] = {0};

    while (lista != NULL) {
        for (int i = 0; i < 4; i++) {
            if (strstr(lista->descricao, personagens[i]) != NULL) {
                contadores[i]++;
            }
        }
        lista = lista->prox;
    }

    printf("=== Contagem de Pistas por Personagem ===\n");
    for (int i = 0; i < 4; i++) {
        printf("%s: %d pistas\n", personagens[i], contadores[i]);
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
