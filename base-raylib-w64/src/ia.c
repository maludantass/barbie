// ia.c

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "raylib.h"
#include "ia.h"
#include "pistas.h"
#include "gemini.h"
#include "interface.h"
#include "menu.h"
#include "final.h"

#define SCREEN_WIDTH  1800
#define SCREEN_HEIGHT 950

// Referências às variáveis globais que devem estar em main.c (sem 'static')
extern Music gameplayMusic;
extern bool  musicIsPlaying;

void consultarIAComContexto(const char* promptCena, char* resposta) {
    const char* contextoPretendentes =
        "Você é uma Inteligência Artificial investigativa dentro de um jogo fofo, divertido e cheio de mistério, onde o jogador está tentando descobrir quem é o admirador secreto da Barbie.\n\n"
        "O tom do jogo é leve, jovem e encantador, feito para quem ama romance, investigação e pistas misteriosas com um toque fashion.\n"
        "Fale com o jogador como se estivesse numa conversa entre amigas, sempre com gentileza e emoção! Você pode usar expressões tipo “hmm…”, “ai, será?”, “isso tá bem suspeito!” e muito charme.\n\n"
        "Mas não esqueça: sua resposta deve sempre ajudar o jogador a formar sua teoria com base lógica.\n\n"
        "Suspeitos:\n"
        "- Micucci: tímido, introspectivo, manda bilhetes, evita contato direto, usa capuz e mochila.\n"
        "- Bruno: extrovertido, popular, engraçado, bilhetes no grêmio, sempre rodeado de amigos.\n"
        "- Felipe: estudioso, ama astrologia e constelações, frequenta a biblioteca, fala de signos, usa óculos.\n"
        "- Samuca: atleta de basquete, fala gírias, sempre de roupa de treino, brinca com todas, chama as meninas de “parça”.\n\n"
        "A seguir virão as cenas. Para cada uma, gere uma resposta curta, charmosa e investigativa.\n\nPrompt:\n";

    static char promptFinal[4096];
    int variacao = GetRandomValue(1, 99999);
    snprintf(promptFinal, sizeof(promptFinal), "%s%s\n\n[Variação Jogador: %d]",
             contextoPretendentes, promptCena, variacao);
    respt(promptFinal, resposta);
}

Pista* modificarPistas(Pista** lista, const char* resposta) {
    if (resposta && strlen(resposta) > 0) {
        adicionarPista(lista, resposta, 5);
        return *lista;
    }
    return NULL;
}

void consultarIA(const char* prompt, char* resposta) {
    respt(prompt, resposta);
}

// Macro para definir cenas com fade, typewriter e manutenção do áudio
#define DEFINIR_CENA(nomeFuncao, promptSim, promptNao, bgFile)                                     \
void nomeFuncao(Pista** lista, int usarIA, const char *bgFilename) {                               \
    Texture2D bg        = LoadTexture(bgFilename);                                                 \
    float fadeAlpha     = 0.0f;                                                                    \
    bool  fadingIn      = true;                                                                    \
    bool  waiting       = false;                                                                   \
    bool  fadingOut     = false;                                                                   \
                                                                                                    \
    char  raw[2048]     = {0};                                                                     \
    char  wrapped[4096] = {0};                                                                     \
    int   totalLen      = 0;                                                                       \
    int   currLen       = 0;                                                                       \
    float charTimer     = 0.0f;                                                                    \
    const float interval= 0.02f;                                                                   \
    const char* prompt = usarIA ? promptSim : promptNao;                                           \
                                                                                                    \
    while (!WindowShouldClose()) {                                                                 \
        /* mantém o áudio de fundo tocando */                                                      \
        if (musicIsPlaying) UpdateMusicStream(gameplayMusic);                                       \
                                                                                                    \
        float dt = GetFrameTime();                                                                 \
        if (fadingIn) {                                                                            \
            fadeAlpha = fminf(fadeAlpha + dt * 0.5f, 1.0f);                                        \
            if (fadeAlpha >= 1.0f) {                                                               \
                fadingIn = false;                                                                  \
                consultarIAComContexto(prompt, raw);                                               \
                modificarPistas(lista, raw);                                                       \
                /* wrap de texto a cada 60 cols */                                                 \
                {                                                                                   \
                    int lw = 0, wi = 0;                                                            \
                    for (int i = 0; raw[i] && wi < (int)sizeof(wrapped)-1; i++) {                   \
                        char c = raw[i];                                                            \
                        if (lw >= 60 && c == ' ') {                                                 \
                            wrapped[wi++] = '\n';                                                   \
                            lw = 0;                                                                 \
                        } else {                                                                    \
                            wrapped[wi++] = c;                                                      \
                            lw++;                                                                   \
                        }                                                                           \
                    }                                                                               \
                    wrapped[wi] = '\0'; totalLen = wi;                                               \
                }                                                                                   \
                waiting = true;                                                                     \
            }                                                                                       \
        }                                                                                           \
        else if (waiting && !fadingOut) {                                                           \
            if (currLen < totalLen) {                                                               \
                charTimer += dt;                                                                    \
                if (charTimer >= interval) { currLen++; charTimer -= interval; }                    \
            } else if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))                          \
                fadingOut = true;                                                                   \
        }                                                                                           \
        else if (fadingOut) {                                                                       \
            fadeAlpha = fmaxf(fadeAlpha - dt * 0.5f, 0.0f);                                         \
            if (fadeAlpha <= 0.0f) break;                                                           \
        }                                                                                           \
                                                                                                    \
        BeginDrawing();                                                                             \
        ClearBackground(RAYWHITE);                                                                  \
        DrawTexturePro(bg,                                                                          \
            (Rectangle){0,0,bg.width,bg.height},                                                    \
            (Rectangle){0,0,SCREEN_WIDTH,SCREEN_HEIGHT},                                            \
            (Vector2){0,0}, 0.0f,                                                                    \
            (Color){255,255,255,(unsigned char)(255 * fadeAlpha)}                                   \
        );                                                                                          \
        if (!fadingIn) {                                                                            \
            DrawRectangle(100,600,SCREEN_WIDTH-200,200,(Color){255,192,203,200});                   \
            DrawTextEx(GetFontDefault(), TextSubtext(wrapped,0,currLen),                            \
                       (Vector2){120,620}, 24,1, BLACK);                                              \
            if (currLen >= totalLen)                                                                 \
                DrawText("Pressione ENTER ou ESPAÇO para continuar",                                 \
                         120,820,20,DARKGRAY);                                                       \
        }                                                                                           \
        EndDrawing();                                                                               \
    }                                                                                               \
    UnloadTexture(bg);                                                                              \
}

// Define cada cena passando o arquivo de fundo
DEFINIR_CENA(cenaMensagemMisteriosa,
    "O jogador viu o celular da Barbie vibrar com uma mensagem de número desconhecido dizendo 'Vamos sair?'. Barbie não percebeu. O número está em grupos escolares antigos. Um dos colegas, conhecido por ser muito reservado e tímido, costuma evitar conversas presenciais e prefere mandar mensagens discretas. Esse perfil lembra Micucci, que ainda participa silenciosamente desses grupos. O que pode ser deduzido sobre o remetente da mensagem?",
    "O jogador ignorou a mensagem misteriosa. Mais tarde, escuta Vanessa dizendo: \"Esse número é igual ao do Samuca. Vive mandando mensagem chamando as meninas de ‘parça’. Deve ser ele.\" Samuca é extrovertido, brincalhão e atleta. Com base nessa fofoca, o que pode ser deduzido sobre o remetente?",
    "assets/closet.jpg")

DEFINIR_CENA(cenaCupcakeCantina,
    "O jogador ouviu que alguém deixou um cupcake com bilhete para a Barbie. A funcionária lembra que o garoto usava capuz e uma mochila com estampa de time de basquete. Samuca é jogador de basquete e anda sempre com roupa de treino. Micucci também costuma usar capuz, mas raramente entra no refeitório. O que pode ser deduzido sobre o possível autor do presente?",
    "O jogador optou por não investigar. Mais tarde, ouve alguém comentar: \"Bruno vive fazendo essas brincadeiras românticas. Aposto que foi ele.\" Bruno é popular e brincalhão, mas essa informação é baseada apenas em suposição. O que pode ser deduzido?",
    "assets/cozinha.jpg")

DEFINIR_CENA(cenaComputadorLaboratorio,
    "O jogador encontrou um notebook aberto no Instagram da Barbie. O modelo é igual ao que Micucci costuma usar, o que levanta suspeita. No entanto, ao investigar o IP, descobre-se que esse computador também é utilizado por Felipe, que costuma estudar nesse laboratório. O que pode ser deduzido com base nisso?",
    "O jogador optou por não investigar o computador deixado aberto no laboratório. Nenhuma informação adicional foi obtida.",
    "assets/computador.jpg")

DEFINIR_CENA(cenaOlharNaQuadra,
    "Durante o jogo, o jogador viu Bruno acenar para o lado da arquibancada onde a Barbie estava. Bruno é conhecido por ser extrovertido e cumprimentar muitas pessoas. Também havia um grupo de amigos ao lado da Barbie. Esse gesto pode indicar algo sobre um possível interesse romântico?",
    "O jogador se distraiu durante o jogo e não observou o comportamento dos jogadores. Nenhuma pista foi coletada.",
    "assets/quadra.jpg")

DEFINIR_CENA(cenaMarcadorBiblioteca,
    "O jogador viu um marcador com a frase 'Estou apaixonado pela Barbie' cair de um livro sobre astrologia que Barbie devolveu. O sistema indica que o último empréstimo foi feito por Felipe, conhecido por gostar de astrologia. No entanto, o jogador lembra que Micucci havia emprestado esse livro dias antes para Felipe, dizendo que era pra um trabalho. Com base nessa relação, o que pode ser deduzido sobre o autor do marcador?",
    "O jogador ignorou o marcador. Mais tarde, ouve alguém comentar: \"Felipe é fissurado em signos. Deve ter sido ele.\" Essa suposição tem alguma base ou é apenas coincidência?",
    "assets/cadeiras.jpg")

DEFINIR_CENA(cenaBilheteFesta,
    "Durante a festa, o jogador vê um bilhete na mesa da Barbie: 'Nos encontramos às 21h na varanda.' A caligrafia lembra a de Bruno, que costuma escrever mensagens no grêmio e fazer bilhetes engraçados. No entanto, a inclinação da letra está diferente, como se alguém estivesse imitando. O que pode ser deduzido a partir disso?",
    "O jogador não investigou o bilhete. Mais tarde, escuta Vanessa dizer: \"Vi o Bruno mexendo perto da mesa. Deve ser ele.\" Mas ele só estava pegando um copo. Essa observação serve como pista?",
    "assets/festa.jpg")

DEFINIR_CENA(cenaFofoqueira,
    "O jogador ouve Vanessa dizendo com convicção: \"Foi o Felipe! Eu vi ele colando uma figurinha de constelação com o nome da Barbie no caderno dele!\" Mas Felipe estava apenas preparando material para o clube de astronomia. Essa dedução é confiável?",
    "O jogador decide ignorar a fala de Vanessa, conhecida por exagerar e inventar histórias. Nenhuma pista é adicionada.",
    "assets/fofoqueira.jpg")
