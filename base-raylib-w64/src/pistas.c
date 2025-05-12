#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pistas.h"
#include "raylib.h"

// Função para adicionar uma nova pista à lista
void adicionarPista(Pista** lista, const char* descricao, int relevancia) {
    Pista* nova = (Pista*)malloc(sizeof(Pista));  // Aloca memória para a nova pista

    if (nova == NULL) {  // Verifica se a alocação de memória foi bem-sucedida
        fprintf(stderr, "Erro: Falha ao alocar memória para nova pista.\n");
        return;
    }

    // Copia a descrição da pista para o nó
    strncpy(nova->descricao, descricao, sizeof(nova->descricao) - 1);
    nova->descricao[sizeof(nova->descricao) - 1] = '\0';  // Garante que a string esteja terminada corretamente
    nova->relevancia = relevancia;  // Define a relevância
    nova->prox = *lista;  // Adiciona no início da lista

    *lista = nova;  // Atualiza o ponteiro para a lista
}

// Função para mostrar as pistas (para depuração no console)
void mostrarPistas(Pista* lista) {
    Pista* temp = lista;

    if (lista == NULL) {
        printf("Nenhuma pista coletada ainda.\n");
        return;
    }

    printf("--- Pistas Coletadas ---\n");
    while (temp != NULL) {
        printf("Pista: %s (Relevância: %d)\n", temp->descricao, temp->relevancia);
        temp = temp->prox;
    }
    printf("--- Fim das Pistas ---\n");
}

// Função para mostrar as pistas usando Raylib (para a interface do jogo)
void mostrarPistasRaylib(Pista* lista) {
    int yOffset = 50;
    int lineHeight = 20;
    int padding = 10;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (lista == NULL) {
        DrawText("Nenhuma pista coletada ainda.", 100, 100, 20, BLACK);
    } else {
        DrawText("--- Pistas Coletadas ---", 100, yOffset, 20, BLACK);
        yOffset += lineHeight + padding;

        Pista* temp = lista;
        while (temp != NULL) {
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


// Função para ordenar as pistas por nome do personagem (Insertion Sort)
void ordenarPistasPorPersonagem(Pista** lista) {
    if (*lista == NULL || (*lista)->prox == NULL) {
        // Lista vazia ou com apenas um elemento, já está ordenada
        return;
    }
    Pista* ordenado = NULL; // Nova lista ordenada
    Pista* atual = *lista;
    while (atual != NULL) {
        Pista* proximo = atual->prox;
        inserirOrdenado(&ordenado, atual);
        atual = proximo;
    }
    *lista = ordenado; // Atualiza a lista original para a lista ordenada
}

void inserirOrdenado(Pista** ordenado, Pista* novaPista) {
    if (*ordenado == NULL || strcmp(novaPista->descricao, (*ordenado)->descricao) < 0) {
        // Inserir no início
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

// Função para imprimir a lista 
void imprimirLista(Pista* lista) {
    Pista* temp = lista;
    while (temp != NULL) {
        printf("%s -> ", temp->descricao);
        temp = temp->prox;
    }
    printf("NULL\n");
}

Pista* filtrarPistasPorPersonagem(Pista* lista, const char* personagem) {
    Pista* filtrada = NULL;

    while (lista != NULL) {
        printf("Checando pista: %s\n", lista->descricao);//funciona para debug
        if (strstr(lista->descricao, personagem) != NULL) {
            printf(">>> Achou personagem: %s\n", personagem); //para debug
            adicionarPista(&filtrada, lista->descricao, lista->relevancia);
        }
        lista = lista->prox;
    }

    return filtrada;
}