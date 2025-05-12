# 💘 Barbie’s Love Detective

Um jogo de mistério romântico onde o jogador precisa descobrir quem é o crush secreto da Barbie. Com uma narrativa interativa, pistas enigmáticas e a ajuda de uma Inteligência Artificial, cada partida traz uma experiência diferente.

---

## 🎮 Sobre o Jogo

**Barbie’s Love Detective** é um jogo desenvolvido em **C** que integra:

- 📚 **Estruturas de dados** (listas encadeadas)
- ⚙️ **Algoritmo de ordenação** (Insertion Sort)
- 🤖 **Integração com API de Inteligência Artificial** (Gemini)
- 🖼️ **Interface gráfica com Raylib**

A narrativa se adapta conforme as escolhas do jogador, e a IA altera dinamicamente pistas, diálogos e possíveis finais.

---

## 🧠 Estrutura de Dados

### Lista Encadeada de Pistas

Cada pista é um nó em uma lista ligada. A lista é fundamental para a lógica do jogo, pois é constantemente manipulada durante as interações:

- Ao interagir com personagens, novas pistas são adicionadas.
- A IA pode inserir pistas falsas ou remover pistas irrelevantes.
- As pistas são ordenadas por relevância a cada rodada.
- O jogador pode visualizar ou investigar pistas em tempo real.

> A manipulação dessa estrutura influencia diretamente o rumo da investigação, as suspeitas levantadas e as decisões do jogador.

---

## ⚡ Algoritmo de Ordenação

### Insertion Sort

Usado para reorganizar os suspeitos ou pistas com base no grau de suspeita/relevância atribuído pela IA ou pelas ações do jogador.

---

## 🤖 API de Inteligência Artificial

### Gemini (Google AI)

Responsável por:

- Gerar trechos narrativos personalizados
- Modificar comportamentos de personagens
- Adicionar ou alterar pistas com base nas escolhas do jogador
- Criar finais alternativos

---

## 🔧 Funções Principais

- `inserirPista()`
- `removerPista()`
- `ordenarPistas()`
- `interagirPersonagem()`
- `consultarIA()`
- `mostrarMenu()`
- `verificarCondicaoVitoria()`

---

## 🖼️ Interface Gráfica

### Raylib

- Interface com botões e diálogos
- Tela inicial com botão “Começar”
- Exibição de pistas e respostas da IA
- Navegação entre escolhas

---

## 💻 Como Executar

### 🔧 Requisitos

- Compilador C (`gcc`)
- `libcurl` (para comunicação com a API)
- Internet (para chamadas à API Gemini)
- Raylib (para interface gráfica)

### 📦 Passos

```bash
git clone https://github.com/seu-usuario/BarbiesLoveDetective.git
cd BarbiesLoveDetective
gcc main.c -o jogo -lcurl
./jogo
```

### 🎨 Para compilar com Raylib:

```bash
gcc main.c -o jogo -lraylib -lcurl -lm -ldl -lpthread
```

---

## 📽️ Vídeo

🎥 Será disponibilizado na entrega final.

---

## 👩‍💻 Equipe

- Amanda Montarroios  
- Fabiana Coelho  
- Julia Maria Teixeira  
- Maria Julia Dantas  
- Maria Luiza Dantas  

---

## 📚 Referências

- API Gemini – Google AI
- Notas de aula (Estrutura de Dados – 2025)
- Raylib (https://www.raylib.com/)
- libcurl – HTTP requests em C

---

## 🌟 Destaques

- IA personalizada altera história e pistas
- Uso prático de lista encadeada com manipulação dinâmica
- Ordenação com finalidade narrativa (relevância e suspeita)
- Interface opcional com Raylib
- Tema criativo: romance + mistério

---

> Feito com 💗 por um time apaixonado por programação e boas histórias.
