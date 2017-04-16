CC = gcc

CFLAGS = -std=gnu99 -lm -lpng16 -Wall -g -O3 -march=native -flto -Wextra -pedantic -fopenmp -lGL -lglut -lGLU

TARGET = voronoi

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
clean:
	$(RM) $(TARGET)
