# Nombre del ejecutable sin extensión
EXEC = Paquete_de_programas-Metodos_numericos
EXT = exe

# Nombre del compilador y banderas
GCC = gcc
CFLAGS = -Wall -Werror -Wextra

# Archivos de compilación y ubicaciónes de estos
SRC_DIR = src
SRC = $(SRC_DIR)/main.c \
	$(SRC_DIR)/Funciones_basicas.c \
	$(SRC_DIR)/Opcion_01.c \
	$(SRC_DIR)/Opcion_02.c \
	$(SRC_DIR)/Opcion_03.c \
	$(SRC_DIR)/Matrices.c \
	$(SRC_DIR)/Metodos_sistemas_ecuaciones.c
INC_DIR = headers
OBJ = $(SRC:.c=.o)





all: $(EXEC)

$(EXEC):
	$(GCC) $(CFLAGS) -I $(INC_DIR) $(SRC) -o $(EXEC).$(EXT) -lm

build: $(OBJ)
	$(GCC) $(CFLAGS) $(OBJ) -o $(EXEC).$(EXT) -lm

%.o: %.c
	$(GCC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@ -lm

clean:
	rm -f $(OBJ)

cleanall: clean
	rm -f $(EXEC).$(EXT)
