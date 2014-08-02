vpath %.c src
vpath %.h inc

CC := g++


carrom	: main.c defines.h structs.h Vector2D.h AI.c draw.c physics.c
	$(CC) src/main.c -lglut -lGLU -lglui -o Carrom -I inc
clean	: 
	rm -f Carrom 

