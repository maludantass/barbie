#ifndef PERSONAGENS_H
#define PERSONAGENS_H

#include "pistas.h" // Você precisará incluir pistas.h aqui, pois essas funções trabalham com a struct Pista

void ordenarPistasPorPersonagem(Pista** lista);
Pista* filtrarPistasPorPersonagem(Pista* lista, const char* personagem);
void contarPistasPorPersonagem(Pista* lista);
void inserirOrdenado(Pista** ordenado, Pista* novaPista); 

#endif