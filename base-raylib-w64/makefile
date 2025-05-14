# Nome do executável (sem extensão)
TARGET = app

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib_raylib
RELEASE_DIR = bin

# Fontes
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Detecta o sistema operacional
UNAME_S := $(shell uname -s)

# Configurações padrão
CFLAGS = -Wall -std=c99 -I$(INCLUDE_DIR) -Icurl/include
LIBS = -L$(LIB_DIR) -Lcurl/lib -lraylib -lcurl
EXT =

# Ajustes específicos para macOS com Homebrew
ifeq ($(UNAME_S),Darwin)
    CFLAGS += -I/opt/homebrew/include
    LIBS = -lcurl -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -L/opt/homebrew/lib
endif

# Se for Windows (MINGW ou similar)
ifeq ($(OS),Windows_NT)
    LIBS = -L$(LIB_DIR) -Lcurl/lib -lraylib -lcurl -lopengl32 -lgdi32 -lwinmm
    EXT = .exe
endif

# Alvo final com extensão adequada
BIN_TARGET = $(RELEASE_DIR)/$(TARGET)$(EXT)

# Regra para compilar
$(BIN_TARGET): $(SOURCES)
	@mkdir -p $(RELEASE_DIR)
	gcc $(CFLAGS) $(SOURCES) -o $@ $(LIBS)

# Regra para executar
run: $(BIN_TARGET)
	@./$(BIN_TARGET)