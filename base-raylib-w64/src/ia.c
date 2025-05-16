#include <stdio.h>
#include <string.h>
#include "ia.h"
#include "pistas.h"
#include "gemini.h"

void consultarIAComContexto(const char* promptCena, char* resposta) {
    const char* contextoPretendentes =
        "Você é uma Inteligência Artificial investigativa dentro de um jogo fofo, divertido e cheio de mistério, onde o jogador está tentando descobrir quem é o admirador secreto da Barbie.\n\nO tom do jogo é leve, jovem e encantador, feito para quem ama romance, investigação e pistas misteriosas com um toque fashion. \nFale com o jogador como se estivesse numa conversa entre amigas, sempre com gentileza e emoção! Você pode usar expressões tipo “hmm…”, “ai, será?”, “isso tá bem suspeito!” e muito charme.\n\nMas não esqueça: sua resposta deve sempre ajudar o jogador a formar sua teoria com base lógica.\n\nSuspeitos:\n- Micucci: tímido, introspectivo, manda bilhetes, evita contato direto, usa capuz e mochila.\n- Bruno: extrovertido, popular, engraçado, bilhetes no grêmio, sempre rodeado de amigos.\n- Felipe: estudioso, ama astrologia e constelações, frequenta a biblioteca, fala de signos, usa óculos.\n- Samuca: atleta de basquete, fala gírias, sempre de roupa de treino, brinca com todas, chama as meninas de “parça”.\n\nA seguir virão as cenas. Para cada uma, gere uma resposta curta, charmosa e investigativa. " "\n\nPrompt:\n";

    static char promptFinal[4096];
    snprintf(promptFinal, sizeof(promptFinal), "%s%s", contextoPretendentes, promptCena);
    consultarIA(promptFinal, resposta);
}

void modificarPistas(Pista** lista, const char* resposta) {
    if (resposta && strlen(resposta) > 0) {
        adicionarPista(lista, resposta, 5); // relevância padrão
    }
}

// ======================= CENAS =======================

void cenaMensagemMisteriosa(Pista** lista, int usarIA) {
    char resposta[1024];
    const char* promptCena;

    if (usarIA) {
        promptCena =
            "O jogador viu o celular da Barbie vibrar com uma mensagem de número desconhecido dizendo 'Vamos sair?'. Barbie não percebeu. "
            "O número está em grupos escolares antigos. Um dos colegas, conhecido por ser muito reservado e tímido, costuma evitar conversas presenciais e prefere mandar mensagens discretas. "
            "Esse perfil lembra Micucci, que ainda participa silenciosamente desses grupos. O que pode ser deduzido sobre o remetente da mensagem?";

    } else {
        promptCena =
            "O jogador ignorou a mensagem misteriosa. Mais tarde, escuta Vanessa dizendo: "
            "\"Esse número é igual ao do Samuca. Vive mandando mensagem chamando as meninas de ‘parça’. Deve ser ele.\" "
            "Samuca é extrovertido, brincalhão e atleta. Com base nessa fofoca, o que pode ser deduzido sobre o remetente?";
    }

    consultarIAComContexto(promptCena, resposta);
    modificarPistas(lista, resposta);
}

void cenaBrownieCantina(Pista** lista, int usarIA) {
    char resposta[1024];
    const char* promptCena;

    if (usarIA) {
       promptCena =
            "O jogador ouviu que alguém deixou um brownie com bilhete para a Barbie. A funcionária lembra que o garoto usava capuz e uma mochila com estampa de time de basquete. "
            "Samuca é jogador de basquete e anda sempre com roupa de treino. Micucci também costuma usar capuz, mas raramente entra no refeitório. "
            "O que pode ser deduzido sobre o possível autor do presente?";

    } else {
        promptCena =
            "O jogador optou por não investigar. Mais tarde, ouve alguém comentar: "
            "\"Bruno vive fazendo essas brincadeiras românticas. Aposto que foi ele.\" "
            "Bruno é popular e brincalhão, mas essa informação é baseada apenas em suposição. O que pode ser deduzido?";
    }

    consultarIAComContexto(promptCena, resposta);
    modificarPistas(lista, resposta);
}

void cenaComputadorLaboratorio(Pista** lista, int usarIA) {
    char resposta[1024];
    const char* promptCena;

    if (usarIA) {
        promptCena =
            "O jogador encontrou um notebook aberto no Instagram da Barbie. O modelo é igual ao que Micucci costuma usar, o que levanta suspeita. "
            "No entanto, ao investigar o IP, descobre-se que esse computador também é utilizado por Felipe, que costuma estudar nesse laboratório. "
            "O que pode ser deduzido com base nisso?";

    } else {
        promptCena =
            "O jogador optou por não investigar o computador deixado aberto no laboratório. Nenhuma informação adicional foi obtida.";

    }

    consultarIAComContexto(promptCena, resposta);
    modificarPistas(lista, resposta);
}

void cenaOlharNaQuadra(Pista** lista, int usarIA) {
    char resposta[1024];
    const char* promptCena;

    if (usarIA) {
        promptCena =
            "Durante o jogo, o jogador viu Bruno acenar para o lado da arquibancada onde a Barbie estava. Bruno é conhecido por ser extrovertido e cumprimentar muitas pessoas. "
            "Também havia um grupo de amigos ao lado da Barbie. Esse gesto pode indicar algo sobre um possível interesse romântico?";

    } else {
        promptCena =
            "O jogador se distraiu durante o jogo e não observou o comportamento dos jogadores. Nenhuma pista foi coletada.";

    }

    consultarIAComContexto(promptCena, resposta);
    modificarPistas(lista, resposta);
}

void cenaMarcadorBiblioteca(Pista** lista, int usarIA) {
    char resposta[1024];
    const char* promptCena;

    if (usarIA) {
        promptCena =
            "O jogador viu um marcador com a frase 'Estou apaixonado pela Barbie' cair de um livro sobre astrologia que Barbie devolveu. "
            "O sistema indica que o último empréstimo foi feito por Felipe, conhecido por gostar de astrologia. No entanto, o jogador lembra que Micucci havia emprestado esse livro dias antes para Felipe, dizendo que era pra um trabalho. "
            "Com base nessa relação, o que pode ser deduzido sobre o autor do marcador?";

    } else {
        promptCena =
            "O jogador ignorou o marcador. Mais tarde, ouve alguém comentar: "
            "\"Felipe é fissurado em signos. Deve ter sido ele.\" "
            "Essa suposição tem alguma base ou é apenas coincidência?";

    }

    consultarIAComContexto(promptCena, resposta);
    modificarPistas(lista, resposta);
}

void cenaBilheteFesta(Pista** lista, int usarIA) {
    char resposta[1024];
    const char* promptCena;

    if (usarIA) {
        promptCena =
            "Durante a festa, o jogador vê um bilhete na mesa da Barbie: 'Nos encontramos às 21h na varanda.' "
            "A caligrafia lembra a de Bruno, que costuma escrever mensagens no grêmio e fazer bilhetes engraçados. "
            "No entanto, a inclinação da letra está diferente, como se alguém estivesse imitando. O que pode ser deduzido a partir disso?";

    } else {
        promptCena =
            "O jogador não investigou o bilhete. Mais tarde, escuta Vanessa dizer: "
            "\"Vi o Bruno mexendo perto da mesa. Deve ter sido ele.\" "
            "Mas ele só estava pegando um copo. Essa observação serve como pista?";
    }

    consultarIAComContexto(promptCena, resposta);
    modificarPistas(lista, resposta);
}

void cenaFofoqueira(Pista** lista, int usarIA) {
    char resposta[1024];
    const char* promptCena;

    if (usarIA) {
        promptCena =
            "O jogador ouve Vanessa dizendo com convicção: "
            "\"Foi o Felipe! Eu vi ele colando uma figurinha de constelação com o nome da Barbie no caderno dele!\" "
            "Mas Felipe estava apenas preparando material para o clube de astronomia. Essa dedução é confiável?";


    } else {
        promptCena =
        "O jogador decide ignorar a fala de Vanessa, conhecida por exagerar e inventar histórias. Nenhuma pista é adicionada.";

    }

    consultarIAComContexto(promptCena, resposta);
    modificarPistas(lista, resposta);
}
// ======================= FIM CENAS =======================