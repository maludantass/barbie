#ifndef PISTAS_H
#define PISTAS_H

typedef struct Pista {
    char descricao[256];        // Descrição da pista
    int relevancia;             // Relevância da pista (quanto mais alta, mais relevante)
    struct Pista* prox;         // Ponteiro para o próximo nó
} Pista;

// Função para adicionar uma nova pista na lista
void adicionarPista(Pista** lista, const char* descricao, int relevancia);

// Função para exibir todas as pistas (para depuração no console)
void mostrarPistas(Pista* lista);

// Função para exibir todas as pistas usando Raylib (para a interface do jogo)
void mostrarPistasRaylib(Pista* lista);

// Função para ordenar as pistas por nome do personagem
void ordenarPistasPorPersonagem(Pista** lista);

// Função auxiliar para inserir um nó na lista ordenada
void inserirOrdenado(Pista** ordenado, Pista* novaPista);

// Função para imprimir a lista (útil para debug)
void imprimirLista(Pista* lista);

#endif