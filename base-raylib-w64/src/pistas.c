#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pistas.h"

// FUNÇÃO REQUISITO: Adiciona uma nova pista à lista encadeada
void adicionarPista(Pista** lista, const char* descricao, int relevancia) {
    Pista* nova = (Pista*)malloc(sizeof(Pista));
    if (nova == NULL) return;

    strncpy(nova->descricao, descricao, sizeof(nova->descricao) - 1);
    nova->descricao[sizeof(nova->descricao) - 1] = '\0';
    nova->relevancia = relevancia;
    nova->prox = *lista;

    *lista = nova;
}

// FUNÇÃO REQUISITO: Mostra as pistas coletadas no terminal (modo texto)
void mostrarPistas(Pista* lista) {
    Pista* temp = lista;
    while (temp != NULL) {
        printf("Pista: %s (Relevância: %d)\n", temp->descricao, temp->relevancia);
        temp = temp->prox;
    }
}

// FUNÇÃO REQUISITO + BÔNUS: Mostra as pistas usando Raylib (modo gráfico)
void mostrarPistasRaylib(Pista* lista) {
    int yOffset = 50;
    int lineHeight = 20;
    int padding = 10;
    int maxAlturaTela = GetScreenHeight();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (lista == NULL) {
        DrawText("Nenhuma pista coletada ainda.", 100, 100, 20, BLACK);
    } else {
        DrawText("--- Pistas Coletadas ---", 100, yOffset, 20, BLACK);
        yOffset += lineHeight + padding;

        Pista* temp = lista;
        while (temp != NULL && yOffset < maxAlturaTela - 50) {
            char text[300];
            snprintf(text, sizeof(text), "Pista: %s (Relevância: %d)", temp->descricao, temp->relevancia);
            DrawText(text, 100, yOffset, 16, DARKGRAY);
            yOffset += lineHeight;
            temp = temp->prox;
        }
        DrawText("--- Fim das Pistas ---", 100, yOffset + padding, 20, BLACK);
    }

    EndDrawing();
}

// DEBUG opcional: imprime os nós da lista
void imprimirLista(Pista* lista) {
    Pista* temp = lista;
    while (temp != NULL) {
        printf("%s -> ", temp->descricao);
        temp = temp->prox;
    }
    printf("NULL\n");
}

// FUNÇÃO REQUISITO: Libera toda a memória da lista encadeada
void liberarPistas(Pista* lista) {
    Pista* atual = lista;
    while (atual != NULL) {
        Pista* temp = atual;
        atual = atual->prox;
        free(temp);
    }
}
