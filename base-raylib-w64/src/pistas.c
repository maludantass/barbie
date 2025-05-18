#include "raylib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pistas.h"

// 🔧 Declaração antecipada
void inserirOrdenado(Pista** ordenado, Pista* novaPista);

void adicionarPista(Pista** lista, const char* descricao, int relevancia) {
    Pista* nova = (Pista*)malloc(sizeof(Pista));
    if (nova == NULL) return;

    strncpy(nova->descricao, descricao, sizeof(nova->descricao) - 1);
    nova->descricao[sizeof(nova->descricao) - 1] = '\0';
    nova->relevancia = relevancia;
    nova->prox = *lista;
    *lista = nova;
}

// Mostra todas as pistas no terminal (debug ou modo texto)
void mostrarPistas(Pista* lista) {
    Pista* atual = lista;
    printf("=== Pistas Coletadas ===\n");
    while (atual != NULL) {
        printf("• %s (Relevância: %d)\n", atual->descricao, atual->relevancia);
        atual = atual->prox;
    }
}

// Mostra todas as pistas visualmente com Raylib
void mostrarPistasRaylib(Pista* lista) {
    int yOffset = 50;
    int lineHeight = 20;
    int padding = 10;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (lista == NULL) {
            DrawText("Nenhuma pista coletada ainda.", 100, 100, 20, BLACK);
        } else {
            DrawText("--- Pistas Coletadas ---", 100, yOffset, 20, BLACK);
            yOffset = 80;

            Pista* temp = lista;
            while (temp != NULL) {
                char text[300];
                snprintf(text, sizeof(text), "Pista: %s (Relevância: %d)", temp->descricao, temp->relevancia);
                DrawText(text, 100, yOffset, 16, DARKGRAY);
                yOffset += lineHeight + padding;
                temp = temp->prox;
            }
            DrawText("--- Fim das Pistas ---", 100, yOffset + 10, 20, BLACK);
        }

        DrawText("Pressione ENTER para continuar", 100, 850, 20, GRAY);
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }
}

// Mostra uma única pista isolada (por cena)
void mostrarPistaUnicaRaylib(const char* texto) {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (texto == NULL || strlen(texto) == 0) {
            DrawText("Nenhuma pista nesta cena.", 100, 100, 20, BLACK);
        } else {
            DrawText("--- Pista Coletada ---", 100, 80, 20, BLACK);
            DrawText(texto, 100, 120, 18, DARKGRAY);
        }

        DrawText("Pressione ENTER para continuar", 100, 850, 20, GRAY);
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }
}

// Filtra pistas que contêm o nome do personagem na descrição
Pista* filtrarPistasPorPersonagem(Pista* lista, const char* personagem) {
    Pista* filtradas = NULL;

    while (lista != NULL) {
        if (strstr(lista->descricao, personagem) != NULL) {
            adicionarPista(&filtradas, lista->descricao, lista->relevancia);
        }
        lista = lista->prox;
    }

    return filtradas;
}

void contarPistasPorPersonagem(Pista* lista) {
    const char* personagens[] = {"Micucci", "Bruno", "Felipe", "Samuca"};
    int contadores[4] = {0};

    while (lista != NULL) {
        for (int i = 0; i < 4; i++) {
            if (strstr(lista->descricao, personagens[i]) != NULL) {
                contadores[i]++;
            }
        }
        lista = lista->prox;
    }

    // Mostra os resultados na tela
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("📊 Contagem de Pistas por Personagem", 500, 100, 30, DARKPURPLE);

        for (int i = 0; i < 4; i++) {
            char texto[100];
            snprintf(texto, sizeof(texto), "%s: %d pistas", personagens[i], contadores[i]);
            DrawText(texto, 600, 180 + i * 40, 24, BLACK);
        }

        DrawText("Pressione ENTER para voltar ao menu", 550, 400, 20, GRAY);

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) break;
    }
}


// Libera toda a memória da lista
void liberarPistas(Pista* lista) {
    Pista* atual = lista;
    while (atual != NULL) {
        Pista* temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

//para o mergesort-> requisito
const char* personagens[] = {"Micucci", "Bruno", "Felipe", "Samuca"};
#define QTD_PERSONAGENS 4

const char* extrairPersonagem(const char* descricao) {
    for (int i = 0; i < QTD_PERSONAGENS; i++) {
        if (strstr(descricao, personagens[i]) != NULL) {
            return personagens[i];
        }
    } // caso não ache nenhum personagem
}

// Função para dividir a lista em duas metades
void dividirLista(Pista* fonte, Pista** frente, Pista** atras) {
    Pista* lento;
    Pista* rapido;
    lento = fonte;
    rapido = fonte->prox;

    while (rapido != NULL) {
        rapido = rapido->prox;
        if (rapido != NULL) {
            lento = lento->prox;
            rapido = rapido->prox;
        }
    }

    *frente = fonte;
    *atras = lento->prox;
    lento->prox = NULL;
}

// Comparar duas pistas pela ordem alfabética do personagem na descrição
int compararPistas(const Pista* a, const Pista* b) {
    const char* pA = extrairPersonagem(a->descricao);
    const char* pB = extrairPersonagem(b->descricao);

    if (pA == NULL && pB == NULL) return 0; 
    if (pA == NULL) return 1;               
    if (pB == NULL) return -1;                

    return strcmp(pA, pB);
}

// Função de merge para duas listas ordenadas
Pista* mergeOrdenado(Pista* a, Pista* b) {
    Pista* resultado = NULL;

    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    if (compararPistas(a, b) <= 0) {
        resultado = a;
        resultado->prox = mergeOrdenado(a->prox, b);
    } else {
        resultado = b;
        resultado->prox = mergeOrdenado(a, b->prox);
    }
    return resultado;
}

// Função merge sort principal para ordenar a lista
void ordenarPistasPorPersonagem(Pista** lista) {
    if (*lista == NULL || (*lista)->prox == NULL) {
        return;
    }

    Pista* frente;
    Pista* atras;

    dividirLista(*lista, &frente, &atras);

    ordenarPistasPorPersonagem(&frente);
    ordenarPistasPorPersonagem(&atras);

    *lista = mergeOrdenado(frente, atras);
}