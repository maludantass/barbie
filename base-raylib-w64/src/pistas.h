#ifndef PISTAS_H
#define PISTAS_H

typedef struct Pista {
    char descricao[256];        // Descrição da pista
    int relevancia;             // Relevância da pista
    struct Pista* prox;         // Próximo nó da lista
} Pista;

// Funções principais
void adicionarPista(Pista** lista, const char* descricao, int relevancia);
void mostrarPistas(Pista* lista);
void mostrarPistasRaylib(Pista* lista);
void ordenarPistasPorPersonagem(Pista** lista);  // <-- Corrigido aqui
void inserirOrdenado(Pista** ordenado, Pista* novaPista);
void liberarPistas(Pista* lista);
Pista* filtrarPistasPorPersonagem(Pista* lista, const char* personagem);
void contarPistasPorPersonagem(Pista* lista);

#endif
