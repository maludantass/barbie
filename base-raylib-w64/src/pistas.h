#ifndef PISTAS_H
#define PISTAS_H


#include "raylib.h"

typedef struct Pista {
    char descricao[256];
    int relevancia;
    struct Pista* prox;
} Pista;

void DrawTextRec(Font font, const char* text, Rectangle bounds, float fontSize, float spacing, bool wordWrap, Color tint);

// Cria uma nova pista e adiciona na lista
void adicionarPista(Pista** lista, const char* descricao, int relevancia);

// Mostra todas as pistas acumuladas (para uso no final do jogo)
void mostrarPistasRaylib(Pista* lista, Texture2D menuImg, Rectangle menuArea);

// Mostra apenas uma pista isolada na tela (por cena)
void mostrarPistaUnicaRaylib(const char* texto);

// Libera a memória da lista de pistas
void liberarPistas(Pista* lista);

// Conta quantas pistas mencionam cada personagem
void contarPistasPorPersonagem(Pista* lista, Texture2D menuImg, Rectangle menuArea);

// Filtra pistas que contêm o nome do personagem na descrição
Pista* filtrarPistasPorPersonagem(Pista* lista, const char* personagem);

#endif