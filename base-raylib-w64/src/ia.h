#ifndef IA_H
#define IA_H

#include "pistas.h"

// Funções que representam as cenas do jogo
void cenaMensagemMisteriosa(Pista** lista, int usarIA, const char *bgFilename);
void cenaCupcakeCantina(Pista** lista, int usarIA, const char *bgFilename);
void cenaComputadorLaboratorio(Pista** lista, int usarIA, const char *bgFilename);
void cenaOlharNaQuadra(Pista** lista, int usarIA, const char *bgFilename);
void cenaMarcadorBiblioteca(Pista** lista, int usarIA, const char *bgFilename);
void cenaBilheteFesta(Pista** lista, int usarIA, const char *bgFilename);
void cenaFofoqueira(Pista** lista, int usarIA, const char *bgFilename);

// Consulta à IA com prompt direto
void consultarIA(const char* prompt, char* resposta);

// Consulta com contexto completo do jogo
void consultarIAComContexto(const char* promptCena, char* resposta);

// ⬇️ Corrigido: agora retorna a nova pista adicionada
Pista* modificarPistas(Pista** listaPistas, const char* resposta);

#endif
