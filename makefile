# Directorios de origen y destino
SRC_DIR := src
BIN_DIR := bin

SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Obtener todos los archivos .cpp en el directorio de origen
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# Generar los nombres de los archivos .exe en el directorio de destino
EXE_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.exe,$(CPP_FILES))

# Regla para compilar cada archivo .cpp y generar el archivo .exe correspondiente
$(BIN_DIR)/%.exe: $(SRC_DIR)/%.cpp
	g++ $< -o $@ $(SFML) -Iinclude

# Regla por defecto para compilar todos los archivos .cpp
all: $(EXE_FILES)

# Regla para ejecutar cada archivo .exe
run%: $(BIN_DIR)/%.exe
	./$<

# Regla para limpiar los archivos generados
clean:
	rm -f $(EXE_FILES)

.PHONY: all clean
.PHONY: run-%