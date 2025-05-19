# 💘 Barbie’s Love Detective
Um jogo investigativo e encantador feito em C com Raylib!  
Assuma o papel de detetive e descubra, através de pistas misteriosas geradas por uma IA, quem é o admirador secreto da Barbie!  
Prepare-se para cenas fofas, mistério fashion e decisões dedutivas.

---

## ✨ Sobre o Jogo

O jogador acompanha cenas envolvendo Barbie e interage com situações que revelam pistas.  
Essas pistas são geradas dinamicamente por uma **IA integrada com a API do Gemini (Google)**, tornando cada investigação **única**.

O jogo é dividido em:
- Introdução animada com música
- Tela de instruções
- Sete cenas investigativas
- Resultado final com as pistas coletadas exibidas visualmente

---

## 🧠 Funcionalidades

- ✅ Cenas com narrativa interativa
- ✅ Integração com API da IA para gerar pistas diferentes a cada rodada
- ✅ Lista encadeada para armazenar pistas
- ✅ Exibição gráfica das pistas usando Raylib
- ✅ Tela de introdução com animação e áudio
- ✅ Reinício possível após uma rodada

---

## 📁 Estrutura do Projeto

```

base-raylib-w64/
├── assets/              # Imagens e músicas do jogo
├── curl/                # Lib curl e includes
├── include/             # Headers do projeto (.h)
├── lib\_raylib/          # Biblioteca Raylib compilada
├── src/                 # Códigos-fonte (.c)
│   ├── main.c
│   ├── interface.c
│   ├── ia.c
│   ├── gemini.c
│   ├── pistas.c
│   ├── personagens.c
│   ├── jogo.c
├── bin/                 # Executável gerado
├── makefile             # Script de compilação

````

---

## 🛠️ Como Compilar

Você precisa ter:
- Raylib instalado e configurado (já incluso na pasta `lib_raylib`)
- Libcurl (já incluso na pasta `curl/`)
- Compilador GCC via MSYS2, MinGW ou W64DevKit

### 💻 Passo a passo no terminal:

Abra o terminal dentro da pasta `base-raylib-w64` e execute:

```bash
make
````

Isso irá compilar o projeto e gerar o executável em `bin/app.exe`.

### ▶️ Para rodar o jogo:

```bash
make run
```

Ou diretamente:

```bash
./bin/app.exe
```

 Comando real:
```bash
gcc -Wall -std=c99 -Iinclude -Icurl/include src/*.c -o bin/app.exe -Llib_raylib -Lcurl/lib -lraylib -lcurl -lopengl32 -lgdi32 -lwinmm
```
---

## 📌 Dependências

* [Raylib](https://www.raylib.com/) — v5.5
* [libcurl](https://curl.se/libcurl/)
* [cJSON](https://github.com/DaveGamble/cJSON)
* API Gemini (Google AI) — Para geração de pistas automáticas

---

## 👩‍💻 Equipe

Projeto desenvolvido por estudantes da **CESAR School** para a disciplina de Algoritmos e Estruturas de Dados.

- Amanda Montarroios  
- Fabiana Coelho  
- Julia Maria Teixeira  
- Maria Julia Dantas  
- Maria Luiza Dantas  


---

## 🧪 Observação

*            As pistas serão **diferentes** a cada partida!

---

