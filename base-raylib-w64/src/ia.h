#ifndef IA_H
#define IA_H

#include "pistas.h"

// Consulta simples da IA (sem contexto, se quiser usar direto)
void consultarIA(const char* prompt, char* resposta);

// Consulta com contexto dos suspeitos (RECOMENDADO)
void consultarIAComContexto(const char* promptCena, char* resposta);

// Modifica a lista de pistas com base na resposta da IA
void modificarPistas(Pista** listaPistas, const char* resposta);

// Cenas do jogo
void cenaMensagemMisteriosa(Pista** lista, int usarIA);
void cenaBrownieCantina(Pista** lista, int usarIA);
void cenaComputadorLaboratorio(Pista** lista, int usarIA);
void cenaOlharNaQuadra(Pista** lista, int usarIA);
void cenaMarcadorBiblioteca(Pista** lista, int usarIA);
void cenaBilheteFesta(Pista** lista, int usarIA);
void cenaFofoqueira(Pista** lista, int usarIA);

#endif
