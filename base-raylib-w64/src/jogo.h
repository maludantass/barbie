//#ifndef JOGO_H
//#define JOGO_H

//#include "pistas.h"

//void iniciarJogo();

//#endif
#ifndef JOGO_H
#define JOGO_H

#include "pistas.h"  // Para que as funções de pistas sejam reconhecidas

// Funções para o jogo
void adicionarPista(Pista** lista, const char* descricao, int relevancia);
void mostrarPistas(Pista* lista);

#endif