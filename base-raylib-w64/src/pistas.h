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

<<<<<<< HEAD
// Função para ordenar as pistas por nome do personagem
void ordenarPistasPorPersonagem(Pista** lista);

// Função auxiliar para inserir um nó na lista ordenada
void inserirOrdenado(Pista** ordenado, Pista* novaPista);

// Função para imprimir a lista (útil para debug)
void imprimirLista(Pista* lista);

//filtar por personagem
Pista* filtrarPistasPorPersonagem(Pista* lista, const char* personagem);

//funcao de qnts pistas cada personagem tem
void contarPistasPorPersonagem(Pista* lista);

//funcao de liberar lista
void liberarPistas(Pista* lista)

#endif
=======
#endif
>>>>>>> parent of 89c0a73 (add funções de pistas)
