# Nome do executável
TARGET = main

# Compilador
CC = g++

# Opções de compilação
CFLAGS =  -Wall

# Arquivos fonte
SRCS = mapRoute.cpp astar.cpp

# Objetos correspondentes aos arquivos fonte
OBJS = $(SRCS:.cpp=.o)

# Regra para compilar todos os arquivos
all: $(TARGET)

# Regra para o arquivo executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) main.cpp -o $(TARGET) $(OBJS)

# Regra genérica para compilar arquivos fonte
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos intermediários e o executável
clean:
	rm -f $(OBJS) $(TARGET)
