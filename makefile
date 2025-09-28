# Nombre del ejecutable sin extensión
EXEC = Paquete_de_programas-Metodos_numericos

# Nombre del compilador y banderas
GCC = gcc 
CFLAGS = -Wall -Werror -Wextra

# Archivos de compilación y ubicaciónes de estos
SRC_DIR = src 
SRC = $(SRC_DIR)/main.c \
        $(SRC_DIR)/Funciones_basicas.c \
        $(SRC_DIR)/Opcion_01.c
INC_DIR = headers
OBJ = $(SRC:.c=.o)





all: $(EXEC)

$(EXEC):
        $(GCC) $(CFLAGS) -I $(INC_DIR) $(SRC) -o $(EXEC).exe -lm 

build: $(OBJ)
        $(GCC) $(CFLAGS) $(OBJ) -o $(EXEC).exe -lm 

%.o: %.c 
        $(GCC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@ -lm 

clean:
        rm -f $(OBJ)

cleanall: clean
        rm -f $(EXEC).exe
