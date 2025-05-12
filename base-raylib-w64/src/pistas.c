#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pistas.h"

// Função para adicionar uma nova pista à lista
void adicionarPista(Pista** lista, const char* descricao, int relevancia) {
    Pista* nova = (Pista*)malloc(sizeof(Pista));  // Aloca memória para a nova pista
    if (nova == NULL) {  // Verifica se a alocação de memória foi bem-sucedida
       
        return;
    }

    // Copia a descrição da pista para o nó
    strncpy(nova->descricao, descricao, sizeof(nova->descricao) - 1);
    nova->descricao[sizeof(nova->descricao) - 1] = '\0';  // Garante que a string esteja terminada corretamente
    nova->relevancia = relevancia;  // Define a relevância
    nova->prox = *lista;  // Adiciona no início da lista

    *lista = nova;  // Atualiza o ponteiro para a lista
}

// Função para mostrar as pistas
void mostrarPistas(Pista* lista) {
    Pista* temp = lista;
    while (temp != NULL) {
        printf("Pista: %s (Relevância: %d)\n", temp->descricao, temp->relevancia);
        temp = temp->prox;
    }
}
