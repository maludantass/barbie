#ifndef PISTAS_H
#define PISTAS_H

typedef struct Pista {
    char descricao[256];
    int relevancia;
    struct Pista* prox;
} Pista;

// Cria uma nova pista e adiciona na lista
void adicionarPista(Pista** lista, const char* descricao, int relevancia);

// Mostra todas as pistas acumuladas (para uso no final do jogo)
void mostrarPistasRaylib(Pista* lista);

// Mostra apenas uma pista isolada na tela (por cena)
void mostrarPistaUnicaRaylib(const char* texto);

// Ordena as pistas por nome
void ordenarPistasPorPersonagem(Pista** lista);

// Libera a memória da lista de pistas
void liberarPistas(Pista* lista);

// Conta quantas pistas mencionam cada personagem
void contarPistasPorPersonagem(Pista* lista);

// Filtra pistas que contêm o nome do personagem na descrição
Pista* filtrarPistasPorPersonagem(Pista* lista, const char* personagem);


#endif
