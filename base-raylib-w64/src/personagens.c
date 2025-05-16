#include "personagens.h"
#include "pistas.h"
#include <string.h>
#include <stdio.h>

// FUNÇÃO REQUISITO: Ordena pistas por nome do personagem (Insertion Sort)
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

//auxiliar
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

// FUNÇÃO REQUISITO: Filtra as pistas de um personagem específico
Pista* filtrarPistasPorPersonagem(Pista* lista, const char* personagem) {
    Pista* filtrada = NULL;

    while (lista != NULL) {
        if (strstr(lista->descricao, personagem) != NULL) {
            adicionarPista(&filtrada, lista->descricao, lista->relevancia); // Assumindo que adicionarPista está em pistas.c/h
        }
        lista = lista->prox;
    }

    return filtrada;
}

// FUNÇÃO REQUISITO: Conta quantas pistas cada personagem teve
void contarPistasPorPersonagem(Pista* lista) {
    if (lista == NULL) {
        printf("Nenhuma pista para contar.\n");
        return;
    }

    const char* personagens[] = {"Micucci", "Bruno", "Felipe", "Samuca"};
    int numPersonagens = sizeof(personagens) / sizeof(personagens[0]);
    int contadores[numPersonagens];

    for (int i = 0; i < numPersonagens; i++) {
        contadores[i] = 0;
    }

    Pista* temp = lista;
    while (temp != NULL) {
        for (int i = 0; i < numPersonagens; i++) {
            if (strstr(temp->descricao, personagens[i]) != NULL) {
                contadores[i]++;
            }
        }
        temp = temp->prox;
    }

    printf("=== Contagem de Pistas por Personagem ===\n");
    for (int i = 0; i < numPersonagens; i++) {
        printf("%s: %d pistas\n", personagens[i], contadores[i]);
    }
}
