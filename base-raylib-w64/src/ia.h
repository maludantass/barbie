#ifndef IA_H
#define IA_H

#include "pistas.h"

// Função para consultar a IA com um prompt e retornar a resposta
void consultarIA(const char* prompt, char* resposta);

// Função para modificar pistas com base na resposta da IA
void modificarPistas(Pista** listaPistas, const char* resposta);

#endif
