#ifndef PISTAS_H
#define PISTAS_H

typedef struct Pista {
    char descricao[256];        // Descrição da pista
    int relevancia;             // Relevância da pista (quanto mais alta, mais relevante)
    struct Pista* prox;         // Ponteiro para o próximo nó
} Pista;

// Função para adicionar uma nova pista na lista
void adicionarPista(Pista** lista, const char* descricao, int relevancia);

// Função para exibir todas as pistas
void mostrarPistas(Pista* lista);

// Função para ordenar as pistas por relevância ou nome, conforme necessário
void ordenarPistas(Pista** lista);
void inserirOrdenado(Pista** ordenado, Pista* novaPista);


#endif
